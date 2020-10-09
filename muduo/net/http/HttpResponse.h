// Copyright 2010, Shuo Chen.  All rights reserved.
// http://code.google.com/p/muduo/
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Shuo Chen (chenshuo at chenshuo dot com)
//
// This is a public header file, it must only include public header files.

#ifndef MUDUO_NET_HTTP_HTTPRESPONSE_H
#define MUDUO_NET_HTTP_HTTPRESPONSE_H

#include "muduo/base/copyable.h"
#include "muduo/base/Types.h"

#include <map>

namespace muduo
{
namespace net
{

class Buffer;
class HttpResponse : public muduo::copyable
{
 public:
  enum HttpStatusCode
  {
    kUnknown,
    k200Ok = 200,
    k301MovedPermanently = 301,
    k400BadRequest = 400,
    k404NotFound = 404,

    StatusContinue             = 100,// RFC 7231, 6.2.1
    StatusSwitchingProtocols   = 101,// RFC 7231, 6.2.2
    StatusProcessing           = 102,// RFC 2518, 10.1
    StatusEarlyHints           = 103,// RFC 8297
    StatusOK                   = 200,// RFC 7231, 6.3.1
    StatusCreated              = 201,// RFC 7231, 6.3.2
    StatusAccepted             = 202,// RFC 7231, 6.3.3
    StatusNonAuthoritativeInfo = 203,// RFC 7231, 6.3.4
    StatusNoContent            = 204,// RFC 7231, 6.3.5
    StatusResetContent         = 205,// RFC 7231, 6.3.6
    StatusPartialContent       = 206,// RFC 7233, 4.1
    StatusMultiStatus          = 207,// RFC 4918, 11.1
    StatusAlreadyReported      = 208,// RFC 5842, 7.1
    StatusIMUsed               = 226,// RFC 3229, 10.4.1

    StatusMultipleChoices  = 300,// RFC 7231, 6.4.1
    StatusMovedPermanently = 301,// RFC 7231, 6.4.2
    StatusFound            = 302,// RFC 7231, 6.4.3
    StatusSeeOther         = 303,// RFC 7231, 6.4.4
    StatusNotModified      = 304,// RFC 7232, 4.1
    StatusUseProxy         = 305,// RFC 7231, 6.4.5

    StatusTemporaryRedirect = 307,// RFC 7231, 6.4.7
    StatusPermanentRedirect = 308,// RFC 7538, 3

    StatusBadRequest                   = 400,// RFC 7231, 6.5.1
    StatusUnauthorized                 = 401,// RFC 7235, 3.1
    StatusPaymentRequired              = 402,// RFC 7231, 6.5.2
    StatusForbidden                    = 403,// RFC 7231, 6.5.3
    StatusNotFound                     = 404,// RFC 7231, 6.5.4
    StatusMethodNotAllowed             = 405,// RFC 7231, 6.5.5
    StatusNotAcceptable                = 406,// RFC 7231, 6.5.6
    StatusProxyAuthRequired            = 407,// RFC 7235, 3.2
    StatusRequestTimeout               = 408,// RFC 7231, 6.5.7
    StatusConflict                     = 409,// RFC 7231, 6.5.8
    StatusGone                         = 410,// RFC 7231, 6.5.9
    StatusLengthRequired               = 411,// RFC 7231, 6.5.10
    StatusPreconditionFailed           = 412,// RFC 7232, 4.2
    StatusRequestEntityTooLarge        = 413,// RFC 7231, 6.5.11
    StatusRequestURITooLong            = 414,// RFC 7231, 6.5.12
    StatusUnsupportedMediaType         = 415,// RFC 7231, 6.5.13
    StatusRequestedRangeNotSatisfiable = 416,// RFC 7233, 4.4
    StatusExpectationFailed            = 417,// RFC 7231, 6.5.14
    StatusTeapot                       = 418,// RFC 7168, 2.3.3
    StatusMisdirectedRequest           = 421,// RFC 7540, 9.1.2
    StatusUnprocessableEntity          = 422,// RFC 4918, 11.2
    StatusLocked                       = 423,// RFC 4918, 11.3
    StatusFailedDependency             = 424,// RFC 4918, 11.4
    StatusTooEarly                     = 425,// RFC 8470, 5.2.
    StatusUpgradeRequired              = 426,// RFC 7231, 6.5.15
    StatusPreconditionRequired         = 428,// RFC 6585, 3
    StatusTooManyRequests              = 429,// RFC 6585, 4
    StatusRequestHeaderFieldsTooLarge  = 431,// RFC 6585, 5
    StatusUnavailableForLegalReasons   = 451,// RFC 7725, 3

    StatusInternalServerError           = 500,// RFC 7231, 6.6.1
    StatusNotImplemented                = 501,// RFC 7231, 6.6.2
    StatusBadGateway                    = 502,// RFC 7231, 6.6.3
    StatusServiceUnavailable            = 503,// RFC 7231, 6.6.4
    StatusGatewayTimeout                = 504,// RFC 7231, 6.6.5
    StatusHTTPVersionNotSupported       = 505,// RFC 7231, 6.6.6
    StatusVariantAlsoNegotiates         = 506,// RFC 2295, 8.1
    StatusInsufficientStorage           = 507,// RFC 4918, 11.5
    StatusLoopDetected                  = 508,// RFC 5842, 7.2
    StatusNotExtended                   = 510,// RFC 2774, 7
    StatusNetworkAuthenticationRequired = 511,// RFC 6585, 6

  };

  explicit HttpResponse(bool close)
    : statusCode_(kUnknown),
      closeConnection_(close)
  {
  }

  void setStatusCode(HttpStatusCode code)
  { statusCode_ = code; }

  void setStatusMessage(const string& message)
  { statusMessage_ = message; }

  void setCloseConnection(bool on)
  { closeConnection_ = on; }

  bool closeConnection() const
  { return closeConnection_; }

  void setContentType(const string& contentType)
  { addHeader("Content-Type", contentType); }

  // FIXME: replace string with StringPiece
  void addHeader(const string& key, const string& value)
  { headers_[key] = value; }

  void setBody(const string& body)
  { body_ = body; }

  void appendToBuffer(Buffer* output) const;

 private:
  std::map<string, string> headers_;
  HttpStatusCode statusCode_;
  // FIXME: add http version
  string statusMessage_;
  bool closeConnection_;
  string body_;
};

}  // namespace net
}  // namespace muduo

#endif  // MUDUO_NET_HTTP_HTTPRESPONSE_H

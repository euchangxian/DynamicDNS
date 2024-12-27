#include "client.hpp"

#include <cpr/cpr.h>

#include <expected>
#include <ostream>
#include <string_view>

namespace http {

std::ostream& operator<<(std::ostream& os, const Response& response) {
  return os << "Response(" << response.code << "): " << response.body;
}

std::ostream& operator<<(std::ostream& os, const Error& error) {
  return os << "Error(" << error.code << "): " << error.message;
}

std::expected<Response, Error> Client::get(std::string_view url) {
  cpr::Response r = cpr::Get(cpr::Url{url});

  if (r.error) {
    return std::unexpected{Error{
        .message = r.error.message,
        .code = 0,  // CPR error, not HTTP.
    }};
  }

  if (r.status_code >= 400) {
    return std::unexpected{Error{
        .message = r.reason,
        .code = r.status_code,
    }};
  }

  return Response{
      .body = r.text,
      .code = r.status_code,
  };
}

}  // namespace http

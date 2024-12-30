#include "client.hpp"

#include <cpr/cpr.h>

#include <expected>
#include <ostream>
#include <string_view>

namespace http {

std::ostream& operator<<(std::ostream& os, const Response& response) noexcept {
  return os << "response(" << response.code << "): " << response.body;
}

std::ostream& operator<<(std::ostream& os, const Error& error) noexcept {
  return os << "http error(" << error.code << "): " << error.message;
}

std::expected<Response, Error> Client::get(std::string_view url) {
  cpr::Response r = cpr::Get(cpr::Url{url});

  if (r.error) {
    return std::unexpected{Error(r.error.message, 0)};
  }

  if (r.status_code >= 400) {
    return std::unexpected{Error(r.reason, r.status_code)};
  }

  return Response(r.text, r.status_code);
}

}  // namespace http

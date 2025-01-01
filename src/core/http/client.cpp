#include "client.hpp"

#include <cpr/cpr.h>

#include <expected>
#include <ostream>
#include <string_view>

namespace http {

std::ostream& operator<<(std::ostream& os, const Response& response) noexcept {
  return os << "response(" << response.code << "): " << response.body;
}

std::expected<Response, Error> Client::get(std::string_view url) {
  cpr::Response r = cpr::Get(cpr::Url{url});

  if (r.error) {
    return std::unexpected{Error(r.error.message, 0)};
  }

  if (r.status_code >= 400) {
    // TODO: check why r.reason is empty, and whether cpr::Response provides
    // a field that actually contains the HTTP Message.
    return std::unexpected{Error(r.reason, r.status_code)};
  }

  return Response(r.text, r.status_code);
}

}  // namespace http

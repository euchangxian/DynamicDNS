#include "client.hpp"

#include <cpr/cpr.h>

#include <expected>
#include <map>
#include <ostream>
#include <string>
#include <string_view>

namespace http {

std::ostream& operator<<(std::ostream& os, const Response& response) noexcept {
  return os << "response(" << response.code << "): " << response.body;
}

std::expected<Response, Error> Client::get(std::string_view url) const {
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

std::expected<Response, Error> Client::post(
    std::string_view url,
    std::string_view body,
    const std::map<std::string, std::string>& headers) const {
  cpr::Response r = cpr::Post(cpr::Url{url}, cpr::Body{body},
                              cpr::Header{headers.begin(), headers.end()});

  if (r.error) {
    return std::unexpected{Error(r.error.message, 0)};
  }

  if (r.status_code >= 400) {
    return std::unexpected{Error{r.reason, r.status_code}};
  }

  return Response(r.text, r.status_code);
}

}  // namespace http

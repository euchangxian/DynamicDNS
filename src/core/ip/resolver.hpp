#pragma once
#include <expected>
#include <string>
#include <string_view>

#include "src/core/error/error.hpp"
#include "src/core/http/client.hpp"
#include "src/core/json/parser.hpp"

namespace ip {

using Error = error::Error;

constexpr std::string_view IP_KEY{"ip"};

template <typename Protocol>
class Resolver {
 public:
  explicit Resolver(http::IClient& client, json::IParser& parser)
      : httpClient_(client), jsonParser_(parser) {}

  std::expected<Protocol, Error> getCurrentIP() const {
    auto queryResult = queryService(Protocol::SERVICE_URL);

    if (!queryResult) {
      return std::unexpected{Error(queryResult.error().message)};
    }

    auto parseResult = jsonParser_.parse(queryResult.value().body);
    if (!parseResult) {
      return std::unexpected{Error(parseResult.error().message)};
    }

    auto parsed = parseResult.value();
    if (!parsed.contains(IP_KEY)) {
      return std::unexpected{Error("ip key not found")};
    }

    return Protocol(parsed[IP_KEY]);
  }

 private:
  const http::IClient& httpClient_;
  const json::IParser& jsonParser_;

  std::expected<http::Response, http::Error> queryService(
      std::string_view url) const {
    return httpClient_.get(url);
  };
};

}  // namespace ip

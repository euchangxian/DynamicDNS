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
 private:
  http::IClient& httpClient_;
  json::IParser& jsonParser_;

 public:
  explicit Resolver(http::IClient& client, json::IParser& parser)
      : httpClient_(client), jsonParser_(parser) {}

  std::expected<Protocol, Error> getCurrentIP() {
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
  std::expected<http::Response, http::Error> queryService(
      std::string_view url) {
    return httpClient_.get(url);
  };
};

}  // namespace ip

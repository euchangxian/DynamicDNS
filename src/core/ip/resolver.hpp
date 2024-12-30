#pragma once
#include <expected>
#include <ostream>
#include <string>
#include <string_view>

#include "src/core/http/client.hpp"
#include "src/core/json/parser.hpp"

namespace ip {

constexpr std::string_view IP_KEY{"ip"};

struct Error {
  const std::string message{};

  explicit Error(std::string msg) : message(std::move(msg)) {}

  friend std::ostream& operator<<(std::ostream& os,
                                  const Error& error) noexcept;
};

struct V4 {
  static constexpr std::string_view SERVICE_URL{
      "https://api.ipify.org?format=json",
  };

  const std::string address{};

  explicit V4(std::string addr) : address(std::move(addr)) {}

  friend std::ostream& operator<<(std::ostream& os, const V4& ipv4) noexcept;
};

struct V6 {
  // failable if the caller has no public ipv6 address.
  static constexpr std::string_view SERVICE_URL{
      "https://api6.ipify.org?format=json",
  };

  const std::string address{};

  explicit V6(std::string addr) : address(std::move(addr)) {}

  friend std::ostream& operator<<(std::ostream& os, const V6& ipv6) noexcept;
};

template <typename Protocol>
class Resolver {
 private:
  // TODO: Check if Resolver should own the HTTP Client, or share a reference.
  http::IClient& httpClient;
  json::IParser& jsonParser;

 public:
  explicit Resolver(http::IClient& client, json::IParser& parser)
      : httpClient(client), jsonParser(parser) {}

  std::expected<Protocol, Error> getCurrentIP() {
    auto queryResult = queryService(Protocol::SERVICE_URL);

    if (!queryResult) {
      return std::unexpected{Error(queryResult.error().message)};
    }

    auto parseResult = jsonParser.parse(queryResult.value().body);
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
    return httpClient.get(url);
  };
};

}  // namespace ip

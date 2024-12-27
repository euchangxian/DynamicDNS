#pragma once
#include <cpr/cpr.h>

#include <format>
#include <string>
#include <string_view>

namespace ip {

struct V4 {
  static constexpr std::string_view SERVICE_URL{
      "https://api.ipify.org?format=json",
  };

  const std::string address{};

  explicit V4(std::string addr) : address(std::move(addr)) {}
};

struct V6 {
  // failable if the caller has no public ipv6 address.
  static constexpr std::string_view SERVICE_URL{
      "https://api6.ipify.org?format=json",
  };

  const std::string address{};

  explicit V6(std::string addr) : address(std::move(addr)) {}
};

template <typename Protocol>
class Resolver {
 public:
  Protocol getCurrentIP() {
    return Protocol{
        queryService(Protocol::SERVICE_URL),
    };
  }

 private:
  std::string queryService(std::string_view url) {
    cpr::Response r = cpr::Get(cpr::Url{url});

    return std::format("Hello, {}!", url);
  };
};

}  // namespace ip

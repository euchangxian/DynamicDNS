#include <ostream>
#include <string>
#include <string_view>
#include <utility>

namespace ip {

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
}  // namespace ip

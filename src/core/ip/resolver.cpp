#include "resolver.hpp"

#include <ostream>

#include "types.hpp"

namespace ip {

std::ostream& operator<<(std::ostream& os, const V4& ipv4) noexcept {
  return os << ipv4.address;
}

std::ostream& operator<<(std::ostream& os, const V6& ipv6) noexcept {
  return os << ipv6.address;
}

}  // namespace ip

#include "error.hpp"

#include <ostream>

namespace error {

std::ostream& operator<<(std::ostream& os, const Error& error) noexcept {
  os << error.what();
  if (error.code_ != 0) {
    os << ", code: " << error.code_;
  }
  return os;
}

}  // namespace error

#include "error.hpp"

#include <ostream>

namespace error {

std::ostream& operator<<(std::ostream& os, const Error& error) noexcept {
  os << "error ";
  if (error.code_ > 0) {
    os << error.code_ << ' ';
  }
  return os << error.what();
}

}  // namespace error

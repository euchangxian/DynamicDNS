#include "types.hpp"

#include <iomanip>
#include <nlohmann/json.hpp>
#include <ostream>

namespace config {

std::ostream& operator<<(std::ostream& os, const Config& cfg) {
  nlohmann::json j = cfg;
  return os << std::setw(4) << j;
}

}  // namespace config

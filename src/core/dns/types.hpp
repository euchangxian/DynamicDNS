#pragma once
#include <array>
#include <cstddef>
#include <string>
#include <string_view>

namespace ttl {

constexpr int SECOND{1};
constexpr int MINUTE{60 * SECOND};
constexpr int HOUR{60 * MINUTE};
constexpr int DAY{24 * HOUR};

}  // namespace ttl

namespace dns::record {

class Type {
 public:
  // Scope promotion, no need Type::Value::A, just Type::Value.
  // enum Value instead of enum class Value allows for implicit conversion.
  enum Value : std::size_t {
    A,     // IPv4
    AAAA,  // IPv6
    COUNT,
  };

  constexpr Type(Value v) : value_(v) {}

  constexpr std::string_view toString() const noexcept { return Names[value_]; }

  static constexpr Type fromString(std::string_view type) {
    for (std::size_t i = 0; i < Names.size(); ++i) {
      if (type == Names[i]) {
        return Type{static_cast<Value>(i)};
      }
    }

    // WARNING: A little unsure on how to handle unsupported DNS Record types.
    // For now, caller (currently only retrieveRecords deserializes from
    // strings) should check and display only supported types.
    return Type::COUNT;
  }

 private:
  Value value_;

  // use CTAD instead of initializing with Types::Count, for static assertion.
  static constexpr std::array Names{
      std::string_view{"A"},
      std::string_view{"AAAA"},
  };

  static_assert(Type::COUNT == Type::Names.size(),
                "DNS Record Enum names not correctly populated");
};

struct Record {
  std::string name;     // Subdomain name, or FQDN, depending on the API call.
  Type type{Type::A};   // Only support for A/AAAA
  std::string content;  // IP address for A/AAAA records
  int ttl{ttl::DAY};
};

}  // namespace dns::record

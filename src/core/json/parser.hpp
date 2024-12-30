#pragma once
#include <expected>
#include <nlohmann/json.hpp>
#include <ostream>
#include <string_view>
#include <utility>

namespace json {

using Parsed = nlohmann::json;

struct Error {
  const std::string message{};

  explicit Error(std::string msg) : message(std::move(msg)) {}

  friend std::ostream& operator<<(std::ostream& os,
                                  const Error& error) noexcept;
};

class IParser {
 public:
  virtual ~IParser() = default;

  virtual std::expected<Parsed, Error> parse(std::string_view obj) = 0;
};

class Parser : public IParser {
 public:
  std::expected<Parsed, Error> parse(std::string_view obj) override;
};

}  // namespace json

#pragma once
#include <expected>
#include <nlohmann/json.hpp>
#include <string_view>

#include "src/core/error/error.hpp"

namespace json {

using Parsed = nlohmann::json;
using Error = error::Error;

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

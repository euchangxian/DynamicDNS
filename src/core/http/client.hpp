#pragma once
#include <expected>
#include <ostream>
#include <string>
#include <string_view>
#include <utility>

#include "src/core/error/error.hpp"

namespace http {

using Error = error::Error;

struct Response {
  const std::string body{};
  const long code{};

  explicit Response(std::string body, long code)
      : body(std::move(body)), code(code) {}

  friend std::ostream& operator<<(std::ostream& os,
                                  const Response& response) noexcept;
};

class IClient {
 public:
  virtual ~IClient() = default;
  virtual std::expected<Response, Error> get(std::string_view url) = 0;
};

class Client : public IClient {
 public:
  std::expected<Response, Error> get(std::string_view url) override;
};

}  // namespace http

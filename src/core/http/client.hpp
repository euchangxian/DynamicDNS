#pragma once
#include <expected>
#include <map>
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

  virtual std::expected<Response, Error> get(std::string_view url) const = 0;

  virtual std::expected<Response, Error> post(
      std::string_view url,
      std::string_view body = "",
      const std::map<std::string, std::string>& headers = {}) const = 0;
};

class Client : public IClient {
 public:
  std::expected<Response, Error> get(std::string_view url) const override;

  std::expected<Response, Error> post(
      std::string_view url,
      std::string_view body = "",
      const std::map<std::string, std::string>& headers = {}) const override;
};

}  // namespace http

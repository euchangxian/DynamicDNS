#pragma once
#include <ostream>
#include <stdexcept>
#include <string>

namespace error {

class Error : public std::runtime_error {
 private:
  long code_;

 public:
  std::string message;

  Error(std::string msg, long code = 0)
      : std::runtime_error(std::move(msg)), code_(code) {}

  long code() const noexcept { return code_; }

  friend std::ostream& operator<<(std::ostream& os,
                                  const Error& error) noexcept;
};

}  // namespace error

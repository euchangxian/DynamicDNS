#include <iostream>

#include "src/core/http/client.hpp"
#include "src/core/ip/resolver.hpp"
#include "src/core/ip/types.hpp"

int main() {
  http::Client httpClient{};
  json::Parser jsonParser{};
  if (auto ipv4 = ip::Resolver<ip::V4>{httpClient, jsonParser}.getCurrentIP();
      !ipv4) {
    std::cout << ipv4.error() << '\n';
  } else {
    std::cout << ipv4.value().address << '\n';
  }

  if (auto res = httpClient.post("https://httpbin.org/post"); !res) {
    std::cout << res.error() << '\n';
  } else {
    std::cout << res.value().body << '\n';
  }
  return 0;
}

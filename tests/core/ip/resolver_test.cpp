#include "src/core/ip/resolver.hpp"

#include <gtest/gtest.h>

#include "src/core/http/client.hpp"
#include "src/core/ip/types.hpp"
#include "src/core/json/parser.hpp"

TEST(IPResolverIntegrationTest, GetCurrentIP) {
  http::Client httpClient{};
  json::Parser jsonParser{};

  ip::Resolver<ip::V4> resolver(httpClient, jsonParser);

  auto ip = resolver.getCurrentIP();

  ASSERT_TRUE(ip.has_value());
}

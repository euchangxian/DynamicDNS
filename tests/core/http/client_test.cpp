#include "src/core/http/client.hpp"

#include <gtest/gtest.h>

TEST(HTTPClientIntegrationTest, GetSuccessRequest) {
  http::Client client{};
  auto result = client.get("https://httpbin.org/get");

  ASSERT_TRUE(result.has_value());
  EXPECT_EQ(result->code, 200);
  EXPECT_FALSE(result->body.empty());
}

TEST(HTTPClientIntegrationTest, GetNotFound) {
  http::Client client{};
  auto result = client.get("https://httpbin.org/status/404");

  ASSERT_FALSE(result.has_value());
  EXPECT_EQ(result.error().code(), 404);
}

TEST(HTTPClientIntegrationTest, GetInternalServerError) {
  http::Client client{};
  auto result = client.get("https://httpbin.org/status/500");

  ASSERT_FALSE(result.has_value());
  EXPECT_EQ(result.error().code(), 500);
}

TEST(HTTPClientIntegrationTest, GetInvalidURL) {
  http::Client client{};
  auto result = client.get("localhost:xxx");

  ASSERT_FALSE(result.has_value());
  EXPECT_EQ(result.error().code(), 0);
}

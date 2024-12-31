#include "src/core/json/parser.hpp"

#include <gtest/gtest.h>

// No need to test a Library extensively. Just make sure it
// serializes/deserializes as expected.
TEST(JSONParserUnitTest, ParseValidIP) {
  constexpr std::string_view validIP{"{\"ip\" : \"192.168.0.5\"}"};

  json::Parser parser{};
  auto result = parser.parse(validIP);

  ASSERT_TRUE(result.has_value());
  ASSERT_EQ((*result)["ip"], "192.168.0.5");
}

TEST(JSONParserUnitTest, ParseInvalidError) {
  constexpr std::string_view invalidJSON{"{\"ip\" : \"192.168.0.5\""};

  json::Parser parser{};
  auto result = parser.parse(invalidJSON);

  ASSERT_FALSE(result.has_value());
}

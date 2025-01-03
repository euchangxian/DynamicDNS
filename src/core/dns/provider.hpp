#pragma once
#include <cstddef>
#include <expected>
#include <string>

#include "src/core/error/error.hpp"
#include "src/core/http/client.hpp"
#include "src/core/ip/types.hpp"
#include "src/core/json/parser.hpp"
#include "types.hpp"

namespace dns {

using Error = error::Error;

class IProvider {
 public:
  virtual ~IProvider() = default;

  virtual std::expected<bool, Error> createRecords(
      std::string_view domain,
      const std::vector<record::Record>& records) const = 0;

  virtual std::expected<std::vector<record::Record>, Error> readRecords(
      std::string_view domain) const = 0;

  std::expected<bool, Error> updateRecords(std::string_view domain,
                                           const ip::V4& ipv4) const {
    return updateRecords(domain, record::Type::A, ipv4.address);
  }

  std::expected<bool, Error> updateRecord(std::string_view domain,
                                          const ip::V6& ipv6) const {
    return updateRecords(domain, record::Type::AAAA, ipv6.address);
  }

  virtual std::expected<bool, Error> deleteRecords(
      std::string_view domain,
      const std::vector<record::Record>& records) const = 0;

 protected:
  virtual std::expected<bool, Error> updateRecords(
      std::string_view domain,
      record::Type type,
      std::string_view address) const = 0;
};

class PorkBunProvider final : public IProvider {
 public:
  PorkBunProvider(std::string apiKey,
                  std::string secretKey,
                  const http::IClient& httpClient,
                  const json::IParser& jsonParser)
      : apiKey_(std::move(apiKey)),
        secretKey_(std::move(secretKey)),
        httpClient_(httpClient),
        jsonParser_(jsonParser) {}

  std::expected<bool, Error> createRecords(
      std::string_view domain,
      const std::vector<record::Record>& record) const override;

  std::expected<std::vector<record::Record>, Error> readRecords(
      std::string_view name) const override;

  std::expected<bool, Error> deleteRecords(
      std::string_view name,
      const std::vector<record::Record>& records) const override;

 protected:
  std::expected<bool, Error> updateRecords(
      std::string_view name,
      record::Type type,
      std::string_view address) const override;

 private:
  // Args: DOMAIN
  static constexpr std::string_view CREATE_RECORD_ENDPOINT{
      "https://api.porkbun.com/api/json/v3/dns/create/{}",
  };

  // Args: DOMAIN
  static constexpr std::string_view READ_RECORD_ENDPOINT{
      "https://api.porkbun.com/api/json/v3/dns/retrieve/{}",
  };

  // Updates all records for the domain that matches the type and subdomain
  // Args: DOMAIN, TYPE, SUBDOMAIN
  // TODO: SUBDOMAIN is optional. Check if there is a need for a "batch" update
  // by Record Type. May need to implement client-side rate-limits.
  static constexpr std::string_view UPDATE_RECORD_ENDPOINT{
      "https://api.porkbun.com/api/json/v3/dns/update/{}/{}/{}",
  };

  // Deletes all records for teh domain that matches the type and subdomain
  // Args: DOMAIN, TYPE, SUBDOMAIN
  static constexpr std::string_view DELETE_RECORD_ENDPOINT{
      "https://api.porkbun.com/api/json/v3/dns/delete/{}/{}/{}",
  };

  const std::string apiKey_;
  const std::string secretKey_;
  const http::IClient& httpClient_;
  [[maybe_unused]] const json::IParser& jsonParser_;

  // Responsibility lies on Caller to pass the correct arguments.
  static std::string formatEndpoint(std::string_view fmtStr,
                                    std::string_view domain,
                                    std::string_view recordType = "",
                                    std::string_view subdomain = "");
};

}  // namespace dns

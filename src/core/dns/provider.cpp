#include "provider.hpp"

#include <format>
#include <string_view>
#include <vector>

#include "types.hpp"

namespace dns {

std::expected<bool, Error> PorkBunProvider::createRecords(
    std::string_view domain,
    [[maybe_unused]] const std::vector<record::Record>& record) const {
  // TODO:
  if (domain.empty()) {
    return std::unexpected{Error("empty domain name")};
  }

  std::string requestEndpoint = formatEndpoint(CREATE_RECORD_ENDPOINT, domain);
  return false;
}

std::expected<std::vector<record::Record>, Error> PorkBunProvider::readRecords(
    std::string_view domain) const {
  // TODO:
  std::string requestEndpoint = formatEndpoint(READ_RECORD_ENDPOINT, domain);
  auto result = httpClient_.post(requestEndpoint);
  if (!result) {
    return std::unexpected{result.error()};
  }

  return {};
}

std::expected<bool, Error> PorkBunProvider::deleteRecords(
    std::string_view domain,
    [[maybe_unused]] const std::vector<record::Record>& records) const {
  std::string requestEndpoint = formatEndpoint(DELETE_RECORD_ENDPOINT, domain);
  return false;
}

std::expected<bool, Error> PorkBunProvider::updateRecords(
    std::string_view domain,
    record::Type type,
    [[maybe_unused]] std::string_view address) const {
  // TODO:
  std::string requestEndpoint =
      formatEndpoint(UPDATE_RECORD_ENDPOINT, domain, type.toString());
  return false;
}

std::string PorkBunProvider::formatEndpoint(std::string_view fmtStr,
                                            std::string_view domain,
                                            std::string_view recordType,
                                            std::string_view subdomain) {
  return std::vformat(fmtStr,
                      std::make_format_args(domain, recordType, subdomain));
}

}  // namespace dns

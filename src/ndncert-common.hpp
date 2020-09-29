/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/**
 * Copyright (c) 2017-2020, Regents of the University of California.
 *
 * This file is part of ndncert, a certificate management system based on NDN.
 *
 * ndncert is free software: you can redistribute it and/or modify it under the terms
 * of the GNU General Public License as published by the Free Software Foundation, either
 * version 3 of the License, or (at your option) any later version.
 *
 * ndncert is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 *
 * You should have received copies of the GNU General Public License along with
 * ndncert, e.g., in COPYING.md file.  If not, see <http://www.gnu.org/licenses/>.
 *
 * See AUTHORS.md for complete list of ndncert authors and contributors.
 */

#ifndef NDNCERT_NDNCERT_COMMON_HPP
#define NDNCERT_NDNCERT_COMMON_HPP

#include "ndncert-config.hpp"

#ifdef HAVE_TESTS
#define VIRTUAL_WITH_TESTS virtual
#define PUBLIC_WITH_TESTS_ELSE_PROTECTED public
#define PUBLIC_WITH_TESTS_ELSE_PRIVATE public
#define PROTECTED_WITH_TESTS_ELSE_PRIVATE protected
#else
#define VIRTUAL_WITH_TESTS
#define PUBLIC_WITH_TESTS_ELSE_PROTECTED protected
#define PUBLIC_WITH_TESTS_ELSE_PRIVATE private
#define PROTECTED_WITH_TESTS_ELSE_PRIVATE private
#endif

#include <cstddef>
#include <cstdint>
#include <ndn-cxx/data.hpp>
#include <ndn-cxx/encoding/block.hpp>
#include <ndn-cxx/face.hpp>
#include <ndn-cxx/interest.hpp>
#include <ndn-cxx/link.hpp>
#include <ndn-cxx/lp/nack.hpp>
#include <ndn-cxx/name.hpp>
#include <ndn-cxx/security/key-chain.hpp>
#include <ndn-cxx/security/v2/certificate.hpp>
#include <ndn-cxx/util/logger.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/assert.hpp>
#include <boost/noncopyable.hpp>
#include <boost/throw_exception.hpp>

namespace ndn {
namespace ndncert {

using boost::noncopyable;
using ndn::Block;
using ndn::Data;
using ndn::Interest;
using ndn::make_unique;
using ndn::Name;
using ndn::PartialName;
using ndn::time::system_clock;
using ndn::time::toUnixTimestamp;
using std::bind;
using std::enable_shared_from_this;
using std::function;
using std::make_shared;
using std::shared_ptr;
using std::size_t;
using std::unique_ptr;
using std::weak_ptr;

#define _LOG_INIT(name) NDN_LOG_INIT(ndncert.name)
#define _LOG_DEBUG(x) NDN_LOG_DEBUG(__FILE__ << ":" << __LINE__ << ":" << " " << x)
#define _LOG_TRACE(x) NDN_LOG_TRACE(__FILE__ << ":" << __LINE__ << ":" << " " << x)
#define _LOG_ERROR(x) NDN_LOG_ERROR(x)

enum : uint32_t {
  tlv_ca_prefix = 129,
  tlv_ca_info = 131,
  tlv_parameter_key = 133,
  tlv_parameter_value = 135,
  tlv_ca_certificate = 137,
  tlv_max_validity_period = 139,
  tlv_max_suffix_length = 177,
  tlv_probe_response = 141,
  tlv_allow_longer_name = 143,
  tlv_ecdh_pub = 145,
  tlv_cert_request = 147,
  tlv_salt = 149,
  tlv_request_id = 151,
  tlv_challenge = 153,
  tlv_status = 155,
  tlv_initialization_vector = 157,
  tlv_encrypted_payload = 159,
  tlv_selected_challenge = 161,
  tlv_challenge_status = 163,
  tlv_remaining_tries = 165,
  tlv_remaining_time = 167,
  tlv_issued_cert_name = 169,
  tlv_error_code = 171,
  tlv_error_info = 173,
  tlv_authentication_tag = 175,
  tlv_cert_to_revoke = 179
};

// Parse CA Configuration file
const std::string CONFIG_CA_PREFIX = "ca-prefix";
const std::string CONFIG_CA_INFO = "ca-info";
const std::string CONFIG_MAX_VALIDITY_PERIOD = "max-validity-period";
const std::string CONFIG_PROBE_PARAMETERS = "probe-parameters";
const std::string CONFIG_PROBE_PARAMETER = "probe-parameter-key";
const std::string CONFIG_SUPPORTED_CHALLENGES = "supported-challenges";
const std::string CONFIG_CHALLENGE = "challenge";
const std::string CONFIG_MAX_SUFFIX_LENGTH = "max-suffix-length";

// NDNCERT Status Enum
enum class Status : uint16_t {
  BEFORE_CHALLENGE = 0,
  CHALLENGE = 1,
  PENDING = 2,
  SUCCESS = 3,
  FAILURE = 4,
  NOT_STARTED = 5,
  ENDED = 6
};

std::string statusToString(Status status);

enum class ErrorCode : uint16_t {
  NO_ERROR = 0,
  BAD_INTEREST_FORMAT = 1,
  BAD_PARAMETER_FORMAT = 2,
  BAD_SIGNATURE = 3,
  INVALID_PARAMETER = 4,
  NAME_NOT_ALLOWED = 5,
  BAD_VALIDITY_PERIOD = 6,
  OUT_OF_TRIES = 7,
  OUT_OF_TIME = 8,
  NO_AVAILABLE_NAMES = 9
};

enum class RequestType : uint16_t {
  NOTINITIALIZED = 0,
  NEW = 1,
  RENEW = 2,
  REVOKE = 3
};

std::string requestTypeToString(RequestType type);

}  // namespace ndncert
}  // namespace ndn

#endif  // NDNCERT_NDNCERT_COMMON_HPP

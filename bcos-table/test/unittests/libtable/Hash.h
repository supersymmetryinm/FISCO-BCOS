/**
 *  Copyright (C) 2021 FISCO BCOS.
 *  SPDX-License-Identifier: Apache-2.0
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 * @brief the Header256Hash return first 32 byte as hash result
 * @file Header256Hash.h
 */

#pragma once
#include "bcos-framework/storage/Entry.h"
#include "bcos-framework/storage/Table.h"
#include <bcos-crypto/hasher/OpenSSLHasher.h>
#include <bcos-crypto/interfaces/crypto/Hash.h>
#include <functional>

namespace std
{
inline ostream& operator<<(ostream& os, const std::optional<bcos::storage::Entry>& entry)
{
    os << entry.has_value();
    return os;
}

inline ostream& operator<<(ostream& os, const std::optional<bcos::storage::Table>& table)
{
    os << table.has_value();
    return os;
}

inline ostream& operator<<(ostream& os, const std::unique_ptr<bcos::Error>& error)
{
    os << error->what();
    return os;
}

inline ostream& operator<<(ostream& os, const std::tuple<std::string, bcos::crypto::HashType>& pair)
{
    os << std::get<0>(pair) << " " << std::get<1>(pair).hex();
    return os;
}
}  // namespace std

namespace bcos
{
namespace crypto
{
class Header256Hash : public Hash
{
public:
    typedef std::shared_ptr<Header256Hash> Ptr;
    Header256Hash() = default;
    virtual ~Header256Hash(){};
    HashType hash(bytesConstRef _data) const override
    {
        std::hash<std::string_view> hash;
        auto h = hash(std::string_view((const char*)_data.data(), _data.size()));
        uint8_t hash_result[32] = {0};
        memcpy(hash_result, &h, sizeof(h));
        return HashType(hash_result, 32);
    }
    bcos::crypto::hasher::AnyHasher hasher() const override
    {
        return bcos::crypto::hasher::AnyHasher{bcos::crypto::hasher::openssl::OpenSSL_SM3_Hasher{}};
    };
};

}  // namespace crypto

}  // namespace bcos

/**
*** Copyright (c) 2016-present,
*** Jaguar0625, gimre, BloodyRookie, Tech Bureau, Corp. All rights reserved.
***
*** This file is part of Catapult.
***
*** Catapult is free software: you can redistribute it and/or modify
*** it under the terms of the GNU Lesser General Public License as published by
*** the Free Software Foundation, either version 3 of the License, or
*** (at your option) any later version.
***
*** Catapult is distributed in the hope that it will be useful,
*** but WITHOUT ANY WARRANTY; without even the implied warranty of
*** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
*** GNU Lesser General Public License for more details.
***
*** You should have received a copy of the GNU Lesser General Public License
*** along with Catapult. If not, see <http://www.gnu.org/licenses/>.
**/

#pragma once
#include "src/state/SecretLockInfo.h"
#include "plugins/txes/lock_shared/src/cache/LockInfoCacheTypes.h"
#include "catapult/cache/ReadOnlyArtifactCache.h"

namespace catapult {
	namespace cache {
		class BasicSecretLockInfoCacheDelta;
		class BasicSecretLockInfoCacheView;
		struct SecretLockInfoBaseSetDeltaPointers;
		struct SecretLockInfoBaseSets;
		class SecretLockInfoCache;
		class SecretLockInfoCacheDelta;
		struct SecretLockInfoCacheTypes;
		class SecretLockInfoCacheView;
		class SecretLockInfoPatriciaTree;
		struct SecretLockInfoPrimarySerializer;
	}
}

namespace catapult { namespace cache {

	/// Describes a secret lock info cache.
	struct SecretLockInfoCacheDescriptor {
	public:
		static constexpr auto Name = "SecretLockInfoCache";

	public:
		// key value types
		using KeyType = Hash512;
		using ValueType = state::SecretLockInfo;

		// cache types
		using CacheType = SecretLockInfoCache;
		using CacheDeltaType = SecretLockInfoCacheDelta;
		using CacheViewType = SecretLockInfoCacheView;

		using Serializer = SecretLockInfoPrimarySerializer;
		using PatriciaTree = SecretLockInfoPatriciaTree;

	public:
		/// Gets the key corresponding to \a lockInfo.
		static const auto& GetKeyFromValue(const ValueType& lockInfo) {
			return lockInfo.Secret;
		}
	};

	/// Secret lock info cache types.
	struct SecretLockInfoCacheTypes : public LockInfoCacheTypes<SecretLockInfoCacheDescriptor> {
		using CacheReadOnlyType = ReadOnlyArtifactCache<
			BasicSecretLockInfoCacheView,
			BasicSecretLockInfoCacheDelta,
			Hash512,
			state::SecretLockInfo>;

		using BaseSetDeltaPointers = SecretLockInfoBaseSetDeltaPointers;
		using BaseSets = SecretLockInfoBaseSets;
	};
}}

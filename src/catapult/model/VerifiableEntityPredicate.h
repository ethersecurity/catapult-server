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
#include "VerifiableEntity.h"
#include "catapult/functions.h"
#include "catapult/preprocessor.h"

namespace catapult { namespace model {

	/// Prototype for a verifiable entity predicate.
	using VerifiableEntityPredicate = predicate<const VerifiableEntity&>;

	/// Creates a predicate that always returns \c true.
	CATAPULT_INLINE
	VerifiableEntityPredicate NeverFilter() {
		return [](const auto&) { return true; };
	}

	/// Creates a predicate that returns \c true when an entity has a matching entity \a type.
	CATAPULT_INLINE
	VerifiableEntityPredicate HasTypeFilter(EntityType type) {
		return [type](const auto& entity) { return entity.Type == type; };
	}

	/// Creates a predicate that returns \c true when an entity has a matching basic entity \a type.
	CATAPULT_INLINE
	VerifiableEntityPredicate HasBasicTypeFilter(BasicEntityType type) {
		return [type](const auto& entity) { return ToBasicEntityType(entity.Type) == type; };
	}
}}

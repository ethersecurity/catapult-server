#include "JointValidator.h"
#include "catapult/cache/ReadOnlyCatapultCache.h"
#include "catapult/plugins/PluginManager.h"
#include "catapult/validators/ValidatorContext.h"

using namespace catapult::validators;

namespace catapult { namespace chain {

	namespace {
		std::string CreateJointValidatorName(const std::string& statelessName, const std::string statefulName) {
			std::ostringstream out;
			out << "JointValidator (" << statelessName << ", " << statefulName << ")";
			return out.str();
		}

		class JointValidator : public stateless::NotificationValidator {
		public:
			JointValidator(
					const cache::CatapultCache& cache,
					const TimeSupplier& timeSupplier,
					const plugins::PluginManager& pluginManager,
					const ValidationResultPredicate& isSuppressedFailure)
					: m_cache(cache)
					, m_timeSupplier(timeSupplier)
					, m_network(pluginManager.config().Network)
					, m_pStatelessValidator(pluginManager.createStatelessValidator(isSuppressedFailure))
					, m_pStatefulValidator(pluginManager.createStatefulValidator(isSuppressedFailure))
					, m_name(CreateJointValidatorName(m_pStatelessValidator->name(), m_pStatefulValidator->name()))
			{}

		public:
			const std::string& name() const override {
				return m_name;
			}

			ValidationResult validate(const model::Notification& notification) const override {
				auto result = validateStateless(notification);
				if (IsValidationResultFailure(result))
					return result;

				auto statefulResult = validateStateful(notification);
				AggregateValidationResult(result, statefulResult);
				return result;
			}

		private:
			ValidationResult validateStateless(const model::Notification& notification) const {
				return m_pStatelessValidator->validate(notification);
			}

			ValidationResult validateStateful(const model::Notification& notification) const {
				auto cacheView = m_cache.createView();
				auto readOnlyCache = cacheView.toReadOnly();
				auto validatorContext = ValidatorContext(cacheView.height(), m_timeSupplier(), m_network, readOnlyCache);
				return m_pStatefulValidator->validate(notification, validatorContext);
			}

		private:
			const cache::CatapultCache& m_cache;
			TimeSupplier m_timeSupplier;
			model::NetworkInfo m_network;
			std::unique_ptr<const stateless::NotificationValidator> m_pStatelessValidator;
			std::unique_ptr<const stateful::NotificationValidator> m_pStatefulValidator;
			std::string m_name;
		};
	}

	std::unique_ptr<const stateless::NotificationValidator> CreateJointValidator(
			const cache::CatapultCache& cache,
			const TimeSupplier& timeSupplier,
			const plugins::PluginManager& pluginManager,
			const ValidationResultPredicate& isSuppressedFailure) {
		return std::make_unique<JointValidator>(cache, timeSupplier, pluginManager, isSuppressedFailure);
	}
}}
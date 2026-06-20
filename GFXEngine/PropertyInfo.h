#pragma once
#include "DataTypes.h"
#include <string>
#include <variant>
#include <vector>
#include <functional>

namespace GFXEngine {

	namespace Core {

		enum class PropertyHint {
			None,
			Enum,
			Multiline,
			ReadOnly,
			File,
			Asset,
			Color,	
			Range
		};

		struct EnumMetaData {
			std::vector<std::string> options;
		};

		struct RangeMetaData {
			float min;
			float max;
			float step;
		};

		struct RangeIntMetaData {
			int min;
			int max;
			int step;
		};

		using PropertyMetaData = std::variant<std::monostate, EnumMetaData, RangeMetaData, RangeIntMetaData>;

		using PropertyDataPointer = std::variant<
			std::string*, 
			int*, 
			bool*, 
			float*, 
			glm::vec2*, 
			glm::vec3*, 
			glm::vec4*, 
			glm::quat*, 
			GFXEngine::EngineTypes::EntityReference*,
			GFXEngine::EngineTypes::AssetReference*
		>;

		struct PropertyInfo {
			std::string name;
			PropertyDataPointer data;
			PropertyHint hint = PropertyHint::None;
			PropertyMetaData metaData;
			std::function<void()> onChanged;
		};
	}
}
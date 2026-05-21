#pragma once
#include "DataTypes.h"
#include <string>
#include <variant>
#include <vector>
#include <functional>

namespace GFXEngine {

	namespace Core {

		/// <summary>
		/// PropertyHint enum represents additional hints for how a property should be displayed or edited in an editor.
		/// </summary>
		enum class PropertyHint {
			None,
			Enum,
			Multiline,
			ReadOnly,
			File,
			Asset,
			Range
		};

		/// <summary>
		/// EnumMetaData struct represents additional metadata for properties of type Enum, such as the list of options that should be displayed in an editor.
		/// </summary>
		struct EnumMetaData {
			std::vector<std::string> options;
		};

		/// <summary>
		/// MetaData struct for an range between a minimum and maximum value, with an optional step value.
		/// </summary>
		struct RangeMetaData {
			float min;
			float max;
			float step;
		};

		/// <summary>
		/// MetaData struct for an integer range between a minimum and maximum value, with an optional step value.
		/// </summary>
		struct RangeIntMetaData {
			int min;
			int max;
			int step;
		};

		/// <summary>
		/// PropertyMetaData is a variant type that can hold additional metadata for a property.
		/// </summary>
		using PropertyMetaData = std::variant<std::monostate, EnumMetaData, RangeMetaData, RangeIntMetaData>;

		/// <summary>
		/// PropertyDataPointer is a variant type that can hold a pointer to the actual data of a property.
		/// </summary>
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

		/// <summary>
		/// PropertyInfo struct represents a property of a behavior.
		/// </summary>
		struct PropertyInfo {
			std::string name;
			PropertyDataPointer data;
			PropertyHint hint = PropertyHint::None;
			PropertyMetaData metaData;
			std::function<void()> onChanged;
		};
	}
}
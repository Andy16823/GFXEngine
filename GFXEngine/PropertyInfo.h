#pragma once
#include <string>
#include <variant>
#include <vector>
#include <functional>

namespace GFXEngine {
	namespace Core {
		/// <summary>
		/// PropertyType enum represents the type of a property that can be used in a behavior.
		/// </summary>
		enum class PropertyType {
			String,
			Int,
			Bool,
			Float,
			Vector2,
			Vector3,
			Vector4,
			Color,
			Entity
		};

		/// <summary>
		/// PropertyHint enum represents additional hints for how a property should be displayed or edited in an editor.
		/// </summary>
		enum class PropertyHint {
			None,
			Enum,
			Multiline,
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
		/// PropertyInfo struct represents a property of a behavior.
		/// </summary>
		struct PropertyInfo {
			std::string name;
			PropertyType type;
			PropertyHint hint = PropertyHint::None;
			void* data;
			PropertyMetaData metaData;
			std::function<void()> onChanged;
		};
	}
}
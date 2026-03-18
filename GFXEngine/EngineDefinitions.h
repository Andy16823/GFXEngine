#pragma once

namespace GFXEngine {
	namespace Defintions {

		enum PipelineType {
			PRESENT_PIPELINE = 'P',
			GEOMETRY_PIPELINE = 'G',
			GEOMETRY_PIPELINE_UNLIT = 'GU',
			INSTANCED_GEOMETRY_PIPELINE = 'I',
			INSTANCED_GEOMETRY_PIPELINE_UNLIT = 'IU',	
			ENVIRONMENT_PIPELINE = 'E',
			DEBUG_PIPELINE = 'D'
		};

	}
}
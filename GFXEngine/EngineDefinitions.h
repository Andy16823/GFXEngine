#pragma once

namespace GFXEngine {
	namespace Defintions {

		enum PipelineType : uint32_t {
			PRESENT_PIPELINE					= 'PRES',
			GEOMETRY_PIPELINE					= 'GEOM',
			GEOMETRY_PIPELINE_UNLIT				= 'GULI',
			INSTANCED_GEOMETRY_PIPELINE			= 'INST',
			INSTANCED_GEOMETRY_PIPELINE_UNLIT	= 'IULI',	
			ENVIRONMENT_PIPELINE				= 'ENVI',
			DEBUG_PIPELINE						= 'DEBG'
		};

	}
}
#pragma once

namespace GFXEngine {
	namespace Defintions {

		enum PipelineType : unsigned int {
			PRESENT_PIPELINE					= 'PRES',
			GEOMETRY_PIPELINE					= 'GEOM',
			GEOMETRY_PIPELINE_UNLIT				= 'GULI',
			INSTANCED_GEOMETRY_PIPELINE			= 'INST',
			INSTANCED_GEOMETRY_PIPELINE_UNLIT	= 'IULI',	
			ENVIRONMENT_PIPELINE				= 'ENVI',
			DEBUG_PIPELINE						= 'DEBG',
			SPRITE_PIPELINE						= 'SPRT'
		};

		enum RenderResource : unsigned int {
			CAMERA_RESOURCE						= 'CAMR',
			MATERIAL_RESOURCE					= 'MATR',
			INSTANCE_DATA_RESOURCE				= 'INSR',
			DIRECTIONAL_LIGHT_RESOURCE			= 'DLIR',
			POINT_LIGHTS_RESOURCE				= 'PLIR',
			FOG_RESOURCE						= 'FOGR',
			ENVIRONMENT_MAP_RESOURCE			= 'ENVR'
		};
	}
}
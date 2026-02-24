#pragma once
#include <vector>
#include <glm/glm.hpp>

namespace GFXEngine {
	namespace EngineTypes {

		/// <summary>
		/// Simple vertex structure for 3D rendering, containing position, color, texture coordinates, and normal vector.
		/// </summary>
		struct Vertex3D
		{
		public:
			glm::vec3 pos;
			glm::vec3 color;
			glm::vec2 texCoord;
			glm::vec3 normal;
		};

		/// <summary>
		/// Simple vertex structure for 2D rendering, containing position, color, and texture coordinates.
		/// </summary>
		struct Vertex2D
		{
			glm::vec2 pos;
			glm::vec3 color;
			glm::vec2 texCoord;
		};

		/// <summary>
		/// Vertex structure for skinned meshes, containing position, color, texture coordinates, normal vector, bone IDs, and weights for skinning.
		/// </summary>
		struct SkinningVertex
		{
			glm::vec3 pos;
			glm::vec3 color;
			glm::vec2 texCoord;
			glm::vec3 normal;
			glm::ivec4 boneIDs;
			glm::vec4 weights;
		};

		/// <summary>
		/// Uniform buffer object for camera data, containing view and projection matrices, as well as the camera position for lighting calculations.
		/// </summary>
		struct CameraBufferObject
		{
			glm::mat4 view;
			glm::mat4 proj;
			glm::vec4 cameraPos;
		};
#
		/// <summary>
		/// Instance data structure for instanced rendering, containing a model matrix for transforming each instance and an extras vector for any additional per-instance data.
		/// </summary>
		struct InstanceData
		{
			glm::mat4 model;
			glm::vec4 extras;
		};	
	}
}
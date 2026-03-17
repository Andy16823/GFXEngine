#version 450

// Vertex Inputs
layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 vcolor;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in vec3 normal;
layout(location = 4) in vec4 tangent;

// Camera unform buffer
layout(set = 0, binding = 0) uniform UboViewProjection {
    mat4 view;
    mat4 projection;
    vec4 cameraPos;
} uboViewProjection;

// Push constants for model matrix
layout(push_constant) uniform PushConstants {
    mat4 model;
} pushConstants;

// Outputs to fragment shader
layout(location = 0) out vec3 color;
layout(location = 1) out vec2 fragTexCoord;
layout(location = 2) out vec3 fragNormal;
layout(location = 4) out vec3 fragWorldPos;

// Main function
void main() {
    gl_Position = uboViewProjection.projection * uboViewProjection.view * pushConstants.model * vec4(pos, 1.0);
    color = vcolor;
    fragTexCoord = texCoord;
    fragNormal = normalize(mat3(transpose(inverse(pushConstants.model))) * normal);
    fragWorldPos = (pushConstants.model * vec4(pos, 1.0)).xyz;
}
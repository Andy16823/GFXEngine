#version 450
layout(location = 0) in vec3 vPos;
layout(location = 1) in vec3 vColor;
layout(location = 2) in vec2 vTexCoord;

layout(set = 0, binding = 0) uniform UboViewProjection {
    mat4 view;
    mat4 projection;
    vec4 cameraPos;
} uboViewProjection;

// Push constants for model matrix
layout(push_constant) uniform PushConstants {
    mat4 model;
} pushConstants;

layout(location = 0) out vec4 color;
layout(location = 1) out vec2 fragTexCoord;

void main() {
    gl_Position = uboViewProjection.projection * uboViewProjection.view * pushConstants.model * vec4(vPos, 1.0);
    color = vec4(vColor, 1.0);
    fragTexCoord = vTexCoord;
}
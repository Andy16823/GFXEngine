#version 450

layout(location = 0) in vec3 pos;

layout(set = 0, binding = 0) uniform UboViewProjection {
    mat4 view;
    mat4 projection;
    vec4 cameraPos;
} uboViewProjection;

layout(push_constant) uniform PushConstants {
    mat4 model;
} pushConstants;


void main() {
    gl_Position = uboViewProjection.projection * uboViewProjection.view * pushConstants.model * vec4(pos, 1.0);
}
#version 450

layout(location = 0) in vec3 pos;
layout(location = 0) out vec3 fragDir;

layout(set = 0, binding = 0) uniform UboViewProjection {
    mat4 view;
    mat4 projection;
    vec4 cameraPos;
} uboViewProjection;

void main() {
    mat4 viewNoTranslation = mat4(mat3(uboViewProjection.view));
    gl_Position = uboViewProjection.projection * viewNoTranslation * vec4(pos, 1.0);
    gl_Position.z = gl_Position.w; // set depth to far plane
    fragDir = pos;
}
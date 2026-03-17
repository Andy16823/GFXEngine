#version 450

// Vertex Inputs
layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 vcolor;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in vec3 normal;
layout(location = 4) in vec4 tangent;

// Instance data structure
struct InstanceData {
    mat4 model;
    vec4 extras; // x = visibe, yzw = unused
};

// Camera unform buffer
layout(set = 0, binding = 0) uniform UboViewProjection {
    mat4 view;
    mat4 projection;
    vec4 cameraPos;
} uboViewProjection;

// Instancing data buffer
layout(set = 3, binding = 0) readonly buffer InstanceBuffer {
    InstanceData instances[];
} instanceBuffer;

// Outputs to fragment shader
layout(location = 0) out vec3 color;
layout(location = 1) out vec2 fragTexCoord;
layout(location = 2) out vec3 fragNormal;
layout(location = 3) flat out vec4 fragExtras;
layout(location = 4) out vec3 fragWorldPos;

// Main function
void main() {
    InstanceData instance = instanceBuffer.instances[gl_InstanceIndex];
    gl_Position = uboViewProjection.projection * uboViewProjection.view * instance.model * vec4(pos, 1.0);
    color = vcolor;
    fragTexCoord = texCoord;
    fragNormal = normalize(mat3(transpose(inverse(instance.model))) * normal);
    fragExtras = instance.extras;
    fragWorldPos = (instance.model * vec4(pos, 1.0)).xyz;
}
#version 450

layout(location = 0) in vec3 color;
layout(location = 1) in vec3 fragNormal;
layout(location = 2) in vec3 fragWorldPos;

layout(set = 1, binding = 0) uniform MaterialSolidColor {
    vec4 color;
} material;

layout(location = 0) out vec4 fragColor;

void main() { 
    fragColor = material.color;
}
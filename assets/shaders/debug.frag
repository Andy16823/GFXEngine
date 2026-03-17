#version 450

layout(location = 0) out vec4 fragColor;

vec3 color = vec3(1.0, 0.0, 0.0); // Red color for debugging

void main() { 
    fragColor = vec4(color, 1.0);
}
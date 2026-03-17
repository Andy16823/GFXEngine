#version 450

layout(location = 0) out vec4 fragColor;

layout(location = 1) in vec2 fragTexCoord;

layout(set = 0, binding = 0) uniform sampler2D textureSampler;

void main() { 
    vec4 texColor = texture(textureSampler, fragTexCoord);
    fragColor = texColor;
}
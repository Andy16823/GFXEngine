#version 450

layout(location = 0) in vec4 color;
layout(location = 1) in vec2 fragTexCoord;

layout(set = 1, binding = 0) uniform sampler2D spriteTexture;

layout(location = 0) out vec4 fragColor;

void main() {
	vec4 texColor = texture(spriteTexture, fragTexCoord);
	fragColor = texColor * color;
}
#version 450

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 texCoord;

layout(location = 0) out vec3 color;
layout(location = 1) out vec2 fragTexCoord;

void main() {
    gl_Position = vec4(pos, 1.0);
    fragTexCoord = texCoord;
}
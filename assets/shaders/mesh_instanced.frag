#version 450

// Outputs
layout(location = 0) out vec4 fragColor;

// Inputs from vertex shader
layout(location = 0) in vec3 color;
layout(location = 1) in vec2 fragTexCoord;
layout(location = 2) flat in vec4 instanceExtras;

// Texture sampler
layout(set = 1, binding = 0) uniform sampler2D textureSampler;

void main() { 

    // Discard instance if not visible
    if (instanceExtras.x < 0.5) {
        discard;
    }

    // Sample texture and combine with vertex color
    vec4 texColor = texture(textureSampler, fragTexCoord);
    fragColor = vec4(color, 1.0) * texColor;
}
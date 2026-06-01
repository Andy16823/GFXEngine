#version 450
layout(location = 0) in vec3 fragDir;
layout(location = 0) out vec4 fragColor;

layout(set = 1, binding = 0) uniform samplerCube skybox;

layout(set = 2, binding = 0) uniform Fog {
    vec4 color;
    vec4 parameters;
} fog;

void main() {
    vec3 skyColor = texture(skybox, fragDir).rgb;
    float fogDensity = fog.parameters.z;
    skyColor = mix(fog.color.rgb, skyColor, fogDensity);
    fragColor = vec4(skyColor, 1.0);
}
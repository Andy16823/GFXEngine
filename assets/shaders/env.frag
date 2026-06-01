#version 450
layout(location = 0) in vec3 fragDir;
layout(location = 0) out vec4 fragColor;

layout(set = 1, binding = 0) uniform samplerCube skybox;

layout(set = 2, binding = 0) uniform Fog {
    vec4 color;
    vec4 parameters;
} fog;

void main() {
    vec3 dir = normalize(fragDir);
    vec3 skyColor = texture(skybox, dir).rgb;

    // 0 = oben
    // 1 = unten
    float horizonFactor = 1.0 - abs(dir.y);
    horizonFactor = pow(horizonFactor, 1.5);
    float fakeDistance = mix(fog.parameters.x, fog.parameters.y, horizonFactor);
    float fogRange = fog.parameters.y - fog.parameters.x;
    float fogFactor = clamp((fog.parameters.y - fakeDistance) / fogRange, 0.0, 1.0);
    skyColor = mix(fog.color.rgb, skyColor, fogFactor);
    // Maybe multiply fogFactor with fog.parameters.z for density control. It would allow to disable fog by setting density to 0, or make it thicker by increasing density.
    // also add an env uniform buffer with an vec4 to control the fake distance range, so that the user can adjust it to fit the scene better.
    fragColor = vec4(skyColor, 1.0);
}
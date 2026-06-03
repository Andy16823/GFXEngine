#version 450
layout(location = 0) in vec3 fragDir;
layout(location = 0) out vec4 fragColor;

layout(set = 1, binding = 0) uniform samplerCube skybox;

layout(set = 2, binding = 0) uniform EnviromentData {
    vec4 parameters; // x = horizonFactor, y = horizonFactorExponent, zw = padding
} envData;

layout(set = 3, binding = 0) uniform Fog {
    vec4 color;
    vec4 parameters;
} fog;

float calculateFogFactor(vec3 dir) {
    // 0 = oben // 1 = unten
    float horizonFactor = envData.parameters.x - abs(dir.y);
    horizonFactor = pow(horizonFactor, envData.parameters.y);
    float fakeDistance = mix(fog.parameters.x, fog.parameters.y, horizonFactor);
    float fogRange = fog.parameters.y - fog.parameters.x;
    float fogFactor = clamp((fog.parameters.y - fakeDistance) / fogRange, 0.0, 1.0);
    fogFactor = mix(1.0, fogFactor, envData.parameters.z);  // Apply density
    return fogFactor;
}


void main() {
    vec3 dir = normalize(fragDir);
    vec3 skyColor = texture(skybox, dir).rgb;

    float fogFactor = calculateFogFactor(dir);    
    skyColor = mix(fog.color.rgb, skyColor, fogFactor);

    fragColor = vec4(skyColor, 1.0);
}
#version 450 

layout(binding = 1) uniform sampler2D texSampler;

layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec2 fragTexCoord;

layout(location = 0) out vec4 outColor;

void main() {
//    outColor = vec4(fragColor * texture(texSampler, fragTexCoord).rgb, 1.0);
    outColor = vec4(fragTexCoord.x, fragTexCoord.y, 0.5, 1);
//    outColor = vec4(fragColor.x, fragColor.y, fragColor.z, 1);
}
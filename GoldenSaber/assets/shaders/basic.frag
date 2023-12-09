#version 430 core

layout(location=0) in vec2 oTexCoord;

layout(location=0) out vec4 outColor;

layout(location=2) uniform vec4 uTint;

uniform sampler2D textureSampler;

void main()
{
    outColor = texture(textureSampler, oTexCoord) * uTint;
}
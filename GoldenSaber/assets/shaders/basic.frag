#version 430 core

layout(location=0) out vec4 outColor;

layout(location=0) uniform vec4 uTint;

void main()
{
    outColor = uTint * vec4(0.5, 1.0, 1.0, 1.0);
}
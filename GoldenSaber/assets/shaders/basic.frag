#version 430 core

layout(location=0) in vec2 oTexCoord;
layout(location=1) in flat float oTexIndex;

layout(location=0) out vec4 outColor;

//layout(location=2) uniform vec4 uTint;

uniform sampler2D uTextures[32];

void main()
{
    vec4 texColor = vec4(1, 1, 1, 1);

	switch(int(oTexIndex))
	{
		case  0: texColor *= texture(uTextures[ 0], oTexCoord); break;
		case  1: texColor *= texture(uTextures[ 1], oTexCoord); break;
		case  2: texColor *= texture(uTextures[ 2], oTexCoord); break;
		case  3: texColor *= texture(uTextures[ 3], oTexCoord); break;
		case  4: texColor *= texture(uTextures[ 4], oTexCoord); break;
		case  5: texColor *= texture(uTextures[ 5], oTexCoord); break;
		case  6: texColor *= texture(uTextures[ 6], oTexCoord); break;
		case  7: texColor *= texture(uTextures[ 7], oTexCoord); break;
		case  8: texColor *= texture(uTextures[ 8], oTexCoord); break;
		case  9: texColor *= texture(uTextures[ 9], oTexCoord); break;
		case 10: texColor *= texture(uTextures[10], oTexCoord); break;
		case 11: texColor *= texture(uTextures[11], oTexCoord); break;
		case 12: texColor *= texture(uTextures[12], oTexCoord); break;
		case 13: texColor *= texture(uTextures[13], oTexCoord); break;
		case 14: texColor *= texture(uTextures[14], oTexCoord); break;
		case 15: texColor *= texture(uTextures[15], oTexCoord); break;
		case 16: texColor *= texture(uTextures[16], oTexCoord); break;
		case 17: texColor *= texture(uTextures[17], oTexCoord); break;
		case 18: texColor *= texture(uTextures[18], oTexCoord); break;
		case 19: texColor *= texture(uTextures[19], oTexCoord); break;
		case 20: texColor *= texture(uTextures[20], oTexCoord); break;
		case 21: texColor *= texture(uTextures[21], oTexCoord); break;
		case 22: texColor *= texture(uTextures[22], oTexCoord); break;
		case 23: texColor *= texture(uTextures[23], oTexCoord); break;
		case 24: texColor *= texture(uTextures[24], oTexCoord); break;
		case 25: texColor *= texture(uTextures[25], oTexCoord); break;
		case 26: texColor *= texture(uTextures[26], oTexCoord); break;
		case 27: texColor *= texture(uTextures[27], oTexCoord); break;
		case 28: texColor *= texture(uTextures[28], oTexCoord); break;
		case 29: texColor *= texture(uTextures[29], oTexCoord); break;
		case 30: texColor *= texture(uTextures[30], oTexCoord); break;
		case 31: texColor *= texture(uTextures[31], oTexCoord); break;
	}

	outColor = texColor;
}
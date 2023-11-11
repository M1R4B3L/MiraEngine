#version 460

in vec4 oColor;
in vec2 texCoord;

out vec4 fragColor;

layout(binding=0) uniform sampler2D oTexture;

void main()
{
	//fragColor = oColor;
	fragColor = texture2D(oTexture, texCoord);// * oColor;
}

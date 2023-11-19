#version 460

out vec4 fragColor;

uniform vec3 lightDir;
in vec3 surfacePosition;
in vec3 surfaceNormal;

in vec2 uv;



layout(binding=0) uniform sampler2D oTexture;

void main()
{

	normalize(surfaceNormal);

	//fragColor = oColor;
	fragColor = texture2D(oTexture, uv);
}

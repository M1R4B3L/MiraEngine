#version 460
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;

layout (location = 0) uniform mat4 model; 
layout (location = 1) uniform mat4 view; 
layout (location = 2) uniform mat4 projection; 

out vec3 surfacePosition;
out vec3 surfaceNormal;

out vec2 uv;

void main()
{
	gl_Position = projection * view * model * vec4(position, 1.0);

	surfacePosition = (model*vec4(position,1.0f)).xyz;
	surfaceNormal = transpose(inverse(mat3(model))) * normal;

	uv = texCoord;
}
#version 460
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 col;

layout (location = 0) uniform mat4 model; 
layout (location = 1) uniform mat4 view; 
layout (location = 2) uniform mat4 proj; 

out vec4 oColor;

void main()
{
	gl_Position = proj * view * model * vec4(pos, 1.0);

	oColor = vec4(col,1.0f);
}
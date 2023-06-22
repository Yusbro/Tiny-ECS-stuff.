#version 330

in vec3 vertexPosition;
in vec2 vertexTexCoord;
in vec3 vertexNormal;
in vec4 vertexColor;

uniform mat4 mvp;

out vec2 fragTexCoord;
out vec4 fragColor;
out vec4 vertex_color;

void main()
{
	fragTexCoord = vertexTexCoord;
	fragColor = vertexColor;
	
	vertex_color = vertexColor;

	gl_Position = mvp * vec4(vertexPosition, 1.0);
}

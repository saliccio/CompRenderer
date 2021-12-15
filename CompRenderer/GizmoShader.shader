#shader vertex
#version 330 core

layout(location = 0) in vec3 positionVector;
layout(location = 1) in vec3 normalVector;
layout(location = 2) in vec2 textureCoords;

out vec4 v_MvpPosition;
out vec3 v_NormalDirection;
out vec2 v_TextureCoords;

uniform mat4 u_Mvp;

void main() {
	v_MvpPosition = u_Mvp * vec4(positionVector, 1.0);
	v_NormalDirection = normalVector;
	v_TextureCoords = textureCoords;

	gl_Position = v_MvpPosition;
}

#shader fragment
#version 330 core

in vec4 v_MvpPosition;
in vec3 v_NormalDirection;
in vec2 v_TextureCoords;

layout(location = 0) out vec4 color;

uniform mat3 u_NormalMatrix;
uniform vec3 u_LightDir;
uniform vec3 u_LightColor;

void main() {
	
}
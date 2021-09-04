#shader vertex
// DO NOT FORGET TO DO THE NORMAL MATRIX COMPUTATION
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

struct Material {
	sampler2D diffuseTexture;
	sampler2D specularTexture;

	vec3 ambientColor;
	vec3 diffuseColor;
	vec3 specularColor;

	float ambientFactor;
	float diffuseFactor;
	float specularFactor;

	float shininess;

	float opacity;
};

in vec4 v_MvpPosition;
in vec3 v_NormalDirection;
in vec2 v_TextureCoords;

layout(location = 0) out vec4 color;

uniform Material u_Material;
uniform mat3 u_NormalMatrix;
uniform vec3 u_LightDir;
uniform vec3 u_LightColor;

void main() {
	vec3 normalDirection = v_NormalDirection;		// cannot modify a vary

	normalDirection = u_NormalMatrix * normalDirection;		// convert normal vector to world direction

	//vec3 u_LightDir = normalize(u_LightPos - v_MvpPosition.xyz);

	//ambient
	vec4 ambient = vec4(0.2f * (u_Material.ambientColor * u_LightColor), 1.0);

	// diffuse
	float diffFactor = max(dot(normalDirection, -u_LightDir), 0.0);
	vec4 diffuse = vec4(0.7f * diffFactor * (u_Material.diffuseColor * u_LightColor), 1.0);

	// specular
	vec3 viewDir = normalize(-v_MvpPosition.xyz);
	vec3 reflectionDir = reflect(normalize(u_LightDir), normalDirection);
	
	float specFactor = pow(max(dot(viewDir, reflectionDir), 0.0), u_Material.shininess);
	vec4 specular = vec4(specFactor * (u_Material.specularColor * u_LightColor), 1.0);

	diffuse = diffuse * texture(u_Material.diffuseTexture, v_TextureCoords);

	specular = specular * texture(u_Material.specularTexture, v_TextureCoords);

	vec3 combinedColor = (ambient + diffuse + specular).xyz;
	color = vec4(combinedColor, u_Material.opacity);
}
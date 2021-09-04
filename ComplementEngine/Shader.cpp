#include <iostream>
#include <fstream>
#include <sstream>
#include "Shader.h"
#include "errorcheck.h"

namespace ComplementEngine {
	Shader::Shader(const std::string& filePath, const std::string& geometryShaderPath)
		: m_ProgramID(0)
	{
		ShaderProgramSource programSource = parseShader(filePath);
		int vertexShaderID = compileShader(GL_VERTEX_SHADER, programSource.vertex);
		int fragmentShaderID = compileShader(GL_FRAGMENT_SHADER, programSource.fragment);
		int geometryShaderID = -1;
		if (geometryShaderPath != "") {
			std::string geometrySource = parseGeometryShader(geometryShaderPath);
			geometryShaderID = compileShader(GL_GEOMETRY_SHADER, geometrySource);
		}
		if (vertexShaderID != -1 && fragmentShaderID != -1) {
			int programID = createProgram(vertexShaderID, fragmentShaderID);
			if (programID != -1) {
				m_ProgramID = programID;
			}
		}
	}

	Shader::~Shader()
	{
		E(glDeleteProgram(m_ProgramID));
	}

	void Shader::bind() const
	{
		E(glUseProgram(m_ProgramID));
	}

	void Shader::setUniform1i(const std::string& name, int value)
	{
		int uniformLocation = getUniformLocation(name);
		E(glUniform1i(uniformLocation, value));
	}

	void Shader::setUniform1f(const std::string& name, float value)
	{
		int uniformLocation = getUniformLocation(name);
		E(glUniform1f(uniformLocation, value));
	}

	void Shader::setUniform3f(const std::string& name, float v0, float v1, float v2)
	{
		int uniformLocation = getUniformLocation(name);
		E(glUniform3f(uniformLocation, v0, v1, v2));
	}

	void Shader::setUniform3fv(const std::string& name, const glm::mat3& value)
	{
		int uniformLocation = getUniformLocation(name);
		E(glUniformMatrix3fv(uniformLocation, 1, GL_FALSE, &value[0][0]));
	}

	void Shader::setUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
	{
		int uniformLocation = getUniformLocation(name);
		E(glUniform4f(uniformLocation, v0, v1, v2, v3));
	}

	void Shader::setUniform4fv(const std::string& name, const glm::mat4& value)
	{
		int uniformLocation = getUniformLocation(name);
		E(glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, &value[0][0]));
	}

	void Shader::setUniformPhongMaterial(const MaterialProperties& materialProperties, const Light& lightSource, const glm::mat4& modelMatrix, const glm::mat4& viewProjectionMatrix, unsigned int diffuseSlot, unsigned int specularSlot)
	{
		glm::mat4 mvp = viewProjectionMatrix * modelMatrix;
		setUniform4fv("u_Mvp", mvp);
		setUniform3fv("u_NormalMatrix", glm::transpose(glm::inverse(glm::mat3(mvp))));

		materialProperties.bindTextures(diffuseSlot, specularSlot);
		setUniform1i("u_Material.diffuseTexture", diffuseSlot);
		setUniform1i("u_Material.specularTexture", specularSlot);

		glm::vec3 ambientColor = materialProperties.ambientColor;
		setUniform3f("u_Material.ambientColor", ambientColor.x, ambientColor.y, ambientColor.z);

		glm::vec3 diffuseColor = materialProperties.diffuseColor;
		setUniform3f("u_Material.diffuseColor", diffuseColor.x, diffuseColor.y, diffuseColor.z);

		glm::vec3 specularColor = materialProperties.specularColor;
		setUniform3f("u_Material.specularColor", specularColor.x, specularColor.y, specularColor.z);

		/*setUniform1f("u_Material.ambientFactor", materialProperties.ambientFactor);
		setUniform1f("u_Material.diffuseFactor", materialProperties.diffuseFactor);
		setUniform1f("u_Material.specularFactor", materialProperties.specularFactor);*		deprecated */

		setUniform1f("u_Material.shininess", materialProperties.shininess);

		setUniform1f("u_Material.opacity", materialProperties.opacity);

		glm::vec3 lightDir = (glm::mat3(viewProjectionMatrix) * lightSource.transform.getForwardVector());
		glm::vec3 lightColor = lightSource.getLightColor();

		//lightPosition = mvp * lightPosition;
		setUniform3f("u_LightDir", lightDir.x, lightDir.y, lightDir.z);
		setUniform3f("u_LightColor", lightColor.x, lightColor.y, lightColor.z);
	}

	Shader& Shader::getShader(const std::string& name, const std::string& geometryShader)
	{
		Shader* shader = new Shader(name, geometryShader);
		return *shader;
	}

	ShaderProgramSource Shader::parseShader(const std::string& filePath)
	{
		enum class ShaderType {
			NONE = -1, VERTEX = 0, FRAGMENT = 1, GEOMETRY = 2
		};
		ShaderType currentType = ShaderType::NONE;
		std::ifstream str(filePath);
		std::stringstream ss[2];
		std::string line;
		while (std::getline(str, line)) {
			if (line.find("#shader") != std::string::npos) {
				if (line.find("vertex") != std::string::npos) {
					currentType = ShaderType::VERTEX;
				}
				else if (line.find("fragment") != std::string::npos) {
					currentType = ShaderType::FRAGMENT;
				}
			}
			else {
				ss[(int)currentType] << line << std::endl;
			}
		}
		return { ss[0].str(), ss[1].str() };
	}

	const std::string Shader::parseGeometryShader(const std::string& filePath)
	{
		std::ifstream str(filePath);
		std::stringstream ss;
		std::string line;
		while (std::getline(str, line)) {
			ss << line << std::endl;
		}

		return ss.str();
	}

	int Shader::compileShader(unsigned int type, const std::string& source)
	{
		E(unsigned int shaderID = glCreateShader(type));
		const char* src = source.c_str();
		E(glShaderSource(shaderID, 1, &src, nullptr));
		E(glCompileShader(shaderID));

		int compilationResult;
		E(glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compilationResult));
		if (compilationResult == GL_FALSE) {
			int errorLength;
			E(glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &errorLength));
			char* errorMessage = new char[errorLength];
			E(glGetShaderInfoLog(shaderID, errorLength, &errorLength, errorMessage));
			
			std::string typeStr;
			switch (type) {
			case GL_VERTEX_SHADER:
				typeStr = "vertex";
				break;
			case GL_FRAGMENT_SHADER:
				typeStr = "fragment";
				break;
			case GL_GEOMETRY_SHADER:
				typeStr = "geometry";
				break;
			}

			std::cout << "Error while compiling " << typeStr << " shader (ID " << shaderID << ").    Message:\n" << errorMessage << std::endl;
			delete[] errorMessage;
			E(glDeleteShader(shaderID));
			return -1;
		}
		return shaderID;
	}

	int Shader::createProgram(unsigned int vertexID, unsigned int fragmentID, int geometryID)
	{
		bool geometryShaderExists = (geometryID != -1);

		E(unsigned int programID = glCreateProgram());
		E(glAttachShader(programID, vertexID));
		E(glAttachShader(programID, fragmentID));
		if (geometryShaderExists) {
			E(glAttachShader(programID, geometryID));
		}
		E(glLinkProgram(programID));

		int linkResult;
		E(glGetProgramiv(programID, GL_LINK_STATUS, &linkResult));
		if (linkResult == GL_FALSE) {
			int errorLength;
			E(glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &errorLength));
			char* errorMessage = new char[errorLength];
			glGetProgramInfoLog(programID, errorLength, &errorLength, errorMessage);
			std::cout << "Error while linking program (ID " << programID << ") with vertex shader " << vertexID << ", fragment shader " << fragmentID << " and geometry shader " << geometryID << "    Message:\n" << errorMessage << std::endl;
			delete[] errorMessage;
			E(glDeleteProgram(programID));
			return -1;
		}
		E(glDeleteShader(vertexID));
		E(glDeleteShader(fragmentID));
		if (geometryShaderExists) {
			E(glDeleteShader(geometryID));
		}
		return programID;
	}

	int Shader::getUniformLocation(const std::string& name)
	{
		if (m_uniformLocations.find(name) != m_uniformLocations.end()) {
			return m_uniformLocations[name];
		}

		const char* uniformName = name.c_str();
		E(int uniformLocation = glGetUniformLocation(m_ProgramID, uniformName));
		if (uniformLocation == -1) {
			std::cout << "Error: Uniform '" << name << "' does not exist." << std::endl;
		}
		m_uniformLocations[name] = uniformLocation;
		return uniformLocation;
	}
}
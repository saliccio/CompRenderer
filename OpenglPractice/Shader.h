#pragma once
#include <string>
#include <unordered_map>
#include <GL/glew.h>
#include "glm/glm.hpp"
#include "Material.h"
#include "Light.h"

namespace ComplementEngine {
	struct ShaderProgramSource {
		const std::string vertex;
		const std::string fragment;
	};

	class Shader {
	private:
		unsigned int m_ProgramID;
		std::string m_FilePath;
		std::unordered_map<std::string, int> m_uniformLocations;

		ShaderProgramSource parseShader(const std::string& filePath);
		const std::string parseGeometryShader(const std::string& geometryShaderPath);
		int compileShader(unsigned int type, const std::string& source);
		int createProgram(unsigned int vertexID, unsigned int fragmentID, int geometryID = -1);
		int getUniformLocation(const std::string& name);
	public:
		static Shader& getShader(const std::string& name, const std::string& geometryShader = "");
	public:
		Shader() = default;
		Shader(const std::string& filePath, const std::string& geometryShaderPath = "");
		~Shader();

		void bind() const;
		void setUniform1i(const std::string& name, int value);
		void setUniform1f(const std::string& name, float value);
		void setUniform3f(const std::string& name, float v0, float v1, float v2);
		void setUniform3fv(const std::string& name, const glm::mat3& value);
		void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
		void setUniform4fv(const std::string& name, const glm::mat4& value);
		void setUniformPhongMaterial(const MaterialProperties& materialProperties, const Light& lightSource, const glm::mat4& modelMatrix, const glm::mat4& viewProjectionMatrix, unsigned int diffuseSlot = 0U, unsigned int specularSlot = 1U);
	};
}
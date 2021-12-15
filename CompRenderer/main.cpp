#include <iostream>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Renderer.h"
#include "Texture.h"
#include "Transform.h"
#include "Camera.h"
#include "GLFWContext.h"
#include "Vertex.h"
#include "Entity.h"

#include "Macros.h"

#define WIDTH 1200
#define HEIGHT 800

using namespace CompRenderer;

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		(glfwSetWindowShouldClose(window, true));
	}
}

void GLInit() {
	(glfwInit());
	glewExperimental = true;
	(glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3));
	(glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3));
	(glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE));
	GLFWwindow* mainWindow;
	mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Engine", NULL, NULL);
	if (mainWindow == NULL) {
		std::cout << "Failed to create the main window." << std::endl;
	}
	(glfwMakeContextCurrent(mainWindow));
	GLFWContext::setInstance(mainWindow);
	(glViewport(0, 0, WIDTH, HEIGHT));
	(glewInit());
}

void ImGuiInit() {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(GLFWContext::getInstance(), true);
	ImGui_ImplOpenGL3_Init((char*)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));
}

void ImGuiFPSWindow() {
	ImGui::Begin("FPS");
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();
}

int main() {
	GLInit();
	ImGuiInit();
	CE_STATIC_CONSTRUCTION();
	glfwSwapInterval(1);

	Camera c(true);
	c.setFov(45.0f);
	c.setNearClip(0.1f);
	c.setFarClip(10000.0f);
	glm::vec3 tempvec = glm::vec3(0.0, 0.0, 90.0);


	Transform lightTransform;
	lightTransform.setPosition(glm::vec3(8.0f, 0.0f, 0.0f));
	glm::vec3 lightRotation(20.0f, 20.0f, 0.0f);
	lightTransform.setRotation(lightRotation);
	lightTransform.setScale(glm::vec3(1.0f, 1.0f, 1.0f));
	Light defaultLight(glm::vec3(1.0f, 1.0f, 1.0f), lightTransform);
	Light::addLight(defaultLight);

	E(glEnable(GL_BLEND));
	E(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	E(glEnable(GL_DEPTH_TEST));

	Model model("cube.fbx");

	Entity entity("entity1", model);

	Renderer renderer(c);
	glfwSetTime(0.0);
	float timeSinceStart = glfwGetTime();
	
	float entityPos[3] = { 0.0f, 0.0f, -5.0f };
	float entityRot[3] = { 0.0f };
	float entityScale[3] = { 1.0f, 1.0f, 1.0f };;

	float lightPos[3] = { 0.0f };
	float lightRot[3] = { 0.0f };
	float lightScale[3] = { 1.0f, 1.0f, 1.0f };

	while (!glfwWindowShouldClose(GLFWContext::getInstance())) {
		double startCursorX, startCursorY;
		glfwGetCursorPos(GLFWContext::getInstance(), &startCursorX, &startCursorY);

		renderer.clear();

		processInput(GLFWContext::getInstance());
		c.onKeyboardListen();

		entity.draw(renderer);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGuiFPSWindow();

		ImGui::Begin("Model Transform");
		ImGui::SliderFloat3("World Position", entityPos, -100.0f, 100.0f);
		ImGui::SliderFloat3("World Rotation", entityRot, 0, 360);
		ImGui::SliderFloat3("World Scale", entityScale, 1, 50);
		ImGui::End();

		glm::vec3 positionVec = glm::vec3(entityPos[0], entityPos[1], entityPos[2]);
		glm::vec3 rotationVec = glm::vec3(entityRot[0], entityRot[1], entityRot[2]);
		glm::vec3 scaleVec = glm::vec3(entityScale[0], entityScale[1], entityScale[2]);

		entity.transform.setPosition(positionVec);
		entity.transform.setRotation(rotationVec);
		entity.transform.setScale(scaleVec);

		ImGui::Begin("Light Transform");
		ImGui::SliderFloat3("World Position", lightPos, -100.0f, 100.0f);
		Light::getLight(0).transform.setPosition(glm::vec3(lightPos[0], lightPos[1], lightPos[2]));
		ImGui::SliderFloat3("World Rotation", lightRot, 0, 360);
		glm::vec3 rot(lightRot[0], lightRot[1], lightRot[2]);
		Light::getLight(0).transform.setRotation(rot);
		ImGui::SliderFloat3("World Scale", lightScale, 0, 5);
		glm::vec3 sca(lightScale[0], lightScale[1], lightScale[2]);
		Light::getLight(0).transform.setScale(sca);
		ImGui::End();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		(glfwSwapBuffers(GLFWContext::getInstance()));
		(glfwPollEvents());

		double endCursorX, endCursorY;
		glfwGetCursorPos(GLFWContext::getInstance(), &endCursorX, &endCursorY);
		GLFWContext::setDeltaMouseCursorX(endCursorX - startCursorX);
		GLFWContext::setDeltaMouseCursorY(endCursorY - startCursorY);

		double newTimeSinceStart = glfwGetTime();
		GLFWContext::setDeltaTime(newTimeSinceStart - timeSinceStart);
		timeSinceStart = newTimeSinceStart;
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	return 0;
}
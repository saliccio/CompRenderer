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

#include "CE_Macros.h"

#define WIDTH 800
#define HEIGHT 600

using namespace ComplementEngine;

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

void ImGuiSampleWindow() {
	ImGui::Begin("Hello, world!");
	ImGui::Text("This is some useful text.");
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();
}

int main() {
	GLInit();
	ImGuiInit();
	CE_STATIC_CONSTRUCTION();
	glfwSwapInterval(1);
	float vertices[] = {
		-0.5, -0.5, 0.0, 0.0,
		-0.5, 0.5, 0.0, 1.0,
		 0.5, -0.5, 1.0, 0.0,
		 0.5, 0.5, 1.0, 1.0
	};

	unsigned int indices[] = {
		1, 0, 2, 1, 3, 2
	};

	/*Vertex* vertices = new Vertex[4];
	vertices[0].Position = glm::vec3(-0.5f, -0.5f, 0.0f);
	vertices[1].Position = glm::vec3(-0.5f, 0.5f, 0.0f);
	vertices[2].Position = glm::vec3(0.5f, -0.5f, 0.0f);
	vertices[3].Position = glm::vec3(0.5f, 0.5f, 0.0f);

	vertices[0].TexCoords = glm::vec2(0.0f, 0.0f);
	vertices[1].TexCoords = glm::vec2(0.0f, 1.0f);
	vertices[2].TexCoords = glm::vec2(1.0f, 0.0f);
	vertices[3].TexCoords = glm::vec2(1.0f, 1.0f);*/

	Camera c(true);
	c.setFov(45.0f);
	c.setNearClip(0.1f);
	c.setFarClip(10000.0f);
	glm::vec3 tempvec = glm::vec3(0.0, 0.0, 90.0);
	//c.transform.rotate(tempvec);


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

	Transform transform;
	transform.move(glm::vec3(0.0, 0.0, 0.0));
	transform.setScale(glm::vec3(1.0, 1.0, 1.0));

	VertexArray vertexArray;
	VertexBuffer vertexBuffer{ vertices, 4 * 4 * sizeof(float) };
	IndexBuffer indexBuffer(indices, 6 * sizeof(unsigned int));
	VertexBufferLayout bufferLayout;
	bufferLayout.Add<float>(2);
	bufferLayout.Add<float>(2);
	vertexArray.addBuffer(vertexBuffer, bufferLayout);
	vertexArray.bind();
	Shader shader("MinimalShader.shader", "GSModelShader.shader");
	shader.bind();
	Texture texture("logo.jpg", aiTextureType::aiTextureType_DIFFUSE);
	texture.bind(15);
	shader.setUniform1i("u_Texture", 15);

	Entity lightPlaceHolder("cube", "cube.fbx");
	Renderer renderer(c);

	glfwSetTime(0.0);
	float timeSinceStart = glfwGetTime();
	
	float lightPos[3] = { 0.0f };
	float lightRot[3] = { 0.0f };
	float lightScale[3] = { 1.0f };;

	while (!glfwWindowShouldClose(GLFWContext::getInstance())) {
		double startCursorX, startCursorY;
		glfwGetCursorPos(GLFWContext::getInstance(), &startCursorX, &startCursorY);

		renderer.clear();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		processInput(GLFWContext::getInstance());
		c.onKeyboardListen();

		lightPlaceHolder.draw(renderer);

		ImGuiSampleWindow();
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
#include "mkpch.h"
#include "Game.h"

#include "Core/Layer.h"
#include "Shaders/Shader.h"
#include "Renderer/Core/Mesh.h"
#include "Material/Texture.h"
#include "Utility/Cemera.h"
#include "Core/Input.h"

#include "Renderer/Opengl/SkyBox.h"
#include "Renderer/Debug/Grid.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

glm::mat4 projection;
glm::mat4 orthProj;
Misk::Camera camera;
Misk::Timestep deltaTime;

float angle = 0.0f;
float speedAng = 10.0f;
float tempScal = 1.0f;
float tx = 30.0f;
float ty = 0.0f;
float tz = -2.0f;
const float toRadians = 3.14159265f / 180.0f;


class MainLayer : public Misk::Layer
{
private:
	Misk::Mesh* squar;
	Misk::Shader* shader;
	Misk::Shader* colorShader;
	Misk::Texture* texture;
	Misk::Skybox skybox;

public:

	~MainLayer()
	{
		delete squar;
		delete shader;
		delete colorShader;
		delete texture;
	}


	void OnAttach() override
	{
		std::vector<Vertex> cubeVertices = {
			// Bottom face
			Vertex{ { -0.5f, -0.5f, -0.5f}, { 0.0f, -1.0f,  0.0f}, {0.0f, 0.0f}},  // 0
			Vertex{ {  0.5f, -0.5f, -0.5f}, { 0.0f, -1.0f,  0.0f}, {1.0f, 0.0f}},  // 1
			Vertex{ {  0.5f, -0.5f,  0.5f}, { 0.0f, -1.0f,  0.0f}, {1.0f, 1.0f}},  // 2
			Vertex{ { -0.5f, -0.5f,  0.5f}, { 0.0f, -1.0f,  0.0f}, {0.0f, 1.0f}},  // 3

			// Top face
			Vertex{ { -0.5f,  0.5f, -0.5f}, { 0.0f,  1.0f,  0.0f}, {0.0f, 1.0f}},  // 4
			Vertex{ {  0.5f,  0.5f, -0.5f}, { 0.0f,  1.0f,  0.0f}, {1.0f, 1.0f}},  // 5
			Vertex{ {  0.5f,  0.5f,  0.5f}, { 0.0f,  1.0f,  0.0f}, {1.0f, 0.0f}},  // 6
			Vertex{ { -0.5f,  0.5f,  0.5f}, { 0.0f,  1.0f,  0.0f}, {0.0f, 0.0f}},  // 7

			// Left face
			Vertex{ { -0.5f, -0.5f, -0.5f}, {-1.0f,  0.0f,  0.0f}, {1.0f, 0.0f}},  // 8
			Vertex{ { -0.5f,  0.5f, -0.5f}, {-1.0f,  0.0f,  0.0f}, {1.0f, 1.0f}},  // 9
			Vertex{ { -0.5f,  0.5f,  0.5f}, {-1.0f,  0.0f,  0.0f}, {0.0f, 1.0f}},  // 10
			Vertex{ { -0.5f, -0.5f,  0.5f}, {-1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}},  // 11

			// Right face
			Vertex{ {  0.5f, -0.5f, -0.5f}, { 1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}},  // 12
			Vertex{ {  0.5f,  0.5f, -0.5f}, { 1.0f,  0.0f,  0.0f}, {0.0f, 1.0f}},  // 13
			Vertex{ {  0.5f,  0.5f,  0.5f}, { 1.0f,  0.0f,  0.0f}, {1.0f, 1.0f}},  // 14
			Vertex{ {  0.5f, -0.5f,  0.5f}, { 1.0f,  0.0f,  0.0f}, {1.0f, 0.0f}},  // 15

			// Front face
			Vertex{ { -0.5f, -0.5f,  0.5f}, { 0.0f,  0.0f,  1.0f}, {0.0f, 0.0f}},  // 16
			Vertex{ {  0.5f, -0.5f,  0.5f}, { 0.0f,  0.0f,  1.0f}, {1.0f, 0.0f}},  // 17
			Vertex{ {  0.5f,  0.5f,  0.5f}, { 0.0f,  0.0f,  1.0f}, {1.0f, 1.0f}},  // 18
			Vertex{ { -0.5f,  0.5f,  0.5f}, { 0.0f,  0.0f,  1.0f}, {0.0f, 1.0f}},  // 19

			// Back face
			Vertex{ { -0.5f, -0.5f, -0.5f}, { 0.0f,  0.0f, -1.0f}, {0.0f, 0.0f}},  // 20
			Vertex{ {  0.5f, -0.5f, -0.5f}, { 0.0f,  0.0f, -1.0f}, {1.0f, 0.0f}},  // 21
			Vertex{ {  0.5f,  0.5f, -0.5f}, { 0.0f,  0.0f, -1.0f}, {1.0f, 1.0f}},  // 22
			Vertex{ { -0.5f,  0.5f, -0.5f}, { 0.0f,  0.0f, -1.0f}, {0.0f, 1.0f}},  // 23

		};


		std::vector<unsigned int> cubeIndices = {
			// Bottom face
			0, 1, 2,   // First triangle
			2, 3, 0,   // Second triangle

			// Top face
			4, 5, 6,   // First triangle
			6, 7, 4,   // Second triangle

			// Left face
			8, 9, 10,  // First triangle
			10, 11, 8, // Second triangle

			// Right face
			12, 13, 14, // First triangle
			14, 15, 12, // Second triangle

			// Front face
			16, 17, 18, // First triangle
			18, 19, 16, // Second triangle

			// Back face
			20, 21, 22, // First triangle
			22, 23, 20  // Second triangle
		};

		squar = new Misk::Mesh(cubeVertices, cubeIndices);
		MK_ASSERT(squar, "the object faild")
			squar->initMesh();

		shader = new Misk::Shader();
		MK_ASSERT(shader, "the object faild");

		shader->init("src/Shaders/glsl/shaderV1.vert", "src/Shaders/glsl/shaderV1.frag");

		texture = new Misk::Texture();
		texture->loadTexture("Media/container.jpg");

		//skybox initailization
		skybox.init();
		std::vector<std::string> faces
		{
			"right.jpg",
				"left.jpg",
				"top.jpg",
				"bottom.jpg",
				"front.jpg",
				"back.jpg"
		};
		std::vector<std::string> faces2
		{
			"right2.jpg",
				"left2.jpg",
				"top2.jpg",
				"bottom2.jpg",
				"front2.jpg",
				"back2.jpg"
		};
		skybox.loadCubemap("ocean", faces);
		skybox.loadCubemap("space", faces2);

	}
	void OnUpdate(Misk::Timestep ts) override
	{
		static bool mouseOn = false;
		deltaTime = ts;
		Misk::Application& app = Misk::Application::Get();

		if (Misk::Input::IsKeyPressedOnce(MK_KEY_C))
		{
			mouseOn = !mouseOn;
			MK_INFO("the camera state", mouseOn);
		}
		if (mouseOn)
		{
			glfwSetInputMode(app.GetWindow().GetNativeWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			camera.freeCamera(ts);
			camera.mouseControl(app.GetXChange(), app.GetYChange());
		}
		else {
			glfwSetInputMode(app.GetWindow().GetNativeWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}

		//skybox render
		skybox.renderSkybox("ocean", projection, camera.calculateViewMatrix());
		//skybox.renderSkybox("space", projection, camera.calculateViewMatrix());

		shader->use();
		shader->setMat4f("view", camera.calculateViewMatrix());
		shader->setMat4f("projection", projection);
		//MK_INFO("Its Works!");
		glm::mat4 model(1.0f);

		if (angle > 360.0f)
			angle = 0.0f;
		//transformation matrix(model)
		for (int i = 0; i < 5; i++) {

			angle += speedAng * ts;
			model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(float(tx * i / 10), ty, tz));
			model = glm::scale(model, glm::vec3(tempScal));
			model = glm::rotate(model, (angle * toRadians), glm::vec3(1.0f, 0.0f, 0.0f));
			shader->setMat4f("model", model);
			texture->applyTexture(0);
			squar->DrawMesh();
			//xDrawObject(squar, shader);
		}

	}

	void OnImguiRender() override
	{
		static bool show_another_window = true;
		MK_ASSERT(Misk::ImguiLayer::GetImguiContext(), "sad!");
		ImGui::SetCurrentContext(Misk::ImguiLayer::GetImguiContext());

		if (show_another_window)
		{
			ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
			ImGui::Text("My name is almakhtar and this my window!");
			ImGui::Text("current angle = %.2f", angle);
			ImGui::End();
		}
	}

	void OnEvent(Misk::Event& e) override
	{
		
		//MK_TRACE(e.ToString());
	}

};

class DebugLayer : public Misk::Layer
{
private:
	Misk::Grid* grid;
	float lineThikness = 0.025f;
public:
	DebugLayer() {
		grid = new Misk::Grid();
		grid->init();
	}
	~DebugLayer() {
		delete grid;
	}

	void OnUpdate(Misk::Timestep ts) override
	{
		//MK_TRACE("work!");
		grid->render(projection, camera.getCameraPosition(), camera.calculateViewMatrix(), lineThikness);
		static bool show = true;
		ImGui::SetCurrentContext(Misk::ImguiLayer::GetImguiContext());
		ImGui::Begin("Debug", &show);
		ImGui::SliderFloat("Thikness", &lineThikness, 0.0f, 1.0f);
		ImGui::End();
	}
	
	


};


Game::Game()
{

	projection = glm::perspective(45.0f,
		(float)this->GetWindow().GetWidth() / (float)this->GetWindow().GetHeight(),
		0.1f, 100.0f);	
	//projection = orthProj = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f);

	orthProj = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f);
	camera = Misk::Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 0.5f);

	glfwSetInputMode(this->GetWindow().GetNativeWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	PushLayer(new MainLayer());
	PushOverlay(new DebugLayer());
}

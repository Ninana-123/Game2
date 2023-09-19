#include "pch.h"
#include "Graphics.h"

namespace Engine
{

	glm::vec3 translationA(200, 200, 0);
	glm::vec3 translationB(400, 200, 0);
	Shader shader("res/Shader/basic.shader");

	Graphics::Graphics()
	{
		// Constructor implementation here
		window = nullptr; // Initialize the member variable
	}

	Graphics::~Graphics()
	{
		// Destructor implementation here
	}

	void Graphics::Initialize()
	{
		/* Initialize the library */
		if (!glfwInit())
			return;

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		/* Create a windowed mode window and its OpenGL context */
		window = glfwCreateWindow(1000, 700, "Graphics", NULL, NULL);

		if (!window)
		{
			glfwTerminate();
			return;
		}

		/* Make the window's context current */
		glfwMakeContextCurrent(window);

		glfwSwapInterval(3);

		if (glewInit() != GLEW_OK)
		{
			std::cout << "Error!" << std::endl;
		}

		std::cout << glGetString(GL_VERSION) << std::endl;

		// Initialize other variables and objects here

		// Vertex positions
		float positions[] =
		{
			-50.0f, -50.0f, 0.0f, 0.0f, // 0
			50.0f, -50.0f, 1.0f, 0.0f, // 1
			50.0f, 50.0f, 1.0f, 1.0f, // 2
			-50.0f, 50.0f, 0.0f, 1.0f // 3
		};

		unsigned int indices[] =
		{
			0, 1, 2,
			2, 3, 0
		};

		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		VertexArray va{ 1 };
		VertexBuffer vb(positions, 4 * 4 * sizeof(float));

		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);
		va.AddBuffer(vb, layout);

		IndexBuffer ib(indices, 6);

		// Moving of the texture
		proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
		view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)); // Left translation
		Shader shader("res/Shader/basic.shader");
		shader.Bind();
		shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

		Texture luffyTexture("res/textures/Luffy.png");
		luffyTexture.Bind();
		shader.SetUniform1i("u_Texture", 0);

		Texture zoroTexture("res/textures/zoro.png"); // Load the new texture
		zoroTexture.Bind(1); // Bind the texture to a different texture unit (e.g., unit 1)

		va.Unbind();
		vb.Unbind();
		ib.Unbind();
		shader.Unbind();

		Renderer renderer;

		//ImGui::CreateContext();
		//ImGui_ImplGlfwGL3_Init(window, true);
		//ImGui::StyleColorsDark();

	}

	void Graphics::Update()
	{
		if (!window)
		{
			// Handle the case where the window creation failed
			return;
		}

		// Main graphics loop
		while (!glfwWindowShouldClose(this->window))
		{
			// Handle graphics updates here
			//renderer.Clear();
			//ImGui_ImplGlfwGL3_NewFrame();

			// Handle keyboard input
			if (glfwGetKey(this->window, GLFW_KEY_RIGHT) == GLFW_PRESS)
			{
				// Right arrow key is pressed, move right
				translationA.x += 5.0f;
			}
			if (glfwGetKey(this->window, GLFW_KEY_LEFT) == GLFW_PRESS)
			{
				// Left arrow key is pressed, move left
				translationA.x -= 5.0f;
			}
			if (glfwGetKey(this->window, GLFW_KEY_DOWN) == GLFW_PRESS)
			{
				// Down arrow key is pressed, move down
				translationA.y -= 5.0f;
			}
			if (glfwGetKey(this->window, GLFW_KEY_UP) == GLFW_PRESS)
			{
				// UP arrow key is pressed, move UP
				translationA.y += 5.0f;
			}

			// Check for "R" key press
			if (glfwGetKey(this->window, GLFW_KEY_R) == GLFW_PRESS)
			{
				// "R" key is pressed, increment rotation angle
				rotationAngle += 0.05f;
			}


			{
				glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA); // Left translation
				model = glm::rotate(model, rotationAngle, glm::vec3(0.0f, 0.0f, 1.0f)); // Rotate around the Z-axis
				glm::mat4 mvp = proj * view * model;
				luffyTexture.Bind();
				shader.Bind();
				shader.SetUniformMat4f("u_MVP", mvp);
				renderer.Draw(va, ib, shader);
			}

			{
				glm::mat4 model = glm::translate(glm::mat4(1.0f), translationB); // Right translation
				model = glm::rotate(model, rotationAngle, glm::vec3(0.0f, 0.0f, 1.0f)); // Rotate around the Z-axis
				glm::mat4 mvp = proj * view * model;
				zoroTexture.Bind();
				shader.Bind();
				shader.SetUniformMat4f("u_MVP", mvp);
				renderer.Draw(va, ib, shader);
			}

			//ImGui::SliderFloat3("TranslationA", &translationA.x, 0.0f, 960.0f);
			//ImGui::SliderFloat3("TranslationB", &translationB.x, 0.0f, 960.0f);
			//ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
			//1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);


			// Increment the rotation angle for animation
			rotationAngle += 0.05f;

			// Additional code for rendering and user interface interactions
			//ImGui::Render();
			//ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

			/* Swap front and back buffers */
			glfwSwapBuffers(this->window);

			/* Poll for and process events */
			glfwPollEvents();
		}

		// Cleanup code
		//ImGui_ImplGlfwGL3_Shutdown();
		//ImGui::DestroyContext();
		// No need to terminate GLFW here; it should be terminated in a destructor or elsewhere.
	}

	// Implement other functions here

} // namespace Engine


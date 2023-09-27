
#include "pch.h"
#include "Graphics.h"
#include "AudioEngine.h"
#include "Logger.h"
#include "Collision.h"
#include "Vector2d.h"
namespace Engine
{
    Logger GraphicsLogger;

    Graphics::Graphics()
        : shader("Resource/Shaders/Basic.shader")
    {
    }

    Graphics::~Graphics()
    {
        // Cleanup any resources here
        // Terminate GLFW
        glfwTerminate();
    }

    void Graphics::InitializeGLEW() {
        // Initialize GLEW
        GLenum glewInitResult = glewInit();
        if (glewInitResult != GLEW_OK)
        {
            GraphicsLogger.Log(LogLevel::Error, "GLEW failed to initialize");
            glfwTerminate();
        }
        else
            GraphicsLogger.Log(LogLevel::Debug, "GLEW successfully initialized");
    }

    void Graphics::Initialize() {

        Window = glfwGetCurrentContext();

        Graphics::InitializeGLEW();
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

        // Clear the color buffer
        glClear(GL_COLOR_BUFFER_BIT);

        //define vertex array and indices
        float positions[] = {
       -60.0f,  -60.0f, 0.0f, 0.0f,    //0
        60.0f,  -60.0f, 1.0f, 0.0f,    //1
        60.0f,   60.0f, 1.0f, 1.0f,    //2
       -60.0f,   60.0f, 0.0f, 1.0f     //3
        };

        // Copy vtx_position into vtx_position member variable
        std::copy(std::begin(positions), std::end(positions), std::begin(this->vtx_postions));

        unsigned int indices[] =
        {
            0, 1, 2,
            2, 3, 0
        };

        std::copy(std::begin(indices), std::end(indices), std::begin(this->indices));

        //enable blending for transparency
        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        //create vertex array, vertex buffer, and index buffer
    
        VertexBuffer vb(positions, 4 * 4 * sizeof(float));

        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        Graphics::va.AddBuffer(vb, layout);

        Graphics::ib.SetData(indices, 6);

        // set up projection and view matrices
        Graphics::proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
        Graphics::view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)); // Left translation

        // load and initialize the shader
        InitializeShader();

        // initialize and bind textures
        InitializeTextures();

        ib.Unbind();
        va.Unbind();
        vb.Unbind();
        shader.Unbind();
    }

    void Graphics::Update(std::unordered_map<EntityID, std::unique_ptr<Entity>>* entities)
    {
        renderer.Clear();
        for (const auto& entityPair : *entities)
        {
            Entity* entity = entityPair.second.get();

            if (entity->HasComponent(ComponentType::Transform))
            {
                //Assign reference to transform component
                TransformComponent* transform = dynamic_cast<TransformComponent*>(entity->GetComponent(ComponentType::Transform));

                //Read transform data from Transform component

                //translate
                glm::vec3 transA(transform->x, transform->y, 0);

                //rotate
                float rotationA = transform->rot;

                //scale
                glm::vec3 localScale(transform->scaleX, transform->scaleY, 1.0f);

                int width, height;
                glfwGetWindowSize(Window, &width, &height);
                UpdateViewport(width, height);


                // Check collision with the window boundaries
                // VECTORMATH::Vec2 velA(0.0f, 0.0f);
                float halfWidth = 50.0f;  // Half of the texture width
                float halfHeight = 50.0f; // Half of the texture height

                AABB aabb1;
                aabb1.min = VECTORMATH::Vec2(transA.x - halfWidth, transA.y - halfHeight);
                aabb1.max = VECTORMATH::Vec2(transA.x + halfWidth, transA.y + halfHeight);

                bool isCollisionWithWindow = false;
               // bool isCollisionWithBoundary = false;

                if (aabb1.min.x < 0 || aabb1.max.x > width || aabb1.min.y < 0 || aabb1.max.y > height) {
                    isCollisionWithWindow = true;
                }

                if (isCollisionWithWindow)
                {
                    std::cout << "Collision with the window detected!" << std::endl;
                }


                // collision with the entities
                for (const auto& otherEntityPair : *entities)
                {
                    if (otherEntityPair.first != entityPair.first)
                    {
                        Entity* otherEntity = otherEntityPair.second.get();

                        if (otherEntity->HasComponent(ComponentType::Transform))
                        {
                            TransformComponent* otherTransform = dynamic_cast<TransformComponent*>(otherEntity->GetComponent(ComponentType::Transform));

                            float halfWidthB = 50.0f;  // Half of the texture width for entity2
                            float halfHeightB = 50.0f; // Half of the texture height for entity2

                            AABB aabb2;
                            aabb2.min = VECTORMATH::Vec2(otherTransform->x - halfWidthB, otherTransform->y - halfHeightB);
                            aabb2.max = VECTORMATH::Vec2(otherTransform->x + halfWidthB, otherTransform->y + halfHeightB);

                            // Check for collision between aabb1 and aabb2
                            if (aabb1.min.x < aabb2.max.x && aabb1.max.x > aabb2.min.x &&
                                aabb1.min.y < aabb2.max.y && aabb1.max.y > aabb2.min.y)
                            {
                                std::cout << "Collision between new entity and old entity detected!" << std::endl;
                                // Handle the collision as needed
                            }
                        }
                    }
                }


                // Apply transformations from UpdateTransformations
                glm::mat4 modelA = SetupModelMatrix(transA, rotationA, localScale);

                glm::mat4 mvpA = proj * view * modelA;

                //Get the current state of the 'P' key
                bool currentPState = glfwGetKey(this->Window, GLFW_KEY_P) == GLFW_PRESS;

                // Check if there's a change in the 'P' key state
                if (currentPState && !previousPState)
                {
                    // Toggle the rendering mode
                    ToggleRenderMode();
                }

                // Update the previous 'P' key state
                previousPState = currentPState;

                if (renderTexturedSquare)
                {

                    shader.Bind();


                    double currentTime = glfwGetTime();
                    double elapsedTime = currentTime - programStartTime;
                    int textureIndex = static_cast<int>(elapsedTime / 3.0) % 2;

                    if (textureIndex == 0)
                    {
                        textureA.Bind(0);
                    }
                    else
                    {
                        textureB.Bind(0);
                    }


                    shader.SetUniform1i("u_RenderTextured", 1); // Render textured
                    shader.SetUniform1i("u_Texture", 0);
                    shader.SetUniformMat4f("u_MVP", mvpA);
                    renderer.Draw(va, ib, shader);

                    // Draw a square around Texture A
                    shader.SetUniform1i("u_RenderTextured", 0); // Render plain (no texture)
                    shader.SetUniform4f("u_Color", 0.0f, 0.0f, 0.0f, 1.0f); // Set the line color

                    // Draw the square as lines 
                    GLCall(glDrawArrays(GL_LINE_LOOP, 0, 4));

                    // Reset the shader render mode to textured
                    shader.SetUniform1i("u_RenderTextured", 1);

                }
                else
                {
                    // Bind the shader and set uniforms
                    shader.Bind();
                    shader.SetUniform4f("u_Color", 0.0f, 0.0f, 0.0f, 1.0f);
                    shader.SetUniformMat4f("u_MVP", mvpA);

                    // Render the blue square
                    renderer.Draw(va, ib, shader);
                }
                transform->x = static_cast<int>(transA.x);
                transform->y = static_cast<int>(transA.y);

            }

        }
        //GraphicsLogger.Log(LogLevel::Debug, "Currently updating graphics");
    }

    void Graphics::UpdateViewport(int width, int height)
    {
        glViewport(0, 0, width, height);
        proj = glm::ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height), -1.0f, 1.0f);
    }

    void Graphics::InitializeShader()
    {
        shader.LoadShader("Resource/Shaders/Basic.shader");

        shader.Initialize();
        shader.Bind();
        shader.SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
    }

    void Graphics::InitializeTextures()
    {
        if (!textureA.Load("Resource/Texture/Tank.png")) // Check for texture loading errors
        {
            GraphicsLogger.Log(LogLevel::Error, "Failed to load Texture A.");
            // Handle the error as needed, e.g., return or throw an exception
        }
        else {
            textureA.InitGL();
            textureA.Bind(0);
        }

        if (!textureB.Load("Resource/Texture/Archer.png")) // Check for texture loading errors
        {
            GraphicsLogger.Log(LogLevel::Error, "Failed to load Texture B.");
            // Handle the error as needed, e.g., return or throw an exception
        }
        else {
            textureB.InitGL();
            textureB.Bind(1); // Bind the texture to a different texture unit (e.g., unit 1)
        }
    }

    // Function to toggle between textured and plain squares
    void Graphics::ToggleRenderMode()
    {
        renderTexturedSquare = !renderTexturedSquare;
        shader.Bind();
        shader.SetUniform1i("u_RenderTextured", renderTexturedSquare ? 1 : 0);
    }

    glm::mat4 Graphics::SetupModelMatrix(const glm::vec3& translation, float rotationAngle, const glm::vec3& scale)
    {
        glm::mat4 model = glm::mat4(1.0f); // Initialize the model matrix as identity
        model = glm::translate(model, translation);
        model = glm::scale(model, scale);
        model = glm::rotate(model, rotationAngle, glm::vec3(0.0f, 0.0f, 1.0f));
        return model;
    }

} // namespace Engine
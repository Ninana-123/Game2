#include "pch.h"
#include "GraphicsSystem.h"
#include "AudioEngine.h"
#include "Logger.h"
#include "CollisionSystem.h"
#include "Vector2d.h"
namespace Engine
{

    Logger GraphicsLogger;

    GraphicsSystem::GraphicsSystem()
        : shader("Resource/Shaders/Basic.shader")
    {
    }

    GraphicsSystem::~GraphicsSystem()
    {
        // Cleanup any resources here
        // Terminate GLFW
        glfwTerminate();
    }

    void GraphicsSystem::InitializeGLEW() {
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

    void GraphicsSystem::Initialize() {

        Window = glfwGetCurrentContext();

        GraphicsSystem::InitializeGLEW();

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

        // Clear the color buffer
        glClear(GL_COLOR_BUFFER_BIT);

        int screenWidth, screenHeight;
        glfwGetWindowSize(Window, &screenWidth, &screenHeight);


        // load and initialize the shader
        InitializeShader();

        // initialize and bind textures
        InitializeTextures();

        //enable blending for transparency
        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));


        // set up projection and view matrices
        GraphicsSystem::proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
        GraphicsSystem::view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)); // Left translation

        /**************************************************************************************************/
          //define vertex array and indices
        float positions[] =
        {
       -60.0f,  -60.0f, 0.0f, 0.0f,    //0
        60.0f,  -60.0f, 1.0f, 0.0f,    //1
        60.0f,   60.0f, 1.0f, 1.0f,    //2
       -60.0f,   60.0f, 0.0f, 1.0f     //3
        };

        // Copy vtx_position into vtx_position member variable
       // std::copy(std::begin(positions), std::end(positions), std::begin(this->vtx_positions));

        unsigned int indices[] =
        {
            0, 1, 2,
            2, 3, 0
        };

        std::copy(std::begin(indices), std::end(indices), std::begin(this->indices));
        VertexBuffer vb(positions, 4 * 4 * sizeof(float));

        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        GraphicsSystem::va.AddBuffer(vb, layout);

        GraphicsSystem::ib.SetData(indices, 6);

        /**************************************************************************************************/

        VertexArray vaLines;
        // Define vertex array and indices for lines
        float linePositions[] =
        {
            -30.0f, -30.0f, 0.0f, 0.0f,
             30.0f, -30.0f, 1.0f, 0.0f,
             30.0f,  30.0f, 1.0f, 1.0f,
            -30.0f,  30.0f, 0.0f, 1.0f
        };

        VertexBuffer vbLines(linePositions, 4 * 4 * sizeof(float));

        VertexBufferLayout layoutLines;
        layoutLines.Push<float>(2);
        layoutLines.Push<float>(2);
        GraphicsSystem::vaLines.AddBuffer(vbLines, layoutLines);

        /**************************************************************************************************/
        //VertexArray vaSingleLine;
        //// Define vertex array and indices for a single line
        //float singleLinePositions[] =
        //{
        //    -10.0f, 0.0f,   // Start point
        //    10.0f, 0.0f     // End point
        //};

        //VertexBuffer vbSingleLine(singleLinePositions, 2 * 2 * sizeof(float));

        //VertexBufferLayout layoutSingleLine;
        //layoutSingleLine.Push<float>(2);
        //vaSingleLine.AddBuffer(vbSingleLine, layoutSingleLine);
        /**************************************************************************************************/

      // Define vertices for the background
        float backgroundPositions[] =
        {
            -static_cast<float>(screenWidth) / 2.0f, -static_cast<float>(screenHeight) / 2.0f, 0.0f, 0.0f,
             static_cast<float>(screenWidth) / 2.0f, -static_cast<float>(screenHeight) / 2.0f, 1.0f, 0.0f,
             static_cast<float>(screenWidth) / 2.0f,  static_cast<float>(screenHeight) / 2.0f, 1.0f, 1.0f,
            -static_cast<float>(screenWidth) / 2.0f,  static_cast<float> (screenHeight) / 2.0f, 0.0f, 1.0f
        };


        // Define indices for the background
        unsigned int backgroundIndices[] =
        {
            0, 1, 2,
            2, 3, 0
        };

        VertexBuffer vbBackground(backgroundPositions, 4 * 4 * sizeof(float));

        VertexBufferLayout layoutBackground;
        layoutBackground.Push<float>(2);
        layoutBackground.Push<float>(2);

        GraphicsSystem::vaBackground.AddBuffer(vbBackground, layoutBackground);
        GraphicsSystem::ibBackground.SetData(backgroundIndices, 6);

        /**************************************************************************************************/

        ib.Unbind();
        va.Unbind();
        vb.Unbind();

        vbLines.Unbind();
        //vbSingleLine.Unbind();

        vaBackground.Unbind();
        ibBackground.Unbind();

        shader.Unbind();
    }

    void GraphicsSystem::RenderBackground()
    {
        shader.Bind();
        textureC.Bind(0);
        shader.SetUniform1i("u_RenderTextured", 1); // Render textured
        shader.SetUniform1i("u_Texture", 0);
        /*glm::mat4 mvpMatrix(0.0f); 
        shader.SetUniformMat4f("u_MVP", mvpMatrix);*/

        vaBackground.Bind(); // Bind the background vertex array
        ibBackground.Bind(); // Bind the background index buffer

        renderer.Draw(vaBackground, ibBackground, shader);
        textureC.Unbind();
        shader.Unbind();
    }

    void GraphicsSystem::RenderTexturedEntity(const glm::mat4& mvpMatrix)
    {
        shader.Bind();

        double currentTime = glfwGetTime();
        double elapsedTime = currentTime - programStartTime;
        int textureIndex = static_cast<int>(elapsedTime / 3.0) % 2;

        if (textureIndex)
        {
            textureA.Bind(0);
        }
        else
        {
            textureB.Bind(0);
        }

        shader.SetUniform1i("u_RenderTextured", 1); // Render textured
        shader.SetUniform1i("u_Texture", 0);
        shader.SetUniformMat4f("u_MVP", mvpMatrix);

        renderer.Draw(va, ib, shader);
        shader.Unbind();
    }

    void GraphicsSystem::RenderLines(const glm::mat4& mvpMatrix)
    {
        // Bind the shader and set uniforms for line rendering
        shader.Bind();
        vaLines.Bind();
        shader.SetUniform1i("u_RenderTextured", 0); // no texture
        shader.SetUniform4f("u_Color", 0.0f, 0.0f, 0.0f, 1.0f); // Set the line color

        // Draw the lines directly without an IBO
        GLCall(glDrawArrays(GL_LINE_LOOP, 0, 4));

        // Debugging statement to print that the square lines are being drawn
        std::cout << "Drawing square lines..." << std::endl;

        shader.SetUniform1i("u_RenderTextured", 1);
        vaLines.Unbind();
        shader.Unbind();
    }

    void GraphicsSystem::RenderSingleLine(const glm::mat4& mvpMatrix, const glm::vec2& lineStart, const glm::vec2& lineEnd)
    {
        shader.Bind();
        vaLines.Bind();
        shader.SetUniform1i("u_RenderTextured", 0); // no texture
        shader.SetUniform4f("u_Color", 0.0f, 0.0f, 0.0f, 1.0f); // Set the line color

        // Update the line vertices based on the new start and end positions
        float linePositions[] =
        {
            lineStart.x, lineStart.y, 0.0f, 0.0f,
            lineEnd.x, lineEnd.y, 1.0f, 1.0f
        };

        VertexBuffer vbLines(linePositions, 2 * 4 * sizeof(float));
        VertexBufferLayout layoutLines;
        layoutLines.Push<float>(2);
        layoutLines.Push<float>(2);
        vaLines.AddBuffer(vbLines, layoutLines);

        // Draw a single straight line
        GLCall(glDrawArrays(GL_LINES, 0, 2));

        shader.SetUniform1i("u_RenderTextured", 1);
        vaLines.Unbind();
        shader.Unbind();
    }

    void GraphicsSystem::DrawColoredSquare(const glm::mat4& mvpMatrix)
    {
        // Bind the shader and set uniforms
        shader.Bind();
        shader.SetUniform4f("u_Color", 1.0f, 1.0f, 0.0f, 1.0f);
        shader.SetUniformMat4f("u_MVP", mvpMatrix);
        va.Bind();
        ib.Bind();
        // Render the square
        renderer.Draw(va, ib, shader);
        shader.Unbind();
    }


    void GraphicsSystem::Update(std::unordered_map<EntityID, std::unique_ptr<Entity>>* entities)
    {
        int width, height;
        glfwGetWindowSize(Window, &width, &height);
        UpdateViewport(width, height);
        renderer.Clear();
        RenderBackground();

        for (const auto& entityPair : *entities)
        {
            Entity* entity = entityPair.second.get();

            if (entity->HasComponent(ComponentType::Transform))
            {

                //Assign reference to transform component
                TransformComponent* transform = dynamic_cast<TransformComponent*>(entity->GetComponent(ComponentType::Transform));

                glm::vec3 transA(transform->x, transform->y, 0);
                float rotationA = transform->rot;
                glm::vec3 localScale(transform->scaleX, transform->scaleY, 1.0f);

                // Update the line start and end positions based on user input
                glm::vec2 lineStart(transA.x, transA.y);
                glm::vec2 lineEnd = lineStart + glm::vec2(70.0f, 0.0f); // Adjust as needed

                // Apply transformations from UpdateTransformations
                glm::mat4 modelA = SetupModelMatrix(transA, rotationA, localScale);
                glm::mat4 mvpA = proj * view * modelA;

                // Get the current state of the 'P' key
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
                    RenderTexturedEntity(mvpA);
                    RenderLines(mvpA);

                }
                else
                {

                    DrawColoredSquare(mvpA);
                }
                RenderSingleLine(mvpA, lineStart, lineEnd);

                transform->x = static_cast<int>(transA.x);
                transform->y = static_cast<int>(transA.y);
            }
        }
        //GraphicsLogger.Log(LogLevel::Debug, "Currently updating graphics");
    }


    void GraphicsSystem::UpdateViewport(int width, int height)
    {
        glViewport(0, 0, width, height);
        proj = glm::ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height), -1.0f, 1.0f);
    }

    void GraphicsSystem::InitializeShader()
    {
        shader.LoadShader("Resource/Shaders/Basic.shader");

        shader.Initialize();
        shader.Bind();

        shader.SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
    }

    void GraphicsSystem::InitializeTextures()
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
            textureB.Bind(0); // Bind the texture to a different texture unit (e.g., unit 1)
        }


        if (!textureC.Load("Resource/Texture/Background.png")) // Check for texture loading errors
        {
            GraphicsLogger.Log(LogLevel::Error, "Failed to load Texture C.");
            // Handle the error as needed, e.g., return or throw an exception
        }
        else {
            textureC.InitGL();
            textureC.Bind(0); // Bind the texture to a different texture unit (e.g., unit 1)
        }


        if (!textureC.Load("Resource/Texture/Background.png")) // Check for texture loading errors
        {
            GraphicsLogger.Log(LogLevel::Error, "Failed to load Texture B.");
            // Handle the error as needed, e.g., return or throw an exception
        }
        else {
            textureC.InitGL();
            textureC.Bind(1); // Bind the texture to a different texture unit (e.g., unit 1)
        }
    }

    // Function to toggle between textured and plain squares
    void GraphicsSystem::ToggleRenderMode()
    {
        renderTexturedSquare = !renderTexturedSquare;
        shader.Bind();
        shader.SetUniform1i("u_RenderTextured", renderTexturedSquare ? 1 : 0);
    }

    glm::mat4 GraphicsSystem::SetupModelMatrix(const glm::vec3& translation, float rotationAngle, const glm::vec3& scale)
    {
        int screenWidth, screenHeight;
        glfwGetWindowSize(Window, &screenWidth, &screenHeight);

        glm::mat4 model = glm::mat4(1.0f); // Initialize the model matrix as identity

        // Translate the object to the center of the screen
        model = glm::translate(model, glm::vec3(static_cast<float>(screenWidth) / 2.0f, static_cast<float>(screenHeight) / 2.0f, 0.0f));

        // Apply the provided translation
        model = glm::translate(model, translation);

        model = glm::scale(model, scale);
        model = glm::rotate(model, rotationAngle, glm::vec3(0.0f, 0.0f, 1.0f));
        return model;
    }


} // namespace Engine

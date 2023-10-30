/******************************************************************************/
/*!
\file		GraphicSystem.cpp
\author 	Wayne Kwok Jun Lin
\par    	email: k.junlinwayne@digipen.edu
\date   	August 29, 2023
\brief		This file contains the implementation of the GraphicsSystem class.
            It handles initializing OpenGL, rendering entities, and managing
            rendering modes.

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#include "pch.h"
#include "GraphicsSystem.h"
#include "AudioEngine.h"
#include "Logger.h"
#include "CollisionSystem.h"
#include "Vector2d.h"
#include"Font.h"
#pragma warning(disable: 4100) // disable "unreferenced parameter" 
namespace Engine
{
    Logger GraphicsLogger;
   

    /*!
   * \brief GraphicsSystem constructor.
   *
   * This constructor initializes a GraphicsSystem object and sets up the
   * default shader and textures.
   */
    GraphicsSystem::GraphicsSystem()
        : shader("Resource/Shaders/Basic.shader")
    {
    }

    /*!
   * \brief Initialize the GLEW library.
   *
   * This function initializes the GLEW (OpenGL Extension Wrangler Library)
   * and logs the initialization result.
   */
    void GraphicsSystem::InitializeGLEW() {
        // Initialize GLEW
        GLenum glewInitResult = glewInit();
        if (glewInitResult != GLEW_OK)
        {
            // Log the error using your existing Logger
            GraphicsLogger.Log(LogLevel::Error, "GLEW failed to initialize: " + std::string(reinterpret_cast<const char*>(glewGetErrorString(glewInitResult))));
            glfwTerminate();
        }
        else
            GraphicsLogger.Log(LogLevel::Debug, "GLEW successfully initialized");
    }

    /*!
   * \brief Initialize the GraphicsSystem.
   *
   * This function initializes the GraphicsSystem by setting up OpenGL,
   * loading shaders, and initializing textures.
   */
    void GraphicsSystem::Initialize() {

        Window = glfwGetCurrentContext();

        GraphicsSystem::InitializeGLEW();

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

        // Clear the color buffer
        glClear(GL_COLOR_BUFFER_BIT);

        int screenWidth, screenHeight;
        glfwGetWindowSize(Window, &screenWidth, &screenHeight);
        //std::cout << "Screen Width: " << screenWidth << ", Screen Height: " << screenHeight << std::endl;

        // load and initialize the shader
        InitializeShader();

        // initialize and bind textures
        InitializeTextures();

        Font::font_data myFont;
        myFont.init("resources/fonts/Antonio-Bold.ttf", 24);  // Replace with your actual font file

        // Store the initialized font object in a member variable for later use
        this->ft_font = myFont;

        //enable blending for transparency
        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        const float fscreenWidth = 1280.0f;
        const float fscreenHeight = 720.0f;

        // set up projection and view matrices
        GraphicsSystem::proj = glm::ortho(0.0f, fscreenWidth, 0.0f, fscreenHeight, -1.0f, 1.0f);
        GraphicsSystem::view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)); // Left translation

        /**************************************************************************************************/
        //define vertex array and indices
        float quadPositions[] =
        {
       -60.0f,  -60.0f, 0.0f, 0.0f,    //0
        60.0f,  -60.0f, 1.0f, 0.0f,    //1
        60.0f,   60.0f, 1.0f, 1.0f,    //2
       -60.0f,   60.0f, 0.0f, 1.0f     //3
        };

        // Copy vtx_position into vtx_position member variable
        std::copy(std::begin(quadPositions), std::end(quadPositions), std::begin(this->vtx_positions));

        unsigned int localIndices[] =
        {
            0, 1, 2,
            2, 3, 0
        };

        std::copy(std::begin(localIndices), std::end(localIndices), std::begin(this->indices));
        VertexBuffer vb(quadPositions, 4 * 4 * sizeof(float));

        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        GraphicsSystem::va.AddBuffer(vb, layout);

        GraphicsSystem::ib.SetData(localIndices, 6);

        /**************************************************************************************************/
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
        // Define vertices for the background
        float backgroundPositions[] =
        {
            -static_cast<float>(screenWidth) / 2.0f, -static_cast<float>(screenHeight) / 2.0f, 0.0f, 0.0f,
             static_cast<float>(screenWidth) / 2.0f, -static_cast<float>(screenHeight) / 2.0f, 1.0f, 0.0f,
             static_cast<float>(screenWidth) / 2.0f,  static_cast<float>(screenHeight) / 2.0f, 1.0f, 1.0f,
            -static_cast<float>(screenWidth) / 2.0f,  static_cast<float>(screenHeight) / 2.0f, 0.0f, 1.0f
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

        vaBackground.Unbind();
        ibBackground.Unbind();

        shader.Unbind();
    }

    /*!
    * \brief Initialize the shader used for rendering.
    *
    * This function loads and initializes the shader used for rendering
    * and sets its initial uniform values.
    */
    void GraphicsSystem::InitializeShader()
    {
        shader.LoadShader("Resource/Shaders/Basic.shader");

        shader.Initialize();
        shader.Bind();

        shader.SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
    }

    /*!
    * \brief Initialize textures used for rendering.
    *
    * This function loads and initializes textures used for rendering.
    */
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
            textureC.Bind(0); 
        }
    }

    void GraphicsSystem::RenderBackground(const glm::mat4& mvpMatrix)
    {
        shader.Bind();
        textureC.Bind(0);
        shader.SetUniform1i("u_RenderTextured", 1); // Render textured
        shader.SetUniform1i("u_Texture", 0);
        shader.SetUniformMat4f("u_MVP", mvpMatrix);
        vaBackground.Bind(); // Bind the background vertex array
        ibBackground.Bind(); // Bind the background index buffer

        renderer.Draw(vaBackground, ibBackground, shader);
        textureC.Unbind();
        shader.Unbind();
    }

    /*!
     * \brief Render a textured entity.
     *
     * This function renders a textured entity with the specified MVP matrix and alternates
     * between two textures based on time.
     *
     * \param mvpMatrix The Model-View-Projection matrix for rendering.
     */

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

    /*!
     * \brief Render lines.
     *
     * This function renders lines with the specified MVP matrix.
     *
     * \param mvpMatrix The Model-View-Projection matrix for rendering.
     */
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

    /*!
   * \brief Render a single line.
   *
   * This function renders a single line with the specified MVP matrix, start, and end positions.
   *
   * \param mvpMatrix The Model-View-Projection matrix for rendering.
   * \param lineStart The starting position of the line.
   * \param lineEnd The ending position of the line.
   */
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

    /*!
    * \brief Render a single colored square.
    *
    * This function renders a single colored square with the specified MVP matrix.
    *
    * \param mvpMatrix The Model-View-Projection matrix for rendering.
    */
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

    /*!
     * \brief Update the GraphicsSystem.
     *
     * This function updates the GraphicsSystem by rendering entities and handling
     * user input for toggling rendering modes.
     *
     * \param entities A pointer to a map of entities.
     */
    void GraphicsSystem::Update(std::unordered_map<EntityID, std::unique_ptr<Entity>>* entities)
    {
        int width, height;
        glfwGetWindowSize(Window, &width, &height);
        UpdateViewport(width, height);
        renderer.Clear();
       

        for (const auto& entityPair : *entities)
        {
            Entity* entity = entityPair.second.get();

            if (entity->HasComponent(ComponentType::Transform))
            {
                try
                {
                    // Assign reference to transform component
                    TransformComponent* transform = dynamic_cast<TransformComponent*>(entity->GetComponent(ComponentType::Transform));

                    if (!transform)
                    {
                        // Log the error using your existing Logger
                        GraphicsLogger.Log(LogLevel::Error, "Transform component not found for an entity.");
                        continue; // Continue processing other entities
                    }

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

                    if (entity->HasComponent(ComponentType::Physics))
                    {
                        // Check if there's a change in the 'P' key state
                        if (currentPState && !previousPState)
                        {
                            // Toggle the rendering mode
                            ToggleRenderMode();
                        }

                        // Update the previous 'P' key state
                        previousPState = currentPState;

                        if (!renderTexturedSquare)
                        {
                            RenderTexturedEntity(mvpA);
                            RenderLines(mvpA);
                        }
                        else
                        {
                            DrawColoredSquare(mvpA);
                        }
                    }
                    else
                    {
                        RenderBackground(mvpA); //Assuming background only has Transform
                    }
                    const char* textToRender = "Hello, World!";
                    float textX = transA.x; // Adjust the X position
                    float textY = transA.y - 30.0f; // Adjust the Y position
                    font.print(ft_font, textX, textY, textToRender); // Assuming 'font' is an instance of the Font class



                    //RenderSingleLine(mvpA, lineStart, lineEnd
                    transform->x = static_cast<int>(transA.x);
                    transform->y = static_cast<int>(transA.y);
                }
                catch (const std::exception& ex)
                {
                    GraphicsLogger.Log(LogLevel::Error, "Graphics error: " + std::string(ex.what()));
                }
            }
        }
        //GraphicsLogger.Log(LogLevel::Debug, "Currently updating graphics");
    }

    void GraphicsSystem::UpdateViewport(int width, int height)
    {
        glViewport(0, 0, width, height);
        proj = glm::ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height), -1.0f, 1.0f);
    }

    /*!
     * \brief Toggle the rendering mode.
     *
     * This function toggles between textured and plain squares for rendering.
     */
    void GraphicsSystem::ToggleRenderMode()
    {
        renderTexturedSquare = !renderTexturedSquare;
        shader.Bind();
        shader.SetUniform1i("u_RenderTextured", renderTexturedSquare ? 1 : 0);
    }


    /*!
     * \brief Setup the model matrix for an entity.
     *
     * This function sets up the model matrix for an entity based on translation,
     * rotation, and scale parameters.
     *
     * \param translation The translation vector.
     * \param rotationAngle The rotation angle in radians.
     * \param scale The scale vector.
     *
     * \return The model matrix for the entity.
     */
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

    GraphicsSystem::~GraphicsSystem()
    {
        // Cleanup any resources here
        // Terminate GLFW
        glfwTerminate();
    }
} // namespace Engine
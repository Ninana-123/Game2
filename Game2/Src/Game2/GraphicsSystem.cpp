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
#include "Input.h"
#include "AnimationComponent.h"
#include "Animation.h"

#pragma warning(disable: 4100) // disable "unreferenced parameter" 
namespace Engine
{
    // Logger GraphicsLogger;
    Input InputController;


    /*!
   * \brief GraphicsSystem constructor.
   *
   * This constructor initializes a GraphicsSystem object and sets up the
   * default shader and textures.
   */
    GraphicsSystem::GraphicsSystem()
        : shader("Resource/Shaders/Shader.vert", "Resource/Shaders/Shader.frag",
            "Resource/Shaders/Shader2.vert", "Resource/Shaders/Shader2.frag"),
        m_Camera(-640.0f, 640.0f, -360.0f, 360.0f)
    {
    }
    GraphicsSystem::GraphicsSystem(std::shared_ptr<Engine::AssetManager> assetManager,std::shared_ptr<Engine::EntityManager> entityManager)
        : assetManager(assetManager), shader("Resource/Shaders/Shader.vert", "Resource/Shaders/Shader.frag",
            "Resource/Shaders/Shader2.vert", "Resource/Shaders/Shader2.frag"),
            entityManager(entityManager),
             m_Camera(-640.0f, 640.0f, -360.0f, 360.0f)
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
           
            Logger::GetInstance().Log(LogLevel::Error, "GLEW failed to initialize: "
                + std::string(reinterpret_cast<const char*>(glewGetErrorString(glewInitResult))));
            glfwTerminate();
        }
        else
            Logger::GetInstance().Log(LogLevel::Debug, "GLEW successfully initialized");
    }

    /*!
   * \brief Initialize the GraphicsSystem.
   *
   * This function initializes the GraphicsSystem by setting up OpenGL,
   * loading shaders, and initializing textures.
   */
    void GraphicsSystem::Initialize() {
        Window = glfwGetCurrentContext();

        InitializeGLEW();

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Load and initialize the shader
        try {
            InitializeShader();
        }
        catch (const std::runtime_error& e) {
            // Handle shader initialization error
            throw std::runtime_error("Shader initialization failed: " + std::string(e.what()));
        }

        // Initialize and bind textures
        try {
            InitializeTextures();
        }
        catch (const std::runtime_error& e) {
            // Handle texture initialization error
            throw std::runtime_error("Texture initialization failed: " + std::string(e.what()));
        }

        // Enable blending for transparency
        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        int screenWidth, screenHeight;
        glfwGetWindowSize(Window, &screenWidth, &screenHeight);

        // Set up projection and view matrices
        proj = glm::ortho(0.0f, static_cast<float>(screenWidth), 0.0f, static_cast<float>(screenHeight), -1.0f, 1.0f);
        view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)); // Left translation

        /**************************************************************************************************/
        //define vertex array and indices
        float quadPositions[] =
        {
           -50.f, -50.f, 0.0f, 0.0f,  // bottom-left
            50.f, -50.f, 1.0f, 0.0f,  // bottom-right
            50.f,  50.f, 1.0f, 1.0f,  // top-right
           -50.f,  50.f, 0.0f, 1.0f   // top-left
        };
        vtx_positions_quad.resize(16);
        std::copy(std::begin(vtx_positions_localquad), std::end(vtx_positions_localquad), std::begin(this->vtx_positions_quad));

        unsigned int localIndices[] = {
            0, 1, 2,
            2, 3, 0
        };
        indices_quad.assign(std::begin(localIndices), std::end(localIndices));

        std::copy(std::begin(localIndices), std::end(localIndices), std::begin(this->indices));
        VertexBuffer vb(quadPositions, 4 * 4 * sizeof(float));

        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);

        GraphicsSystem::ib.SetData(localIndices, 6);

        /**************************************************************************************************/
        // Define vertex array and indices for lines
        float linePositions[] =
        {
           -50.f, -50.f, 0.0f, 0.0f,  // bottom-left
            50.f, -50.f, 1.0f, 0.0f,  // bottom-right
            50.f,  50.f, 1.0f, 1.0f,  // top-right
           -50.f,  50.f, 0.0f, 1.0f   // top-left
        };
        vtx_positions_lines.resize(16);
        std::copy(std::begin(vtx_positions_local_lines), std::end(vtx_positions_local_lines), std::begin(this->vtx_positions_lines));

        // Define vertex array and indices for the background
        std::vector<float> vtx_positions_localbackground = {
            -static_cast<float>(screenWidth) / 2.0f, -static_cast<float>(screenHeight) / 2.0f, 0.0f, 0.0f,
             static_cast<float>(screenWidth) / 2.0f, -static_cast<float>(screenHeight) / 2.0f, 1.0f, 0.0f,
             static_cast<float>(screenWidth) / 2.0f,  static_cast<float>(screenHeight) / 2.0f, 1.0f, 1.0f,
            -static_cast<float>(screenWidth) / 2.0f,  static_cast<float>(screenHeight) / 2.0f, 0.0f, 1.0f
        };
        vtx_positions_background.resize(16);
        std::copy(std::begin(vtx_positions_localbackground), std::end(vtx_positions_localbackground), std::begin(this->vtx_positions_background));

        // Create vertex buffers and layouts for quad, lines, and background
        try {
            VertexBuffer vbQuad(vtx_positions_quad.data(), static_cast<unsigned int>(vtx_positions_quad.size() * sizeof(float)));
            VertexBuffer vbLines(vtx_positions_lines.data(), static_cast<unsigned int>(vtx_positions_lines.size() * sizeof(float)));
            VertexBuffer vbBackground(vtx_positions_background.data(), static_cast<unsigned int>(vtx_positions_background.size() * sizeof(float)));

            VertexBufferLayout layout;
            layout.Push<float>(2);
            layout.Push<float>(2);

            vaQuad.AddBuffer(vbQuad, layout);
            vaLines.AddBuffer(vbLines, layout);
            vaBackground.AddBuffer(vbBackground, layout);

        GraphicsSystem::va.AddBuffer(vb, layout);

        GraphicsSystem::vaBackground.AddBuffer(vbBackground, layoutBackground);
        GraphicsSystem::ibBackground.SetData(backgroundIndices, 6);

        // Unbind buffers and shader
        ibQuad.Unbind();
        vaQuad.Unbind();
        ibBackground.Unbind();
        vaBackground.Unbind();
        vaLines.Unbind();
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
        // Initialize the shader object (load shader source files and compile them)
        shader.Initialize();
        shader.Bind();
        //GraphicsLogger.Log(LogLevel::Debug, "Current Shader Set: " + std::to_string(shader.m_CurrentShaderSet));

        std::string vertexShaderPath;
        std::string fragmentShaderPath;

        // Determine which set of shaders to use
        if (shader.GetCurrentShaderSet() == 1)
        {
            vertexShaderPath = "Resource/Shaders/Shader.vert";
            fragmentShaderPath = "Resource/Shaders/Shader.frag";
            Logger::GetInstance().Log(LogLevel::Debug, "Loading Shader Set 1...");
        }
        else if (shader.GetCurrentShaderSet() == 2)
        {
            vertexShaderPath = "Resource/Shaders/Shader2.vert";
            fragmentShaderPath = "Resource/Shaders/Shader2.frag";
            Logger::GetInstance().Log(LogLevel::Debug, "Loading Shader Set 2...");
        }
        else
        {
            throw std::runtime_error("Invalid shader set specified: " + std::to_string(shader.GetCurrentShaderSet()));
        }

        // Load shader source code from files
        std::string vertexShaderSource = shader.LoadShaderSource(vertexShaderPath);
        std::string fragmentShaderSource = shader.LoadShaderSource(fragmentShaderPath);

        // Check if shader source files were successfully loaded
        if (!vertexShaderSource.empty() && !fragmentShaderSource.empty())
        {
            // Compile shaders and create shader program
            unsigned int shaderProgram = shader.CreateShader(vertexShaderSource, fragmentShaderSource);

            // Check for shader compilation and linking errors
            if (shaderProgram != 0)
            {
                // Shader compilation and linking successful
                Logger::GetInstance().Log(LogLevel::Debug, "Shader compilation and linking successful.");

                // Store the shader program ID in the shader class based on the shader set being used
                shader.SetShaderProgram(useShaderSet1 ? 1 : 2, shaderProgram);

                // Check for additional shader compilation errors (if any)
                shader.CheckShaderCompilation(shaderProgram, "Shader Set");
            }
            else
            {
                // Shader compilation or linking failed
                throw std::runtime_error("Shader compilation or linking failed.");
            }
        }
        else
        {
            // Shader source files were not loaded successfully
            throw std::runtime_error("Failed to load shader source files.");
        }

        shader.SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);

        // Unbind the shader program after setting up uniforms
        shader.Unbind();
    }

    /*!
    * \brief Initialize textures used for rendering.
    *
    * This function loads and initializes textures used for rendering.
    */
    void GraphicsSystem::InitializeTextures()
    {
        //if (!textureA.Load("Resource/Texture/InfantryWalking.png")) // Check for texture loading errors
        //{
        //    GraphicsLogger.Log(LogLevel::Error, "Failed to load Texture A.");
        //    // Handle the error as needed, e.g., return or throw an exception
        //}
        //else {
        //    textureA.InitGL();
        //    textureA.Bind(0);
        //}

        //if (!textureB.Load("Resource/Texture/Tank.png")) // Check for texture loading errors
        //{
        //    GraphicsLogger.Log(LogLevel::Error, "Failed to load Texture B.");
        //    // Handle the error as needed, e.g., return or throw an exception
        //}
        //else {
        //    textureB.InitGL();
        //    textureB.Bind(1); // Bind the texture to a different texture unit (e.g., unit 1)
        //}

        //textureC = *(assetManager->getTexture("Background"));
        //// Handle the error as needed, e.g., return or throw an exception
        //textureC.InitGL();
        //textureC.Bind(0);

        textures.resize(TextureClassCount);
        for (int i = 0; i < TextureClassCount; i++) {
            textures[i] = *(assetManager->getTexture(i));
            textures[i].InitGL();
            textures[i].Bind(0);
        }
    }

    void GraphicsSystem::RenderBackground(const glm::mat4& mvpMatrix)
    {
        shader.Bind();
        textures[Background].Bind(0);
        shader.SetUniform1i("u_RenderTextured", 1); // Render textured
        shader.SetUniform1i("u_Texture", 0);
        shader.SetUniformMat4f("u_MVP", m_Camera.GetViewProjectionMatrix());

        const glm::mat4& viewProjectionMatrix = m_Camera.GetViewProjectionMatrix();
        /*  std::cout << "BACKGROUND MATRIX: " << '\n' << " ";
          for (int i = 0; i < 4; i++) {
              for (int j = 0; j < 4; j++) {

                  std::cout << viewProjectionMatrix[i][j] << " ";
              }
              std::cout << std::endl;
          }*/

        vaBackground.Bind(); // Bind the background vertex array
        ibBackground.Bind(); // Bind the background index buffer

        renderer.Draw(vaBackground, ibBackground, shader);
        textures[Background].Unbind();
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
   // void GraphicsSystem::RenderTexturedEntity(const glm::mat4& mvpMatrix)

    void GraphicsSystem::RenderTexturedEntity(const glm::mat4& mvpMatrix, Entity* entity)
    {
        if (!entity->HasComponent(ComponentType::Texture))
            return;

        TextureComponent* texture = dynamic_cast<TextureComponent*>(entity->GetComponent(ComponentType::Texture));

        if (texture != nullptr)
        {
            textures[texture->textureClass].Bind(0);
        }

        shader.Bind();
        //textureA.Bind(0);

        // Calculate deltaTime (time since the last frame)
        static double lastTime = glfwGetTime();
        double currentTime = glfwGetTime();
        double deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        float frameRate = 10.0f;
        float horizontalFrames = 6.0f; // Number of horizontal frames
        float verticalFrames = 1.0f; // Number of vertical frames
        float Length = 1536.0f; // length of sprite sheet
        Anim_Mode playMode = Anim_Mode::LOOP;

        // Create a static animation object if not created already
        static Animation animation(frameRate, horizontalFrames, verticalFrames, playMode);

        // Play the animation
        animation.Play();

        // Update the animation with deltaTime
        animation.Update(static_cast<float>(deltaTime));

        // Get the current frame index
        int currentFrame = animation.GetCurrentFrame();

        // Calculate the texture offset based on the current frame
        float frameWidth = 1.0f/horizontalFrames;
        float frameHeight = 1.0f / verticalFrames;
        float texCoordX = currentFrame * frameWidth;
        //float texCoordY = currentRow * frameHeight;

        // Set the texture offset in the shader
        shader.SetUniform1f("texCoordX", texCoordX);
        //shader.SetUniform1f("texCoordY", texCoordY);


        shader.SetUniform1f("u_FrameCount", horizontalFrames);
        shader.SetUniform1f("u_FrameWidth", frameWidth);
        shader.SetUniform1f("u_FrameHeight", frameHeight);
        shader.SetUniform1i("u_CurrentFrame", currentFrame);

        glm::mat4 result = mvpMatrix * m_Camera.GetViewMatrix();
        shader.SetUniformMat4f("u_MVP", result);

        // Debugging: Print out the values
        std::cout << "Frame Width: " << frameWidth << "TexCoordX: " << texCoordX << "Current Frame: " << currentFrame << std::endl;
        va.Bind();
        ib.Bind();

        // Render the entity
        renderer.Draw(va, ib, shader);

        // Unbind the texture and shader
       // textureA.Unbind();
        shader.Unbind();
    }
    //void GraphicsSystem::RenderTexturedEntity(const glm::mat4& mvpMatrix, Entity* entity)
    //{
    //  

    //        if (!entity->HasComponent(ComponentType::Texture))
    //        {
    //            return;
    //        }
    //        TextureComponent* texture = dynamic_cast<TextureComponent*>(entity->GetComponent(ComponentType::Texture));

    //        if (texture != nullptr)
    //        {
    //            textures[texture->textureClass].Bind(0);
    //        }

    //        shader.Bind();
    //        va.Bind();
    //        ib.Bind();

    //        // Check if the entity has an AnimationComponent
    //        if (entity->HasComponent(ComponentType::Animation))
    //        {
    //            AnimationComponent* Animation = dynamic_cast<AnimationComponent*>(entity->GetComponent(ComponentType:: Animation));
    //            // Calculate deltaTime (time since the last frame)
    //            static double lastTime = glfwGetTime();
    //            double currentTime = glfwGetTime();
    //            double deltaTime = currentTime - lastTime;
    //            lastTime = currentTime;

    //            float frameRate = 1.0f;
    //            float horizontalFrames = 6.0f; // Number of horizontal frames
    //            float verticalFrames = 1.0f; // Number of vertical frames
    //            float Length = 1536.0f; // length of sprite sheet
    //            Anim_Mode playMode = Anim_Mode::LOOP;

    //            // Create a static animation object if not created already
    //            static AnimationComponent AnimationComponent(frameRate, horizontalFrames, verticalFrames, playMode);

    //            // Play the animation
    //            AnimationComponent.Play();

    //            // Update the animation with deltaTime
    //            AnimationComponent.Update(static_cast<float>(deltaTime));

    //            // Get the current frame index
    //            int currentFrame = AnimationComponent.GetCurrentFrame();

    //            // Calculate the texture offset based on the current frame
    //            float frameWidth = 1.0f / horizontalFrames;
    //            float frameHeight = 1.0f / verticalFrames;
    //            float texCoordX = currentFrame * frameWidth;
    //            //float texCoordY = currentRow * frameHeight;

    //            // Set the texture offset in the shader
    //            shader.SetUniform1f("texCoordX", texCoordX);
    //            //shader.SetUniform1f("texCoordY", texCoordY);
    //            shader.SetUniform1f("u_FrameCount", horizontalFrames);
    //            shader.SetUniform1f("u_FrameWidth", frameWidth);
    //            shader.SetUniform1f("u_FrameHeight", frameHeight);
    //            shader.SetUniform1i("u_CurrentFrame", currentFrame);
    //        }

    //        glm::mat4 result = mvpMatrix * m_Camera.GetViewMatrix();
    //        shader.SetUniformMat4f("u_MVP", result);

    //        // Debugging: Print out the values
    //        // std::cout << "Frame Width: " << frameWidth << "TexCoordX: " << texCoordX << "Current Frame: " << currentFrame << std::endl;
    //        /*  va.Bind();
    //        ib.Bind();*/

    //        // Render the entity
    //        renderer.Draw(va, ib, shader);

    //        // Unbind the texture and shader
    //        //textureA.Unbind();
    //    
    //    shader.Unbind();
    //}



    /*!
     * \brief Render lines.
     *
     * This function renders lines with the specified MVP matrix.
     *
     * \param mvpMatrix The Model-View-Projection matrix for rendering.
     */
    void GraphicsSystem::RenderLines(const glm::mat4& mvpMatrix)
    {
        try {
            // Bind the shader and set uniforms for line rendering
            shader.Bind();
            vaLines.Bind();
            shader.SetUniform1i("u_RenderTextured", 0); // no texture
            shader.SetUniform4f("u_Color", 0.0f, 0.0f, 0.0f, 1.0f); // Set the line color

            // Draw the lines directly without an IBO
            GLCall(glDrawArrays(GL_LINE_LOOP, 0, 4));

        shader.SetUniform1i("u_RenderTextured", 1);
        vaLines.Unbind();
       // textureA.Unbind();
        
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
        try {
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
        catch (const std::exception& e) {
            
            GraphicsLogger.Log(LogLevel::Error, "Render single line error: " + std::string(e.what()));
        }
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
        shader.SetUniformMat4f("u_MVP", m_Camera.GetViewProjectionMatrix());

            vaQuad.Bind();
            ibQuad.Bind();
            // Render the square
            renderer.Draw(vaQuad, ibQuad, shader);
            shader.Unbind();
        }
        catch (const std::exception& e) {
            
            GraphicsLogger.Log(LogLevel::Error, "Draw colored square error: " + std::string(e.what()));

        }
    }

    /*!
     * \brief Update the GraphicsSystem.
     *
     * This function updates the GraphicsSystem by rendering entities and handling
     * user input for toggling rendering modes.
     *
     * \param entities A pointer to a map of entities.
     */
    void GraphicsSystem::Update(std::unordered_map<EntityID, std::unique_ptr<Entity>>* entities) {
        int width, height;
        glfwGetWindowSize(Window, &width, &height);
        UpdateViewport(width, height);
        renderer.Clear();

        // Get the current state of the 'S' key
        bool currentSState = glfwGetKey(this->Window, GLFW_KEY_S) == GLFW_PRESS;
        // std::cout << "S Key State: " << currentSState << std::endl;

         // Check if there's a change in the 'S' key state
        //std::cout << "S Key State: " << currentSState << std::endl;
        
        // Check if there's a change in the 'S' key state
        if (currentSState && !previousSState) {
            // Toggle the shader state
            ToggleShaderSet();
        }
        // Update the previous 'S' key state
        previousSState = currentSState;

        std::vector<glm::vec2> batchedPositions;
        std::vector<glm::vec2> batchedTexCoords;
        std::vector<float> batchedTexIndices;

        for (const auto& entityPair : *entities) {
            //std::cout << "Processing Entity ID: " << entityPair.first << std::endl;
            Entity* entity = entityPair.second.get();
            std::cout << "Entity ID: " << entityPair.first << std::endl;
            std::cout << "Has TransformComponent: " << entity->HasComponent(ComponentType::Transform) << std::endl;
            std::cout << "Has TextureComponent: " << entity->HasComponent(ComponentType::Texture) << std::endl;

            if (entity->HasComponent(ComponentType::Transform)) {
                try {
                    // Assign reference to transform component
                    TransformComponent* transform = dynamic_cast<TransformComponent*>(entity->GetComponent(ComponentType::Transform));

                    if (!transform) {
                        // Log the error using your existing Logger
                        Logger::GetInstance().Log(LogLevel::Error, "Transform component not found for an entity.");
                        continue; // Continue processing other entities
                    }

                    glm::vec3 transA(transform->position.x, transform->position.y, 0);
                    float rotationA = transform->rot;
                    glm::vec3 localScale(transform->scaleX, transform->scaleY, 1.0f);

                    // Update the line start and end positions based on user input
                    glm::vec2 lineStart(transA.x, transA.y);
                    glm::vec2 lineEnd = lineStart + glm::vec2(70.0f, 0.0f); // Adjust as needed

                    // Apply transformations from UpdateTransformations
                    glm::mat4 modelA = SetupModelMatrix(transA, rotationA, localScale);
                    glm::mat4 mvpA = proj * view * modelA;
                    // glm::mat4 mvpA = proj* m_Camera.GetViewProjectionMatrix()  * modelA;



                     // Get the current state of the 'P' key
                    bool currentPState = glfwGetKey(this->Window, GLFW_KEY_P) == GLFW_PRESS;

                    if (entity->HasComponent(ComponentType::Texture))
                    {
                        TextureComponent* texture = dynamic_cast<TextureComponent*>(entity->GetComponent(ComponentType::Texture));

                        // Check if there's a change in the 'P' key state
                        if (currentPState && !previousPState) {
                            // Toggle the rendering mode
                            ToggleRenderMode();
                        }

                        // Update the previous 'P' key state
                        previousPState = currentPState;
                    }

                        if (!renderTexturedSquare)
                        {
                            if(texture->textureClass == Background)
                                RenderBackground(mvpA);
                            else {
                                RenderTexturedEntity(mvpA, entity); // Here, we pass the specific entity
                                RenderLines(mvpA);
                            }
                        }
                        else
                        {
                            DrawColoredSquare(mvpA);

                        }
                    }
                    
                    //RenderSingleLine(mvpA, lineStart, lineEnd
                    transform->position.x = transA.x;
                    transform->position.y = transA.y;
                }
                catch (const std::exception& ex)
                {
                    Logger::GetInstance().Log(LogLevel::Error, ("Graphics error: " + std::string(ex.what())).c_str());
                }
            }
        }

        // Call the batch rendering function (assuming RenderBatchedEntities is a member function)
        RenderBatchedEntities(batchedPositions, batchedTexCoords, batchedTexIndices);
        //GraphicsLogger.Log(LogLevel::Debug, "Currently updating graphics");

        // CAMERA
        m_Camera.UpdatePosition(InputController, CameraSpeed);




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
        std::cout << "Render Textured Square: " << (renderTexturedSquare ? "Enabled" : "Disabled") << std::endl;

        shader.Bind();
        shader.SetUniform1i("u_RenderTextured", renderTexturedSquare ? 1 : 0);
        std::cout << "Shader Uniform 'u_RenderTextured' set to: " << (renderTexturedSquare ? "1" : "0") << std::endl;
    }

    void GraphicsSystem::ToggleShaderSet()
    {
        try {
            std::cout << "ToggleShaderSet() called!" << std::endl;
            if (shader.GetCurrentShaderSet() == 1) {
                shader.SetActiveShaderSet(2);
            }
            else {
                shader.SetActiveShaderSet(1);
            }
            std::cout << "Shader Set Toggled: " << (shader.GetCurrentShaderSet() == 1 ? "Shader Set 1" : "Shader Set 2") << std::endl;

            // Attempt to reinitialize shaders based on the new set
            InitializeShader();
        }
        catch (const std::exception& e) {

            GraphicsLogger.Log(LogLevel::Error, "Shader set toggle error: " + std::string(e.what()));
        }
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

        // Calculate the position for your object at the center of the screen
        glm::vec3 objectPosition = glm::vec3(static_cast<float>(screenWidth) / 2.0f, static_cast<float>(screenHeight) / 2.0f, 0.0f);

        glm::mat4 model = glm::mat4(1.0f); // Initialize the model matrix as identity

        // Translate the object to the calculated center position
        model = glm::translate(model, objectPosition);

        // Apply the provided translation, scale, and rotation
        model = glm::translate(model, translation);
        model = glm::scale(model, scale);
        model = glm::rotate(model, rotationAngle, glm::vec3(0.0f, 0.0f, 1.0f));

        return model;
    }


    GraphicsSystem::~GraphicsSystem()
    {
        glfwTerminate();
    }
} // namespace Engine
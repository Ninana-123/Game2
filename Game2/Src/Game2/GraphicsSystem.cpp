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
#include "Animation.h"
#include "ImGuiWrapper.h"
#include "inGameGUI.h"

#pragma warning(disable: 4100) // disable "unreferenced parameter" 
namespace Engine
{
    // Logger GraphicsLogger;
    Input InputController;

    GraphicsSystem::GraphicsSystem()
        : shader("Resource/Shaders/Shader.vert", "Resource/Shaders/Shader.frag",
            "Resource/Shaders/Shader2.vert", "Resource/Shaders/Shader2.frag",
            "Resource/Shaders/Shader3.vert", "Resource/Shaders/Shader3.frag"),
        m_Camera(-640.0f, 640.0f, -360.0f, 360.0f), m_EditorCamera(-640.0f, 640.0f, -360.0f, 360.0f)
    {
    }

    GraphicsSystem::GraphicsSystem(std::shared_ptr<Engine::AssetManager> assetManager,std::shared_ptr<Engine::EntityManager> entityManager)
        : assetManager(assetManager), 
     shader("Resource/Shaders/Shader.vert", "Resource/Shaders/Shader.frag",
            "Resource/Shaders/Shader2.vert", "Resource/Shaders/Shader2.frag",
            "Resource/Shaders/Shader3.vert", "Resource/Shaders/Shader3.frag"),
            entityManager(entityManager),
             m_Camera(-640.0f, 640.0f, -360.0f, 360.0f), m_EditorCamera(-640.0f, 640.0f, -360.0f, 360.0f)
    {
    }


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

    void GraphicsSystem::Initialize() {

        Window = glfwGetCurrentContext();

        GraphicsSystem::InitializeGLEW();

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

        // Clear the color buffer
        glClear(GL_COLOR_BUFFER_BIT);

        //int screenWidth, screenHeight;
        glfwGetWindowSize(Window, &screenWidth, &screenHeight);
        //std::cout << "Screen Width: " << screenWidth << ", Screen Height: " << screenHeight << std::endl;

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
           -50.f, -50.f, 0.0f, 0.0f,  // bottom-left
            50.f, -50.f, 1.0f, 0.0f,  // bottom-right
            50.f,  50.f, 1.0f, 1.0f,  // top-right
           -50.f,  50.f, 0.0f, 1.0f   // top-left
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

        GraphicsSystem::va.AddBuffer(vb, layout);

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

        font.Initialize();
        
      //  font.Initialize("Resource/Fonts/arial.ttf");
      /*  font.Initialize("Resource/Fonts/Inkfree.ttf");
        font.Initialize("Resource/Fonts/arial.ttf");*/
        //font.MakeDisplayList(ft, face);
    }

    void GraphicsSystem::InitializeShader()
    {
        // Initialize the shader object (load shader source files and compile them)
        shader.Initialize();
        shader.Bind();

        // Determine which set of shaders to use
        std::string vertexShaderPath;
        std::string fragmentShaderPath;

        int currentShaderSet = shader.GetCurrentShaderSet();

        if (currentShaderSet == 1)
        {
            vertexShaderPath = "Resource/Shaders/Shader.vert";
            fragmentShaderPath = "Resource/Shaders/Shader.frag";
            Logger::GetInstance().Log(LogLevel::Debug, "Loading Shader Set 1...");
        }
        else if (currentShaderSet == 2)
        {
            vertexShaderPath = "Resource/Shaders/Shader2.vert";
            fragmentShaderPath = "Resource/Shaders/Shader2.frag";
            Logger::GetInstance().Log(LogLevel::Debug, "Loading Shader Set 2...");
        }
        else
        {
            throw std::runtime_error("Invalid shader set specified: " + std::to_string(currentShaderSet));
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

                // Store the shader program ID in the shader class
                shader.SetShaderProgram(useShaderSet1 ? 1 : 2, shaderProgram);
                std::cout << "Current Shader Set: " << shader.GetCurrentShaderSet() << ", Program ID: " << shader.GetID() << std::endl;

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

        // Set uniform values (adjust as needed)
        shader.SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);

        // Unbind the shader program after setting up uniforms
        shader.Unbind();
    }

    void GraphicsSystem::InitializeTextures()
    {
        textures.resize(TextureClassCount);

        for (int i = 0; i < TextureClassCount; i++) {
              // Adjust this based on your requirements

            textures[i].resize(static_cast<std::vector<Texture, std::allocator<Texture>>::size_type>(MAX_SUBINDEX) + 1);  // Resize the vector for subindexes

            for (int j = 0; j <= MAX_SUBINDEX; j++) {
                // Get the texture pointer
                std::shared_ptr<Texture> texturePtr = assetManager->getTexture(i, j);

                // Check if the texture pointer is valid before assigning
                if (texturePtr) {
                    textures[i][j] = *texturePtr;

                    // Check if the texture is valid (not nullptr) before calling InitGL and Bind
                    if (textures[i].size() > j) {
                        textures[i][j].InitGL();
                        textures[i][j].Bind(0);
                        std::cout << "Texture ID: " << i << ", SubIndex: " << j << ", Texture OpenGL ID: " << textures[i][j].GetTextureID() << std::endl;
                    }
                    else {
                        // Handle the case where the texture is nullptr (empty subindex)
                        std::cout << "Texture ID: " << i << ", SubIndex: " << j << " is empty" << std::endl;
                    }
                }
                else {
                    // Handle the case where texturePtr is nullptr                   
                }
            }
        }
    }

    void GraphicsSystem::RenderBackground(const glm::mat4& mvpMatrix)
    {
        try {
        shader.Bind();
        textures[Background][0].Bind(0);
        shader.SetUniform1f("texCoordX", 0.0f);
        //shader.SetUniform1f("u_FrameCount", 1.0f);
        shader.SetUniform1f("u_FrameWidth", 1.0f);
        shader.SetUniform1f("u_FrameHeight", 1.0f);

        glm::mat4 viewProjectionMatrix;
        if (useEditorCamera) {
            viewProjectionMatrix = m_EditorCamera.GetViewProjectionMatrix();
        }
        else {
            viewProjectionMatrix = m_Camera.GetViewProjectionMatrix();
        }

        shader.SetUniformMat4f("u_MVP", viewProjectionMatrix);

        /* Printing Matrix (Uncomment if needed)
        std::cout << "BACKGROUND MATRIX: " << '\n' << " ";
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                std::cout << viewProjectionMatrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
        */

        vaBackground.Bind(); // Bind the background vertex array
        ibBackground.Bind(); // Bind the background index buffer

        renderer.Draw(vaBackground, ibBackground, shader);
        textures[Background][0].Unbind();
        shader.Unbind();
        }
        catch (const std::exception& e) {

            Logger::GetInstance().Log(LogLevel::Error, "Render background error: " + std::string(e.what()));

        }
    }

    void GraphicsSystem::RenderTexturedEntity(const glm::mat4& mvpMatrix, Entity* entity)
    {
        shader.Bind();
        if (!entity->HasComponent(ComponentType::Texture))
        {
            Logger::GetInstance().Log(LogLevel::Error, "Entity does not have a TextureComponent!");
            return;
        }

        TextureComponent* texture = dynamic_cast<TextureComponent*>(entity->GetComponent(ComponentType::Texture));

        if (texture != nullptr)
        {
            // Attempt to bind the texture based on the subindex
            auto& textureVector = textures[texture->textureKey.mainIndex];

            if (texture->textureKey.subIndex < textureVector.size())
            {
                // Texture with the specified subindex exists, bind it
                textureVector[texture->textureKey.subIndex].Bind(0);
            }
            else if (!textureVector.empty())
            {
                // Texture with the specified subindex does not exist, default to subindex 0
                textureVector[0].Bind(0);
            }
            // You might want to add an else case to handle the situation where textureVector is empty

             //If Sprite present
            if ((texture->textureKey.subIndex == 1) && entity->HasComponent(ComponentType::Sprite))
            {
                // Calculate deltaTime (time since the last frame)
                static double lastTime = glfwGetTime();
                double currentTime = glfwGetTime();
                double deltaTime = currentTime - lastTime;
                lastTime = currentTime;
                float frameRate = 10.0f;
                float horizontalFrames = 6.0f; // Number of horizontal frames
                float verticalFrames = 1.0f; // Number of vertical frames
                //float Length = 1536.0f; // length of sprite sheet
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
                float frameWidth = 1.0f / horizontalFrames;
                float frameHeight = 1.0f / verticalFrames;
                float texCoordX = currentFrame * frameWidth;
                //float texCoordY = currentRow * frameHeight;

                // Set the texture offset in the shader
                shader.SetUniform1f("texCoordX", texCoordX);
                //shader.SetUniform1f("u_FrameCount", horizontalFrames);
                shader.SetUniform1f("u_FrameWidth", frameWidth);
                shader.SetUniform1f("u_FrameHeight", frameHeight);
                shader.SetUniform1i("u_CurrentFrame", currentFrame);
            }
            else if ((texture->textureKey.subIndex  == 2 ) && entity->HasComponent(ComponentType::Sprite))
            {
                // Calculate deltaTime (time since the last frame)
                static double lastTime = glfwGetTime();
                double currentTime = glfwGetTime();
                double deltaTime = currentTime - lastTime;
                lastTime = currentTime;
                float frameRate = 10.0f;
                float horizontalFrames = 10.0f; // Number of horizontal frames
                float verticalFrames = 1.0f; // Number of vertical frames
                //float Length = 1536.0f; // length of sprite sheet
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
                float frameWidth = 1.0f / horizontalFrames;
                float frameHeight = 1.0f / verticalFrames;
                float texCoordX = currentFrame * frameWidth;
                //float texCoordY = currentRow * frameHeight;

                // Set the texture offset in the shader
                shader.SetUniform1f("texCoordX", texCoordX);
                //shader.SetUniform1f("u_FrameCount", horizontalFrames);
                shader.SetUniform1f("u_FrameWidth", frameWidth);
                shader.SetUniform1f("u_FrameHeight", frameHeight);
                shader.SetUniform1i("u_CurrentFrame", currentFrame);
            }
            else if ((texture->textureKey.subIndex == 3) && entity->HasComponent(ComponentType::Sprite))
            {
                // Calculate deltaTime (time since the last frame)
                static double lastTime = glfwGetTime();
                double currentTime = glfwGetTime();
                double deltaTime = currentTime - lastTime;
                lastTime = currentTime;
                float frameRate = 10.0f;
                float horizontalFrames = 5.0f; // Number of horizontal frames
                float verticalFrames = 1.0f; // Number of vertical frames
                //float Length = 1536.0f; // length of sprite sheet
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
                float frameWidth = 1.0f / horizontalFrames;
                float frameHeight = 1.0f / verticalFrames;
                float texCoordX = currentFrame * frameWidth;
                //float texCoordY = currentRow * frameHeight;

                // Set the texture offset in the shader
                shader.SetUniform1f("texCoordX", texCoordX);
                //shader.SetUniform1f("u_FrameCount", horizontalFrames);
                shader.SetUniform1f("u_FrameWidth", frameWidth);
                shader.SetUniform1f("u_FrameHeight", frameHeight);
                shader.SetUniform1i("u_CurrentFrame", currentFrame);
            }
            else //render as static
            {
                textures[texture->textureKey.mainIndex][0].Bind(0); //render static version of texture at subindex = 0
                shader.SetUniform1f("texCoordX", 0.0f);
                //shader.SetUniform1f("u_FrameCount", 1.0f);
                shader.SetUniform1f("u_FrameWidth", 1.0f);
                shader.SetUniform1f("u_FrameHeight", 1.0f);
            }
        }       
        shader.Bind();
              
        glm::mat4 result;
        if (useEditorCamera) {
            result =  m_EditorCamera.GetViewProjectionMatrix() * mvpMatrix;
        }
        else {
            result =  m_Camera.GetViewProjectionMatrix() * mvpMatrix;
        }

        /*
        // Extract translation part (last column) of the MVP matrix
        glm::vec4 transformedPosition = result[3];

        std::cout << "Entity: " << static_cast<int>(entity->GetID()) << std::endl;
        // Print the transformed coordinates
        std::cout << "Transformed Coordinates: (" << transformedPosition.x << ", "
            << transformedPosition.y << ", "
            << transformedPosition.z << ")\n";
        */
        
        shader.SetUniformMat4f("u_MVP", result);

        va.Bind();
        ib.Bind();

        // Render the entity
        renderer.Draw(va, ib, shader);

        // Unbind the texture and shader
        shader.Unbind();
    }

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
            shader.Unbind();
        }
        catch (const std::exception& e) {

            Logger::GetInstance().Log(LogLevel::Error, "Render lines error: " + std::string(e.what()));
        }
    }

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

            Logger::GetInstance().Log(LogLevel::Error, "Render single line error: " + std::string(e.what()));
        }
    }

    void GraphicsSystem::DrawColoredSquare(const glm::mat4& mvpMatrix)
    {
        try {
        // Bind the shader and set uniforms
        shader.Bind();
        shader.SetUniform4f("u_Color", 1.0f, 1.0f, 0.0f, 1.0f);

        if (useEditorCamera) {
            shader.SetUniformMat4f("u_MVP", m_EditorCamera.GetViewProjectionMatrix());
        }
        else {
            shader.SetUniformMat4f("u_MVP", m_Camera.GetViewProjectionMatrix());
        }

        va.Bind();
        ib.Bind();
        // Render the square
        renderer.Draw(va, ib, shader);
        shader.Unbind();
        }
        catch (const std::exception& e) {

            Logger::GetInstance().Log(LogLevel::Error, "Draw colored square error: " + std::string(e.what()));

        }
    }

    void GraphicsSystem::Update(std::unordered_map<EntityID, std::unique_ptr<Entity>>* entities)
    {
        //int width, height;
        //glfwGetWindowSize(Window, &width, &height);   
        //UpdateViewport(width, height);
        renderer.Clear();    
   
        // Get the current state of the 'S' key
        bool currentSState = glfwGetKey(this->Window, GLFW_KEY_S) == GLFW_PRESS;

        // Save the current shader state
        int previousShaderSet = shader.GetCurrentShaderSet();
        shader.Bind();
        
        // Check if there's a change in the 'S' key state
        if (currentSState && !previousSState)
        {
            // Toggle the shader state
            ToggleShaderSet();
        }
        // Update the previous 'S' key state
        previousSState = currentSState;

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
                    
                    // glm::mat4 mvpA = proj* m_Camera.GetViewProjectionMatrix()  * modelA;

                    // Get the current state of the 'P' key
                    bool currentPState = glfwGetKey(this->Window, GLFW_KEY_P) == GLFW_PRESS;

                    if (entity->HasComponent(ComponentType::Texture))
                    {
                        TextureComponent* texture = dynamic_cast<TextureComponent*>(entity->GetComponent(ComponentType::Texture));

                        // Check if there's a change in the 'P' key state
                        //if (currentPState && !previousPState)
                        //{
                        //    // Toggle the rendering mode
                        //    ToggleRenderMode();
                        //}

                        //// Update the previous 'P' key state
                        //previousPState = currentPState;

                        if (!renderTexturedSquare)
                        {
                            if(texture->textureKey.mainIndex == Background)
                                RenderBackground(modelA);
                            else {
                                RenderTexturedEntity(modelA, entity); // Here, we pass the specific entity

                                RenderLines(modelA);
                            }
                        }
                        else
                        {
                            DrawColoredSquare(modelA);
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

        // CAMERA
        if (useEditorCamera) {
            m_EditorCamera.UpdatePosition(InputController, CameraSpeed);
        }
        else {
            m_Camera.UpdatePosition(InputController, CameraSpeed);
        }

        //font.RenderText(shader, "Sample", -0.9f, -0.9f, 0.001f, glm::vec3(0.0f, 0.0f, 0.0f));
        
        font.SwitchFont(1);
        //font.RenderText(shader, "Samurai Cat",  0.f, 0.9f, 0.002f, glm::vec3(0.f, 0.f, 0.f));
        //font.SwitchFont(2);
        //font.RenderText(shader, "Hello World", 0.f, 0.6f, 0.002f, glm::vec3(0.f, 0.f, 0.f));
        
        // Render text if cat placement is wrong
        if (!(isStartingPoint)) 
        {
            font.RenderText(shader, "Place unit at the start of the path.", 0.f, 0.9f, 0.002f, glm::vec3(0.f, 0.f, 0.f));
        }
        // Render text if game is paused
        if (isGamePaused)
        {
            font.RenderText(shader, "Game is paused.", 0.f, 0.9f, 0.002f, glm::vec3(0.f, 0.f, 0.f));
        }
        // Render text if in settings
        if (inSettings)
        {
            font.RenderText(shader, "Game is in settings.", 0.f, 0.9f, 0.002f, glm::vec3(0.f, 0.f, 0.f));
        }

        // Restore the previous shader state
        shader.SetActiveShaderSet(previousShaderSet);

        // CAMERA
        m_Camera.UpdatePosition(InputController, CameraSpeed);

    }

    void GraphicsSystem::UpdateShaderSet()
    {
        try {
            std::cout << "UpdateShaderSet() called!" << std::endl;

            // Print the current shader set before reinitializing shaders
            std::cout << "Current Shader Set: " << shader.GetCurrentShaderSet() << std::endl;

            // Reinitialize shaders based on the new set
            InitializeShader();

            // Print the shader set after reinitializing shaders
            std::cout << "Shader Set Updated: " << (shader.GetCurrentShaderSet() == 1 ? "Shader Set 1" : "Shader Set 2") << std::endl;
        }
        catch (const std::exception& e) {
            Logger::GetInstance().Log(LogLevel::Error, "Shader set update error: " + std::string(e.what()));
        }
    }

    void GraphicsSystem::UpdateViewport(int width, int height)
    {
        glViewport(0, 0, width, height);
    }

    void GraphicsSystem::ToggleRenderMode()
    {
        try {
            renderTexturedSquare = !renderTexturedSquare;
            std::cout << "Render Textured Square: " << (renderTexturedSquare ? "Enabled" : "Disabled") << std::endl;

            shader.Bind();
            shader.SetUniform1i("u_RenderTextured", renderTexturedSquare ? 1 : 0);
            std::cout << "Shader Uniform 'u_RenderTextured' set to: " << (renderTexturedSquare ? "1" : "0") << std::endl;
        }
        catch (const std::exception& e) {

            Logger::GetInstance().Log(LogLevel::Error, "Toggle render mode error: " + std::string(e.what()));
        }
    }

    void GraphicsSystem::ToggleShaderSet()
    {
        try
        {
            std::cout << "ToggleShaderSet() called!" << std::endl;

            int newShaderSet = (shader.GetCurrentShaderSet() == 1) ? 2 : 1;
            shader.SetActiveShaderSet(newShaderSet);

            std::cout << "Shader Set Toggled: " << (newShaderSet == 1 ? "Shader Set 1" : "Shader Set 2") << std::endl;

            // Update shader properties based on the new set
            UpdateShaderSet();
        }
        catch (const std::exception& e)
        {
            Logger::GetInstance().Log(LogLevel::Error, "Shader set toggle error: " + std::string(e.what()));
        }
    }

    glm::mat4 GraphicsSystem::SetupModelMatrix(const glm::vec3& translation, float rotationAngle, const glm::vec3& scale)
    {
        //int screenWidth, screenHeight;
        glfwGetWindowSize(Window, &screenWidth, &screenHeight);

        // Calculate the position for your object at the center of the screen
        //glm::vec3 MobjectPosition = glm::vec3(static_cast<float>(screenWidth) / 2.0f, static_cast<float>(screenHeight) / 2.0f, 0.0f);

        glm::mat4 model = glm::mat4(1.0f); // Initialize the model matrix as identity

        // Translate the object to the calculated center position
        //model = glm::translate(model, MobjectPosition);

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
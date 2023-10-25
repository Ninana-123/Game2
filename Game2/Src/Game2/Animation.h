#pragma once
#include <vector>
namespace Engine
{
    class Animation
    {
    public:
        Animation(float frameRate);

        // Add a frame to the animation.
        void AddFrame(int textureIndex);

        // Play the animation.
        void Play();

        // Pause the animation.
        void Pause();

        // Update the animation frame based on elapsed time.
        void Update(float deltaTime);

        // Get the current texture index.
        int GetCurrentFrame();

        // Check if the animation is playing.
        bool IsPlaying();

      

    private:
        float frameRate;
        std::vector<int> frames;
        int currentFrame;
        float frameTimer;
        bool playing;
    };
}
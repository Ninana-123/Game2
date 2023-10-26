#pragma once

#include <vector>

namespace Engine
{
    class Animation
    {
    public:
        Animation(float frameRate, int spriteWidth, int spriteHeight);
        Animation(); // Default constructor

        void AddFrame(int textureIndex, int frameDuration = 1);
        void Play();
        void Pause();
        void Stop();
        void Update(float deltaTime);
        int GetCurrentFrame();
        bool IsPlaying();
        int GetCurrentFrameWidth();
        int GetCurrentFrameHeight();

    private:
        float frameRate;
        int spriteWidth;
        int spriteHeight;
        std::vector<int> frames;
        std::vector<int> frameDurations;
        int currentFrame;
        float frameTimer;
        bool playing;
    };
}

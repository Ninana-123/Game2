#include "pch.h"
#include "Animation.h"

namespace Engine
{
    Animation::Animation(float frameRate, int spriteWidth, int spriteHeight)
        : frameRate(frameRate), spriteWidth(spriteWidth), spriteHeight(spriteHeight),
        currentFrame(0), frameTimer(0), playing(false)
    {
    }

    Animation::Animation()
        : frameRate(0.0f), spriteWidth(0), spriteHeight(0),
        currentFrame(0), frameTimer(0), playing(false)
    {
    }

    void Animation::AddFrame(int textureIndex, int frameDuration)
    {
        frames.push_back(textureIndex);
        frameDurations.push_back(frameDuration);
    }

    void Animation::Play()
    {
        currentFrame = 0;
        frameTimer = 0;
        playing = true;
    }

    void Animation::Pause()
    {
        playing = false;
    }

    void Animation::Stop()
    {
        playing = false;
        currentFrame = 0;
        frameTimer = 0;
    }

    void Animation::Update(float deltaTime)
    {
        if (playing)
        {
            frameTimer += deltaTime;
            int frameDuration = frameDurations[currentFrame];
            if (frameTimer >= frameDuration / frameRate)
            {
                currentFrame = (currentFrame + 1) % frames.size();
                frameTimer = 0;
            }
        }
    }

    int Animation::GetCurrentFrame()
    {
        return frames[currentFrame];
    }

    bool Animation::IsPlaying()
    {
        return playing;
    }

    int Animation::GetCurrentFrameWidth()
    {
        return spriteWidth;
    }

    int Animation::GetCurrentFrameHeight()
    {
        return spriteHeight;
    }
}

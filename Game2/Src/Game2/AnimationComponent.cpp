#include "pch.h"
#include "AnimationComponent.h"

namespace Engine
{
    AnimationComponent::AnimationComponent(float frameRate, int spriteWidth, int spriteHeight)
        : frameRate(frameRate), spriteWidth(spriteWidth), spriteHeight(spriteHeight),
        currentFrame(0), frameTimer(0), playing(false)
    {
    }

    AnimationComponent::AnimationComponent()
        : frameRate(0.0f), spriteWidth(0), spriteHeight(0),
        currentFrame(0), frameTimer(0), playing(false)
    {
    }

    void AnimationComponent::AddFrame(int textureIndex, int frameDuration)
    {
        frames.push_back(textureIndex);
        frameDurations.push_back(frameDuration);
    }

    void AnimationComponent::Play()
    {
        currentFrame = 0;
        frameTimer = 0;
        playing = true;
    }

    void AnimationComponent::Pause()
    {
        playing = false;
    }

    void AnimationComponent::Stop()
    {
        playing = false;
        currentFrame = 0;
        frameTimer = 0;
    }

    void AnimationComponent::UpdateAnimation(float deltaTime)
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

    int AnimationComponent::GetCurrentFrame()
    {
        return frames[currentFrame];
    }

    bool AnimationComponent::IsPlaying()
    {
        return playing;
    }

    int AnimationComponent::GetCurrentFrameWidth()
    {
        return spriteWidth;
    }

    int AnimationComponent::GetCurrentFrameHeight()
    {
        return spriteHeight;
    }

    int AnimationComponent::GetNumFrames() const
    {
        return frames.size();
    }

    void AnimationComponent::SetFrameRate(float frameRate)
    {
        this->frameRate = frameRate;
    }

}


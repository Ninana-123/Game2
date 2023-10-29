#include "pch.h"
#include "Animation.h"

namespace Engine
{
    Animation::Animation(float frameRate, float spriteWidth, float spriteHeight, Anim_Mode mode)
        : frameRate(frameRate), spriteWidth(spriteWidth), spriteHeight(spriteHeight), playMode(mode)
    {
        frameCount = spriteWidth * spriteHeight;
        textureWidth = 1.0f / spriteWidth;
        textureHeight = 1.0f / spriteHeight;
        frameTimer = 1.0f / frameRate;
        playing = false;
        currentFrame = 0;
        animTimer = 0.0f;
        textureXIndex = 0;
        textureYIndex = 0;
    }

    void Animation::Play()
    {
        playing = true;
        textureXIndex = 0;
        textureYIndex = 0;
    }

    void Animation::Pause()
    {
        playing = false;
    }

    int Animation::GetCurrentFrame()
    {
        return currentFrame;
    }

    bool Animation::IsPlaying()
    {
        return playing;
    }

    bool Animation::IsFinished() const
    {
        if (playMode == Anim_Mode::LOOP) {
           
            return false;
        }
        else if (playMode == Anim_Mode::ONE_TIME) {
           
            return currentFrame == frameCount - 1;
        }
       

        return false; 
    }

    void Animation::ResetAnim()
    {
        playing = false;
        textureXIndex = 0;
        textureYIndex = 0;
        currentFrame = 0;
        animTimer = 0;
    }

    float Animation::GetAnimTimer() const
    {
        return animTimer;
    }

    void Animation::NextFrame()
    {
        if (playMode == Anim_Mode::ONE_TIME && currentFrame == frameCount - 1) {
            playing = false;
            return;
        }

        ++currentFrame;
        if (currentFrame >= frameCount) {
            currentFrame = 0; // Wrap around to the first frame
        }

        // Calculate texture coordinates based on the current frame
        textureXIndex = currentFrame % static_cast<int>(spriteWidth);
        textureYIndex = currentFrame / static_cast<int>(spriteWidth);
    }

    


    void Animation::Update(float deltaTime)
    {
        if (!playing) {
            return;
        }

        animTimer += deltaTime;
        if (animTimer >= frameTimer) {
            NextFrame();
            animTimer = 0;
        }
    }
}

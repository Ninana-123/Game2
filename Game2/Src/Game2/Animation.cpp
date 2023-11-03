#include "pch.h"
#include "Animation.h"

namespace Engine
{
    Animation::Animation(float frameRate, float horizontalFrames, float verticalFrames, Anim_Mode mode)
        : frameRate(frameRate), horizontalFrames(static_cast<int>(horizontalFrames)), verticalFrames(static_cast<int>(verticalFrames)), playMode(mode)
    {
        frameCount = static_cast<int>(horizontalFrames * verticalFrames);
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
        textureXIndex = currentFrame % static_cast<int>(horizontalFrames);
        textureYIndex = currentFrame / static_cast<int>(horizontalFrames);
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

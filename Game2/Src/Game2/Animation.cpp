/******************************************************************************/
/*!
\file		Animation.cpp
\author 	Teo Sheen Yeoh
\par    	email: t.sheenyeoh@digipen.edu
\date   	August 29, 2023
\brief      This file defines the member functions of the Animation class, 
            which is responsible for managing sprite animations in the game engine. 
            It includes functions to control animation playback, calculate texture coordinates,
            and update animation frames based on the specified frame rate and playback mode.

            Copyright (C) 2023 DigiPen Institute of Technology.
            Reproduction or disclosure of this file or its contents without the prior
            written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#include "pch.h"
#include "Animation.h"

namespace Engine
{
    Animation::Animation(float frameRate, float horizontalFrames, float verticalFrames, Anim_Mode mode)
        : frameRate(frameRate), horizontalFrames(horizontalFrames), verticalFrames(verticalFrames), playMode(mode)
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
            // Animation always continues in loop mode
            return false;
        }
        else if (playMode == Anim_Mode::ONE_TIME) {
            // Animation finishes when the last frame is reached
            return currentFrame == frameCount - 1;
        }

        return false; // Unhandled playback mode
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
            playing = false; // Stop playing after reaching the last frame in one-time mode
            return;
        }

        ++currentFrame;
        if (currentFrame >= frameCount) {
            currentFrame = 0; // Wrap around to the first frame for continuous looping
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
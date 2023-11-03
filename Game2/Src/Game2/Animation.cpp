/******************************************************************************/
/*!
\file		sprite.cpp
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

    /**
    * @brief Constructor for the Animation class.
    *
    * @param frameRate The frame rate of the animation.
    * @param horizontalFrames Number of frames in a row in the sprite sheet.
    * @param verticalFrames Number of rows of frames in the sprite sheet.
    * @param mode The animation playback mode (LOOP or ONE_TIME).
    */
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


    /**
     * @brief Start playing the animation.
     */
    void Animation::Play()
    {
        playing = true;
    }

    /**
     * @brief Pause the animation.
     */
    void Animation::Pause()
    {
        playing = false;
    }

    /**
    * @brief Get the current frame index of the animation.
    *
    * @return The index of the current frame.
    */
    int Animation::GetCurrentFrame()
    {
        return currentFrame;
    }

    /**
    * @brief Check if the animation is currently playing.
    *
    * @return True if the animation is playing, false otherwise.
    */
    bool Animation::IsPlaying()
    {
        return playing;
    }

    /**
   * @brief Check if the animation has finished playing.
   *
   * @return True if the animation is finished, false otherwise.
   */
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


    /**
    * @brief Reset the animation to its initial state.
    */
    void Animation::ResetAnim()
    {
        playing = false;
        textureXIndex = 0;
        textureYIndex = 0;
        currentFrame = 0;
        animTimer = 0;
    }

    /**
     * @brief Get the current animation timer value.
     *
     * @return The current animation timer value.
     */
    float Animation::GetAnimTimer() const
    {
        return animTimer;
    }


    /**
    * @brief Move to the next frame in the animation.
    */
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


    /**
     * @brief Update the animation based on the elapsed time.
     *
     * @param deltaTime Time elapsed since the last frame.
     */
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

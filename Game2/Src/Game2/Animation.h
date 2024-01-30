/******************************************************************************/
/*!
\file		Animation.h
\author 	Teo Sheen Yeoh
\par    	email: t.sheenyeoh@digipen.edu
\date   	August 29, 2023
\brief      This file declares the member functions of the Animation class, 
            which is responsible for managing sprite animations in the game engine. 
            It includes functions to control animation playback, calculate texture coordinates,
            and update animation frames based on the specified frame rate and playback mode.

            Copyright (C) 2023 DigiPen Institute of Technology.
            Reproduction or disclosure of this file or its contents without the prior
            written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#ifndef ENGINE_ANIMATION_H
#define ENGINE_ANIMATION_H

#include <fstream>
namespace Engine
{
    enum class Anim_Mode
    {
        LOOP, ONE_TIME
    };

    class Animation
    {
    public:
        /**
        * @brief Constructor for the Animation class.
        *
        * @param frameRate The frame rate of the animation.
        * @param horizontalFrames Number of frames in a row in the sprite sheet.
        * @param verticalFrames Number of rows of frames in the sprite sheet.
        * @param mode The animation playback mode (LOOP or ONE_TIME).
        */
        Animation(float frameRate, float  spriteWidth, float spriteHeight, Anim_Mode mode = Anim_Mode::LOOP);

        /**
         * @brief Start playing the animation.
         */
        void Play();

        /**
         * @brief Pause the animation.
         */
        void Pause();
       
        /**
         * @brief Update the animation based on the elapsed time.
         *
         * @param deltaTime Time elapsed since the last frame.
         */
        void Update(float deltaTime);

        /**
        * @brief Get the current frame index of the animation.
        *
        * @return The index of the current frame.
        */
        int GetCurrentFrame();

        /**
        * @brief Check if the animation is currently playing.
        *
        * @return True if the animation is playing, false otherwise.
        */
        bool IsPlaying();      

        /**
        * @brief Check if the animation has finished playing.
        *
        * @return True if the animation is finished, false otherwise.
        */
        bool IsFinished() const;

        /**
        * @brief Reset the animation to its initial state.
        */
        void ResetAnim();

        /**
         * @brief Get the current animation timer value.
         *
         * @return The current animation timer value.
         */
        float GetAnimTimer() const;

        /**
        * @brief Move to the next frame in the animation.
        */
        void NextFrame();

    private:
        float frameRate;
        float horizontalFrames;
        float verticalFrames;
        int frameCount;
        float frameTimer;
        float animTimer;
        int currentFrame;
        int textureXIndex;
        int textureYIndex;
        bool playing;
        Anim_Mode playMode;
    };
}
#endif ENGINE_ANIMATION_H
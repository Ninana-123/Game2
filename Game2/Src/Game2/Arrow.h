/******************************************************************************/
/*!
\file		font.cpp
\author 	Teo Sheen Yeoh
\par    	email: t.sheenyeoh@digipen.edu
\date   	August 29, 2023
\brief       This file declares the member functions of the Animation class, 
            which is responsible for managing sprite animations in the game engine. 
            It includes functions to control animation playback, calculate texture coordinates,
            and update animation frames based on the specified frame rate and playback mode.

            Copyright (C) 2023 DigiPen Institute of Technology.
            Reproduction or disclosure of this file or its contents without the prior
            written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#pragma once

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
        Animation(float frameRate, float  spriteWidth, float spriteHeight, Anim_Mode mode = Anim_Mode::LOOP);

        void Play();
        void Pause();
        void ResetAnim();
        void Update(float deltaTime);
        int GetCurrentFrame();
        bool IsPlaying();        
        void NextFrame();
        float GetAnimTimer() const;
        bool IsFinished() const;


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

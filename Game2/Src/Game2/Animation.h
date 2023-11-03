#pragma once

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
        int horizontalFrames;
        int verticalFrames;
        int frameCount;
        float frameTimer;
        float animTimer;
        float frameDisplayTime;
        int currentFrame;
        int textureXIndex;
        int textureYIndex;
        bool playing;
        Anim_Mode playMode;
    };
}

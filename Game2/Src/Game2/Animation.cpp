#include "pch.h"
#include "Animation.h"


namespace Engine
{
    Animation::Animation(float frameRate)
        : frameRate(frameRate), currentFrame(0), frameTimer(0), playing(false) {
    }

    void Animation::AddFrame(int textureIndex) {
        frames.push_back(textureIndex);
    }

    void Animation::Play() {
        currentFrame = 0;
        frameTimer = 0;
        playing = true;
    }

    void Animation::Pause() {
        playing = false;
    }

    void Animation::Update(float deltaTime) {
        if (playing) {
            frameTimer += deltaTime;
            if (frameTimer >= 1.0f / frameRate) {
                currentFrame = (currentFrame + 1) % frames.size();
                frameTimer = 0;
            }
        }
    }

    int Animation::GetCurrentFrame() {
        return frames[currentFrame];
    }

    bool Animation::IsPlaying() {
        return playing;
    }
}

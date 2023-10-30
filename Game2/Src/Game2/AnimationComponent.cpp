#include "pch.h"
//#include "AnimationComponent.h"
//
//namespace Engine
//{
//    AnimationComponent::AnimationComponent(float frameRate, float horizontalFrames, float verticalFrames, Anim_Mode mode)
//        : frameRate(frameRate), horizontalFrames(horizontalFrames), verticalFrames(verticalFrames), playMode(mode)
//    {
//        frameCount = horizontalFrames * verticalFrames;
//        frameTimer = 1.0f / frameRate;
//        playing = false;
//        currentFrame = 0;
//        animTimer = 0.0f;
//        textureXIndex = 0;
//        textureYIndex = 0;
//    }
//    AnimationComponent::AnimationComponent()
//    {
//
//    }
//    void AnimationComponent::Play()
//    {
//        playing = true;
//    }
//
//    void AnimationComponent::Pause()
//    {
//        playing = false;
//    }
//
//    int AnimationComponent::GetCurrentFrame()
//    {
//        return currentFrame;
//    }
//
//    bool AnimationComponent::IsPlaying()
//    {
//        return playing;
//    }
//
//    bool AnimationComponent::IsFinished() const
//    {
//        if (playMode == Anim_Mode::LOOP) {
//
//            return false;
//        }
//        else if (playMode == Anim_Mode::ONE_TIME) {
//
//            return currentFrame == frameCount - 1;
//        }
//
//
//        return false;
//    }
//
//    void AnimationComponent::ResetAnim()
//    {
//        playing = false;
//        textureXIndex = 0;
//        textureYIndex = 0;
//        currentFrame = 0;
//        animTimer = 0;
//    }
//
//    float AnimationComponent::GetAnimTimer() const
//    {
//        return animTimer;
//    }
//
//    void AnimationComponent::NextFrame()
//    {
//        if (playMode == Anim_Mode::ONE_TIME && currentFrame == frameCount - 1) {
//            playing = false;
//            return;
//        }
//
//        ++currentFrame;
//        if (currentFrame >= frameCount) {
//            currentFrame = 0; // Wrap around to the first frame
//        }
//
//        // Calculate texture coordinates based on the current frame
//        textureXIndex = currentFrame % static_cast<int>(horizontalFrames);
//        textureYIndex = currentFrame / static_cast<int>(horizontalFrames);
//    }
//
//
//    void AnimationComponent::Update(float deltaTime)
//    {
//        if (!playing) {
//            return;
//        }
//
//        animTimer += deltaTime;
//        if (animTimer >= frameTimer) {
//            NextFrame();
//            animTimer = 0;
//        }
//    }
//}
//

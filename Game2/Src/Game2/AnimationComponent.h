//#pragma once
//
//#include "Component.h"
//#include "EngineTypes.h"
//
//namespace Engine
//{
//
//    enum class Anim_Mode
//    {
//        LOOP, ONE_TIME
//    };
//
//    class AnimationComponent : public Component
//    {
//    public:
//        AnimationComponent(float frameRate, float  spriteWidth, float spriteHeight, Anim_Mode mode = Anim_Mode::LOOP);
//        AnimationComponent();
//        void Play();
//        void Pause();
//        void ResetAnim();
//        void Update(float deltaTime);
//        int GetCurrentFrame();
//        bool IsPlaying();
//        void NextFrame();
//        float GetAnimTimer() const;
//        bool IsFinished() const;
//
//        float frameRate;
//        int horizontalFrames;
//        int verticalFrames;
//        int frameCount = horizontalFrames * verticalFrames;;
//        float frameTimer = 1.0f / frameRate;
//        float animTimer;
//        int currentFrame;
//        int textureXIndex;
//        int textureYIndex;
//        bool playing = false;
//        Anim_Mode playMode;
//
//
//        Component* Clone() const override
//        {
//            AnimationComponent* cloneComponent = new AnimationComponent(frameRate, horizontalFrames, verticalFrames, playMode);
//            cloneComponent->frameTimer = frameTimer;
//            cloneComponent->animTimer = animTimer;
//            cloneComponent->currentFrame = currentFrame;
//            cloneComponent->textureXIndex = textureXIndex;
//            cloneComponent->textureYIndex = textureYIndex;
//            cloneComponent->playing = playing;
//            cloneComponent->playMode = playMode;
//            return cloneComponent;
//        }
//
//
//        ComponentType GetType() const override
//        {
//            return ComponentType::Animation;
//        }
//
//        void Serialize(std::ostream& outputStream) const {
//            outputStream << "frameRate: " << frameRate << '\n';
//            outputStream << "horizontalFrames: " << horizontalFrames << '\n';
//            outputStream << "verticalFrames: " << verticalFrames << '\n';
//            outputStream << "frameTimer: " << frameTimer << '\n';
//            outputStream << "animTimer: " << animTimer << '\n';
//            outputStream << "currentFrame: " << currentFrame << '\n';
//            outputStream << "textureXIndex: " << textureXIndex << '\n';
//            outputStream << "textureYIndex: " << textureYIndex << '\n';
//            outputStream << "playing: " << playing << '\n';
//            outputStream << "playMode: " << static_cast<int>(playMode) << '\n';
//        }
//
//        void Deserialize(std::istream& inputStream) {
//            std::string temp;
//            inputStream >> temp >> frameRate;
//            inputStream >> temp >> horizontalFrames;
//            inputStream >> temp >> verticalFrames;
//            inputStream >> temp >> frameTimer;
//            inputStream >> temp >> animTimer;
//            inputStream >> temp >> currentFrame;
//            inputStream >> temp >> textureXIndex;
//            inputStream >> temp >> textureYIndex;
//            inputStream >> temp >> playing;
//            int mode;
//            inputStream >> temp >> mode;
//            playMode = static_cast<Anim_Mode>(mode);
//        }
//
//
//    };
//}
//#pragma once
//
//

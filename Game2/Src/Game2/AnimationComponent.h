#pragma once

#include "Component.h"
#include "EngineTypes.h"

namespace Engine
{
    class AnimationComponent : public Component 
    {
    public:
        AnimationComponent(float frameRate, int spriteWidth, int spriteHeight);
        AnimationComponent(); // Default constructor

        void AddFrame(int textureIndex, int frameDuration);
        void Play();
        void Pause();
        void Stop();
        void UpdateAnimation(float deltaTime);
        int GetCurrentFrame();
        bool IsPlaying();
        int GetCurrentFrameWidth();
        int GetCurrentFrameHeight();
        int GetNumFrames() const;
        void SetFrameRate(float frameRate);

        Component* Clone() const override
        {
            AnimationComponent* cloneComponent = new AnimationComponent(frameRate, spriteWidth, spriteHeight);
            cloneComponent->frames = frames;
            cloneComponent->frameDurations = frameDurations;
            cloneComponent->currentFrame = currentFrame;
            cloneComponent->frameTimer = frameTimer;
            cloneComponent->playing = playing;
            return cloneComponent;
        }

        ComponentType GetType() const override
        {
            return ComponentType::Animation; 
        }

        void Serialize(std::ostream& os) const override 
        {
           
            os << "Frames: ";
            for (int frame : frames) {
                os << frame << ' ';
            }
            os << '\n';

            os << "FrameDurations: ";
            for (int duration : frameDurations) {
                os << duration << ' ';
            }
            os << '\n';
            os << "CurrentFrame: " << currentFrame << '\n';
            os << "FrameTimer: " << frameTimer << '\n';
            os << "Playing: " << (playing ? 1 : 0) << '\n';
        }

        void Deserialize(std::istream& is)
        {
            std::string line;
            while (std::getline(is, line))
            {
                std::istringstream lineStream(line);
                std::string key;
                lineStream >> key;

                if (key == "Frames:")
                {
                    frames.clear();
                    int frame;
                    while (lineStream >> frame)
                    {
                        frames.push_back(frame);
                    }
                }
                else if (key == "FrameDurations:")
                {
                    frameDurations.clear();
                    int duration;
                    while (lineStream >> duration)
                    {
                        frameDurations.push_back(duration);
                    }
                }
                else if (key == "CurrentFrame:")
                {
                    lineStream >> currentFrame;
                }
                else if (key == "FrameTimer:")
                {
                    lineStream >> frameTimer;
                }
                else if (key == "Playing:")
                {
                    int playingValue;
                    lineStream >> playingValue;
                    playing = (playingValue == 1);
                }
            }
        }


    private:
        float frameRate;
        int spriteWidth;
        int spriteHeight;
        std::vector<int> frames;
        std::vector<int> frameDurations;
        int currentFrame;
        float frameTimer;
        bool playing;
    };

}
#pragma once



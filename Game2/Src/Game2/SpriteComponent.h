#pragma once

#include "Animation.h"
#include "Component.h"
#include "EngineTypes.h"

namespace Engine
{
    class SpriteComponent : public Component
    {
    public:
        
        float framerate = 0.f;
        int horizontalframes = 0;
        int verticalframes = 0;
        float animtimer = 0.f;
        int currentframe = 0;
        int texturexindex = 0;
        int textureyindex = 0;
        bool playing = false;
        anim_mode playmode = anim_mode::loop;

        ComponentType GetType() const override { return ComponentType::Sprite; }
        
        Component* Clone() const override
        {
            SpriteComponent* clonecomponent = new SpriteComponent;
            clonecomponent->animtimer = animtimer;
            clonecomponent->currentframe = currentframe;
            clonecomponent->texturexindex = texturexindex;
            clonecomponent->textureyindex = textureyindex;
            clonecomponent->playing = playing;
            clonecomponent->playmode = playmode;
            return clonecomponent;
        }      

        void Serialize(std::ostream& outputstream) const {
            outputstream << "framerate: " << framerate << '\n';
            outputstream << "horizontalframes: " << horizontalframes << '\n';
            outputstream << "verticalframes: " << verticalframes << '\n';
            outputstream << "animtimer: " << animtimer << '\n';
            outputstream << "currentframe: " << currentframe << '\n';
            outputstream << "texturexindex: " << texturexindex << '\n';
            outputstream << "textureyindex: " << textureyindex << '\n';
            outputstream << "playing: " << playing << '\n';
            outputstream << "playmode: " << static_cast<int>(playmode) << '\n';
        }

        void Deserialize(std::istream& inputstream) {
            std::string temp;
            inputstream >> temp >> framerate;
            inputstream >> temp >> horizontalframes;
            inputstream >> temp >> verticalframes;
            inputstream >> temp >> animtimer;
            inputstream >> temp >> currentframe;
            inputstream >> temp >> texturexindex;
            inputstream >> temp >> textureyindex;
            inputstream >> temp >> playing;
            int mode;
            inputstream >> temp >> mode;
            playmode = static_cast<anim_mode>(mode);
        }
    };
}
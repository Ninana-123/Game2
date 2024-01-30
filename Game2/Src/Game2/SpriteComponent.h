/******************************************************************************/
/*!
\file		SpriteComponent.h
\author		Tristan Tham Rui Hong
\par		t.tham@digipen.edu
\date		01/11/2023
\brief		Contains the interface of the Sprite Component

 */
 /******************************************************************************/
#ifndef ENGINE_SPRITECOMPONENT_H
#define ENGINE_SPRITECOMPONENT_H

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
        /*!*****************************************************************

		\brief
		Getter for this Components enum

		\return  ComponentType
		Returns an enum of the component Type

		********************************************************************/
        ComponentType GetType() const override { return ComponentType::Sprite; }

        /*!*****************************************************************

        \brief
        Cloner for this component

        \return  Component*
        Clone component with cloned data members

        ********************************************************************/
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

        /*!*****************************************************************
        \brief
        Serialize the SpriteComponent to an output stream.

        \param outputstream
        The output stream to which the SpriteComponent is serialized.
        ********************************************************************/
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

        /*!*****************************************************************
        \brief
        Deserialize the SpriteComponent from an input stream.

        \param inputstream
        The input stream from which the SpriteComponent is deserialized.
        ********************************************************************/
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
#endif ENGINE_SPRITECOMPONENT_H
/******************************************************************************/
/*!
\file		SoundInfo.h
\author 	Tay Jun Feng Vance
\par    	email: junfengvance.t@digipen.edu
\date       29/09/2023
\brief		This file contains the implementation of class SoundInfo which hold information
            about a sound, including its file path, unique ID, 3D attributes and playback settings.

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#pragma once

class SoundInfo {
public:
    /*!
    ***********************************************************************
    \brief
    Constructor for the SoundInfo class.
    \param[in] filePath
    The file path to the sound file.
    \param[in] uniqueID
    The unique identifier for the sound.
    \param[in] is3D
    Whether the sound is 3D (position-based).
    \param[in] loop
    Whether the sound should loop.
    \param[in] volume
    The volume of the sound (0.0 to 1.0).
    \param[in] reverbAmount
    The reverb amount for the sound (0.0 to 1.0).
    ***********************************************************************/
    SoundInfo(const std::string& filePath, const std::string& uniqueID, bool is3D = false, bool loop = false,
        float volume = 0.0f, float reverbAmount = 0.0f)
        : filePath(filePath), uniqueID(uniqueID), getis3D(is3D), loop(loop),
        volume(volume), reverbAmount(reverbAmount), loaded(false), x(0.0f), y(0.0f), z(0.0f) {}

    /*!
    ***********************************************************************
    \brief
    Get the file path to the sound file.
    \return
    The file path to the sound file.
    ***********************************************************************/
    const std::string& getFilePath() const { return filePath; }

    /*!
    ***********************************************************************
    \brief
    Get the unique identifier for the sound.
    \return
    The unique identifier for the sound.
    ***********************************************************************/
    const std::string& getUniqueID() const { return uniqueID; }

    /*!
    ***********************************************************************
    \brief
    Check if the sound is 3D (position-based).
    \return
    True if the sound is 3D, false otherwise.
    ***********************************************************************/
    bool is3D() const { return getis3D; }

    /*!
    ***********************************************************************
    \brief
    Check if the sound should loop.
    \return
    True if the sound should loop, false otherwise.
    ***********************************************************************/
    bool isLoop() const { return loop; }

    /*!
    ***********************************************************************
    \brief
    Get the volume of the sound.
    \return
    The volume of the sound (0.0 to 1.0).
    ***********************************************************************/
    float getVolume() const { return volume; }

    /*!
    ***********************************************************************
    \brief
    Get the reverb amount for the sound.
    \return
    The reverb amount for the sound (0.0 to 1.0).
    ***********************************************************************/
    float getReverbAmount() const { return reverbAmount; }

    /*!
    ***********************************************************************
    \brief
    Check if the sound has been loaded into the engine.
    \return
    True if the sound has been loaded, false otherwise.
    ***********************************************************************/
    bool isLoaded() const { return loaded; }

    /*!
    ***********************************************************************
    \brief
    Get the X position in 3D space.
    \return
    The X position in 3D space.
    ***********************************************************************/
    float getX() const { return x; }

    /*!
    ***********************************************************************
    \brief
    Get the Y position in 3D space.
    \return
    The Y position in 3D space.
    ***********************************************************************/
    float getY() const { return y; }

    /*!
    ***********************************************************************
    \brief
    Get the Z position in 3D space.
    \return
    The Z position in 3D space.
    ***********************************************************************/
    float getZ() const { return z; }

    /*!
    ***********************************************************************
    \brief
    Set the sound to loop.
    ***********************************************************************/
    inline void setLoop() { loop = true; }

    /*!
    ***********************************************************************
    \brief
    Set the volume of the sound.
    \param[in] newVolume
    The new volume of the sound (0.0 to 1.0).
    ***********************************************************************/
    void setVolume(float newVolume) { volume = newVolume; }

    /*!
    ***********************************************************************
    \brief
    Set whether the sound has been loaded into the engine.
    \param[in] isLoaded
    True if the sound is loaded, false otherwise.
    ***********************************************************************/
    void setLoaded(bool isLoaded) { loaded = isLoaded; }

    /*!
    ***********************************************************************
    \brief
    Set the X position in 3D space.
    \param[in] newX
    The new X position in 3D space.
    ***********************************************************************/
    void setX(float newX) { x = newX; }

    /*!
    ***********************************************************************
    \brief
    Set the Y position in 3D space.
    \param[in] newY
    The new Y position in 3D space.
    ***********************************************************************/
    void setY(float newY) { y = newY; }

    /*!
    ***********************************************************************
    \brief
    Set the Z position in 3D space.
    \param[in] newZ
    The new Z position in 3D space.
    ***********************************************************************/
    void setZ(float newZ) { z = newZ; }

    // You can add getters and setters for other attributes as needed.

private:
    std::string filePath;     // File path to the sound file
    std::string uniqueID;     // Unique identifier for the sound
    bool getis3D;             // Is the sound 3D (position-based)?
    bool loop;                // Should the sound loop?
    float volume;             // Volume of the sound (0.0 to 1.0)
    float reverbAmount;       // Reverb amount for the sound (0.0 to 1.0)
    bool loaded;              // Has the sound been loaded into the engine?
    float x{};                // X position in 3D space
    float y{};                // Y position in 3D space
    float z{};                // Z position in 3D space
};
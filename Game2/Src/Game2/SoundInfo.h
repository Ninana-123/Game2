#pragma once
//#include "pch.h"

/**
 * A class to hold information about a sound, including its file path, unique ID,
 * 3D attributes, and playback settings.
 */



    class SoundInfo {
    public:
        SoundInfo(const std::string& filePath, const std::string& uniqueID, bool is3D = false, bool loop = false,
            float volume = 1.0f, float reverbAmount = 0.0f)
            : filePath(filePath), uniqueID(uniqueID), getis3D(is3D), loop(loop),
            volume(volume), reverbAmount(reverbAmount), loaded(false), x(x), y(y), z(z) {}

        const std::string& getFilePath() const { return filePath; }
        const std::string& getUniqueID() const { return uniqueID; }
        bool is3D() const { return getis3D; }
        bool isLoop() const { return loop; }
        float getVolume() const { return volume; }
        float getReverbAmount() const { return reverbAmount; }
        bool isLoaded() const { return loaded; }
        float getX() const { return x; }
        float getY() const { return y; }
        float getZ() const { return z; }
        inline void setLoop() { loop = true; }

        void setVolume(float newVolume) { volume = newVolume; }
        void setLoaded(bool isLoaded) { loaded = isLoaded; }
        void setX(float newX) { x = newX; }
        void setY(float newY) { y = newY; }
        void setZ(float newZ) { z = newZ; }
        // You can add getters and setters for other attributes as needed.

    private:
        std::string filePath;   // File path to the sound file
        std::string uniqueID;   // Unique identifier for the sound
        bool getis3D;              // Is the sound 3D (position-based)?
        bool loop;              // Should the sound loop?
        float volume;           // Volume of the sound (0.0 to 1.0)
        float reverbAmount;     // Reverb amount for the sound (0.0 to 1.0)
        bool loaded;            // Has the sound been loaded into the engine?
        float x{};                // X position in 3D space
        float y{};                // Y position in 3D space
        float z{};                // Z position in 3D space
    };


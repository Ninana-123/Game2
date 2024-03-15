/******************************************************************************/
/*!
\file		AudioEngine.cpp
\author 	Tay Jun Feng Vance
\co         Wayne Kwok Jun Lin (10%)
\par    	email: junfengvance.t@digipen.edu
\date       29/09/2023
\brief		This file contains the definition of all functions related to the FMOD
            API to allow audio file-based implementations alongside the use of FMOD
            Sound Banks.
            With reference to FMOD documentation.

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#include "pch.h"
#include "AudioEngine.h"
#include <fmod_errors.h>
#include "logger.h"
#include <iostream>

AudioEngine::AudioEngine() : sounds(), loopsPlaying(), soundBanks(),
eventDescriptions(), eventInstances(), reverb() {}

void AudioEngine::init() {
    // Initialize FMOD Studio and Core systems
    ERRCHECK(FMOD::Studio::System::create(&studioSystem));
    ERRCHECK(studioSystem->getCoreSystem(&lowLevelSystem));

    // Set software format and 3D settings
    ERRCHECK(lowLevelSystem->setSoftwareFormat(AUDIO_SAMPLE_RATE, FMOD_SPEAKERMODE_STEREO, 0));
    ERRCHECK(lowLevelSystem->set3DSettings(0.0, DISTANCEFACTOR, 0.0f));

    // Initialize the audio engine
    ERRCHECK(studioSystem->initialize(MAX_AUDIO_CHANNELS, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, 0));
    ERRCHECK(lowLevelSystem->getMasterChannelGroup(&mastergroup));

    // Initialize reverb effect
    initReverb();
}

void AudioEngine::deactivate() {
    lowLevelSystem->close();
    studioSystem->release();
}

void AudioEngine::update() {
    ERRCHECK(studioSystem->update()); // also updates the low level system
}

void AudioEngine::loadSound(SoundInfo soundInfo) {
    if (!soundInfo.isLoaded()) {
        std::cout << "Audio Engine: Loading Sound from file " << soundInfo.getFilePath() << '\n';
        FMOD::Sound* sound;
        FMOD_RESULT result = lowLevelSystem->createSound(soundInfo.getFilePath().c_str(), soundInfo.is3D() ? FMOD_3D : FMOD_2D, 0, &sound);
        if (result != FMOD_OK) {
            std::cout << "Audio Engine: Error creating sound - " << FMOD_ErrorString(result) << '\n';
            return;
        }
        FMOD_MODE mode;
        result = sound->getMode(&mode);
        if (result != FMOD_OK) {
            std::cout << "Audio Engine: Error getting sound mode - " << FMOD_ErrorString(result) << '\n';
            return;
        }
        std::cout << "Audio Engine: Sound mode - " << mode << '\n';

        ERRCHECK(sound->setMode(soundInfo.isLoop() ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF));

        sounds.insert({ soundInfo.getUniqueID(), sound });
        soundInfo.setLoaded(true);
    }
    else {
        std::cout << "Audio Engine: Sound File was already loaded!\n";
    }
}

void AudioEngine::playSound(SoundInfo soundInfo) {
    if (!soundInfo.isLoaded()) {
        //std::cout << "Playing Sound\n";
        FMOD::Channel* channel;
        // start play in 'paused' state
        ERRCHECK(lowLevelSystem->playSound(sounds[soundInfo.getUniqueID()], 0, true /* start paused */, &channel));

        if (soundInfo.is3D())
            set3dChannelPosition(soundInfo, channel);

        //std::cout << "Playing sound at volume " << soundInfo.getVolume() << '\n';
        channel->setVolume(soundInfo.getVolume());

        if (soundInfo.isLoop()) // add to channel map of sounds currently playing, to stop later
            loopsPlaying.insert({ soundInfo.getUniqueID(), channel });

        ERRCHECK(channel->setReverbProperties(0, soundInfo.getReverbAmount()));

        // start audio playback
        ERRCHECK(channel->setPaused(false));

    }
    else
        std::cout << "Audio Engine: Can't play, sound was not loaded yet from " << soundInfo.getFilePath() << '\n';
}

void AudioEngine::stopSound(SoundInfo soundInfo)
{
    if (soundIsPlaying(soundInfo))
    {
        ERRCHECK(loopsPlaying[soundInfo.getUniqueID()]->stop());
        loopsPlaying.erase(soundInfo.getUniqueID());
    }
    // else
        // std::cout << "Audio Engine: Can't stop a looping sound that's not playing!\n";
}

void AudioEngine::pauseAllAudio() {
    // Engine::Logger::GetInstance().Log(Engine::LogLevel::Info, "Pausing all audio.");

    if (loopsPlaying.empty()) {
        // Engine::Logger::GetInstance().Log(Engine::LogLevel::Info, "No channels in loopsPlaying.");
        return;
    }

    for (const auto& pair : loopsPlaying) {
        FMOD::Channel* channel = pair.second;

        // Debug messages for loop
        //Engine::Logger::GetInstance().Log(Engine::LogLevel::Info, "Inside pauseAllAudio loop. Checking channel: " + pair.first);

        bool isPausedBefore;
        channel->getPaused(&isPausedBefore);
        //Engine::Logger::GetInstance().Log(Engine::LogLevel::Info, "Checking channel: " + pair.first + " (IsPausedBefore: " 
        //    + (isPausedBefore ? "true" : "false") + ")");

        if (!isPausedBefore) {
            //Engine::Logger::GetInstance().Log(Engine::LogLevel::Info, "Pausing channel: " + pair.first);
            ERRCHECK(channel->setPaused(true));
        }

        bool isPausedAfter;
        channel->getPaused(&isPausedAfter);
        //Engine::Logger::GetInstance().Log(Engine::LogLevel::Info, "Paused channel: " + pair.first + " (WasPaused: " 
        //    + (isPausedBefore ? "true" : "false") + ", IsPausedAfter: " + (isPausedAfter ? "true" : "false") + ")");
    }
}

void AudioEngine::pauseSound(SoundInfo soundInfo) {
    // Check if the sound is loaded
    if (!soundLoaded(soundInfo)) {
        // std::cerr << "Error: Sound not loaded. Cannot pause." << std::endl;
        return;
    }

    // Get the unique key for the sound
    std::string uniqueKey = soundInfo.getUniqueID();

    // Check if the sound is playing
    auto it = loopsPlaying.find(uniqueKey);
    if (it != loopsPlaying.end()) {
        FMOD::Channel* channel = it->second;

        // Pause the sound
        bool isPaused;
        channel->getPaused(&isPaused);
        channel->setPaused(!isPaused);
    }
    else {
        // std::cerr << "Error: Sound not playing. Cannot pause." << std::endl;
    }
}

void AudioEngine::resumeAllAudio() {
    //Engine::Logger::GetInstance().Log(Engine::LogLevel::Info, "Playing all audio.");

    if (loopsPlaying.empty()) {
        //Engine::Logger::GetInstance().Log(Engine::LogLevel::Info, "No channels in loopsPlaying.");
        return;
    }

    // Log the contents of loopsPlaying before resuming
    //Engine::Logger::GetInstance().Log(Engine::LogLevel::Info, "Channels playing before resume:");
    //for (const auto& pair : loopsPlaying) {
    //    //Engine::Logger::GetInstance().Log(Engine::LogLevel::Info, "Channel ID: " + pair.first);
    //}

    for (const auto& pair : loopsPlaying) {
        FMOD::Channel* channel = pair.second; // Use the channel directly

        // Debug messages for loop
        // Engine::Logger::GetInstance().Log(Engine::LogLevel::Info, "Inside resumeAllAudio loop. Checking channel: " + pair.first);

        bool isPausedBefore;
        channel->getPaused(&isPausedBefore);
        //Engine::Logger::GetInstance().Log(Engine::LogLevel::Info, "Checking channel: " + pair.first + " (IsPausedBefore: " 
        //    + (isPausedBefore ? "true" : "false") + ")");

        if (isPausedBefore) {
            // Engine::Logger::GetInstance().Log(Engine::LogLevel::Info, "Resuming channel: " + pair.first);
            ERRCHECK(channel->setPaused(false));
        }

        bool isPausedAfter;
        channel->getPaused(&isPausedAfter);
        //Engine::Logger::GetInstance().Log(Engine::LogLevel::Info, "Resumed channel: " + pair.first + " (WasPaused: " 
        //    + (isPausedBefore ? "true" : "false") + ", IsPausedAfter: " + (isPausedAfter ? "true" : "false") + ")");
    }
}

void AudioEngine::resumeSound(SoundInfo soundInfo) {
    // Check if the sound is loaded
    if (!soundLoaded(soundInfo)) {
        // std::cerr << "Error: Sound not loaded. Cannot resume." << std::endl;
        return;
    }

    // Get the unique key for the sound
    std::string uniqueKey = soundInfo.getUniqueID();

    // Check if the sound is playing and paused
    auto it = loopsPlaying.find(uniqueKey);
    if (it != loopsPlaying.end()) {
        FMOD::Channel* channel = it->second;

        // Check if the sound is paused
        bool isPaused;
        channel->getPaused(&isPaused);
        if (isPaused) {
            // Resume the sound
            channel->setPaused(false);
        }
        else {
            // std::cerr << "Error: Sound is not paused. Cannot resume." << std::endl;
        }
    }
    else {
        // std::cerr << "Error: Sound not playing. Cannot resume." << std::endl;
    }
}

void AudioEngine::updateSoundLoopVolume(SoundInfo& soundInfo, float newVolume, unsigned int fadeSampleLength)
{
    if (soundIsPlaying(soundInfo)) {
        FMOD::Channel* channel = loopsPlaying[soundInfo.getUniqueID()];
        if (fadeSampleLength <= 64) // 64 samples is default volume fade out
            ERRCHECK(channel->setVolume(newVolume));
        else {
            bool fadeUp = newVolume > soundInfo.getVolume();
            // get current audio clock time
            unsigned long long parentclock = 0;
            ERRCHECK(channel->getDSPClock(NULL, &parentclock));

            float targetFadeVol = fadeUp ? 1.0f : newVolume;

            if (fadeUp) ERRCHECK(channel->setVolume(newVolume));

            ERRCHECK(channel->addFadePoint(parentclock, soundInfo.getVolume()));
            ERRCHECK(channel->addFadePoint(parentclock + fadeSampleLength, targetFadeVol));
            //std::cout << "Current DSP Clock: " << parentclock << ", fade length in samples  = " << fadeSampleLength << "\n";
        }
        //std::cout << "Updating with new soundinfo vol \n";
        soundInfo.setVolume(newVolume); // update the SoundInfo's volume
    }
    //else
    //    std::cout << "AudioEngine: Can't update sound loop volume! (It isn't playing or might not be loaded)\n";
}

void AudioEngine::update3DSoundPosition(SoundInfo soundInfo) {
    if (soundIsPlaying(soundInfo))
        set3dChannelPosition(soundInfo, loopsPlaying[soundInfo.getUniqueID()]);
    //else
    //    std::cout << "Audio Engine: Can't update sound position!\n";

}

bool AudioEngine::soundIsPlaying(SoundInfo soundInfo) {
    return soundInfo.isLoop() && loopsPlaying.count(soundInfo.getUniqueID());
}

void AudioEngine::set3DListenerPosition(float posX, float posY, float posZ, float forwardX, float forwardY, float forwardZ, float upX, float upY, float upZ) {
    listenerpos = { posX,     posY,     posZ };
    forward = { forwardX, forwardY, forwardZ };
    up = { upX,      upY,      upZ };
    ERRCHECK(lowLevelSystem->set3DListenerAttributes(0, &listenerpos, 0, &forward, &up));
}

unsigned int AudioEngine::getSoundLengthInMS(SoundInfo soundInfo) {
    unsigned int length = 0;
    if (sounds.count(soundInfo.getUniqueID()))
        ERRCHECK(sounds[soundInfo.getUniqueID()]->getLength(&length, FMOD_TIMEUNIT_MS));
    return length;
}

void AudioEngine::loadFMODStudioBank(const char* filepath) {
    // std::cout << "Audio Engine: Loading FMOD Studio Sound Bank " << filepath << '\n';
    FMOD::Studio::Bank* bank = NULL;
    ERRCHECK(studioSystem->loadBankFile(filepath, FMOD_STUDIO_LOAD_BANK_NORMAL, &bank));
    soundBanks.insert({ filepath, bank });
}

void AudioEngine::loadFMODStudioEvent(const char* eventName, std::vector<std::pair<const char*, float>> paramsValues) { // std::vector<std::map<const char*, float>> perInstanceParameterValues) {
    // std::cout << "AudioEngine: Loading FMOD Studio Event " << eventName << '\n';
    FMOD::Studio::EventDescription* eventDescription = NULL;
    ERRCHECK(studioSystem->getEvent(eventName, &eventDescription));
    // Create an instance of the event
    FMOD::Studio::EventInstance* eventInstance = NULL;
    ERRCHECK(eventDescription->createInstance(&eventInstance));
    for (const auto& parVal : paramsValues) {
        // std::cout << "AudioEngine: Setting Event Instance Parameter " << parVal.first << "to value: " << parVal.second << '\n';
        // Set the parameter values of the event instance
        ERRCHECK(eventInstance->setParameterByName(parVal.first, parVal.second));
    }
    eventInstances.insert({ eventName, eventInstance });
    eventDescriptions.insert({ eventName, eventDescription });
}

void AudioEngine::setFMODEventParamValue(const char* eventName, const char* parameterName, float value) {
    if (eventInstances.count(eventName) > 0)
        ERRCHECK(eventInstances[eventName]->setParameterByName(parameterName, value));
    //else
    //    std::cout << "AudioEngine: Event " << eventName << " was not in event instance cache, can't set param \n";

}

void AudioEngine::playEvent(const char* eventName, int instanceIndex) {
    // printEventInfo(eventDescriptions[eventName]);
    auto eventInstance = eventInstances[eventName];
    UNREFERENCED_PARAMETER(eventInstance);
    UNREFERENCED_PARAMETER(instanceIndex);
    if (eventInstances.count(eventName) > 0)
        ERRCHECK(eventInstances[eventName]->start());
    //else
    //    std::cout << "AudioEngine: Event " << eventName << " was not in event instance cache, cannot play \n";
}

void AudioEngine::stopEvent(const char* eventName, int instanceIndex) {
    UNREFERENCED_PARAMETER(instanceIndex);
    if (eventInstances.count(eventName) > 0)
        ERRCHECK(eventInstances[eventName]->stop(FMOD_STUDIO_STOP_ALLOWFADEOUT));
    //else
    //    std::cout << "AudioEngine: Event " << eventName << " was not in event instance cache, cannot stop \n";
}

void AudioEngine::setEventVolume(const char* eventName, float volume0to1) {
    std::cout << "AudioEngine: Setting Event Volume\n";
    ERRCHECK(eventInstances[eventName]->setVolume(volume0to1));
}

bool AudioEngine::eventIsPlaying(const char* eventName, int instance /*= 0*/) {
    UNREFERENCED_PARAMETER(instance);
    FMOD_STUDIO_PLAYBACK_STATE playbackState;
    ERRCHECK(eventInstances[eventName]->getPlaybackState(&playbackState));
    return playbackState == FMOD_STUDIO_PLAYBACK_PLAYING;
}


void AudioEngine::muteAllSounds() {
    ERRCHECK(mastergroup->setMute(true));
    muted = true;
}

void AudioEngine::unmuteAllSound() {
    ERRCHECK(mastergroup->setMute(false));
    muted = false;
}

bool AudioEngine::isMuted() {
    return muted;
}

// Private definitions 
bool AudioEngine::soundLoaded(SoundInfo soundInfo) {
    //std::cout << "Checking sound " << soundInfo.getUniqueID() << " exists\n";
    return sounds.count(soundInfo.getUniqueID()) > 0;
}

void AudioEngine::set3dChannelPosition(SoundInfo soundInfo, FMOD::Channel* channel) {
    FMOD_VECTOR position = { soundInfo.getX() * DISTANCEFACTOR, soundInfo.getY() * DISTANCEFACTOR, soundInfo.getZ() * DISTANCEFACTOR };
    FMOD_VECTOR velocity = { 0.0f, 0.0f, 0.0f }; // TODO Add dopplar (velocity) support
    ERRCHECK(channel->set3DAttributes(&position, &velocity));
}

void AudioEngine::initReverb() {
    ERRCHECK(lowLevelSystem->createReverb3D(&reverb));
    FMOD_REVERB_PROPERTIES prop2 = FMOD_PRESET_CONCERTHALL;
    ERRCHECK(reverb->setProperties(&prop2));
    ERRCHECK(reverb->set3DAttributes(&revPos, revMinDist, revMaxDist));
}

// Error checking/debugging function definitions

void ERRCHECK_fn(FMOD_RESULT result, const char* file, int line) {
    UNREFERENCED_PARAMETER(file);
    if (result != FMOD_OK)
        std::cout << "FMOD ERROR: AudioEngine.cpp [Line " << line << "] " << result << "  - " << FMOD_ErrorString(result) << '\n';
}

void AudioEngine::printEventInfo(FMOD::Studio::EventDescription* eventDescription) {

    int params;
    bool is3D, isOneshot;
    ERRCHECK(eventDescription->getParameterDescriptionCount(&params));
    ERRCHECK(eventDescription->is3D(&is3D));
    ERRCHECK(eventDescription->isOneshot(&isOneshot));

    std::cout << "FMOD EventDescription has " << params << " parameter descriptions, "
        << (is3D ? " is " : " isn't ") << " 3D, "
        << (isOneshot ? " is " : " isn't ") << " oneshot, "
        << (eventDescription->isValid() ? " is " : " isn't ") << " valid."
        << '\n';
}
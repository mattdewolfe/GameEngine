//build from http://katyscode.wordpress.com/2012/10/05/cutting-your-teeth-on-fmod-part-1-build-environment-initialization-and-playing-sounds/

#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <string>
#include <map>

#include "audio\fmod\fmod.hpp"
#include "Audio\fmod\fmod_errors.h"

typedef std::map<std::string, FMOD::Sound*>::iterator soundMapIT;
typedef std::map<std::string, FMOD::Channel*>::iterator channelMapIT;

class AudioManager
{
private:
	//
	FMOD::System *fm_system;
	FMOD_RESULT fm_result;
	FMOD_SPEAKERMODE speakerMode;
	
	//FMOD_CAPS caps;
	char name[256];
	int numDrivers;

	//map of sounds for quick retrieval
	std::map<std::string, FMOD::Sound*> soundMap;
	//map of channels for quick retrieval.
	std::map<std::string, FMOD::Channel*> channelMap;

	//maintained vars, applied unless specified otherwise
	float soundVolume;
	float musicVolume;
protected:
	//
public:
	AudioManager();
	~AudioManager();

	bool Init();
	void Update(float _dt);
	void Shutdown();

	void CreateSound(std::string _name);
	void CreateAudioStream(std::string _name);

	void PlaySound(std::string _key);
	void PauseSound(std::string _key);
	void PauseAllSounds();
	void ResumeSound(std::string _key);
	void ResumeAllSounds();
	void StopSound(std::string _key);
	void StopAllSounds();
	
	void SetSoundVolume(std::string _key);
	void SetSoundVolume(float _new);
	void SetMusicVolume(float _new);
	void UnmuteAllSounds();
	void MuteAllSounds();
};

#endif

//KW
#include "Audio\AudioManager.h"

#define MAXCHANNELS 100

#define CHECKFMODRESULT(r) if(r != FMOD_OK) { FMOD_ErrorString(r); return false; } 

#pragma region cons/des
AudioManager::AudioManager()
{

}

AudioManager::~AudioManager()
{

}

#pragma endregion

#pragma region init/run/shutdown
bool AudioManager::Init()
{
	//creating the fmod system for the audio system. 
	fm_result = FMOD::System_Create(&fm_system);
	CHECKFMODRESULT(fm_result);

	fm_result = fm_system->getNumDrivers(&numDrivers);
	CHECKFMODRESULT(fm_result);

	//no sound cards -> disabled sounds.
	if(numDrivers == 0)
	{
		fm_result = fm_system->setOutput(FMOD_OUTPUTTYPE_NOSOUND);
		CHECKFMODRESULT(fm_result);
	}

	fm_result = fm_system->getDriverInfo(0, name, 256, 0, 0, 0, 0);
	CHECKFMODRESULT(fm_result);

	//actually initialize fmod.
	fm_result = fm_system->init(MAXCHANNELS, FMOD_INIT_NORMAL, 0);
	if(fm_result == FMOD_ERR_OUTPUT_CREATEBUFFER)
	{
		fm_result = fm_system->setSoftwareFormat(48000, FMOD_SPEAKERMODE_STEREO, 0);
	}
	CHECKFMODRESULT(fm_result);

	return true;
}

void AudioManager::Update(float _dt)
{

}

void AudioManager::Shutdown()
{
	//release all memory allocated to short sounds.
	for(soundMapIT it = soundMap.begin(); it != soundMap.end(); ++it)
	{
		(*it).second->release();
	}

	//release the fmod system.
	fm_system->release();
}
#pragma endregion

#pragma region creation

//requires full name "gamma.ogg" for instance.
void AudioManager::CreateSound(std::string _name)
{
	// "Assets/Audio Assets/my noise.wewe "
	std::string path = "Assets/Audio Assets/" + _name;

	FMOD::Sound* temp;
	fm_system->createSound(path.c_str(), FMOD_DEFAULT, 0 , &temp);
	soundMap[_name] = temp;

	FMOD::Channel* tempChannel;
	tempChannel->setVolume(soundVolume);
	channelMap[_name] = tempChannel;
}

void AudioManager::CreateAudioStream(std::string _name)
{
	
}

#pragma region

#pragma region adjust playback
void AudioManager::PlaySound(std::string _key)
{
	channelMap[_key]->setVolume(soundVolume);
	fm_system->playSound(soundMap[_key], NULL, false, &channelMap[_key]);
}

void AudioManager::PauseSound(std::string _key)
{
	bool isPlaying;
	fm_result = channelMap[_key]->isPlaying(&isPlaying);

	if(isPlaying == true)
	{
		channelMap[_key]->setPaused(true);
	}
}

void AudioManager::PauseAllSounds()
{
	for(channelMapIT it = channelMap.begin(); it != channelMap.end(); ++it)
	{
		bool isPlaying;
		fm_result = it->second->isPlaying(&isPlaying);

		if(isPlaying == true)
		{
			it->second->setPaused(true);
		}
	}
}

void AudioManager::ResumeSound(std::string _key)
{
	bool isPlaying;
	fm_result = channelMap[_key]->isPlaying(&isPlaying);

	if(isPlaying == false)
	{
		channelMap[_key]->setPaused(false);
	}
}

void AudioManager::ResumeAllSounds()
{
	for(channelMapIT it = channelMap.begin(); it != channelMap.end(); ++it)
	{
		bool isPlaying;
		fm_result = it->second->isPlaying(&isPlaying);

		if(isPlaying == false)
		{
			it->second->setPaused(false);
		}
	}
}

void AudioManager::StopSound(std::string _key)
{
	channelMap[_key]->stop();
}

void AudioManager::StopAllSounds()
{
	for(channelMapIT it = channelMap.begin(); it != channelMap.end(); ++it)
	{
		it->second->stop();
	}
}

#pragma endregion

#pragma region adjust volume 
void AudioManager::SetSoundVolume(float _new)
{
	soundVolume = _new;
}

void AudioManager::SetMusicVolume(float _new)
{
	musicVolume = _new;
}

void AudioManager::UnmuteAllSounds()
{
	for(channelMapIT it = channelMap.begin(); it != channelMap.end(); ++it)
	{
		bool isMuted;
		fm_result = it->second->isPlaying(&isMuted);

		if(isMuted == true)
		{
			it->second->setMute(false);
		}
	}
}

void AudioManager::MuteAllSounds()
{
	for(channelMapIT it = channelMap.begin(); it != channelMap.end(); ++it)
	{
		bool isMuted;
		fm_result = it->second->isPlaying(&isMuted);

		if(isMuted == false)
		{
			it->second->setPaused(true);
		}
	}
}

#pragma endregion

//KW
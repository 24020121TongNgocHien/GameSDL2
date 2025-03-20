#pragma once

#include"CommonFunc.h"

class Music {
private:
    Mix_Music* music; 

public:

    Music(const std::string& filePath) {
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
            std::cerr << "error init SDL_mixer: " << Mix_GetError() << std::endl;
        }

        music = Mix_LoadMUS(filePath.c_str());
        if (!music) {
            std::cerr << "error load music: " << Mix_GetError() << std::endl;
        }
    }

    
    void play() {
        if (music) {
            Mix_PlayMusic(music, -1);
        }
    }

    
    // D?ng nh?c
    void stop() {
        Mix_HaltMusic();
    }

    // ?i?u ch?nh âm l??ng (0 - 128)
    void setVolume(int volume) {
        Mix_VolumeMusic(volume);
    }

    // Destructor: Gi?i phóng b? nh?
    ~Music() {
        Mix_FreeMusic(music);
        Mix_CloseAudio();
    }
};

#include "global.h"

int current_volume = 100;

void playBGM(const wchar_t path[])
{
    PlaySoundW(path, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}

void stopBGM()
{
    PlaySound(NULL, 0, 0);
}

void playSFX(const wchar_t path[])
{
    wstring command = L"play \"" + wstring(path) + L"\"";

    mciSendStringW(command.c_str(), NULL, 0, NULL);
}

void setVolume(int volume)
{
    if(volume < 0)
        volume = 0;

    if(volume > 100)
        volume = 100;

    current_volume = volume;

    DWORD win_volume = (65535 * volume) / 100;

    DWORD final_volume =(win_volume & 0xFFFF) | (win_volume << 16);

    waveOutSetVolume(0, final_volume);
}
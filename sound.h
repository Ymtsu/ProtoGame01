#pragma once

#include <windows.h>
#include "xaudio2.h"


bool InitSound(HWND hWnd);
void UninitSound(void);

int LoadSound(char* pFilename);
void PlaySounds(int index, int loopCount);
void ReplaySound(int index);//プレイサウンドが発動した後でないと仕事しない
void StopSound(int index);
void PauseSound(int index);
void StopSoundAll(void);
void SetVolume(int index, float vol);//第2引数：ボリュームの大きさ。0.0f～1.0f
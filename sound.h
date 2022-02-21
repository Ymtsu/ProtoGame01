#pragma once

#include <windows.h>
#include "xaudio2.h"


bool InitSound(HWND hWnd);
void UninitSound(void);

int LoadSound(char* pFilename);
void PlaySounds(int index, int loopCount);
void ReplaySound(int index);//�v���C�T�E���h������������łȂ��Ǝd�����Ȃ�
void StopSound(int index);
void PauseSound(int index);
void StopSoundAll(void);
void SetVolume(int index, float vol);//��2�����F�{�����[���̑傫���B0.0f�`1.0f
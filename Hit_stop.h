#pragma once
#include "main.h"
#include "collision.h"

//�����F���݂̎���, �q�b�g�X�g�b�v���n�܂鎞��(��{0�B�����̍d�����Ⴄ�ꍇ�g�p), 
// �@�@ �q�b�g�X�g�b�v���I��鎞��, �ǂ̂��炢�̒x���ɂȂ邩�̕ω���(0�`10)
//�߂�l�F���݂̃A�j���[�V�����i60���A�j���[�V�����O��j
int HitStop(int now_time, int start_time, int finish_time, int rate_of_change);
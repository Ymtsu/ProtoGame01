#include "random.h"
#include <random>
#include <time.h>

float FloatRandom(float min, float max)
{
	uint32_t get_rand_range(uint32_t min_val, uint32_t max_val);
	{
		// ����������i�����ɃV�[�h���w��j
		static std::mt19937 mt32((unsigned int)time(NULL));

		// [min_val, max_val] �̈�l���z���� (float) �̕��z������
		std::uniform_real_distribution<float> get_rand_uni_real(min, max);

		// �����𐶐�
		return get_rand_uni_real(mt32);
	}
}

int IntRandom(int min, int max)
{
	uint32_t get_rand_range(uint32_t min_val, uint32_t max_val);
	{
		// ����������i�����ɃV�[�h���w��j
		static std::mt19937 mt32((unsigned int)time(NULL));

		// [min_val, max_val] �̈�l���z���� (int) �̕��z������
		std::uniform_int_distribution<int> get_rand_uni_int(min, max);

		// �����𐶐�
		return get_rand_uni_int(mt32);
	}
}

bool FlagRandom(float probability)
{
	// ����������i�����ɃV�[�h���w��j
	static std::default_random_engine engine((unsigned int)time(NULL));

	// �����l�̊m���ł̃x���k�[�C���z(bool�^)�̕��z������
	std::bernoulli_distribution get_rand_uni_bool(probability);

	// �����𐶐�
	return get_rand_uni_bool(engine);
}

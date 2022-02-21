#include "random.h"
#include <random>
#include <time.h>

float FloatRandom(float min, float max)
{
	uint32_t get_rand_range(uint32_t min_val, uint32_t max_val);
	{
		// 乱数生成器（引数にシードを指定）
		static std::mt19937 mt32((unsigned int)time(NULL));

		// [min_val, max_val] の一様分布実数 (float) の分布生成器
		std::uniform_real_distribution<float> get_rand_uni_real(min, max);

		// 乱数を生成
		return get_rand_uni_real(mt32);
	}
}

int IntRandom(int min, int max)
{
	uint32_t get_rand_range(uint32_t min_val, uint32_t max_val);
	{
		// 乱数生成器（引数にシードを指定）
		static std::mt19937 mt32((unsigned int)time(NULL));

		// [min_val, max_val] の一様分布整数 (int) の分布生成器
		std::uniform_int_distribution<int> get_rand_uni_int(min, max);

		// 乱数を生成
		return get_rand_uni_int(mt32);
	}
}

bool FlagRandom(float probability)
{
	// 乱数生成器（引数にシードを指定）
	static std::default_random_engine engine((unsigned int)time(NULL));

	// 引数値の確率でのベルヌーイ分布(bool型)の分布生成器
	std::bernoulli_distribution get_rand_uni_bool(probability);

	// 乱数を生成
	return get_rand_uni_bool(engine);
}

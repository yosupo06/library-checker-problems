#include <cstdint>
#include <iostream>
#include <tuple>

#include "random.h"
#include "../params.h"

using namespace std;

int main(int, char* argv[])
{
	long long seed = atoll(argv[1]);
	auto gen = Random(seed);

	std::size_t n{gen.uniform<std::size_t>(1, N_AND_Q_MAX)};
	std::uint32_t q{gen.uniform<std::uint32_t>(1, N_AND_Q_MAX)};
	printf("%zu %u\n", n, q);

	for(std::size_t i = 0; i < n; ++i)
	{
		printf("%lld", gen.uniform<long long>(-A_K_MIN_MAX, A_K_MIN_MAX));
		if(i != n - 1)
		{ printf(" "); }
	}
	printf("\n");

	for(std::uint32_t t = 0; t < q; ++t)
	{
		std::uint16_t queryType{gen.uniform<std::uint16_t>(0, 1)};
		std::pair<std::size_t, std::size_t> bounds{gen.uniform_pair<std::size_t>(0, n)};
		printf("%hu %zu %zu", queryType, bounds.first, bounds.second - 1);
		if(!queryType)
		{ printf(" %lld", gen.uniform<long long>(-A_K_MIN_MAX, A_K_MIN_MAX)); }
		printf("\n");
	}
}

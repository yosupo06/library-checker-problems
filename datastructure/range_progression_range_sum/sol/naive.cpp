// Rahul Chalamala (rchalamala)
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <vector>

constexpr int32_t MODULUS{998244353};

int main()
{
	std::size_t n;
	std::uint32_t q;
	scanf("%zu %u", &n, &q);
	std::vector<std::int64_t> a(n);
	for(auto& ai : a)
	{ scanf("%jd", &ai); }
	for(std::uint32_t t = 0; t < q; ++t)
	{
		std::uint16_t queryType;
		scanf("%hu ", &queryType);
		if(queryType)
		{
			std::size_t l, r;
			scanf("%zu %zu", &l, &r);
			int64_t result{};
			for(; l <= r; ++l)
			{ (result += a[l]) %= MODULUS; }
			printf("%jd\n", result);
		}
		else
		{
			std::size_t l, r;
			std::int64_t k;
			scanf("%zu %zu %jd", &l, &r, &k);
			k %= MODULUS;
			if(k < 0)
			{ k += MODULUS; }
			for(size_t i = 1; l + i - 1 <= r; ++i)
			{ (a[l + i - 1] += ((i * k) % MODULUS)) %= MODULUS; }
		}
	}
}

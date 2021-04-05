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
	std::vector<long long> a(n);
	for(auto& ai : a)
	{ scanf("%lld", &ai); }
	for(std::uint32_t t = 0; t < q; ++t)
	{
		std::uint16_t queryType;
		scanf("%hu ", &queryType);
		if(queryType)
		{
			std::size_t l, r;
			scanf("%zu %zu", &l, &r);
			long long result{};
			for(; l <= r; ++l)
			{ (result += a[l]) %= MODULUS; }
			printf("%lld\n", result);
		}
		else
		{
			std::size_t l, r;
			std::long long k;
			scanf("%zu %zu %lld", &l, &r, &k);
			k %= MODULUS;
			if(k < 0)
			{ k += MODULUS; }
			for(size_t i = 1; l + i - 1 <= r; ++i)
			{ (a[l + i - 1] += ((i * k) % MODULUS)) %= MODULUS; }
		}
	}
}

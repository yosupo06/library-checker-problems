// Rahul Chalamala (rchalamala)
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <vector>

constexpr int32_t MODULUS{998244353};

template<class T> class SegmentTree
{
private:
	struct Node
	{
		T value{}, delta{}, deltaAP{};

		Node(const T& uValue, const T& uDelta, const T& uDeltaAP) : value{uValue}, delta{uDelta}, deltaAP{uDeltaAP}
		{
		}

		Node(const T& uValue) : value{uValue}
		{
		}

		Node()
		{
		}
	};

	const std::size_t size;
	std::vector<Node> tree;

	void propagate_update(const std::size_t& parent, const std::size_t& leftChild, const std::size_t& rightChild, const std::size_t& intervalLength)
	{
		if(tree[parent].delta)
		{
			if(intervalLength > 1)
			{
				(tree[leftChild].delta += tree[parent].delta) %= MODULUS;
				(tree[rightChild].delta += tree[parent].delta) %= MODULUS;
			}
			(tree[parent].value += intervalLength * tree[parent].delta) %= MODULUS;
			tree[parent].delta = 0;
		}
		if(tree[parent].deltaAP)
		{
			if(intervalLength > 1)
			{
				(tree[leftChild].deltaAP += tree[parent].deltaAP) %= MODULUS;
				(tree[rightChild].deltaAP += tree[parent].deltaAP) %= MODULUS;
				(tree[rightChild].delta += tree[parent].deltaAP * ((intervalLength + 1) >> 1)) %= MODULUS;
			}
			(tree[parent].value += (((((intervalLength * (intervalLength + 1)) >> 1) * tree[parent].deltaAP)) % MODULUS)) %= MODULUS;
			tree[parent].deltaAP = 0;
		}
	}

	void propagate(const std::size_t& i, const std::size_t& treeLeft, const std::size_t& treeRight)
	{
		if(treeLeft != treeRight)
		{ propagate_update(i, i << 1, (i << 1) ^ 1, treeRight - treeLeft + 1); }
		else
		{ propagate_update(i, i, i, 1); }
	}

	template<typename Iterable> void build(const std::size_t& i, const std::size_t& left, const std::size_t& right, const Iterable& elements)
	{
		if(left == right)
		{
			tree[i] = Node{elements[left]};
			return;
		}
		const std::size_t midpoint = left + ((right - left) >> 1);
		build(i << 1, left, midpoint, elements);
		build((i << 1) ^ 1, midpoint + 1, right, elements);
		tree[i] = (tree[i << 1].value + tree[(i << 1) ^ 1].value) % MODULUS;
	}

	void change(const std::size_t& i, const std::size_t& treeLeft, const std::size_t& treeRight, const std::size_t& left, const std::size_t& right, const T& k)
	{
		propagate(i, treeLeft, treeRight);
		if(left > treeRight || treeLeft > right)
		{ return; }
		if(left <= treeLeft && treeRight <= right)
		{
			(tree[i].delta += (((treeLeft - left) * k) % MODULUS)) %= MODULUS;
			(tree[i].deltaAP += k) %= MODULUS;
			propagate(i, treeLeft, treeRight);
			return;
		}
		const std::size_t midpoint = treeLeft + ((treeRight - treeLeft) >> 1);
		change(i << 1, treeLeft, midpoint, left, right, k);
		change((i << 1) ^ 1, midpoint + 1, treeRight, left, right, k);
		tree[i] = (tree[i << 1].value + tree[(i << 1) ^ 1].value) % MODULUS;
	}

	Node range(const std::size_t& i, const std::size_t& treeLeft, const std::size_t& treeRight, const std::size_t& left, const std::size_t& right)
	{
		if(left > treeRight || treeLeft > right)
		{ return {}; }
		propagate(i, treeLeft, treeRight);
		if(left <= treeLeft && treeRight <= right)
		{ return tree[i]; }
		const std::size_t midpoint = treeLeft + ((treeRight - treeLeft) >> 1);
		return (range(i << 1, treeLeft, midpoint, left, right).value + range((i << 1) ^ 1, midpoint + 1, treeRight, left, right).value) % MODULUS;
	}

public:
	explicit SegmentTree(const std::size_t& uSize) : size{uSize}
	{
		tree.assign(size << 2, Node{});
	}

	template<typename Iterable> void build(const Iterable& uElements)
	{
		build(1, 0, size - 1, uElements);
	}

	void change(const std::size_t& left, const std::size_t& right, const T& k)
	{
		change(1, 0, size - 1, left, right, k);
	}

	T range(const std::size_t& left, const std::size_t& right)
	{
		return range(1, 0, size - 1, left, right).value;
	}
};

int main()
{
	std::size_t n;
	std::uint32_t q;
	scanf("%zu %u", &n, &q);
	std::vector<long long> a(n);
	for(auto& ai : a)
	{ scanf("%lld ", &ai); }
	SegmentTree<long long> tree(n);
	tree.build(a);
	for(std::uint32_t t = 0; t < q; ++t)
	{
		std::uint16_t queryType;
		scanf("%hu ", &queryType);
		if(queryType)
		{
			std::size_t l, r;
			scanf("%zu %zu", &l, &r);
			printf("%lld\n", tree.range(l, r));
		}
		else
		{
			std::size_t l, r;
			long long k;
			scanf("%zu %zu %lld", &l, &r, &k);
			k %= MODULUS;
			if(k < 0)
			{ k += MODULUS; }
			tree.change(l, r, k);
		}
	}
}

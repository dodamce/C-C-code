#pragma once

#include<vector>
#include<cassert>

using namespace std;

namespace NUC
{
	template<size_t Size>//Size表示开几位
	class BitSet
	{
	public:
		BitSet() {
			_bits.resize((Size / (4 * 8)) + 1, 0);//多开一个整数，保证所有整数都可以映射到
		}

		void Set(size_t x)//把x映射的位标记为1
		{
			assert(x < Size);
			//先计算x在那个整数上
			size_t index_int = x / 32;
			//计算x在哪一位
			size_t index_bit = x % 32;
			
			_bits[index_int] |= (1 << index_bit);
		}

		void ReSet(size_t x)//把x映射的位标记为0
		{
			assert(x < Size);
			//先计算x在那个整数上
			size_t index_int = x / 32;
			//计算x在哪一位
			size_t index_bit = x % 32;

			_bits[index_int] &= (~(1 << index_bit));
		}

		bool Find(size_t x)//查找x是否在位图上，true为存在
		{
			assert(x < Size);
			//先计算x在那个整数上
			size_t index_int = x / 32;
			//计算x在哪一位
			size_t index_bit = x % 32;

			//判断第index_bit为是否为1
			return ((_bits[index_int] >> index_bit) & 1) == 1;
		}
	private:
		vector<int>_bits;
	};
}
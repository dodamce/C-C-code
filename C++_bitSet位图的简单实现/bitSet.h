#pragma once

#include<iostream>
#include<vector>
#include<cassert>

namespace dodamce
{
	class bitSet
	{
	public:
		bitSet(size_t Size = 100)//位图大小
		{
			_bit.resize(Size / 32 + 1, 0);//0代表数字存在，1代表数字不存在
		}

		void Set(size_t x)//将x映射到的位置标记为1
		{
			size_t Pos = x / 32;
			size_t PosBit = x % 32;
			assert(Pos < _bit.size());

			//_bit[Pos]的PosBit位设置为1代表1这个数字存在

			_bit[Pos] = (1 << PosBit) | _bit[Pos];

		}

		void Reset(size_t x)
		{
			size_t Pos = x / 32;
			size_t PosBit = x % 32;

			//bit[Pos]的PosBit位设置为0标识这个数字被移除

			_bit[Pos] = (~(1 << PosBit)) & _bit[Pos];
		}

		bool Find(size_t x)//查找x在不在位图中
		{
			size_t Pos = x / 32;
			size_t PosBit = x % 32;

			//查找bit[Pos]的PosBit位是1还是0

			if ((_bit[Pos] >> PosBit) & 1)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	private:
		std::vector<int>_bit;
	};
}

#pragma once

#include<iostream>
#include<vector>
#include<cassert>

namespace dodamce
{
	class bitSet
	{
	public:
		bitSet(size_t Size = 100)//λͼ��С
		{
			_bit.resize(Size / 32 + 1, 0);//0�������ִ��ڣ�1�������ֲ�����
		}

		void Set(size_t x)//��xӳ�䵽��λ�ñ��Ϊ1
		{
			size_t Pos = x / 32;
			size_t PosBit = x % 32;
			assert(Pos < _bit.size());

			//_bit[Pos]��PosBitλ����Ϊ1����1������ִ���

			_bit[Pos] = (1 << PosBit) | _bit[Pos];

		}

		void Reset(size_t x)
		{
			size_t Pos = x / 32;
			size_t PosBit = x % 32;

			//bit[Pos]��PosBitλ����Ϊ0��ʶ������ֱ��Ƴ�

			_bit[Pos] = (~(1 << PosBit)) & _bit[Pos];
		}

		bool Find(size_t x)//����x�ڲ���λͼ��
		{
			size_t Pos = x / 32;
			size_t PosBit = x % 32;

			//����bit[Pos]��PosBitλ��1����0

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

#pragma once


//�º��� ��������

template<class T>
struct Less
{
	bool operator()(const T& a,const T& b)
	{
		return a < b;
	}
};

template<class T>
struct Greater
{
	bool operator()(T a, T b)
	{
		return a > b;
	}
};



#pragma once


// �������� �˰���
template<class Data>
class Less_Functor
{
public:
	inline bool operator()(const Data& data1, const Data& data2)
	{
		if (data1 < data2)
		{
			return true;
		}
		return false;
	}
};
// �������� �˰���
template<class Data>
class Greater_Functor
{
public:
	inline bool operator()(const Data& data1, const Data& data2)
	{
		if (data1 < data2)
		{
			return false;
		}
		return true;
	}
};

// ������
template<class Data, class Iterator>
class Quick_Sort_Functor
{
public:
	inline void operator()(Iterator left, Iterator right, const std::function<bool(const Data& data1, const Data& data2)>& func)
	{
		Iterator pivot = left;
		Iterator low = left + 1;
		Iterator high = right;


		while (low < high)
		{
			// low�� left+1���� �����Ͽ� right���� �۰� pivot������ Ŭ������ low�� ����
			while (func(*low, *pivot) && (low < high || low == high)) low++;
			// high�� right ���� �����Ͽ� left+1���� ũ�� pivot������ ���������� high�� ����
			while (!func(*high, *pivot) && (high > left + 1 || high == left + 1)) high--;
			// ���� ���������ʾ��� ��� ����..
			if (low < high || low == high)
			{
				Data tmpData = *low;
				*low = *high;
				*high = tmpData;
			}
		}
		// ���� low�� high �� ����Ű�� ���� ������� low���̳� high���� �ƹ���( ���� �����ϱ�) pivot ���� ���� ���� �ٲ۴�.
		if (low == high && func(*low, *pivot))
		{
			Data tmpData = *pivot;
			*pivot = *high;
			*high = tmpData;
		}
		else if (low != high)
		{
			Data tmpData = *pivot;
			*pivot = *high;
			*high = tmpData;
		}
		if (left < high)
		{
			operator()(left, high - 1,func);
		}
		if (low < right)
		{
			operator()(low, right,func);
		}
	}
};
#pragma once
#include <functional>

// 오름차순 알고리즘
template <class Data>
bool Less(const Data& data1, const Data& data2)
{
	if (data1 <= data2)
	{
		return true;
	}
	return false;
}
template <class Data>
bool Greater(const Data& data1, const Data& data2)
{
	if (data1 <= data2)
	{
		return false;
	}
	return true;
}

// 퀵정렬
template<class Iterator, class Data>
void Quick_Sort(Iterator left, Iterator right, const std::function<bool(const Data& data1, const Data& data2)>& func)
{
	Iterator pivot = left;
	Iterator low = left + 1;
	Iterator high = right;


	while (low < high)
	{
		// low가 left+1부터 시작하여 right보다 작고 pivot값보다 클떄까지 low값 증가
		while (func(*low, *pivot) && (low < high || low == high)) low++;
		// high가 right 부터 시작하여 left+1보다 크고 pivot갑보다 작을때까지 high값 증가
		while (!func(*high, *pivot) && (high > left + 1 || high == left + 1)) high--;
		// 서로 교차하지않았을 경우 스왑..
		if (low < high || low == high)
		{
			Data tmpData = *low;
			*low = *high;
			*high = tmpData;
		}
	}
	// 만약 low와 high 가 가르키는 값이 같을경우 low값이나 high값중 아무나( 차피 같으니까) pivot 값과 비교해 값을 바꾼다.
	if (low == high && func(*low, *pivot))
	{
		Data tmpData = *pivot;
		*pivot = *high;
		*high = tmpData;
	}
	else if(low != high)
	{
		Data tmpData = *pivot;
		*pivot = *high;
		*high = tmpData;
	}
	if (left < high)
	{
		Quick_Sort(left, high - 1, func);
	}
	if (low < right)
	{
		Quick_Sort(low, right, func);
	}

	return;
}
#include <iostream>
#include <chrono>
#include <random>

int main_array[1000000];
int arr[1000000];

int bin_search(int* arr, int len, int key)
{
	int l_idx = 0;
	int r_idx = len - 1;
	while (l_idx <= r_idx)
	{
		int median = (l_idx + r_idx) / 2;
		if (main_array[median] > key)
		{
			r_idx = median - 1;
		}

		else if (main_array[median] < key)
		{
			l_idx = median + 1;
		}
		else
		{
			return median;
		}
	}
	return len;
}

bool line_search(int* arr, int len, int key)
{
	for (unsigned idx = 0; idx != len; idx++)
	{
		if (arr[idx] == key)
		{
			return true;
		}
	}
	return false;
}

int main()
{
	for (int j = 0; j < 1000000; j++)
	{
		arr[j] = j;
	}
	unsigned seed = 50;
	std::default_random_engine rng(seed);
	std::uniform_int_distribution<unsigned> dstr(0, 1000000);

	for (int n = 0; n <= 1000000; n += 10000)
	{
		for (int s = 0; s < n; s++)
		{
			main_array[s] = arr[dstr(rng)];
		}
		std::sort(main_array, main_array + n);
		int const amount(20000);
		auto begin = std::chrono::steady_clock::now();
		for (unsigned cnt = 0; cnt != amount; ++cnt)
		{
			int number = arr[dstr(rng)];
			bin_search(main_array, n, number);
		}
		auto end = std::chrono::steady_clock::now();
		auto time_span = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
		std::cout << n << " " << time_span.count() << std::endl;
	}
}
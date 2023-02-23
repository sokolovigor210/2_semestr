#include <iostream>
#include <chrono>
#include <random>

int main_array[1000000];
int arr[1000000];

bool line_search(int* arr, int len, int key)
{
	for (unsigned idx = 0; idx != len; idx++)
	{
		if (key == arr[idx])
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
	unsigned seed = 1001;
	std::default_random_engine rng(seed);
	std::uniform_int_distribution<unsigned> dstr(0, 1000000);

	for (int n = 0; n <= 1000000; n += 10000)
	{
		for (int s = 0; s < n; s++)
		{
			main_array[s] = arr[dstr(rng)];
		}
		int const amount(2000);
		auto begin = std::chrono::steady_clock::now();
		for (unsigned cnt = 0; cnt != amount; ++cnt)
		{
			int number = arr[dstr(rng)];
			line_search(main_array, n, number);
		}
		auto end = std::chrono::steady_clock::now();
		auto time_span = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);

		std::cout << n << " " << time_span.count() << std::endl;
	}
}
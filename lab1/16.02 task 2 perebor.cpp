#include <iostream>
#include <chrono>
#include <random>

int main_array[500000];
int arr[500000];

int sum_perebor(int n, int key)
{
	int f_idx_res = 0;
	int s_idx_res = 0;
	bool found = false;
	for (int f_idx = 0; f_idx < n && !found; f_idx++)
	{
		for (int s_idx = f_idx + 1; s_idx < n && !found; s_idx++)
		{
			if (main_array[f_idx] + main_array[s_idx] == key && f_idx != s_idx && 
				main_array[f_idx] != main_array[s_idx])
			{
				std::cout << "Values: " << main_array[f_idx] << "and" << main_array[s_idx] << std::endl;
				found = true;
			}
		}
	}
	if (found == false)
	{
		std::cout << "This pair doesn't exist" << std::endl;
	}
	return -1;
}

int main()
{
	for (int j = 0; j < 500000; j++)
	{
		arr[j] = j;
	}
	unsigned seed = 500;
	std::default_random_engine rng(seed);
	std::uniform_int_distribution<unsigned> dstr(0, 500000);

	for (int n = 0; n <= 50000; n += 5000)
	{
		int const amount(5);
		auto begin = std::chrono::steady_clock::now();
		for (unsigned cnt = 0; cnt != amount; ++cnt)
		{
			for (int s = 0; s < n; s++)
			{
				main_array[s] = arr[dstr(rng)] % n;
			}

			int number = 3 * n;
			sum_perebor(n, number);
		}
		auto end = std::chrono::steady_clock::now();
		auto time_span = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
		std::cout << n << " " << time_span.count() << std::endl;
	}
}
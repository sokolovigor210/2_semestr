#include <iostream>
#include <chrono>
#include <random>

int main_array[1000000];
int arr[500000];

void algo(int n, int key)
{
	bool found = false;
	int l_idx = 0;
	int r_idx = n - 1;
	while ((l_idx != r_idx) && (found != true))
	{
		if (main_array[l_idx] + main_array[r_idx] == key)
		{
			//std::cout << "Values: " << main_array[l_idx] << "and" << main_array[r_idx] << std::endl; - to see the elements
			found = true;
		}
		else if (main_array[l_idx] + main_array[r_idx] < key)
		{
			l_idx += 1;
		}
		else if (main_array[l_idx] + main_array[r_idx] > key)
		{
			r_idx -= 1;
		}
	}
	if (found == false)
	{
		std::cout << n << " " << "0" << std::endl;
	}
}

int main()
{
	for (int j = 0; j < 500000; j++)
	{
		arr[j] = j;
	}
	unsigned seed = 1001;
	std::default_random_engine rng(seed);
	std::uniform_int_distribution<unsigned> dstr(0, 500000);

	for (int n = 5000; n <= 500000; n += 5000)
	{
		for (int s = 0; s < n; s++)
		{
			main_array[s] = arr[dstr(rng)];
		}
		std::sort(main_array, main_array + n);
		int const amount(10);

		auto begin = std::chrono::steady_clock::now();
		for (unsigned cnt = 0; cnt != amount; ++cnt)
		{
			int number = arr[dstr(rng)];
			algo(n, number);
		}
		auto end = std::chrono::steady_clock::now();
		auto time_span = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
		std::cout << n << " " << time_span.count() << std::endl;
	}
}
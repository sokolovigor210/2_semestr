#include <iostream>
#include <algorithm>

void optimum(int* nominals, int *opt_coins_amount, int sum, int N)
{
    opt_coins_amount[0] = 0;
    for (int local_sum = 1; local_sum != sum + 1; ++local_sum)
    {
        int local_min_of_coins = std::numeric_limits<int>::max();
        for (int coin_idx = 0; coin_idx != N; ++coin_idx)
        {
            if (local_sum >= nominals[coin_idx])
            {
                local_min_of_coins = std::min(opt_coins_amount[local_sum - nominals[coin_idx]] + 1, local_min_of_coins);
            }
        }
        opt_coins_amount[local_sum] = local_min_of_coins;
    }
    if (opt_coins_amount[sum] < 0)
    {
        std::cout << "Impossiible!" << std::endl;
    }
    else
    {
        std::cout << "Minimal amount of coins to change " << sum << " is " << opt_coins_amount[sum] << std::endl;
        std::cout << "Coins denominations: ";
        int s = sum;
        while (s > 0)
        {
            for (int coin_idx = 0; coin_idx != N; ++coin_idx)
            {
                if (nominals[coin_idx] <= s && opt_coins_amount[s - nominals[coin_idx]] == opt_coins_amount[s] - 1)
                {
                    std::cout << nominals[coin_idx] << ' ';
                    s -= nominals[coin_idx];
                    break;
                }
            }
        }
    }
    }


int input(int* nominals, int N)
{
    for (int i = 0; i < N; ++i)
    {
        int n;
        std::cin >> n;
        nominals[i] = n;
    }
    std::sort(nominals, nominals + N);
    int S;
    std::cout << "Enter sum: " << std::endl;
    std::cin >> S;
    return S;
}

int main()
{
    std::cout << "Enter amount of coins: " << std::endl;
    int N;
    std::cin >> N;
    std::cout << "Enter denominations of coins: " << std::endl;
    int *nominals = new int[N];

    int sum = input(nominals, N);

    int* opt_coins_amount = new int[sum + 1];

    for (int i = 0; i < sum + 1; ++i)
    {
        opt_coins_amount[i] = 0;
    }

    optimum(nominals, opt_coins_amount, sum, N);

    delete[] nominals;
    delete[] opt_coins_amount;

    return 0;
}

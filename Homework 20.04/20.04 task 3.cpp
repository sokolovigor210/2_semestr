#include <iostream>

int optim_way(int** p, int** act_fine, int M, int N, int money)
{
    act_fine[0][0] = p[0][0];
    for (int i = 1; i < M; ++i)
    {
        act_fine[0][i] = act_fine[0][i - 1] + p[0][i];
    }
    for (int j = 1; j < N; ++j)
    {
        act_fine[j][0] = act_fine[j - 1][0] + p[j][0];
    }
    for (int i = 1; i < M; ++i)
    {
        for (int j = 1; j < N; ++j)
        {
            act_fine[i][j] = p[i][j] + std::min(act_fine[i - 1][j], act_fine[i][j - 1]);
        }
    }
    if ( money - act_fine[M - 1][N - 1] < 0)
    {
        std::cout << "Impossible!" << std::endl;
        return -1;
    }
    else
    {
        return money - act_fine[M - 1][N - 1];
    }
}


int input_and_filling(int** p, int** act_money, int M, int N)
{
    M = std::max(M, 2);
    N = std::max(N, 2);
    for (int i = 0; i < M; ++i)
    {
        p[i] = new int[N];
        for (int j = 0; j < N; ++j)
        {
            std::cin >> p[i][j];
        }
    }

    for (int i = 0; i < M; ++i)
    {
        act_money[i] = new int[N];
        for (int j = 0; j < N; ++j)
        {
            act_money[i][j] = std::numeric_limits<int>::max();
        }
    }

    std::cout << "Enter Vasya's money: " << std::endl;
    int C;
    std::cin >> C;
    return C;
}

void output(int** p, int** act_money, int M, int N, int C)
{
    int result = optim_way(p, act_money, M, N, C);

    if (result > 0)
    {
        std::cout << "Remaining money: " << result << std::endl;
    }
}


int main()
{
    std::cout << "Enter field's size: " << std::endl;
    int M; // количество строк
    int N; // количество столбцов
    std::cin >> M >> N;
    M = std::max(M, 2);
    N = std::max(N, 2);
    int** p = new int* [M];
    int** act_fine = new int* [M];

    std::cout << "Enter field's fines: " << std::endl;

    int money = input_and_filling(p, act_fine, M, N);

    output(p, act_fine, M, N, money);

    for (int i = 0; i < N; ++i)
    {
        delete[] p[i];
    }

    for (int i = 0; i < N; ++i)
    {
        delete[] act_fine[i];
    }

    delete[] act_fine;
    delete[] p;
}

#include <iostream>
#include <string>

int min_pollen(int *fines, std::string *way, int N)
{
    if (N == 1)
    {
        way[0] = '0';
        return fines[0];
    }
    else if (N == 2)
    {
        if (fines[0] > fines[1])
        {
            way[1] = '1';
            return fines[1];
        }
        else
        {
            way[1] = '0';
            return fines[0];
        }
    }
    else if (N >= 3)
    {
        int* pollen = new int[N];
        pollen[0] = fines[0];
        pollen[1] = fines[1];
        way[0] = '0';
        way[1] = '1';
        for (int i = 2; i < N; ++i)
        {
            pollen[i] = std::min(pollen[i - 1], pollen[i - 2]) + fines[i];
            if (pollen[i - 1] > pollen[i - 2])
            {
                std::string smb = std::to_string(i);
                way[i] = way[i - 2] + " -> " + smb;
            }
            else
            {
                std::string smb = std::to_string(i);
                way[i] = way[i - 1] + " -> " + smb;
            }
        }
        int best_res = pollen[N - 1];
        delete[] pollen;
        return best_res;
    }
    return -1;
}

void input(int* fines, int N)
{
    for (int i = 0; i < N; ++i)
    {
        int fine;
        std::cin >> fine;
        fines[i] = fine;
    }
}

void output(int* fines, std::string* way, int N)
{
    std::cout << "Min pollen: " << std::endl;
    std::cout << min_pollen(fines, way, N);
    std::cout << std::endl;
    std::cout << "Way: " << std::endl;
    std::cout << way[N - 1] << ' ';
}

int main()
{
    std::cout << "Enter flowers' amount: " << std::endl;
    int N;
    std::cin >> N;
    std::cout << "Enter the number of pollen on the flowers: " << std::endl;
    int* fines = new int[N];
    std::string* way = new std::string[N];

    input(fines, N);
    output(fines, way, N);

    delete[] fines;
    delete[] way;

    return 0;
}

#include <iostream>
#include <chrono>
#include <random>
#include <math.h>

struct LinkedList
{
    int data;
    LinkedList* next;
};

LinkedList* insert_after(LinkedList* const current, int& count)
{
    if (current == nullptr)
    {
        return new LinkedList{ count, current };
    }
    else
    {
        auto new_node = new LinkedList{ count, current->next };
        current->next = new_node;
        return new_node;
    }
}

LinkedList* remove_after(LinkedList* const current)
{
    if (nullptr == current)
    {
        return current;
    }
    else
    {
        auto new_current = current->next;
        current->next = new_current->next;
        delete new_current;
        return current->next;
    }
}

int decision_by_massives(int* array, int n, int key)
{
    int index = 0;
    while (n > 1)
    {
        index = (index + (key - 1)) % n;
        for (int i = index; i < n - 1; ++i)
        {
            array[i] = array[i + 1];
        }
        --n;
    }
    return array[0];
}

void test_massive(int key)
{
    for (int i = 2000; i < 100000; i += 2000)
    {
        int* main_array = new int[i];

        for (int s = 0; s < i; s++)
        {
            main_array[s] = s;
        }

        auto begin = std::chrono::steady_clock::now();
        decision_by_massives(main_array, i, key);
        auto end = std::chrono::steady_clock::now();
        auto time_span = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
        std::cout << i << " " << time_span.count() << std::endl;

        delete[] main_array;
    }
}

int decision_by_list(LinkedList* head, int n, int key)
{
    LinkedList* tmp = head;
    while (tmp != tmp->next)
    {
        for (int k = 0; k < key - 1; ++k)
        {
            tmp = tmp->next;
        }
        remove_after(tmp);
    }
    return tmp->data;
}

void test_list(int key)
{
    for (int i = 0; i < 1000000; i += 5000)
    {
        int first_node_data = 0;
        LinkedList* first_node = insert_after(nullptr, first_node_data);
        LinkedList* tail = first_node;
        for (int s = 1; s < i; s++)
        {
            tail = insert_after(tail, s);
        }
        tail->next = first_node;
            
        auto begin = std::chrono::steady_clock::now();
        decision_by_list(first_node, i, key);
        auto end = std::chrono::steady_clock::now();
        auto time_span = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
        std::cout << i << " " << time_span.count() << std::endl;
    }
}

void test_list_for_key()
{
    int count = 100000;

    for (int key = 1; key < 50000; key += 2000)
    {
        int first_node_data = 0;
        LinkedList* first_node = insert_after(nullptr, first_node_data);
        LinkedList* tail = first_node;
        for (int s = 1; s < count; s++)
        {
            tail = insert_after(tail, s);
        }
        tail->next = first_node;

        auto begin = std::chrono::steady_clock::now();
        decision_by_list(first_node, count, key);
        auto end = std::chrono::steady_clock::now();
        auto time_span = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
        std::cout << key << " " << time_span.count() << std::endl;
    }
}

int main()
{
    int count = 0;
    int choose;
    std::cout << "Enter 1 (for massive decision), 2 (for list decision): " << std::endl;
    std::cin >> choose;
    int key;
    std::cout << "Enter index of soldiers, who would be killed: " << std::endl;
    std::cin >> key;

    if (choose == 1)
    {
        test_massive(key);
    }
    else if (choose == 2)
    {
        test_list_for_key();
    }

    return 0;
}

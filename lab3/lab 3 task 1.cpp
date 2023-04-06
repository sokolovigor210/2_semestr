#include <iostream>

struct LinkedList
{
    int data;
    LinkedList* next;
};

LinkedList* insert_after(LinkedList* const current)
{
    if (current == nullptr)
    {
        return new LinkedList{ 0, current };
    }
    else
    {
        auto new_node = new LinkedList{ 0, current->next };
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

void erase(LinkedList* const head)
{
    auto current = head;
    auto prev = current;
    while (current != nullptr)
    {
        /*printf("Deleting %d\n", current->data);*/
        current = current->next;
        delete prev;
        prev = current;
    }
}
LinkedList* reverse_rec(LinkedList* const head)
{
    if (nullptr == head)
    {
        return head;
    }
    if (nullptr == head->next)
    {
        return head;
    }
    LinkedList* new_head = reverse_rec(head->next);

    head->next->next = head;
    head->next = nullptr;
    return new_head;

}

LinkedList* reverse_itr(LinkedList* const head)
{
    if (nullptr == head)
    {
        return head;
    }
    auto current = head;
    LinkedList* prev_node = nullptr;
    while (current != nullptr)
    {
        auto next_node = current->next;
        current->next = prev_node;
        prev_node = current;
        current = next_node;
    }
    return prev_node;
}

LinkedList* enter_data(LinkedList* const head, int count)
{
    LinkedList* tail = head;
    for (int i = 0; i < count - 1; i++)
    {
        tail = insert_after(tail);
        std::cin >> tail->data;
    }
    return tail;
}

void print_list(LinkedList* const head)
{
    if (nullptr == head)
    {
        std::cout << "List is empty!" << std::endl;
        return;
    }
    auto current = head;
    while (current != nullptr)
    {
        std::cout << current->data << ' ';
        current = current->next;
    }
    std::cout << std::endl;
}

void test(LinkedList* head, LinkedList* tail, int count)
{
    std::cout << "List: " << std::endl;
    print_list(head);
    std::cout << "After deleting an element: " << std::endl;
    remove_after(head);
    print_list(head);
    std::cout << "Reverse by iterations: " << std::endl;
    reverse_itr(head);
    print_list(tail);
    std::cout << "Reverse by recursion: " << std::endl;
    reverse_rec(tail);
    print_list(head);
    std::cout << "Erasing list: " << std::endl;
    erase(head);
    head = nullptr;
    print_list(head);
}

int main()
{
    int count = 0;
    std::cout << "Enter nodes' number: " << std::endl;
    std::cin >> count;
    std::cout << "Enter" << ' ' << count - 1 << ' ' << "elements:" << std::endl;

    auto head = insert_after(nullptr);
    head->data = 0;

    auto tail = enter_data(head, count);
    test(head, tail, count);

    return 0;
}
#include <iostream>
#include <string>

struct BinaryTree
{
    BinaryTree *left;
    BinaryTree *right;
    int data;
};

BinaryTree* Add_Node(BinaryTree* root, BinaryTree* key)
{
    if (nullptr == root)
    {
        return key;
    }
    if (key->data > root->data)
    {
        root->right = Add_Node(root->right, key);
    }
    else
    {
        root->left = Add_Node(root->left, key);
    }
    return root;
}

void add_node(BinaryTree** p_root, BinaryTree* key)
{
    if (nullptr == *p_root)
    {
        *p_root = key;
        return;
    }
    if ((*p_root)->data < key->data)
    {
        add_node(&(*p_root)->right, key);
    }
    else
    {
        add_node(&(*p_root)->left, key);
    }
}

int deep_and_sum(BinaryTree* root, int level, int &sum)
{
    if (root == nullptr)
    {
        return sum;
    }

    else
    {
        sum = sum + (root->data * level);
        level *= -1;
        deep_and_sum(root->right, level, sum);
        deep_and_sum(root->left, level, sum);
    }
    return 0;
}

void print_tree(BinaryTree* root)
{
    if (root == nullptr)
    {
        return;
    }
    else
    {
        std::cout << root->data << ' ';
        print_tree(root->right);
        print_tree(root->left);
    }
}

void print_tree_mod(BinaryTree* root, std::string& str)
{
    if (root == nullptr)
    {
        return;
    }
    else
    {
            str.push_back('(');
            print_tree_mod(root->left, str);
            str += std::to_string(root->data);
            print_tree_mod(root->right, str);
            str.push_back(')');
    }
}

int max(int x, int y)
{
    if (x >= y)
    {
        return x;
    }
    else
    {
        return y;
    }
}

int height(BinaryTree* root)
{
    if (root == nullptr)
    {
        return 0;
    }
    else
    {
        return (1 + max(height(root->left), height(root->right)));
    }
}

bool AVL_or_not(BinaryTree* root)
{
    int left_height;
    int right_height;

    if (root == nullptr)
    {
        return true;
    }
    else
    {
        left_height = height(root->left);
        right_height = height(root->right);
        if (abs(left_height - right_height) <= 1 && AVL_or_not(root->left) && AVL_or_not(root->right))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

void enter_data(BinaryTree* root)
{
    std::cout << "Enter number of tree's leaves: " << std::endl;
    int n;
    std::cin >> n;
    std::cout << "Enter " << n << " leaves' data: " << std::endl;
    int data;
    for (int i = 0; i < n; ++i)
    {
        std::cin >> data;
        BinaryTree* leave = new BinaryTree{ nullptr, nullptr, data };
        add_node(&root, leave);
    }
}

void test(BinaryTree* root)
{
    std::cout << std::endl;
    print_tree(root);
    std::cout << std::endl;

    int sum = 0;
    std::string tree = "";
    std::cout << "Elements' sum with signs: ";
    deep_and_sum(root, 1, sum);
    std::cout << sum << std::endl;
    std::cout << std::endl;
    print_tree_mod(root, tree);
    std::cout << "Bracket representation of the tree: " << std::endl;
    std::cout << tree << std::endl;
    std::cout << std::endl;
    std::cout << "Is it an AVL-tree?" << std::endl;
    if (AVL_or_not(root))
    {
        std::cout << "Yes" << std::endl;
    }
    else
    {
        std::cout << "No" << std::endl;
    }
}

int main()
{
    std::cout << "Enter tree's root data: " << std::endl;
    int data_0;
    std::cin >> data_0;
    BinaryTree* root = new BinaryTree{ nullptr, nullptr, data_0 };
    enter_data(root);
    test(root);

    return 0;

}

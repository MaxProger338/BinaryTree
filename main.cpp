#include <iostream>
#include <string>
using namespace std;

template<typename T>
class BinaryTree
{
    private:
        class Node
        {
            public: 
                T value;
                Node* parent;
                Node* left;
                Node* right;

                Node(T value):  value{value}, parent{nullptr},
                                left{nullptr}, right{nullptr} {}

                Node& Print(short indent, string name)
                {
                    for (int i = 0; i < indent-1; i++)
                    {
                        cout << '\t';
                    }
                    cout << name << (indent > 0 ? "\t" : "");
                    cout << value << endl;

                    return *this;
                }
        };

        Node* _root;

        BinaryTree& PrintNode(Node* node, int indent, string name)
        {
            node->Print(indent, name);
            if (node->left)
                PrintNode(node->left, indent + 1, "left");
            
            if (node->right)
                PrintNode(node->right, indent + 1, "right");

            return *this;
        }

    public:
        BinaryTree(): _root{nullptr} {}

        ~BinaryTree()
        {
            DeleteNode(_root);
        }

        bool isEmpty() const
        {
            return _root == nullptr;
        }

        BinaryTree& DeleteNode(Node* node)
        {
            if (node->left)
                DeleteNode(node->left);
            if (node->right)
                DeleteNode(node->right);

            delete node;
            return *this;
        }

        BinaryTree& Push(T value)
        {
            Node* node = new Node(value);
            if (isEmpty())
            {
                _root = node;
                return *this;
            }

            Node* current = _root;

            while (current != nullptr)
            {
                node->parent = current;

                if (node->value > current->value)
                    current = current->right;
                else
                    current = current->left;
            }

            if (node->value > node->parent->value)
                node->parent->right = node;
            else
                node->parent->left = node;

            return *this;
        }

        BinaryTree& Print()
        {
            PrintNode(_root, 0, "");
            return *this;
        }

        bool isExists(T element)
        {   
            Node* current = _root;

            while (current != nullptr)
            {
                if (element == current->value)
                    return true;

                if (element > current->value)
                    current = current->right;
                else
                    current = current->left;
            }

            return false;
        }

        BinaryTree& DeleteElement(T element)
        {
            if (isEmpty())
                return *this;

            Node* current = _root;
            while (current != nullptr)
            {
                if (element == current->value)
                    break;

                if (element > current->value)
                    current = current->right;
                else
                    current = current->left;
            }
            if (current == nullptr)
                return *this;

            Node* maxInLeft = current->left;
            while (maxInLeft->right != nullptr)
            {
                maxInLeft = maxInLeft->right;
            }

            current->value = maxInLeft->value;

            maxInLeft->parent->right = maxInLeft->left;
            delete maxInLeft;

            return *this;
        }
};

int main()
{
    BinaryTree<int> tree;

    tree.Push(10);
    tree.Push(13);
    tree.Push(5);
    tree.Push(8);
    tree.Push(3);
    tree.Push(4);
    tree.Push(2);
    tree.Push(6);
    tree.Push(9);
    tree.Push(7);

    tree.Print();

    cout << endl;
    cout << "===========================" << endl;
    cout << endl;

    tree.DeleteElement(10);

    tree.Print();

    return 0;
}

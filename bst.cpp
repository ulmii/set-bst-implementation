#include <iostream>

template <typename T>
class BSTree
{
    friend std::ostream& operator<<(std::ostream& os, const BSTree<T> &tree)
    {
        tree.printBST(os, tree.root);
        return os << "\n";
    }
 
    friend void swap(BSTree<T>& first, BSTree<T>& second)
    {
        using std::swap;
 
        swap(first.root, second.root);
        second.root = nullptr;
    }
 
    public:
        struct Node {
            T value;
            Node *left = nullptr, *right = nullptr, *parent = nullptr;
        };

        BSTree() : root(nullptr) { log("BST constructor"); }
        BSTree(const BSTree& other);
        BSTree(BSTree&& other) noexcept;
        ~BSTree() { log("BST destructor"); destroyer(root); }
 
        BSTree<T>& operator=(const BSTree<T>& other);
        BSTree<T>& operator=(BSTree<T>&& other);
 
        bool isEmpty() const { return root == nullptr; }
        Node* insert(T value);
        Node* search(T value) const;
        void remove(Node* removeNode);
        void remove(T removeVal);
        Node* getRoot() const { return root; }
        int size() const { return helperSize(getRoot()); }
 
    private:
        Node* root;
 
        void destroyer(Node* Node)
        {
            if(Node != NULL)
            {
                destroyer(Node->left);
                destroyer(Node->right);
                delete Node;
            }
        }
 
        void copy(Node* &origin, const Node* sourceNode)
        {
            if(sourceNode == nullptr)
                origin == nullptr;
            else
            {
                origin = new Node;
                origin->value = sourceNode->value;
                copy(origin->left, sourceNode->left);
                copy(origin->right, sourceNode->right);
            }
 
        }
 
        //postOrder
        void printBST(std::ostream& os, Node* pass) const
        {
            if (pass != nullptr)
            {
                printBST(os, pass->left);
                printBST(os, pass->right);
                std::cout << pass->value << " ";
            }
        }
 
        int helperSize(Node* root) const
        {
            if(root == nullptr)
                return 0;
            else
                return (helperSize(root->left) + 1 + helperSize(root->right));
        }
 
        void log(const char* msg) const
        {
            std::cout << "[" << this << "] " << msg << "\n";
        }
};
 
template <typename T>
BSTree<T>::BSTree(const BSTree<T>& other)
    : root(nullptr)
{
    log("BST copy constructor");
 
    if(other.root != nullptr)
    copy(this->root, other.root);
}
 
template <typename T>
BSTree<T>::BSTree(BSTree<T>&& other) noexcept
    : root(nullptr)
{
    log("BST move constructor");
 
    swap(*this, other);
}
 
template <typename T>
BSTree<T>& BSTree<T>::operator=(const BSTree<T>& other)
{
    log("BST copy assignment operator");
 
    BSTree temp(other);
    swap(*this, temp);
    return *this;
}
 
template <typename T>
BSTree<T>& BSTree<T>::operator=(BSTree<T>&& other)
{
    log("BST move assignment operator");
 
    swap(*this, other);
    return *this;
}
 
template <typename T>
auto BSTree<T>::insert(T value) -> Node*
{
    if(root == nullptr)
    {
        root = new Node;
        root->value = value;
        root->left = nullptr;
        root->right = nullptr;
 
        return root;
    }
    else
    {
        Node* temp = root;
        Node* temp2 = nullptr;
 
        Node* pass = new Node;
        pass->value = value;
        pass->left = nullptr;
        pass->right = nullptr;
 
        while(temp != nullptr)
        {
            if (value > temp->value)
            {
                temp2 = temp;
                temp = temp->right;
            }
 
            else if (value < temp->value)
            {
                temp2 = temp;
                temp = temp->left;
            }
        }
 
        if (value > temp2->value)
        {
            temp2->right = pass;
            pass->parent = temp2;
        }
        else if(value < temp2->value)
        {
            temp2->left = pass;
            pass->parent = temp2;
        }
 
        return pass;
    }
}
 
template <typename T>
auto BSTree<T>::search(T value) const -> Node*
{
    if (root == nullptr)
    {
        log("BST tree is empty");
        return nullptr;
    }
 
    Node* temp = root;
 
    while(temp != nullptr)
    {
        if (value == temp->value)
            return temp;
 
        else if (value > temp->value)
            temp = temp->right;
 
        else if (value < temp->value)
            temp = temp->left;
    }
 
    if (temp == nullptr)
        return nullptr;
}
 
template <typename T>
void BSTree<T>::remove(Node* rmNode)
{
    if(rmNode == nullptr)
    {
        log("Can't delete, Node is a null pointer");
        return;
    }
 
    if(rmNode != nullptr)
    {
        if (rmNode->left == nullptr && rmNode->right == nullptr) 
        {
            Node* parent = rmNode->parent;
 
            if(parent->left == rmNode)
                parent->left = nullptr;
            else if (parent->right == rmNode)
                parent->right = nullptr;
 
        delete rmNode;
        }
        else if( (rmNode->left != nullptr && rmNode->right == nullptr) )
        {
            Node* parent = rmNode->parent;
 
            if (parent->left == rmNode)
                parent->left = rmNode->left;
            else if (parent->right == rmNode)
                parent->right = rmNode->left;
 
            delete rmNode;
        }
 
        else if(rmNode->left == nullptr && rmNode->right != nullptr)
        {
            Node* parent = rmNode->parent;
 
            if(parent->left == rmNode)
                parent->left = rmNode->right;
            else if (parent->right == rmNode)
                parent->right = rmNode->right;
 
            delete rmNode;
        }
        else if (rmNode->left != nullptr && rmNode->right != nullptr) 
        {
            Node* successor = rmNode->right;
 
            if(successor->left == nullptr)
            {
                T tempVal = successor->value;
 
                remove(successor->value);
 
        rmNode->value = tempVal;
                return;
            }
 
            else if (successor->left != nullptr)
            {
                Node* temp = successor;
 
                while (temp != nullptr)
                {
                    successor = temp;
                    temp = temp->left;
                }
 
                T tempVal = successor->value;
 
                remove(successor->value);
 
                rmNode->value = tempVal;
                return;
            }
        }
    }
}
 
template <typename T>
void BSTree<T>::remove(T removeVal)
{
    Node* rmNode = search(removeVal);
    if(rmNode != nullptr)
        remove(rmNode);
    else
        log("Can't delete, value is not present in the tree");
}
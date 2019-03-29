#include <stdexcept> 
#include "bst.cpp"

template <typename T>
class MySet
{
    class Iterator {
        friend class MySet<T>;

        Iterator() = default;

        public:
            bool operator==(const Iterator &it) const;
            bool operator!=(const Iterator &it) const { return !(*this == it); }
            Iterator& operator++();
            Iterator operator++(int);
            T& operator*() const;
            T* operator->() const;   
            operator bool() const { return !(this->_currNode == nullptr); } 

        private:
            Iterator(typename BSTree<T>::Node* node, const MySet<T>* set) 
                : _currNode(node), _set(set) {} 

            typename BSTree<T>::Node* _currNode;
            const MySet<T>* _set;
    };

	friend std::ostream& operator<<(std::ostream& os, const MySet<T> &set)
    {
        return os << set._tree;
    }

    friend void swap(MySet<T>& first, MySet<T>& second) noexcept
    {
        using std::swap;

        swap(first._tree, second._tree);
    }

	public:
        MySet() : _tree() { log("SET constructor"); }
        MySet(const MySet& other) = default;
        MySet(MySet&& other) noexcept = default;
        ~MySet() = default;

        MySet<T>& operator=(const MySet<T>& other);
        MySet<T>& operator=(MySet<T>&& other);

        bool insert(T value);
        T search(T value) const;
        void remove(T removeVal);
        bool empty() const { return _tree.isEmpty() == nullptr; }
        int size() const { return _tree.size(); }
        
        Iterator begin() const;
        Iterator end() const;

	private:
		BSTree<T> _tree;

        void log(const char* msg) const
        {
            std::cout << "[" << this << "] " << msg << "\n";
        }
};

template <typename T>
bool MySet<T>::Iterator::operator==(const Iterator &it) const
{
    return _set->_tree.getRoot() == it._set->_tree.getRoot() && _currNode == it._currNode;
}

template <typename T>
typename MySet<T>::Iterator& MySet<T>::Iterator::operator++()
{
    typename BSTree<T>::Node* temp;
    if(_currNode == nullptr)
        {
            _currNode = _set->_tree.getRoot();

            if(_currNode == nullptr)
            {
                throw std::invalid_argument("MySet<T>::Iterator::operator++\n : Set is empty");
            }

            while(_currNode->left != nullptr)
            {
                _currNode = _currNode->left;
            }
        }
    else
    {
        if(_currNode->right != nullptr)
        {
            _currNode = _currNode->right;

            while(_currNode->left!=nullptr)
            {
                _currNode = _currNode->left;
            }
        }
        else
        {
            temp = _currNode->parent;
            while(temp != nullptr && _currNode == temp->right)
            {
                _currNode = temp;
                temp = temp->parent;
            }

            _currNode = temp;
        }

        return *this;
    }
}

template <typename T>
typename MySet<T>::Iterator MySet<T>::Iterator::operator++(int)
{
    Iterator temp(*this);
    ++(*this);
    return temp;
}

template <typename T>
auto MySet<T>::Iterator::operator*() const -> T&
{
    if(_currNode != nullptr)
        return _currNode->value;
    else
    {
        throw std::invalid_argument("MySet<T>::Iterator::operator*\n : Set is empty");
    }
}

template <typename T>
auto MySet<T>::Iterator::operator->() const -> T*
{
    return &_currNode->value;
}

template <typename T>
typename MySet<T>::Iterator MySet<T>::begin() const 
{  
    typename BSTree<T>::Node* temp = _tree.getRoot();
    if(temp != nullptr) {
        while(temp->left != nullptr)
        {
            temp = temp->left;
        }
        return typename MySet<T>::Iterator(temp, this);
    } else {
        return this->end();
    }
}

template <typename T>
typename MySet<T>::Iterator MySet<T>::end() const
{
    return Iterator(nullptr, this);
}

/*
    ------------------- SET ---------------
*/
template <typename T>
MySet<T>& MySet<T>::operator=(const MySet<T>& other)
{
    log("SET copy assignment operator");

    MySet<T> temp(other);
    swap(*this, temp);
    return *this;
}

template <typename T>
MySet<T>& MySet<T>::operator=(MySet<T>&& other)
{
    log("SET move assignment operator");

    swap(*this, other);
    return *this;
}

template <typename T>
bool MySet<T>::insert(T value)
{
	if(_tree.search(value) == nullptr)
		if(_tree.insert(value) != nullptr)
            return true;
    return false;
}

template <typename T>
void MySet<T>::remove(T value)
{
	_tree.remove(_tree.getRoot(), value);
}

template <typename T>
auto MySet<T>::search(T value) const -> T
{
    typename BSTree<T>::Node* temp = _tree.search(value);
    if(temp!=nullptr)
        return temp->value;
    else
        throw std::invalid_argument("Value not present in the _tree");
}
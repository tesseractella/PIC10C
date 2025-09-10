#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <string>
#include <stack>
#include <queue>
#include <iomanip>

template <class T> class BinarySearchTree;
template <class T> class Node;
template <class T> class Iterator;
template <class T> class BreadthFirstIterator;

template <class T>
class Node
{
public:
    
    static long int ncall;
    //equals the total number of constructor calls
    Node(){
     left=nullptr;
     right = nullptr;
     ncall++;
    };

private:
    T data;
    Node<T>* left;
    Node<T>* right;
    friend class BinarySearchTree<T>;
    friend class BreadthFirstIterator<T>;
    friend class Iterator<T>;
};

template <class T>
class Iterator
{
public:
    /**
       Looks up the value at a position.
       @return the value of the node to which the iterator points
    */
    T get() const;
    /**
       Advances the iterator to the next node.
       Inorder Traversal
    */
    void next();
    /**
       Compares two iterators.
       @param other the iterator to compare with this iterator
       @return true if this iterator and other are equal
    */
    bool equals(const Iterator<T>& other) const;
    bool isend() const;
private:
    const BinarySearchTree<T>* container;
    std::stack<Node<T>*> nodeStack;
//Stack: Typically used for in - order, pre - order, or post - order traversal.
//Queue : Used for level - order traversal(BFS).

    friend class BinarySearchTree<T>;
};



/*
   This class implements a binary search tree whose
   nodes hold strings.
*/

template <class T>
class BinarySearchTree
{
public:
    /**
       Constructs an empty tree.
    */
   
    BinarySearchTree();
    
    BinarySearchTree(const BinarySearchTree<T>& a);
    // copy constructor
    
    ~BinarySearchTree();
    //destructor
    
    void DESTROY(Node<T>* curr);
    //helper function to deconstructor to recursively call on bst
    
    /*copy assignment*/
    BinarySearchTree<T>& operator=(const BinarySearchTree<T>& right);

    
    Node<T>* copy(Node<T>* n);
    
    /**
       Inserts a new node into the tree.
       @param element the element to insert
    */
    
    void insert(T element);

    /**
       Tries to find an element in the tree.
       @param element the element to find
       @return 1 if the element is contained in the tree
    */
    int count(T element) const;

    /**
       Tries to remove an element from the tree. Does nothing
       if the element is not contained in the tree.
       @param element the element to remove
    */
    void erase(T element);

    /**
       Prints the contents of the tree in sorted order.
    */
    void print() const;

    /**
   Returns an iterator to the beginning of this BinarySearchTree.
   @return a BinarySearchTree iterator to the beginning
*/
    Iterator<T> begin() const;

    /**
       Returns an iterator past the end of this BinarySearchTree.
       @return a BinarySearchTree iterator past the end
    */
    Iterator<T> end() const;


    /**
Returns an BreadthFirstIterator to the beginning of this BinarySearchTree.
@return a BinarySearchTree iterator to the beginning
*/
    BreadthFirstIterator<T> Bbegin() const;

    /**
       Returns an BreadthFirstIterator past the end of this BinarySearchTree.
       @return a BinarySearchTree iterator past the end
    */
    BreadthFirstIterator<T> Bend() const;

private:
    /**
       Prints a node and all of its descendants in sorted order.
       @param parent the root of the subtree to print
    */
    void print(Node<T>* parent, int indent, char symbol) const;

    /**
       Inserts a new node as a descendant of a given node.
       @param parent the root node
       @param new_node the node to insert
    */
    void add_node(Node<T>* parent, Node<T>* new_node) const;

    Node<T>* root;
    friend class Iterator<T>;
    friend class BreadthFirstIterator<T>;
};


/**
   This iterator visits the nodes of a tree in
   breadth-first order.
*/
template <class T>
class BreadthFirstIterator
{
public:
    /**
       Constructs an iterator for a given tree.
       @param root the root of the tree
    */
    BreadthFirstIterator(Node<T>* root);
    /**
       Gets the element to which this iterator points.
       @return the element
    */
    T get() const;
    /**
       Advances this iterator to the next position.
    */
    void next();
    bool equals(const BreadthFirstIterator<T>& other) const;
    bool isend() const;
private:
    std::queue<Node<T>*> q;
};

template <class T>
BinarySearchTree<T>::BinarySearchTree()
{
    root = nullptr;
}

template <class T>
long int Node<T>::ncall = 0;

template <class T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree<T>& a){
//    for (BreadthFirstIterator it = a.Bbegin(); !it.equals(a.Bend()); it.next()){
//        insert(it.get());
//    }
    root = copy(a.root);
}

template <class T>
Node<T>* BinarySearchTree<T>::copy(Node<T>* n){
    if (n == nullptr){
        return nullptr;
    }
    
    if ((n->left == nullptr) && (n->right==nullptr)){
        Node<T>* newNode = new Node<T>;
        newNode->data = n->data;
        return newNode;
        
    }
    else{
//        copy(n->right);
//        copy(n->left);
        Node<T>* parent = new Node<T>;
        parent->data = n->data;
        parent->left = copy(n->left);
        parent->right = copy(n->right);
        return parent;
    }
}

template <class T>
BinarySearchTree<T>& BinarySearchTree<T>::operator=(const BinarySearchTree<T>& right){
    this->~BinarySearchTree();
//    for (BreadthFirstIterator it = right.Bbegin(); !it.equals(right.Bend()); it.next()){
//        insert(it.get());
//    }
//    return *this;
    root = copy(right.root);
    return *this;
}

template <class T>
BinarySearchTree<T>::~BinarySearchTree(){
    DESTROY(root);
    root = nullptr;
}

template <class T>
void BinarySearchTree<T>::DESTROY(Node<T>* curr){
    if (curr != nullptr){
        if ((curr->left == nullptr)&&(curr->right == nullptr)){
            delete curr;
            curr = nullptr;
        }
        else {
            DESTROY(curr->left);
            DESTROY(curr->right);
        }
    }
}

template <class T>
void BinarySearchTree<T>::insert(T element)
{
    Node<T>* new_node = new Node<T>;
    new_node->data = element;
    new_node->left = nullptr;
    new_node->right = nullptr;
    if (root == nullptr) { root = new_node; }
    else { add_node(root, new_node); }
}

template <class T>
int BinarySearchTree<T>::count(T element) const
{
    Node<T>* current = root;
    while (current != nullptr)
    {
        if (element < current->data)
        {
            current = current->left;
        }
        else if (element > current->data)
        {
            current = current->right;
        }
        else return 1;
    }
    return 0;
}

template <class T>
void BinarySearchTree<T>::erase(T element)
{
    // Find node to be removed

    Node<T>* to_be_removed = root;
    Node<T>* parent = nullptr;
    bool found = false;
    while (!found && to_be_removed != nullptr)
    {
        if (element == to_be_removed->data)
        {
            found = true;
        }
        else
        {
            parent = to_be_removed;
            if (element < to_be_removed->data)
            {
                to_be_removed = to_be_removed->left;
            }
            else
            {
                to_be_removed = to_be_removed->right;
            }
        }
    }

    if (!found) { return; }

    // to_be_removed contains element

    // If one of the children is empty, use the other

    if (to_be_removed->left == nullptr || to_be_removed->right == nullptr)
    {
        Node<T>* new_child;
        if (to_be_removed->left == nullptr)
        {
            new_child = to_be_removed->right;
        }
        else
        {
            new_child = to_be_removed->left;
        }

        if (parent == nullptr) // Found in root
        {
            root = new_child;
        }
        else if (parent->left == to_be_removed)
        {
            parent->left = new_child;
        }
        else
        {
            parent->right = new_child;
        }
        return;
    }

    // Neither subtree is empty

    // Find smallest element of the right subtree

    Node<T>* smallest_parent = to_be_removed;
    Node<T>* smallest = to_be_removed->right;
    while (smallest->left != nullptr)
    {
        smallest_parent = smallest;
        smallest = smallest->left;
    }

    // smallest contains smallest child in right subtree

    // Move contents, unlink child

    to_be_removed->data = smallest->data;
    if (smallest_parent == to_be_removed)
    {
        smallest_parent->right = smallest->right;
    }
    else
    {
        smallest_parent->left = smallest->right;
    }
}

template <class T>
void BinarySearchTree<T>::print() const
{
    print(root,0,' ');
    std::cout << std::endl;
}

template <class T>
void BinarySearchTree<T>::print(Node<T>* parent, int indent, char symbol) const
{
    if (parent == nullptr) { return; }
    print(parent->right, indent + 4, '/');
    // Print right subtree with increased indentation
    std::cout << std::setw(indent) << symbol << parent->data << std::endl;
    // Print current node with indentation
    print(parent->left, indent + 4, '\\');
    // Print left subtree with increased indentation
}

template <class T>
void BinarySearchTree<T>::add_node(Node<T>* parent, Node<T>* new_node) const
{
    if (new_node->data < parent->data)
    {
        if (parent->left == nullptr) { parent->left = new_node; }
        else { add_node(parent->left, new_node); }
    }
    else if (new_node->data > parent->data)
    {
        if (parent->right == nullptr) { parent->right = new_node; }
        else { add_node(parent->right, new_node); }
    }
}




template <class T>
Iterator<T> BinarySearchTree<T>::begin() const
{
    Iterator<T> iter;
    Node<T>* current = root;
    while (current != nullptr)
    {
        iter.nodeStack.push(current);
        current = current->left;
    }


    iter.container = this;
    return iter;
}

template <class T>
Iterator<T> BinarySearchTree<T>::end() const
{
    Iterator<T> iter;
    iter.container = this;
    return iter;
}

template <class T>
T Iterator<T>::get() const
{
    if (!nodeStack.empty())
    {
        return nodeStack.top()->data;
    }
    else
    {
        return "";
    }
   
}

template <class T>
bool Iterator<T>::equals(const Iterator<T>& other) const
{
    if (nodeStack.size() != other.nodeStack.size()) {
        return false;
    }

    // Create temporary stacks to preserve the original stacks
    auto tempStack1 = nodeStack;
    auto tempStack2 = other.nodeStack;

    // Compare each element in the stacks
    while (!tempStack1.empty()) {
        if (tempStack1.top() != tempStack2.top()) {
            return false;  // Elements are different
        }
        tempStack1.pop();
        tempStack2.pop();
    }

    // Stacks are equal
    return true;
}

template <class T>
bool Iterator<T>::isend() const
{
  //  cout << nodeStack.empty();
    return nodeStack.empty();
    //if nodestack is empty, then iterator reaches the end

}



template <class T>
void Iterator<T>::next()
{
    if (!nodeStack.empty())
    {
        Node<T>* current = nodeStack.top();
        nodeStack.pop();

        // Move to the right subtree
        Node<T>* rightChild = current->right;
        while (rightChild != nullptr)
        {
            nodeStack.push(rightChild);
            rightChild = rightChild->left;
        }
    }
 


}
template <class T>
BreadthFirstIterator<T> BinarySearchTree<T>::Bbegin() const
{
    return BreadthFirstIterator<T>(root);
}

template <class T>
BreadthFirstIterator<T> BinarySearchTree<T>::Bend() const
{
    return BreadthFirstIterator<T>(nullptr);
}

template <class T>
BreadthFirstIterator<T>::BreadthFirstIterator(Node<T>* root)
{
    if (root != nullptr) { q.push(root); }
}

template <class T>
T BreadthFirstIterator<T>::get() const
{
    return q.front()->data;
}

template <class T>
void BreadthFirstIterator<T>::next()
{
    Node<T>* n = q.front();
    q.pop();
    if(n->left!=nullptr){ q.push(n->left); }
    if (n->right != nullptr) { q.push(n->right); }
}

template <class T>
bool BreadthFirstIterator<T>::equals(
    const BreadthFirstIterator<T>& other) const
{
    return (q.size() == 0 && other.q.size() == 0)
        || (q.size() > 0 && other.q.size() > 0
        && q.front() == other.q.front());
}

template <class T>
bool BreadthFirstIterator<T>::isend() const {
    return q.empty();
}



#endif

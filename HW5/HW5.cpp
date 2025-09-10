#include <iostream>
#include <string>
#include <vector>
#include "binary_search_tree.h"

int main()
{
    BinarySearchTree<std::string> tree1;
    tree1.insert("D");tree1.insert("B");tree1.insert("A");
    tree1.insert("C");tree1.insert("F");tree1.insert("E");
    tree1.print();
    BinarySearchTree<int> tree2;
    tree2.insert(1);tree2.insert(3);tree2.insert(6);
    tree2.insert(4);tree2.insert(2);tree2.insert(5);
    tree2.print();
    BinarySearchTree<double> tree3;
    tree3.insert(1.1);tree3.insert(-3);tree3.insert(5.5);
    tree3.insert(0.7);tree3.insert(6);tree3.insert(2.4);
        auto tree4=tree3;
        tree3.~BinarySearchTree();
    tree4.print();
        return 0;
}

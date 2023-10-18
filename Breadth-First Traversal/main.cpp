
// COS30008, Tutorial 12, 2023

#include <iostream>

#include "BTree.h"
#include "BreadthFirstTraversal.h"

void testInOrder()
{
    using BSTree = BTree<size_t>;
    using BSTreeNode = typename BSTree::Node;

    BSTreeNode n25 = BSTree::makeNode(25);
    BSTreeNode n10 = BSTree::makeNode(10);
    BSTreeNode n15 = BSTree::makeNode(15);
    BSTreeNode n37 = BSTree::makeNode(37);
    BSTreeNode n30 = BSTree::makeNode(30);
    BSTreeNode n65 = BSTree::makeNode(65);

    n37->attachLeft(n30);
    n37->attachRight(n65);
    n10->attachRight(n15);
    n25->attachLeft(n10);
    n25->attachRight(n37);

    const BSTreeNode& aBTree = n25;

    std::cout << "The tree (BFS):";
    for ( auto& s : BreadthFirstTraversal<size_t>(aBTree) ) { std::cout << ' ' << s; }
    std::cout << std::endl;

    if ( n25->insert( 8 ) ) { std::cout << "Insert 8 successful." << std::endl; }
    else { std::cout << "Insert 8 failed." << std::endl; }

    std::cout << "The tree (BFS):";
    for ( auto& s : BreadthFirstTraversal<size_t>(aBTree) ) { std::cout << ' ' << s; }
    std::cout << std::endl;

    if ( n25->remove( 8 ) ) { std::cout << "Remove 8 successful." << std::endl; }
    else { std::cout << "Remove 8 failed." << std::endl; }

    if ( n25->remove( 25 ) ) { std::cout << "Remove 25 successful." << std::endl; }
    else { std::cout << "Remove 25 failed." << std::endl; }

    std::cout << "The tree (BFS):";
    for ( auto& s : BreadthFirstTraversal<size_t>(aBTree) ) { std::cout << ' ' << s; }
    std::cout << std::endl;
}

int main()
{
    testInOrder();

    return 0;
}


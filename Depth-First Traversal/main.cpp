
// COS30008, Tutorial 12, 2023

#include <iostream>

#include "BTree.h"
#include "DepthFirstTraversal.h"
#include "BreadthFirstTraversal.h"

//void testInOrder()
//{
//    using BSTree = BTree<size_t>;
//    using BSTreeNode = typename BSTree::Node;
//
//    BSTreeNode n25 = BSTree::makeNode(25);
//    BSTreeNode n10 = BSTree::makeNode(10);
//    BSTreeNode n15 = BSTree::makeNode(15);
//    BSTreeNode n37 = BSTree::makeNode(37);
//    BSTreeNode n30 = BSTree::makeNode(30);
//    BSTreeNode n65 = BSTree::makeNode(65);
//
//    n37->attachLeft(n30);
//    n37->attachRight(n65);
//    n10->attachRight(n15);
//    n25->attachLeft(n10);
//    n25->attachRight(n37);
//
//    const BSTreeNode& aBTree = n25;
//
//    std::cout << "Pre-Order Traversal:";
//
//    for ( auto& s : DepthFirstTraversal<size_t>(aBTree, DepthFirstTraversal<size_t>::Mode::PRE_ORDER) )
//    {
//        std::cout << ' ' << s;
//    }
//
//    std::cout << std::endl;
//
//    std::cout << "In-Order Traversal:";
//
//    for ( auto& s : DepthFirstTraversal<size_t>(aBTree, DepthFirstTraversal<size_t>::Mode::IN_ORDER) )
//    {
//        std::cout << ' ' << s;
//    }
//
//    std::cout << std::endl;
//
//    std::cout << "Post-Order Traversal:";
//
//    for ( auto& s : DepthFirstTraversal<size_t>(aBTree, DepthFirstTraversal<size_t>::Mode::POST_ORDER) )
//    {
//        std::cout << ' ' << s;
//    }
//
//    std::cout << std::endl;
//}

void testInOrderString() {

    using BSTree = BTree<std::string>;
    using BSTreeNode = typename BSTree::Node;

    BSTreeNode n1 = BSTree::makeNode("Node 1");
    BSTreeNode n2 = BSTree::makeNode("Node 2");
    BSTreeNode n3 = BSTree::makeNode("Node 3");
    BSTreeNode n4 = BSTree::makeNode("Node 4");
    BSTreeNode n5 = BSTree::makeNode("Node 5");
    BSTreeNode n6 = BSTree::makeNode("Node 6");
    BSTreeNode n7 = BSTree::makeNode("Node 7");
    BSTreeNode n8 = BSTree::makeNode("Node 8");
    BSTreeNode n9 = BSTree::makeNode("Node 9");
    BSTreeNode n10 = BSTree::makeNode("Node 10");

    // Build the binary tree structure
    n1->attachRight(n2);
    n3->attachLeft(n1);
    n3->attachRight(n4);
    n8->attachLeft(n7);
    n8->attachRight(n5);
    n9->attachLeft(n8);
    n9->attachRight(n10);
    n6->attachLeft(n3);
    n6->attachRight(n9);


    const BSTreeNode& aBTree = n6;

    std::cout << "Pre-Order Traversal:";
    for (auto& s : DepthFirstTraversal<std::string>(aBTree, DepthFirstTraversal<std::string>::Mode::PRE_ORDER))
    {
        std::cout << ' ' << s;
    }
    std::cout << std::endl;

    std::cout << "In-Order Traversal:";
    for (auto& s : DepthFirstTraversal<std::string>(aBTree, DepthFirstTraversal<std::string>::Mode::IN_ORDER))
    {
        std::cout << ' ' << s;
    }
    std::cout << std::endl;

    std::cout << "Post-Order Traversal:";
    for (auto& s : DepthFirstTraversal<std::string>(aBTree, DepthFirstTraversal<std::string>::Mode::POST_ORDER))
    {
        std::cout << ' ' << s;
    }
    std::cout << std::endl;

    std::cout << "Breadth-First Traversal:";
    for (auto& s : BreadthFirstTraversal<std::string>(aBTree))
    {
        std::cout << ' ' << s;
    }
    std::cout << std::endl;
}


int main()
{
    testInOrderString();

    return 0;
}


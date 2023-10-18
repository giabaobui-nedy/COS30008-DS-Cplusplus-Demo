//
// Created by Gia Bảo Bùi on 6/6/2023.
//
#pragma once

#include <stack>
#include "BTree.h"

template<typename T>
class DepthFirstTraversal
{
public:
    using BTree_ptr = const BTree<T>*;
    using Iterator = DepthFirstTraversal<T>;
    using Node = typename BTree<T>::Node;

    enum class Mode { PRE_ORDER, POST_ORDER, IN_ORDER };

    struct Frontier
    {
        bool mustExploreRight;
        //a pointer to a Binary Tree
        BTree_ptr node;

        Frontier( BTree_ptr aNode = nullptr ) :
                mustExploreRight(true),
                node(aNode)
        {}

        bool operator==( const Frontier& aOther ) const noexcept
        {
            return mustExploreRight == aOther.mustExploreRight && node == aOther.node;
        }
    };

    DepthFirstTraversal( const Node& aBtree, Mode aMode = Mode::PRE_ORDER ):
    //fRoot is a raw pointer to the BTree.
    fRoot(aBtree.get()),
    fMode(aMode)
    {
        //checks if fRoot is valid (not a nullptr)
//        if (fRoot) {
//            switch (fMode) {
//                case (Mode::PRE_ORDER):
//                    //initialization: push root node onto stack
//                    fStack.push(fRoot);
//                    break;
//                case (Mode::IN_ORDER):
//                    //initialization: push all left nodes, starting at the root node, onto stack.
//                    pushNode(fRoot);
//                    break;
//                case (Mode::POST_ORDER):
//                    pushNode(fRoot);
//                    break;
//            }
//        }
        if (fRoot) {
            if (fMode == Mode::PRE_ORDER) {
                fStack.push(fRoot);
            } else {
                pushNode(fRoot);
            }
        }
    }

    //use top node on stack...
    const T& operator*() const noexcept {
        return **fStack.top().node;
    }

    Iterator& operator++() {
        assert(!fStack.empty());

        switch (fMode) {
            BTree_ptr lTopNode;
            case (Mode::PRE_ORDER):
                //hold on to top node on stack
                lTopNode = fStack.top().node;
                //pop
                fStack.pop();
                //if top node has right node, push it onto stack
                if (lTopNode->hasRight()) {
                    fStack.push(&lTopNode->right());
                }
                //if top node has left node, push it onto stack (will be processed first if anything).
                if (lTopNode->hasLeft()) {
                    fStack.push(&lTopNode->left());
                }
                break;
            case (Mode::IN_ORDER):
                //hold on to top node
                lTopNode = fStack.top().node;
                //pop
                fStack.pop();
                //if top node has right node, push it onto stack
                if (lTopNode->hasRight()) {
                    //push all left nodes, originating from top's right node, onto stacks.
                    pushNode(&lTopNode->right());
                }
                break;
            case (Mode::POST_ORDER):
                //pop
                fStack.pop();
                //if stack is not empty
                if (!fStack.empty()) {
                    if (fStack.top().mustExploreRight) {
                        fStack.top().mustExploreRight = false;
                        lTopNode = fStack.top().node;
                        if (lTopNode->hasRight()) {
                            pushNode(&lTopNode->right());
                        }
                    }
                }
                break;
        }
        return *this;
    }

    Iterator operator++(int) {
        Iterator lOld = *this;
        ++(*this);
        return lOld;
    }

    bool operator==( const Iterator& aOther ) const noexcept {
        if (fRoot == aOther.fRoot && fStack.size() == aOther.fStack.size() && fMode == aOther.fMode) {
            if (fStack.size() > 0) {
                return fStack.top() == aOther.fStack.top();
            }
            return true;
        }
        return false;
    }

    bool operator!=( const Iterator& aOther ) const noexcept  {
        return !(*this == aOther);
    }

    Iterator begin() const noexcept {
        Iterator lBegin = *this;
        std::stack<Frontier> lEmpty;
        lBegin.fStack.swap(lEmpty);
        if (fMode == Mode::PRE_ORDER) {
            lBegin.fStack.push(fRoot);
        } else {
            lBegin.pushNode(fRoot);
        }
        return lBegin;
    }

    Iterator end() const noexcept {
        Iterator lEnd = *this;
        //the end iterator will have an empty stack, after traversing every node.
        std::stack<Frontier> lEmpty;
        lEnd.fStack.swap(lEmpty);
        return lEnd;
    }

private:
    BTree_ptr fRoot;
    std::stack<Frontier> fStack;
    Mode fMode;

    void pushNode( BTree_ptr aNode ) noexcept {
        // if aNode is still valid (it points to something)
        while ( aNode )
        {
            // push the pointer to the node onto the stack
            fStack.push( aNode );
            // starts by pushing all left nodes onto the stack
            if ( aNode->hasLeft() )
            {
                aNode = &aNode->left();
            }

            else
            {
                if ( fMode == Mode::POST_ORDER )
                {
                    // Clear the top node's frontier tag "mustExploreRight"
                    fStack.top().mustExploreRight = false;
                    // if the top node has right node then
                    if ( aNode->hasRight() )
                    {
                        //push it onto stack
                        aNode = &aNode->right();
                        continue;
                    }
                }
                aNode = nullptr;
            }
        }
    }
};

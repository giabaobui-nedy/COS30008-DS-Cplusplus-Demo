//
// Created by Gia Bảo Bùi on 6/6/2023.
//
#pragma once
#include "BTree.h"

#include <queue>
#include <memory>

template<typename T>
class BreadthFirstTraversal {
public:
    using BTree_ptr = const BTree <T> *;
    using Iterator = BreadthFirstTraversal<T>;
    using Node = typename BTree<T>::Node;

    BreadthFirstTraversal(const Node &aBtree):
        fRoot(aBtree.get())
    {
        if (fRoot) {
            fQueue.push(fRoot);
        }
    }

    const T &operator*() const noexcept {
        return **fQueue.front();
    }

    Iterator &operator++() {
        assert(!fQueue.empty());

        BTree_ptr lFront = fQueue.front();
        fQueue.pop();

        if (lFront->hasLeft()) {
            fQueue.push(&lFront->left());
        }

        if (lFront->hasRight()) {
            fQueue.push(&lFront->right());
        }

        return *this;
    }

    Iterator operator++(int) {
        Iterator lOld = *this;
        ++(*this);
        return lOld;
    }

    bool operator==(const Iterator &aOther) const noexcept {
        //compares the underlying data
        // && the size of the queue
        // && the state (first element) of the queue using std::queue::front()
        if (fRoot == aOther.fRoot && fQueue.size() == aOther.fQueue.size()) {
            if (fQueue.size() > 0) {
                return fQueue.front() == aOther.fQueue.front();
            }
            return true;
        }
        return false;
    }

    bool operator!=(const Iterator &aOther) const noexcept {
        return !(*this == aOther);
    }

    Iterator begin() const noexcept {
        Iterator lBegin = *this;
        //create a correct queue for the begin() iterator...
        //which has the pointer to the root of the BTree...
        std::queue<BTree_ptr> lBeginQueue;
        lBeginQueue.push(fRoot);
        lBegin.fQueue.swap(lBeginQueue);
        return lBegin;
    }

    Iterator end() const noexcept {
        Iterator lEnd = *this;
        //create a correct queue for the end() iterator...
        //which is empty...
        std::queue<BTree_ptr> lEndQueue;
        lEnd.fQueue.swap(lEndQueue);
        return lEnd;
    }

private:
    // a pointer to the given BTree's root (the whole tree)
    BTree_ptr fRoot;
    std::queue <BTree_ptr> fQueue;
};
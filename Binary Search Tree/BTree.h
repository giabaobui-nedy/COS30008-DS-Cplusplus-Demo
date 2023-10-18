
// COS30008, Tutorial 12, 2023

#pragma once

#include <memory>
#include <cassert>
#include <iostream>

template<typename T>
class BTree
{
public:
    //Node is used to obtain a unique_ptr of fLeft or fRight.
    //Each Binary tree has two pointers to its left and right Nodes.
    //And only that binary tree has that left and right.
    using Node = std::unique_ptr<BTree>;

    //constructor. Takes the reference of a value T. (Copy?)
    BTree( const T& aKey = T{} ) noexcept :
            fKey(aKey)
    {}


    BTree( T&& aKey ) noexcept :
            fKey(std::move(aKey))
    {}

    template<typename... Args>
    static Node makeNode( Args&&... args )
    {
        return std::make_unique<BTree>( std::forward<Args>(args)... );
    }

    BTree( const BTree& aOther ) :
            fKey(aOther.fKey)
    {
        if ( aOther.fLeft )
        {
            // copy non-empty subtree
            fLeft = std::move(makeNode( *aOther.fLeft ));
        }

        if ( aOther.fRight )
        {
            // copy non-empty subtree
            fRight = std::move(makeNode( *aOther.fRight ));
        }
    }

    BTree& operator=( const BTree& aOther )
    {
        if ( this != &aOther )
        {
            this->~BTree();

            new (this) BTree( aOther );
        }

        return *this;
    }

    BTree( BTree&& aOther ) noexcept :
            BTree()
    {
        swap( aOther );
    }

    BTree& operator=( BTree&& aOther ) noexcept
    {
        if ( this != &aOther )
        {
            swap( aOther );
        }

        return *this;
    }

    void swap( BTree& aOther ) noexcept
    {
        std::swap( fKey, aOther.fKey );
        std::swap( fLeft, aOther.fLeft );
        std::swap( fRight, aOther.fRight );
    }

    const T& operator*() const noexcept
    {
        return fKey;
    }

    bool hasLeft() const noexcept
    {
        return fLeft ? true : false;
    }

    BTree& left() const
    {
        // valid node
        assert( fLeft );

        return *fLeft;
    }

    bool hasRight() const noexcept
    {
        return fRight ? true : false;
    }

    BTree& right() const
    {
        // valid node
        assert( fRight );

        return *fRight;
    }

    void attachLeft( Node& aNode )
    {
        // transfers ownership from aNode to fLeft

        // valid free node
        assert( !fLeft );

        fLeft = std::move(aNode);
    }

    void attachRight( Node& aNode )
    {
        // transfers ownership from aNode to fRight

        // valid free node
        assert( !fRight );

        fRight = std::move(aNode);
    }

    Node detachLeft()
    {
        // transfers ownership from fLeft to result

        // valid index and node
        assert( fLeft );

        return std::move(fLeft);
    }

    Node detachRight()
    {
        // transfers ownership from fRight to result

        // valid index and node
        assert( fRight );

        return std::move(fRight);
    }

    bool leaf() const noexcept
    {
        return !fLeft && !fRight;
    }

    size_t height() const noexcept
    {
        size_t Result = 0;

        if ( !leaf() )
        {
            Result = std::max( fLeft ? fLeft->height() + 1 : 0,
                               fRight ? fRight->height() + 1 : 0 );
        }

        return Result;
    }

    const T& findMax() const noexcept
    {
        if ( hasRight() )
        {
            return right().findMax();
        }

        return **this;
    }

    const T& findMin() const noexcept
    {
        if ( hasLeft() )
        {
            return left().findMin();
        }

        return **this;
    }

    bool insert (const T& aKey) noexcept {
        //pointer to this instance, start the loop
        BTree* x = this;
        //the insertion point
        BTree* y = nullptr;

        //find if insertion is valid, loop to find the insertion point
        while (x) {
            y = x; //copy the value of x --> y
            //x points to a BTree instance.
            //First dereference -> get the instance
            //Second dereference -> get the key
            if (aKey == **x) {return false;} //duplicate key
            //if aKey < this BTree's fKey --> get the raw pointer of the left tree.
            //if aKey > this BTree's fKey --> get the raw pointer of the right tree.
            x = (aKey < **x ? x->fLeft.get() : x->fRight.get());
        }

        //if we use a nullptr for the insert, should be wrong...
        if (!y) {return false;}
        else {
            Node z = BTree::makeNode(aKey);
            if (aKey < **y) {y->fLeft = std::move(z);} else
            {y->fRight = std::move(z);}
        }
        return true;
    }

    bool remove (const T& aKey, BTree* aParent = nullptr) noexcept {
        //pointer to this BTree instance
        BTree* x = this;
        //nullptr
        BTree* y = aParent;

        //find deletion root pointer
        while (x) {
            if (aKey == **x) {break;} //found it!
            y = x;

            x = (aKey < **x ? x->fLeft.get() : x->fRight.get());
        }

        if (!x) {return false;} //no available node

        if (x->hasLeft()) {
            x->fKey = x->left().findMax(); //find Max to left
            x->left().remove(**x, x);
        }
        else
        {
            if (x->hasRight())
            {
                x->fKey = x->right().findMin();
                x->right().remove(**x, x);
            } else
            {
                if (y->fLeft.get() == x) {y->fLeft = nullptr;}
                else {y->fRight = nullptr;}
            }
        }
        return true;
    }

private:
    T fKey;
    Node fLeft;
    Node fRight;
};

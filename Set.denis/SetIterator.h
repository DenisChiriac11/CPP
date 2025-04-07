#pragma once
#include "Set.h"

class SetIterator
{
    //DO NOT CHANGE THIS PART
    friend class Set;
private:
    //DO NOT CHANGE THIS PART
    const Set& set;
    SetIterator(const Set& s);

    int idx; /// the position of the current element
    SetIterator(const Set& m, int position);


public:
    void first();
    void next();
    void nextposition();
    TElem getCurrent();
    bool valid() const;

};



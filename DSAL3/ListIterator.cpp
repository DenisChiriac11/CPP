#include <exception>
#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>
/**
 * Complexitati :
 * Caz defavorabil : Θ(1)
 * Caz mediu : Θ(1)
 * Caz favorabil : Θ(1)
 */

ListIterator::ListIterator(const SortedIndexedList& lis) : list(lis){
    curent = list.prim;
}


/**
 * Complexitati :
 * Caz defavorabil : Θ(1)
 * Caz mediu : Θ(1)
 * Caz favorabil : Θ(1)
 */

void ListIterator::first() {

    curent = list.prim;
}

/**
 * Complexitati :
 * Caz defavorabil : Θ(1)
 * Caz mediu : Θ(1)
 * Caz favorabil : Θ(1)
 */

void ListIterator::next(){
    if(!valid()){
        throw std::exception();
    }
    curent = list.urm[curent];
}


/**
 * Complexitati :
 * Caz defavorabil : Θ(1)
 * Caz mediu : Θ(1)
 * Caz favorabil : Θ(1)
 */

bool ListIterator::valid() const{
    if(curent != -1){
        return true;
    }
	return false;
}
/**
 * Complexitati :
 * Caz defavorabil : Θ(1)
 * Caz mediu : Θ(1)
 * Caz favorabil : Θ(1)
 */

TComp ListIterator::getCurrent() const{
    return list.elemente[curent];
}


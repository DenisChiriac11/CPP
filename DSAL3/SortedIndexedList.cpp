#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <exception>
#include <iostream>
using namespace std;


/**
 * Complexitati :
 * Caz defavorabil : Θ(capacitate)
 * Caz mediu : Θ(capacitate)
 * Caz favorabil : Θ(capacitate)
 */
SortedIndexedList::SortedIndexedList(Relation r) {

    prim = -1;
    ultim = -1;

    for(int i = 0 ; i < capacitate - 1; i++){
        urm[i] = i + 1;
        pre[i] = -1;
    }
   urm[capacitate - 1] = -1;
    pre[capacitate - 1] = -1;

    primLiber = 0;

    rel = r;

}

/**
 * Complexitati :
 * Caz defavorabil : Θ(1)
 * Caz mediu : Θ(1)
 * Caz favorabil : Θ(1)
 */

int SortedIndexedList::aloca(){
    if(primLiber == -1){
        throw std::runtime_error("Nu mai exista spatiu liber");
    }
    int poz = primLiber;
    primLiber = urm[primLiber];
    return poz;
}

/**
 * Complexitati :
 * Caz defavorabil : Θ(1)
 * Caz mediu : Θ(1)
 * Caz favorabil : Θ(1)
 */

void SortedIndexedList::dealoca(int poz){
    urm[poz] = primLiber;
    primLiber = poz;
}


/**
 * Complexitati :
 * Caz defavorabil : Θ(n) parcurgem toate elementele listei secvential
 * Caz mediu : Θ(n)
 * Caz favorabil : Θ(n) verificam daca e goala
 */

int SortedIndexedList::size() const {
	
    int curent = prim;
    int dimensiune = 0;
    while(curent != -1){
        dimensiune++;
        curent = urm[curent];
    }
    return dimensiune;
}


/**
 * Complexitati :
 * Caz defavorabil : Θ(1)
 * Caz mediu : Θ(1)
 * Caz favorabil : Θ(1)
 */

bool SortedIndexedList::isEmpty() const {
    if(prim == -1){
        return true;
    }
	return false;
}


/**
 * Complexitati :
 * Caz defavorabil : Θ(n) parcurgem toata lista
 * Caz mediu : Θ(n)
 * Caz favorabil : Θ(1) primul element din lista este cel accesat
 *
 */

TComp SortedIndexedList::getElement(int i) const{
    if(i < 0 || i >= size()){
        throw std::runtime_error("Pozitie invalida la element");
    }
    int curent = prim;
    for(int j = 0; j < i; j++){
        curent = urm[curent];
    }
    return elemente[curent];
}
/**
 *
 * Complexitati:
 * caz favorabil Θ(max(this->size, list.size))
 * caz mediu Θ(this->size)
 * caz defavorabil Θ(this->size * list.size))
 */
void SortedIndexedList::diff(const SortedIndexedList &list) {

    SortedIndexedList newList(this->rel);


    int curent = this->prim;
    int size = 0;
    int sizeList = 0;

    //theta de size list
    while(curent != -1){
        curent = urm[curent];
        size++;
    }
    curent = list.prim;
    //theta de size lista ca parametru
    while(curent != -1) {
        curent = list.urm[curent];
        sizeList++;
    }

    curent = prim;
    bool found = false;
    for(int i = 0; i < size ; ++i){
        int elem = elemente[curent];
        curent = urm[curent];
        found = false;
        //parcurgem lista din parametru si cautam
        int curentList = list.prim;
        for(int j = 0; j < sizeList && !found; ++j){
            if(elem == list.elemente[curentList])
                found = true;
            curentList = list.urm[curentList];
        }

        //daca nu este gasit adaugam in noua lista - newList
        // elem - de adagaut
        if(!found){
            int poz = newList.primLiber;
            newList.primLiber = newList.urm[poz];
            newList.elemente[poz] = elem;

            if(newList.prim == -1){
                newList.prim = poz;
                newList.ultim = poz;
                newList.urm[poz] = -1;
                newList.pre[poz] = -1;

            }else{
                int inserare = newList.prim;
                int anterior = -1;
                while(inserare != -1 && newList.rel(newList.elemente[inserare], elem)){
                    anterior = inserare;
                    inserare = newList.urm[inserare];

                }
                if(anterior == -1){
                    newList.urm[poz] = inserare;
                    newList.pre[poz] = -1;
                    newList.pre[inserare] = poz;
                    newList.prim = poz;
                }else{
                    newList.urm[poz] = inserare;
                    newList.pre[poz] = anterior;
                    if(inserare == -1){
                        ultim = poz;
                    }else{
                        newList.pre[inserare] = poz;
                    }
                    newList.urm[anterior] = poz;
                }

            }
        }


    }

    //eliberam lista noastra

    curent = prim;
    while(curent != -1){
        int urmator = urm[curent];
        //dealocam spatiul
        urm[curent] = primLiber;
        primLiber = curent;
        curent = urmator;
    }

    //copiem noua lista in a noastra
    curent = newList.prim;
    while(curent != -1){
        //adaugam
        int e = newList.elemente[curent];
        int poz = primLiber;
        primLiber = urm[primLiber];
        elemente[poz] = e;

        if(prim == -1){
            prim = poz;
            ultim = poz;
            urm[poz] = -1;
            pre[poz] = -1;
        } else {
            int it = prim;
            int anterior = -1;
            while(it != -1 && rel(elemente[it], e)){
                anterior = it;
                it = urm[it];
            }
            if(anterior == -1){
                urm[poz] = prim;
                pre[poz] = -1;
                pre[prim] = poz;
                prim = poz;
            } else {
                urm[poz] = it;
                pre[poz] = anterior;
                if(it == -1){
                    ultim = poz;
                } else {
                    pre[it] = poz;
                }
                urm[anterior] = poz;
            }
        }

        curent = newList.urm[curent];
    }

}


/**
 * Complexitati :
 * Caz defavorabil : Θ(n) stergem ultiml element(parcurgem toata lista)
 * Caz mediu : Θ(n)
 * Caz favorabil : Θ(1) primul element din lista este cel pe care vrem sa il stergem
 */

TComp SortedIndexedList::remove(int i) {
    if(i < 0 || i >= size()){
        throw std::runtime_error("Pozitie invalida la stergere");
    }
    int curent = prim;
    for(int j = 0; j < i; j++){
        curent = urm[curent];
    }
    TComp e = elemente[curent];
    if(curent == prim){
        prim = urm[curent];
        pre[prim] = -1;
    } else {
        pre[urm[curent]] = pre[curent];
        urm[pre[curent]] = urm[curent];
    }
    dealoca(curent);
    return e;
}


/**
 * Complexitati :
 * Caz defavorabil : Θ(n) elementul cautat este la finalul listei
 * Caz mediu : Θ(n)
 * Caz favorabil : Θ(1) primul element din lista este cel cautat
 *
 */

int SortedIndexedList::search(TComp e) const {
    int curent = prim;
    int poz = 0;
    while(curent != -1 && rel(elemente[curent] , e)){
        if(elemente[curent] == e){
            return poz;
        }

        curent = urm[curent];
        poz++;

    }
    return -1;
}

/**
 * Complexitati :
 * Caz defavorabil : Θ(n) elementul este adaugat la sfarsitul listei
 * Caz mediu : Θ(n)
 * Caz favorabil : Θ(1) elementul este adaugat la inceputul listei
 */

void SortedIndexedList::add(TComp e)
{
    int poz = aloca();
    elemente[poz] = e;
    if(prim == -1){
        prim = poz;
        ultim = poz;
        urm[poz] = -1;
        pre[poz] = -1;
    } else {
        int curent = prim;
        int anterior = -1;
        while(curent != -1 && rel(elemente[curent], e)){
            anterior = curent;
            curent = urm[curent];
        }
        if(anterior == -1){
            urm[poz] = prim;
            pre[poz] = -1;
            pre[prim] = poz;
            prim = poz;
        } else {
            urm[poz] = curent;
            pre[poz] = anterior;
            if(curent == -1){
                ultim = poz;
            } else {
                pre[curent] = poz;
            }
            urm[anterior] = poz;
        }
    }

}


/**
 * Complexitati :
 * Caz defavorabil : Θ(1)
 * Caz mediu : Θ(1)
 * Caz favorabil : Θ(1)
 */

ListIterator SortedIndexedList::iterator(){
    return ListIterator(*this);
}


/**
 * Complexitati :
 * Caz defavorabil : Θ(n)
 * Caz mediu : Θ(n)
 * Caz favorabil : Θ(n)
 */

SortedIndexedList::~SortedIndexedList() {
    int curent = prim;
    while(curent != -1){
        int urmator = urm[curent];
        dealoca(curent);
        curent = urmator;
    }
}

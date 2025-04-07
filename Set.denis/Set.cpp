#include "Set.h"
#include "SetIterator.h"
#include <iostream>

using namespace std;

Set::Set() {

    this->capacity = 5;
    this->length = 0;
    this->right = 0;
    this->left = 0;
    this->bitarray = new bool[this->capacity];
}
///tetha(n) because we heve to go through all the elements
void Set::resize_up(){
    this->capacity = max(this->capacity, this->right - this->left + 2);
    bool* resized_array = new bool[this->capacity];

    for(int i = 0; i < this->right - this->left + 1; i++)
        resized_array[i] = this->bitarray[i];

    delete[] this->bitarray;
    this->bitarray = resized_array;
}
///tetha(n) because we heve to go through all the elements
void Set::resize_down() {
    this->capacity /= 2;
    bool* resized_array = new bool[this->capacity];

    for(int i = 0; i < this->right - this->left + 1; i++)
        resized_array[i] = this->bitarray[i];
    delete[] this->bitarray;
    this->bitarray = resized_array;
}
////tetha(1) if no resize is needed
////tetha(n), if resize is needed, where n = newArrSize
////tetha(1), amortized complexity, as the worst case(resize, elem doesnt fit the arr) cant occur right after another one
bool Set::add(TElem elem) {
    if(this->isEmpty()){
        this->left = elem;
        this->right = elem;
        this->bitarray[0] = 1;

        this->length++;

        return true;
    }
    if(this->search(elem))
        return false;

    else{
        /// Falls elem entweder neue mini oder neue maxi ist
        if (elem < this->left || elem > this->right) {
            int old_length = this->right - this->left;
            int old_mini = this->left;

            /// aktualisieren, wo der Fall ist
            this->left = min(this->left, elem);
            this->right = max(this->right, elem);

            /// aktualisieren von capacity, wenn notig
            if (this->capacity < (this->right - this->left + 2))
                this->resize_up();
            bool*aux = new bool [this->capacity];

            /// Man initialisiert this->maxi - this->mini + 1 0-wertigen Posiitonen
            for (int i = 0; i <= this->right - this->left; i++)
                aux[i] = 0;

            /// Man markiert das hiznzugefugte Ellement mit Freqvenz 1
            aux[elem - this->left] = 1;

            /// Falls neue maxi => auf der ersten old_length+1 Positionen werden die vorherige Ellemente kopiert
            if (elem == this->right) {
                for (int i = 0; i <= old_length; i++)
                    aux[i] = this->bitarray[i];

            } else { /// neue mini => die Ellemente werden mit i + old_mini - this->mini Positionen verschoben und kopiert
                for (int i = 0; i <= old_length; i++)
                    aux[i + old_mini - this->left] = this->bitarray[i];
            }
            /// delete vorherige bag und neue bag wird aux
            delete[] this->bitarray;
            this->bitarray = aux;


        } else if(!this->search(elem)) { /// elem gehort [min,max] => seine Freqvenz wachst
            this->bitarray[elem - this->left] = 1;
        }
        this->length++;
        return true;
    }
}

/// Komplexitaten:
/// Best Case (elem not in set): Theta(1)
/// Average Case: Theta(n)
/// Worst Case (isEmpty==false): Theta(n)
bool Set::remove(TElem elem) {

    if(!this->search(elem))
        return false;

    int pos = elem - this->left;
    this->bitarray[pos] = 0;

    ///remove min, falls wir der Minimum entfernen
    if(elem == this->left){
        ///Wir brauchen das alte 'left', um zu wissen, um wie viele Plätze wir nach rechts verschieben müssen
        TElem old_left = this->left;
        for(int i = 1; i <= this->right - this->left; i++){
            if(this->bitarray[i] > 0){
                this->left = this->left + i;
                break;
            }
        }
        ///Wir ordnen die Elemente neu an
        for(int i = 0; i <= (this->right - old_left); i++){
            this->bitarray[i] = this->bitarray[this->left - old_left + i];
        }
    }
    ///remove max, falls wir der Maximum enfernen
    if(elem == this->right){
        ///Finden des neuen Maximum
        for(int i = this->right - this->left - 1; i >= 0; i--){
            if(this->bitarray[i] > 0){
                this->right = this->left + i; /// Aktualisieren des Max
                break;
            }
        }
    }
    this->length--;
    if((this->right - this->left + 1) < this->capacity/4)
        this->resize_down();
    return true;
}
/// Komplexitat:
/// Theta(1)
bool Set::search(TElem elem) const {
    if (this->isEmpty())
        return false;

    if(elem >= this->left && elem <= this->right)
        if(this->bitarray[elem - this->left])
            return true;
    return false;
}

/// Komplexitat:
/// Theta(1)
int Set::size() const {
    return this->length;
}

/// Komplexitat:
/// Theta(1)
bool Set::isEmpty() const {
    return this->length == 0;
}

/// O(n)
Set::~Set() {
    delete[] this->bitarray;
}

void Set::print() {
    for (int i = 0; i < this->right - this->left + 1; i++)
        cout << this->bitarray[i] << " ";
    cout << "\n";
}

/// Komplexitat:
/// Theta(1)
SetIterator Set::iterator() const {
    return SetIterator(*this);
}



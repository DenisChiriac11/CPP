#include "SetIterator.h"
#include "Set.h"
#include <exception>

using namespace  std;


SetIterator::SetIterator(const Set& m) : set(m)
{
    this->idx = 0;
}
/// iteraor generalizat:construcor parametru indice, next primeste intreg pozitiv si neativ + complexitati
/// best averae worst pseudocod(speciicatii pre si post) + teste
///SetIterator::SetIterator(const Set &m, int position) : set(m)
///{
///if(position < 0 && position > this.lenght)
///        throw exception();
///this->idx = position
///}
///void SetIterator::nextposition(int nrpos)
///{
///    if(this->idx - nrpos < 0 && this->idx + nrpos >= this.lenght)
///         throw exception();
///    this->idX += nrpos
///}

////tetha(1) if the first elem of the set is true
////tetha(capacity) if there are no true values in the array, or the only true values are at the end
void SetIterator::first() {
    this->idx = 0;
}
////tetha(1) best case: if next elem is true
////tetha(capacity) worst case: if there are no true values is the arr, or the only true values are at the end
void SetIterator::next() {

    if (this->valid()){
        if (this->set.left == this->set.right) {
            this->idx++;
            return;
        }

        this->idx++;

        while (!this->set.bitarray[this->idx] && this->valid())
            this->idx++;
        return ;
    }
    throw exception();
}

///tetha(1)
TElem SetIterator::getCurrent()
{
    if (this->valid())
        return this->set.left + this->idx;
    throw exception();
}
///tetha(1)
bool SetIterator::valid() const {

    if (this->set.isEmpty())
        return false;

    if (this->set.left == this->set.right)
        return this->idx < this->set.length;

    return this->idx <= this->set.right - this->set.left;
}




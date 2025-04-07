#pragma once


typedef int TComp;

typedef bool (*Relation)(TComp, TComp );

#define NULL_TCOMP -11111
#define CAPACITATE 10000


class ListIterator;

class SortedIndexedList {
private:
	friend class ListIterator;
private:

    static const int capacitate = CAPACITATE;
    TComp elemente[CAPACITATE];
    int urm[CAPACITATE];
    int pre[CAPACITATE];
    int primLiber;
    int prim;
    int ultim;
    int dimensiune;
    Relation rel;
    int aloca();
    void dealoca(int poz);
    int creeazaNod(TComp e);
    
public:
	SortedIndexedList(Relation r);

	int size() const;

	bool isEmpty() const;

	TComp getElement(int i) const;

	void add(TComp e);

	TComp remove(int i);

	int search(TComp e) const;

    void diff(const SortedIndexedList& list) ;

	ListIterator iterator();

	~SortedIndexedList();

};

#pragma once
#include <iostream>
#include <string>
#include "TNode.h"
using namespace std;

template<class T>
class TList
{
protected:
	TNode<T>* pFirst=pStop; // первое звено
	TNode<T>* pStop= NULL; // значение указателя, означающего конец списка
	TNode<T>* pCurrent = pStop; // текущее звено, всегда указывает на тот же обьект при изменении длины (кроме изменения себя)
	TNode<T>* pPrevious=pStop; // звено перед текущим
	TNode<T>* pLast=pStop; // последнее звено
	int length=0; // количество звеньев в списке

public:

	TList();
	~TList();
	int GetLength() { return length; }
	bool IsEmpty(); // список пуст ?
	// вставка звеньев
	void InsertFirst(T item); // перед первым
	void InsertCurrent(T item); // перед текущим 
	void InsertLast(T item);  // вставить последним 

	// удаление звеньев
	//void Clear();
	void DeleteFirst();// удалить первое звено 
	void DeleteCurrent(); // удалить текущее звено

	void GoNext(); // сдвиг вправо текущего звена
	// (=1 после применения GoNext для последнего звена списка)

	void Reset(); // установить на начало списка
	bool IsEnd();  // список завершен ?

	T GetCurrentItem();
	void SetCurrentItem(T item) { pCurrent->value = item; }


	friend ostream& operator<<(ostream& os, const TList<T>& obj) {
		//os << &obj;
		if (obj.length == 0) { os << "length = 0 \n[\n]" << endl; return os; }
		try { os << "first = " << obj.pFirst->value << endl; } catch (...) { os << "no first" << endl; }
		try { os << "last = " << obj.pLast->value << endl; } catch (...) { os << "no last" << endl; }
		os << "length = " << obj.length << endl;
		TNode<T>* tmp = obj.pFirst;
		os << "[" << endl;
		while (tmp != obj.pStop)
		{

			os << tmp->value;// << " next" << tmp->pNext;
			if (tmp == obj.pCurrent) os << "<-- current";
			if (tmp == obj.pPrevious) os << "<-- pr";
			os << endl;
			tmp = tmp->pNext;
		}
		os << "]" << endl;
		return os;
	}

};

//*p - данные по ссылке int*p
//&p - ссфлка на данные int p
template <class T>
TList<T>::TList()
{
	length = 0;
	pStop = NULL;
	pFirst = pStop;
	pPrevious = pStop;
	pLast = pStop;
}

template <class T>
TList<T>::~TList()
{
}

template <class T>
bool TList<T>::IsEmpty()
{
	if (length == 0) return true;
	return false;
}

template <class T>
void TList<T>::InsertFirst(T item)
{	
	if (length == 0) {
		TNode<T>* tmp = new TNode<T>();
		tmp->pNext = pStop;
		tmp->value = item;
		pFirst= tmp; 
		pCurrent = pFirst;
		pLast = pFirst;
	}
	else {
		TNode<T>* tmp= new TNode<T>();
		tmp->pNext = pFirst;
		tmp->value = item;
		if (pCurrent == pFirst) { pPrevious = tmp; pCurrent = pFirst; }
		pFirst = tmp;
	}
	length++;

}

template <class T>
void TList<T>::InsertLast(T item)
{
	if (IsEmpty()) { InsertFirst(item); return; }
	TNode<T>* tmp = new TNode<T>();
	tmp->pNext = pStop;
	tmp->value = item;
	pLast->pNext = tmp;
	pLast = tmp;
	length++;
}
template <class T>
void TList<T>::InsertCurrent(T item)
{
	if (length == 0) {
		InsertFirst(item);
		return;
	}
	if (pCurrent == pFirst) { InsertFirst(item); return; }
	TNode<T>* tmp = new TNode<T>();

	tmp->value = item;
	tmp->pNext = pCurrent;
	pPrevious->pNext = tmp;
	pPrevious = tmp;
	length++;

}

template <class T>
void TList<T>::DeleteFirst()
{

	if (length == 0) throw "is Empty";
	//std::cout << "  delF " << *this<<this<< endl;
	if(pCurrent == pFirst) pCurrent= pFirst->pNext;
	if (pLast == pFirst) pLast = pFirst->pNext;
	if (pPrevious == pFirst) pPrevious = pFirst->pNext;
	TNode<T>* tmp = pFirst;
	pFirst = pFirst->pNext;
	tmp = nullptr;
	length--;
}

template <class T>
void TList<T>::DeleteCurrent()
{
	if (length == 0) throw "is Empty";

	if (pCurrent==pStop) throw "Currend in end";
	if ((pCurrent == pFirst)&&(length==1)) { DeleteFirst(); length--;  return; }
	if (pCurrent->pNext == pStop) {
		pLast = pPrevious; 
		pLast->pNext = pStop;
		delete pCurrent;
		Reset();
		length--;
		return;
	
	}
	TNode<T>* tmp = pCurrent->pNext;
	delete pCurrent;
	pCurrent = tmp;
	pPrevious->pNext = pCurrent;
	//std::cout << pCurrent<<"ddd"<<endl;
	tmp=nullptr;
	length--;
}

template <class T>
T TList<T>::GetCurrentItem()
{
	if (length == 0) throw "NOElem";
	if (pCurrent == pStop) throw "IsEnd";
	//std::cout << pCurrent << "ddd2" << endl;
	return pCurrent->value;
}

template <class T>
void TList<T>::Reset()
{
	pCurrent = pFirst;
	pPrevious = NULL;
}

template <class T>
void TList<T>::GoNext()
{
	//std::cout << "sasaa" << *this << this << endl;
	try {
	if (IsEnd()) throw "is end";
		pPrevious = pCurrent;
		pCurrent = pCurrent->pNext;
	}
	catch (...) {}
}

template <class T>
bool TList<T>::IsEnd()
{
	if (IsEmpty()) return 1;
	if (pCurrent == pStop) return true;
	if (pCurrent->pNext == pStop) return true;
	return false;
}





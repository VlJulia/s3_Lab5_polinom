#pragma once
#include "TList.h"
using namespace std;


template<class T>
class THeadList : public TList<T>
{
protected:
	TNode<T>* pHead;  // заголовок, pFirst - звено за pHead
public:
	THeadList();
	~THeadList();
	void InsertFirst(T item); // вставка звеньев после заголовка
	void DeleteFirst(); // удалить первое звено
	void DeleteCurrent();
	void GoNext();
	void Reset();
	void Clear();
};
template <class T>
void THeadList<T>::DeleteCurrent() {
	TList<T>::DeleteCurrent();
	if (pFirst == pCurrent) pPrevious = pLast;

}

template <class T>
void THeadList<T>::Clear() {
	//std::cout << "Clear   " << *this;
	Reset();
	while (length > 0) { DeleteFirst(); }
	pCurrent = pStop; pPrevious = pStop; pLast = pStop;
	pFirst = pStop;
	//std::cout << "Clear END  " << *this;
	length = 0;
}

template<class T>
THeadList<T>::THeadList():TList<T>()
{
	pHead = new TNode<T>();
}

template<class T>
void THeadList<T>::Reset()
{
	 TList<T>::Reset();
	 pPrevious = pLast;
}
template<class T>
void THeadList<T>::GoNext()
{
	if (pCurrent->pNext==pStop) THeadList<T>::Reset();
	else TList<T>::GoNext();
}
template<class T>
THeadList<T>::~THeadList()
{
	TList<T>::~TList<T>();
	pHead = NULL;
}

template <class T>
void THeadList<T>::InsertFirst(T item)
{
	TList<T>::InsertFirst(item);
	//	if (!IsEmpty()) pHead->pNext = pFirst;
}

template <class T>
void THeadList<T>::DeleteFirst()
{
	TList<T>::DeleteFirst();
	if (length != 0) pHead = pFirst;
	else pHead = NULL;
}

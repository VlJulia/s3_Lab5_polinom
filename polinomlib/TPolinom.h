#pragma once
#include "THeadList.h"
#include "TMonom.h"
#include "TNode.h"
#include <string>

const int nonDisplayedZeros = 4; // Количество неотображаемых нулей при выводе коэффициента полинома
								 // Кол-во символов после запятой = 6 - nonDisplayedZeros


class TPolinom : public THeadList<TMonom>
{
public:
	TPolinom();
	TPolinom(TPolinom& other);
	TPolinom(string str);
	TPolinom& operator=(TPolinom& other); // присваивание
	TPolinom& operator+(TPolinom& q); // сложение полиномов

	// дополнительно можно реализовать:
	void AddMonom(TMonom newMonom); // добавление монома
	TPolinom MultMonom(TMonom monom); // умножение мономов
	TPolinom AddPolinom(TPolinom& other); // добавление полинома
	TPolinom operator*(double c); // умножение полинома на число
	TPolinom operator* (TPolinom& other); // умножение полиномов
	bool operator==(TPolinom& other); // сравнение полиномов на равенство
	string ToString(); // перевод в строку
};

TPolinom::TPolinom() :THeadList<TMonom>::THeadList()
{

}

TPolinom::TPolinom(TPolinom& other):THeadList<TMonom>::THeadList()
{
	TNode<TMonom>* st = other.pCurrent;
	TMonom tmp;
	other.Reset();

	while (!other.IsEnd()) {
		TMonom tmp = other.pCurrent->value;
		InsertLast(tmp);
		other.GoNext();
	}
	if (!other.IsEmpty()) {
		TMonom tmp = other.pCurrent->value;
		InsertLast(tmp);
	}
	while (other.pCurrent != st) { other.GoNext(); GoNext(); }
	length = other.length;
	st = nullptr;
	return;
}

TPolinom::TPolinom(string str)
{
	
	bool st = 0;
	char c;
	int i = 0;
	string mon_per = "XYZ";
	TMonom m;
	//mon_per="";
	//while ((mon_per.size() < 3)&&(i<str.size())) {
	//	c = str[i];
	//	if ((!((c >= '0') || (c <= '9')))&&(c != '^') && (c != '+') && (c != '*')&&(mon_per.find(c)>=0)) mon_per += c; 
	//	i++;
	//}
	//int* mon_ind = new int(mon_per.size());
	//for (int i = 0; i < mon_per.size(); i++) mon_per[i] = 0;
	//i = 0;
	//std::cout << mon_per;
	int* mon_ind = new int[3];
	mon_ind[0] = 0; mon_ind[1] = 0; mon_ind[2] = 0;
	int w = 0;
	int p = 1;
	while ( i < str.size()) {
		c = str[i];

		if ((c == '-') || (c == '+')) {
			if (c == '+') p = 1;
			else p = -1;
			st = 0;
			w = 0;
			m.SetIndex(mon_ind[0] * 100 + mon_ind[1] * 10 + mon_ind[2]);
			if (!IsEmpty()) while (GetCurrentItem() < m) GoNext();
			InsertCurrent(m);
			i++;
			m.SetCoef(0);
			m.SetIndex(0);
			mon_ind[0] = 0; mon_ind[1] = 0; mon_ind[2] = 0;
			continue;
		}

		if ((c >= '0') || (c <= '9')) {
			size_t d = 0;
			int a = stoi(&str[i], &d);
			if (!st) m.SetCoef(p*a);
			else {
				mon_ind[w] = a;
				st = 0;
			}
				i += d+1;
				continue;
		}
		if (c == '^') st = 1;
		else { int tmp = mon_per.find(c); if (tmp >= 0) w= tmp; }
		i++;
	}
}

TPolinom& TPolinom::operator=(TPolinom& other)
{
	std::cout << "-----1----" << endl;
	THeadList::~THeadList();
	TNode<TMonom>* st = other.pCurrent;
	TMonom tmp;
	other.Reset();
	while (!other.IsEnd()) {
		TMonom tmp = other.pCurrent->value;
		InsertLast(tmp);
		other.GoNext();
	}
	while (other.pCurrent != st) { other.GoNext(); GoNext(); }
	length = other.length;
	st = nullptr;
	return *this;
}

void TPolinom::AddMonom(TMonom m)
{
	//if (!IsEmpty()) std::cout << GetCurrentItem();
	TMonom* monom = new TMonom(m);
	if (!IsEmpty()) {
		while ((GetCurrentItem() < m) && (!IsEnd())) GoNext();
		if (GetCurrentItem() == m) return;
		if (IsEnd()) InsertLast(*monom);
		else InsertCurrent(*monom);
	}
	else  InsertFirst(*monom);
	
}

TPolinom TPolinom::MultMonom(TMonom monom)
{
	if (IsEmpty()) return *this;
	Reset();
	TPolinom tmp;
	while (!IsEnd())
	{
		if (pCurrent->value == monom) {
		tmp.AddMonom(monom);
		}
	}
	if (pCurrent->value == monom) {
		tmp.AddMonom(monom);
	}
	*this = tmp;
	return *this;
}

TPolinom& TPolinom::operator+(TPolinom& other)
{
	if (other.IsEmpty()) return *this;
	if (this->IsEmpty()) return other;
	if (length >= other.length) { TPolinom* tmp = new TPolinom(*this); 
	other.Reset();
	while (!other.IsEnd()) {
		tmp->AddMonom(other.GetCurrentItem());
		other.GoNext();
	}
	if (!other.IsEmpty()) tmp->AddMonom(other.GetCurrentItem());
	return *tmp;
	}
	else {
		return (other+*this);
	}

	return *this;
}

TPolinom TPolinom::AddPolinom(TPolinom& other)
{
	return (*this+other);
}

TPolinom TPolinom::operator*(double c)
{
	Reset();
	TPolinom* tmp = new TPolinom(*this);
	while (!tmp->IsEnd()) {
		tmp-> pCurrent->value.coef *= c;
		tmp->GoNext();
	}
	if (!IsEmpty()) tmp->pCurrent->value.coef *= c;
	return *tmp;
}

TPolinom TPolinom::operator*(TPolinom& other)
{


	TPolinom* n = new TPolinom;
	if (other.pFirst->value > pLast->value) return *n;
	if (other.pLast->value < pFirst->value) return *n;

	TPolinom* tmp = new TPolinom();
	other.Reset();
	Reset();
	TMonom o, t;
	while ((!other.IsEnd())&&(!IsEnd())) {
		o = other.GetCurrentItem();
		t = GetCurrentItem();
		if (o == t) { tmp->AddMonom(o); GoNext(); other.GoNext(); continue; }
		if (o > t) GoNext();
		else other.GoNext();
	}
	o = other.GetCurrentItem();
	t = GetCurrentItem();
	if (o==t) tmp->AddMonom(o);
	return *tmp;

	return *this;
}

bool TPolinom::operator==(TPolinom& other)
{
	return false;
}


string TPolinom::ToString()
{
	string result;
	return result;
}

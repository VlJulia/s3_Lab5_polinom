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
	int p = 1;//-coef or +
	while ( i < str.size()) {
		c = str[i];
		if (c == ' ') { i++; continue; }
		if ((c == '-') || (c == '+')) {
			if (c == '+') p = 1;
			else p = -1;
			i++;
			continue;
		}

		if ((c >= '0') && (c <= '9')) {
			size_t d = 0;
			double a = stod(&str[i], &d);
			if (!st) m.SetCoef(p*a);
			i += d;
			continue;
		}
		if (c == 'X') {
			//std::cout << "i= " << i;
			if ((i + 1 < str.size()) && (str[i + 1] != 'Y')) w++;
			if ((i + 1 < str.size()) && (str[i + 1] == '^')) {
				i += 2;
				size_t d = 0;
				int a = stoi(&str[i], &d);
				i += d;
				mon_ind[0] = a;
			}
			else { mon_ind[0] = 1; i++; }
			w++;
			c = str[i];
		}
		//std::cout << c;
		if (c == 'Y') {
			if ((i + 1 < str.size()) && (str[i + 1] != 'Z')) w++;
			if ((i + 1 < str.size()) && (str[i + 1] == '^')) {
				i += 2;
				size_t d = 0;
				int a = stoi(&str[i], &d);
				i += d;
				mon_ind[1] = a;
			}
			else { mon_ind[1] = 1; i++; }
			w++;
			c = str[i];
		}
		if (c == 'Z') {
			if ((i+1<str.size())&&(str[i + 1] == '^')) {
				i += 2;
				size_t d = 0;
				int a = stoi(&str[i], &d);
				i += d;
				mon_ind[2] = a;
			}
			else { mon_ind[2] = 1; i++; }
			w++;
			c = str[i];
		}
		//std::cout << c;
		if (w >= 3) {
			m.SetIndex(mon_ind[0] * 100 + mon_ind[1] * 10 + mon_ind[2]);
			mon_ind[0] = 0;
			mon_ind[1] = 0;
			mon_ind[2] = 0;
			AddMonom(m);
			//std::cout << m<<" ";
			m.coef = 0;
			w=0;
		i++;
		continue;
		}
		i++;
	}
	//AddMonom(m);
}

TPolinom& TPolinom::operator=(TPolinom& other)
{
	//std::cout << "-----1----" << endl;
	Clear();
	if (other.IsEmpty()) return *this;
	TNode<TMonom>* st = other.pCurrent;
	TMonom tmp;
	other.Reset();
	while (!other.IsEnd()) {
		tmp = other.pCurrent->value;
		InsertLast(tmp);
		other.GoNext();
	}
	tmp = other.pCurrent->value;
	InsertLast(tmp);
	other.GoNext();
	while (other.pCurrent != st) { other.GoNext(); GoNext(); }
	length = other.length;
	st = nullptr;
	return *this;
}

void TPolinom::AddMonom(TMonom m)
{
	//if (!IsEmpty()) std::cout << GetCurrentItem();

	if (m.GetCoef() == 0) return;

	if (IsEmpty()) { InsertFirst(m);  return; }

	if (((length == 1) && (pFirst->value.index < m.index))) { InsertLast(m);  
	return; }
	if (((length == 1) && (pFirst->value.index > m.index))) {
		InsertFirst(m);
		return;
	}

	Reset();

	while ((GetCurrentItem().index < m.index)&&(!IsEnd())) { GoNext(); }

	if (GetCurrentItem().index == m.index) {
		pCurrent->value.coef += m.coef;
		if (pCurrent->value.coef == 0) {
			DeleteCurrent(); length++;  
			//std::cout << "  2   MONOM =" << m << " Polinom is  " << *this; 
			return;
		}
		//std::cout << "  2   MONOM =" << m << " Polinom is  " << *this;
		return;
	}
	if (GetCurrentItem().index < m.index) {
		InsertLast(m); return;
	}
	if (GetCurrentItem().index > m.index) {
		InsertCurrent(m); return;
	}
	//std::cout << "  2   MONOM =" << m << " Polinom is  " << *this;
	
}

TPolinom TPolinom::MultMonom(TMonom monom)
{
	if (IsEmpty()) return *this;
	if (monom.coef == 0) { Clear(); return *this; }
	Reset();
	TMonom m;
	while (!IsEnd())
	{
		m.SetCoef(pCurrent->value.GetCoef() * monom.GetCoef());
		m.SetIndex(pCurrent->value.index + monom.GetIndex());
		SetCurrentItem(m);
		GoNext();
	}
		m.SetCoef(pCurrent->value.coef * monom.GetCoef());
		m.SetIndex(pCurrent->value.index + monom.GetIndex());
		SetCurrentItem(m);
	return *this;
}

TPolinom& TPolinom::operator+(TPolinom& other)
{
	if (other.IsEmpty()) return *this;
	//std::cout << "Other " << other<<endl;
	if (this->IsEmpty()) return other;

	if (length >= other.length) {
		TPolinom* tmp = new TPolinom(*this);
		//std::cout << "   +  tmp 1  " << *tmp ;
	other.Reset();
	while (!other.IsEnd()) {
		tmp->AddMonom(other.GetCurrentItem());
		//std::cout << "   +  tmp "  << *tmp ;
		other.GoNext();
	}
	tmp->AddMonom(other.GetCurrentItem());
	//std::cout << "   +  tmp r  " << *tmp;
	return *tmp;
	}
	else return (other + *this);
}

TPolinom TPolinom::AddPolinom(TPolinom& other)
{
	*this = *this + other;
	return *this;
}

TPolinom TPolinom::operator*(double c)
{
	Reset();
	if (IsEmpty()) return *this;
	TPolinom* tmp = new TPolinom(*this);
	tmp->Reset();
	while (!tmp->IsEnd()) {
		tmp-> pCurrent->value.coef *= c;
		tmp->GoNext();
	}
	tmp->pCurrent->value.coef *= c;
	//std::cout <<"TMP"<< *tmp<<"hh";
	return *tmp;
}

TPolinom TPolinom::operator*(TPolinom& other)
{


	if (other.IsEmpty()) return other;
	if (IsEmpty()) return *this;
	TPolinom* tmp = new TPolinom(*this);
	TPolinom* ans = new TPolinom();
	other.Reset();
	Reset();
	while (!other.IsEnd()) {
		tmp->MultMonom(other.GetCurrentItem());
	    //std::cout << "TMP" << *tmp;
		ans->AddPolinom(*tmp);
		//std::cout << "ans" << *ans;
		tmp = this;
		other.GoNext();
	}
	tmp->MultMonom(other.GetCurrentItem());
	ans->AddPolinom(*tmp);
	return *ans;
}

bool TPolinom::operator==(TPolinom& other)
{
	if (length != other.length) return false;
	Reset();
	other.Reset();
	for (int i = 0; i < length; i++) {
		TMonom a, b;
		a = other.GetCurrentItem();
		b = GetCurrentItem();
		GoNext();
		other.GoNext();
		if (!(a == b)) { return false; }
	}
	return true;
}


string TPolinom::ToString()
{
	string result="";
	if (IsEmpty()) return result;
	Reset();
	TMonom tmp;
	while (!IsEnd())
	{
		tmp = GetCurrentItem();
		result += std::to_string(tmp.GetCoef());
		int a = tmp.GetIndex();
		if ((a / 100 != 0)&& (a / 100 != 1)) { result += "X^"; result += std::to_string(a / 100); }
		if (a / 100 == 1) { result += "X"; }
		a %= 100;
		//std::cout << a;
		if ((a / 10 != 0)&& (a / 10 != 1)) { result += "Y^"; result += std::to_string( a / 10); }
		if (a / 10 == 1) { result += "Y";}
		a %= 10;
		if ((a != 0)&& (a != 1)) { result += "Z^"; result += std::to_string(a); }
		if (a == 1) { result += "Z";}
		result += ' ';
		GoNext();
	}

	tmp = GetCurrentItem();
	result += std::to_string(tmp.GetCoef());
	int a = tmp.GetIndex();
	if ((a / 100 != 0) && (a / 100 != 1)) { result += "X^"; result += std::to_string(a / 100); }
	if (a / 100 == 1) { result += "X"; }
	a %= 100;
	//std::cout << a;
	if ((a / 10 != 0) && (a / 10 != 1)) { result += "Y^"; result += std::to_string(a / 10); }
	if (a / 10 == 1) { result += "Y"; }
	a %= 10;
	if ((a != 0) && (a != 1)) { result += "Z^"; result += std::to_string(a); }
	if (a == 1) { result += "Z"; }
	return result;
}

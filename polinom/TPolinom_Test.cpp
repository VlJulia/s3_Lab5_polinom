#include <iostream>
#include <thread>
#include <thread>
#include "TList.h"
#include "TPolinom.h"
#include "THeadList.h"
#include "TMonom.h"
using namespace std;

int main()
{
	setlocale(LC_ALL, "ru");
	cout.precision(2);

	cout << "TLIST" << endl;
	TList<int> t;
	cout << "вставить в начало 0,1" << endl;
	t.InsertFirst(0);
	t.InsertFirst(1);
	cout << t << endl;
	cout << "удалить первый" << endl;
	t.DeleteFirst();
	cout << t << endl;
	cout << "вставить последним 2,3" << endl;
	t.InsertLast(2);
	t.InsertLast(3);
	cout << t << endl;
	cout << "следующий" << endl;
	t.GoNext();
	cout << t << endl;
	cout << "следующий" << endl;
	t.GoNext();
	cout << t << endl;
	cout << "вставить эл" << endl;
	t.InsertCurrent(4);
	cout << t << endl;
	cout << "удалить" << endl;
	t.DeleteCurrent();
	cout << t << endl;
	try {
		cout << "следующий" << endl;
		t.GoNext();
		cout << t << endl;
	}
	catch (...) { cout << " ошибка конец = " << t.IsEnd() << endl << endl; }
	cout << "рестарт" << endl;
	t.Reset();
	cout << t << endl;
	cout << "пустой? = " << t.IsEmpty() << endl << endl;

	cout << "удалить первый пока не пустой" << endl;
	while (!t.IsEmpty()) {
		t.DeleteFirst();
		cout << t;
	}
	cout << "пустой? = " << t.IsEmpty() << endl << endl;
	cout << endl << endl << endl << endl;
	cout << "MONOM" << endl;

	TMonom m1(5, 1, 0, 3);
	TMonom m2(5, 1, 0, 3);
	cout << "m1 " << "кф " << m1.GetCoef() << "   инд " << m1.GetIndex() << endl;
	cout << "m2 " << "кф " << m2.GetCoef() << "   инд " << m2.GetIndex() << endl;
	cout << "m1==m2 " << (m1 == m2) << endl << endl;
	m2.SetCoef(3);
	cout << "m1 " << "кф " << m1.GetCoef() << "   инд " << m1.GetIndex() << endl;
	cout << "m2 " << "кф " << m2.GetCoef() << "   инд " << m2.GetIndex() << endl;
	cout << "m1==m2 " << (m1 == m2) << endl;
	cout << "m1<m2 " << (m1 < m2) << endl;
	cout << "m1>m2 " << (m1 > m2) << endl << endl;
	m1.SetIndex(3);

	cout << "m1 " << "кф " << m1.GetCoef() << "   инд " << m1.GetIndex() << endl;
	cout << "m2 " << "кф " << m2.GetCoef() << "   инд " << m2.GetIndex() << endl;
	cout << "m1==m2 " << (m1 == m2) << endl;
	cout << "m1<m2 " << (m1 < m2) << endl;
	cout << "m1>m2 " << (m1 > m2) << endl << endl;

	cout << endl << endl << endl << endl;




	cout << "HEADLIST" << endl;
	THeadList<int> h1;
	cout << "вставить в начало 0,1" << endl;
	h1.InsertFirst(0);
	h1.InsertFirst(1);
	cout << h1 << endl;
	cout << "удалить первый" << endl;
	h1.DeleteFirst();
	cout << h1 << endl;
	cout << "вставить последним 2,3" << endl;
	h1.InsertLast(2);
	h1.InsertLast(3);
	cout << h1 << endl;
	cout << "следующий" << endl;
	h1.GoNext();
	cout << h1 << endl;
	cout << "следующий" << endl;
	h1.GoNext();
	cout << h1 << endl;
	cout << "вставить эл" << endl;
	h1.InsertCurrent(4);
	cout << h1 << endl;
	cout << "удалить" << endl;
	h1.DeleteCurrent();
	cout << h1 << endl;
	try {
		cout << "следующий" << endl;
		h1.GoNext();
		cout << h1 << endl;
	}
	catch (...) { cout << " ошибка конец = " << h1.IsEnd() << endl << endl; }
	try {
		cout << "следующий" << endl;
		h1.GoNext();
		cout << h1 << endl;
	}
	catch (...) { cout << " ошибка конец = " << h1.IsEnd() << endl << endl; }
	try {
		cout << "следующий" << endl;
		h1.GoNext();
		cout << h1 << endl;
	}
	catch (...) { cout << " ошибка конец = " << h1.IsEnd() << endl << endl; }
	try {
		cout << "следующий" << endl;
		h1.GoNext();
		cout << h1 << endl;
	}
	catch (...) { cout << " ошибка конец = " << h1.IsEnd() << endl << endl; }
	cout << "рестарт" << endl;
	h1.Reset();
	cout << h1 << endl;
	cout << "пустой? = " << h1.IsEmpty() << endl << endl;

	cout << "удалить первый пока не пустой" << endl;
	while (!t.IsEmpty()) {
		h1.DeleteFirst();
		cout << h1;
	}
	cout << "пустой? = " << h1.IsEmpty() << endl << endl;
	cout << endl << endl << endl << endl;


	cout << "POLINOM" << endl;
	TPolinom p;
	p.AddMonom(TMonom(3, 1, 2, 3));
	p.AddMonom(TMonom(2, 1, 4, 3));
	p.AddMonom(TMonom(1, 1, 6, 3));
	TPolinom p2 = p;
	cout << (p2 == p);
	p.Clear();
	p.AddMonom(TMonom(1, 3, 6, 3));
	cout << "p2\n" << p2 << endl << endl;
	cout << "p\n" << p << endl << endl;
	TPolinom p3 = p2 * p;
	cout << "p3 = p2*p \n" << p3 << endl << endl;

	p3.MultMonom(TMonom(1, 1, 6, 3));
	cout << "p3 mult 1, 1, 6, 3\n" << p3 << endl << endl;
	p3.AddMonom(TMonom(1, 1, 6, 3));;
	cout << "p3 add 1, 1, 6, 3\n" << p3 << endl << endl;
	p3.MultMonom(TMonom(1, 1, 6, 3));
	cout << "p3 mult 1, 1, 6, 3\n" << p3 << endl << endl;
	p2.AddMonom(TMonom(1, 3, 2, 6));
	TPolinom p4 = p2 + p3;
	cout << "\np2  =" << p2.ToString();
	cout << "\np3  =" << p3.ToString();
	cout << "\np4 = p2+p3 \n" << p4.ToString() << endl << endl;
	TPolinom p5("4X^9YZ - 5XZ");
	cout << p5;
	cout << p5.ToString() << endl;
	cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
	

	/*TPolinom p,p2;
	int n = 1000;


	for (int i = 0; i < n; i++) p.AddMonom(TMonom(rand()%10, rand() % 10, rand() % 10, rand() % 10));
	for (int i = 0; i < n; i++) p2.AddMonom(TMonom(rand() % 10, rand() % 10, rand() % 10, rand() % 10));
	p.Reset();
	p2.Reset();
	cout << "----------------- ";
	int i=0;
	auto start = chrono::high_resolution_clock::now();
	try {
		p* p2;
		}
		catch (...) { cout << "i is " << i << endl; };
	auto end = chrono::high_resolution_clock::now();
	chrono::duration<double> d = end - start;
	cout << "----------------- " << d.count() << " ------------------------------";
	return 0;*/

	// здесь должна быть проверка работоспособности написанных вами классов
	

}
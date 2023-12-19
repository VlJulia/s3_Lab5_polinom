#pragma once
struct TMonom
{
	double coef; // коэффициент монома
	int index; // индекс (свертка степеней)


	TMonom(double coef = 0, int degX = 0, int degY = 0, int degZ = 0);

	void SetCoef(int cval) { coef = cval; }
	double GetCoef(void) { return coef; }

	void SetIndex(int ival) { index = ival; }
	int GetIndex(void) { return index; }


	bool operator==(const TMonom& other) { return ((index == other.index) && (coef == other.coef)); }
	
	bool operator>(const TMonom& other);

	bool operator<(const TMonom& other);

	TMonom operator=(const TMonom& other);
	friend ostream& operator<<(ostream& os, const TMonom& obj) {
		if (&obj == nullptr) { return os; }
		os << obj.coef << " index " << obj.index;
		return os;
	}
};
TMonom::TMonom(double coef, int degX, int degY, int degZ) {
	this->coef = coef;
	this->index = (degX%10) * 100 + (degY%10) * 10 + (degZ%10);//just in case
}

bool TMonom::operator>(const TMonom& other) {
	/*int s1 = 0, s2 = 0, tmp1 = index, tmp2 = other.index;
	while ((tmp1 != 0) || (tmp2 != 0)) {
		s1 += tmp1 % 10; tmp1 /= 10;
		s2 += tmp2 % 10; tmp2 /= 10;
	}
	if (s1>s2) return 1;
	if (s2 > s1) return 0;*/
	if (index > other.index) return 1;
	if (index < other.index) return 0;
	if (coef>other.coef) return 1;
	return 0;

}

bool TMonom::operator<(const TMonom& other) {
	if (*this == other) return 0;
	if (*this > other) return 0;
	return 1;
};
TMonom  TMonom::operator=(const TMonom& other) {
	if (*this == other) return *this;
	this->coef = other.coef;
	this->index = other.index;
	return *this;
};
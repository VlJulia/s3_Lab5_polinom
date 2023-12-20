#include "TPolinom.h"
#include <gtest.h>

TEST(Polinom, Created_polinom_is_empty) {
	TPolinom p;
	EXPECT_EQ(p.IsEmpty(), 1);
}

TEST(Polinom, Created_polinom_with_one_monom_is_not_empty) {
	TPolinom p;
	p.AddMonom(TMonom(1,2,3,4));
	EXPECT_EQ(p.IsEmpty(), 0);
}

TEST(Polinom, Coefficients_add_up_if_degrees_are_equal) {
	TPolinom p;
	p.AddMonom(TMonom(1, 2, 3, 4));
	p.AddMonom(TMonom(1, 2, 3, 4));

	EXPECT_EQ(2, p.GetCurrentItem().GetCoef());

}

TEST(Polinom, Coefficients_dont_add_up_if_degrees_are_different) {
	TPolinom p;
	p.AddMonom(TMonom(1, 2, 3, 4));
	p.AddMonom(TMonom(1, 5, 3, 4));

	EXPECT_EQ(1, p.GetCurrentItem().GetCoef());
}

TEST(Polinom, Monom_delete_if_coefficient_equal_zero) {
	TPolinom p;
	p.AddMonom(TMonom(1, 2, 3, 4));
	p.AddMonom(TMonom(-1, 2, 3, 4));
	EXPECT_EQ(1, p.IsEmpty());
}

TEST(Polinom, Can_not_get_monom_from_empty_polinom) {
	TPolinom p;
	ASSERT_ANY_THROW(p.GetCurrentItem());
}

TEST(Polinom, Copied_polinom_is_equal_copiable) {
	TPolinom p;
	p.AddMonom(TMonom(1,2,3,4));
	TPolinom p2(p);
	bool ans = (p2==p);
	EXPECT_EQ(ans,1);
}
TEST(Polinom, Assigned_polinom_is_equal_assignable) {
	TPolinom p;
	p.AddMonom(TMonom(1, 2, 3, 4));
	TPolinom p2=p;
	bool ans = (p2 == p);
	EXPECT_EQ(ans, 1);
}

TEST(Polinom, Correct_adding_operator) {
	TPolinom p;
	TMonom m2(1, 5, 3, 4);
	TMonom m1(1, 2, 3, 4);
	p.AddMonom(m2);
	p.AddMonom(m1);
	p.Reset();
	//std::cout << p ;
	bool ans = (m1.GetCoef() == p.GetCurrentItem().GetCoef());
	ans = ans&&(m1.GetIndex() == p.GetCurrentItem().GetIndex());
	p.GoNext();

	ans = ans&&(m2.GetCoef() == p.GetCurrentItem().GetCoef());
	ans = ans && (m2.GetIndex() == p.GetCurrentItem().GetIndex());
	EXPECT_EQ(1, ans);
}
/*
*/
TEST(Polinom, Correct_constant_multiply) {
	TPolinom p;
	TMonom m2(1, 5, 3, 4);
	TMonom m1(1, 2, 3, 4);
	p.AddMonom(m2);
	p.AddMonom(m1);
	//std::cout << p;
	p=p*2;
	//std::cout << p;
	p.Reset();
	bool ans = (2== p.GetCurrentItem().GetCoef());
	ans = ans && (m1.GetIndex() == p.GetCurrentItem().GetIndex());
	p.GoNext();

	ans = ans && (2== p.GetCurrentItem().GetCoef());
	ans = ans && (m2.GetIndex() == p.GetCurrentItem().GetIndex());
	EXPECT_EQ(1, ans);
}

TEST(Polinom, Correct_monom_multiply) {
	TPolinom p;
	p.AddMonom(TMonom(3, 1, 0, 1));
	p.AddMonom(TMonom(1, 1, 2, 1));
	p.MultMonom(TMonom(3, 2, 2, 2));
	TPolinom p2;
	p2.AddMonom(TMonom(9, 3, 2, 3));
	p2.AddMonom(TMonom(3, 3, 4, 3));
	p2.Reset();
	//std::cout << p<<"ddsaddsa"<<p2;
	bool ans = (p== p2);
	EXPECT_EQ(1, ans);
}

TEST(Polinom, polinom_fromString) {
	TPolinom p5("4X^9YZ - 5XZ");
	p5.Reset();
	TMonom m = p5.GetCurrentItem();
	p5.GoNext();
	TMonom m2 = p5.GetCurrentItem();
	bool ans = ((m2.coef == 4) && (m2.index == 911));
	ans = ans && ((m.coef == -5) && (m.index == 101));
	EXPECT_EQ(1, ans);
}

TEST(Polinom, Correct_multiply_polinom1) {
	TPolinom p;
	p.AddMonom(TMonom(3, 1, 2, 3)); 
	p.AddMonom(TMonom(2, 1, 4, 3));
	TPolinom p2;
	p2.AddMonom(TMonom(1, 3, 1, 3));
	p2.AddMonom(TMonom(1, 2, 2, 2));
	TPolinom p3 = p2 * p;
	TPolinom p4;
	p4.AddMonom(TMonom(3, 4, 3, 6));
	p4.AddMonom(TMonom(3, 3, 4, 5));
	p4.AddMonom(TMonom(2, 4, 5, 6));
	p4.AddMonom(TMonom(2, 3, 6, 5));

	//std::cout << p3 << "  " << p4;
	bool ans = (p3 == p4);
	EXPECT_EQ(1, ans);
}

TEST(Polinom, Correct_multiply_polinom2) {
	TPolinom p;
	p.AddMonom(TMonom(3, 1, 2, 3));
	p.AddMonom(TMonom(2, 1, 4, 3)); 
	TPolinom p2 ;
	TPolinom p3 = p2 * p;
	//std::cout << p << "  " << p3;
	bool ans = (p3.IsEmpty());
	EXPECT_EQ(1, ans);
}

TEST(Polinom, Correct_multiply_polinom3) {
	TPolinom p;
	p.AddMonom(TMonom(3, 1, 2, 3)); 
	p.AddMonom(TMonom(2, 1, 4, 3)); 
	p.AddMonom(TMonom(1, 1, 6, 3)); 
	TPolinom p2;
	//std::cout << p2.IsEmpty() << "dsdf ";
	TPolinom p3 = p2 * p;
	bool ans = (p3.IsEmpty());
	EXPECT_EQ(1, ans);
}

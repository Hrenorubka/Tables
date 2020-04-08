#include "Polinom.h"
#include <gtest.h>
/*
Polynomial view : "coef"x^power/y^power/z^power-"coef"x^power/y^power/z^power etc
Examples: 3x^4, y^4x-3z^3, 4, x^7yx
If power >9, when you enter power, you get error
*/

TEST(Polinom_, can_create_polinom)
{
	ASSERT_NO_THROW(Polinom p);
}

TEST(Polinom_, can_create_polinom_from_string)
{
	string obl = "x";
	ASSERT_NO_THROW(Polinom p(obl));
}

TEST(Polinom_, can_create_copy_of_polinom)
{
	string obl = "x";
	Polinom p(obl);
	ASSERT_NO_THROW(Polinom p_cpoy(p));
}

TEST(Polinom_, can_push_elem)
{
	Polinom p;
	Monom obl = {123, 3.14};
	ASSERT_NO_THROW(p.push(obl));
}

TEST(Polinom_, can_check_empty)
{
	Polinom p;
	EXPECT_EQ(true, p.empty());
}

TEST(Polinom_, can_check_no_empty)
{
	Polinom p;
	Monom obl = { 123, 3.14 };
	p.push(obl);
	EXPECT_NE(true, p.empty());
}

TEST(Polinom_, can_check_size)
{
	Polinom p;
	Monom obl = { 123, 3.14 };
	p.push(obl);
	EXPECT_EQ(1, p.get_size());
}

TEST(Polinom_, can_create_or_add_pol_from_string)
{
	Polinom p;
	string s = "xyz";
	ASSERT_NO_THROW(p.create_pol(s););
}

TEST(Polinom_, can_compare_equal_polinom)
{
	string s = "-x+y";
	Polinom p1(s), p2(s);
	EXPECT_EQ(true, p1 == p2);
}

TEST(Polinom_, can_compare_nonequal_polinom)
{
	string s = "-x+y";
	Polinom p1(s), p2(s+"+z");
	EXPECT_EQ(true, p1 != p2);
}

TEST(Polinom_, can_do_operation_equal)
{
	Polinom p;
	string s = "xyz";
	p.create_pol(s);
	ASSERT_NO_THROW(p = p);
}

TEST(Polinom_, can_do_operation_add)
{
	Polinom p;
	string s = "xyz";
	p.create_pol(s);
	ASSERT_NO_THROW(p + p);
}

TEST(Polinom_, can_do_operation_difference)
{
	Polinom p;
	string s = "xyz";
	p.create_pol(s);
	ASSERT_NO_THROW(p - p);
}

TEST(Polinom_, can_do_operation_mult_with_numb)
{
	Polinom p;
	string s = "xyz";
	p.create_pol(s);
	ASSERT_NO_THROW(p * 3);
}

TEST(Polinom_, can_do_operation_mult_with_polynomial)
{
	Polinom p;
	string s = "xyz";
	p.create_pol(s);
	ASSERT_NO_THROW(p * p);
}
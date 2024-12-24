// тесты для вычисления арифметических выражений

#include <gtest.h>
#include "arithmetic.h"


TEST(arithmetic, can_create_arithmetic) {
	string a = "1+2";
	TArithmeticExpression b(a);
	EXPECT_EQ(a, b.GetInfix());
}

TEST(arithmetic, cant_create_arithmetic_extra_arithmetic_sign) {
	string a = "+1+2";
	ASSERT_ANY_THROW(TArithmeticExpression b(a));
}

TEST(arithmetic, cant_create_arithmetic_extra_bracket) {
	string a = "(1+2))";
	ASSERT_ANY_THROW(TArithmeticExpression b(a));
}

TEST(arithmetic, cant_create_arithmetic_extra_point) {
	string a = "1.3.+2";
	ASSERT_ANY_THROW(TArithmeticExpression b(a));
}

TEST(arithmetic, cant_create_arithmetic_incorrect_elem) {
	string a = "1.3?+2";
	ASSERT_ANY_THROW(TArithmeticExpression b(a));
}

TEST(arithmetic, cant_create_arithmetic_sign_after_bracket) {
	string a = "1+(+1.3+2)";
	ASSERT_ANY_THROW(TArithmeticExpression b(a));
}

TEST(arithmetic, cant_create_arithmetic_point_after_bracket) {
	string a = "1+(.1.3+2)";
	ASSERT_ANY_THROW(TArithmeticExpression b(a));
}

TEST(arithmetic, cant_create_arithmetic_point_after_operand) {
	string a = "1+(a.+2)";
	ASSERT_ANY_THROW(TArithmeticExpression b(a));
}

TEST(arithmetic, can_create_postfix_with_operands_different_priority) {
	string a = "1+1*3";
	string res = "113*+";
	TArithmeticExpression b(a);
	EXPECT_EQ(res, b.GetPostfix());
}

TEST(arithmetic, can_create_postfix_with_brackets) {
	string a = "1+2*(3+8)-1";
	string res = "1238+*+1-";
	TArithmeticExpression b(a);
	EXPECT_EQ(res, b.GetPostfix());
}

TEST(arithmetic, can_create_postfix_with_nested_brackets) {
	string a = "1+2*(3+8*(3-18/9))-1";
	string res = "12383189/-*+*+1-";
	TArithmeticExpression b(a);
	EXPECT_EQ(res, b.GetPostfix());
}


TEST(arithmetic, can_calculate_arithmetic_with_operands_different_priority) {
	string a = "1+1*3";
	TArithmeticExpression b(a);
	EXPECT_EQ(4, b.Calculate({}));
}

TEST(arithmetic, can_calculate_arithmetic_with_brackets) {
	string a = "1+2*(3+8)-1";
	TArithmeticExpression b(a);
	EXPECT_EQ(22, b.Calculate({}));
}

TEST(arithmetic, can_calculate_arithmetic_with_nested_brackets) {
	string a = "1+2*(3+8*(3-18/9))-1";
	TArithmeticExpression b(a);
	EXPECT_EQ(22, b.Calculate({}));
}

TEST(arithmetic, can_calculate_arithmetic_with_operands) {
	string a = "1+2*(bc+8*(bc-18/ab))-1";
	TArithmeticExpression b(a);
	EXPECT_EQ(22, b.Calculate({ {"ab", 9}, {"bc", 3} }));
}

TEST(arithmetic, division_by_zero) {
	TArithmeticExpression a("1/0");
	ASSERT_ANY_THROW(a.Calculate({}));
}

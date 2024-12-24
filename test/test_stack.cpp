// тесты для стека

#include <gtest.h>
#include "stack.h"

TEST(stack, can_create_stack) {
	TVectorStack <char> s;
	EXPECT_EQ(0, s.size());
}

TEST(stack, can_push_and_find_last_elem) {
	TVectorStack <char> s;
	s.Push('1');
	s.Push('2');
	EXPECT_EQ(2, s.size());
	EXPECT_EQ('2', s.LastElem());
}

TEST(stack, can_pop) {
	TVectorStack <char> s;
	s.Push('1');
	s.Push('2');
	char a = s.Pop();
	EXPECT_EQ(1, s.size());
	EXPECT_EQ('2', a);
}

TEST(stack, cant_pop) {
	TVectorStack <char> s;
	ASSERT_ANY_THROW(s.Pop());
}

TEST(stack, can_give_last_elem) {
	TVectorStack <char> s;
	s.Push('1');
	s.Push('2');
	EXPECT_EQ('2', s.LastElem());
}

TEST(stack, cant_give_last_elem) {
	TVectorStack <char> s;
	ASSERT_ANY_THROW(s.LastElem());
}

TEST(stack, can_clear_stack) {
	TVectorStack <char> s;
	s.Push('1');
	s.Push('2');
	EXPECT_EQ(2, s.size());
	s.ClearStack();
	EXPECT_EQ(0, s.size());
}

TEST(stack, cant_clear_stack) {
	TVectorStack <char> s;
	ASSERT_ANY_THROW(s.ClearStack());
}

#include "test_containers.h"

TEST(test_stack, constructorDefault) {
  s21::Stack<int> st1;

  EXPECT_EQ(st1.size(), 0);
}

TEST(test_stack, constructorInitializer_list) {
  s21::Stack<int> st1{1, 2, 3, 4, 5};

  EXPECT_EQ(st1.size(), 5);
  EXPECT_EQ(st1.top(), 5);
}

TEST(test_stack, constructorCopy) {
  s21::Stack<int> st1{1, 2, 3, 4, 5};
  s21::Stack<int> st2(st1);

  EXPECT_EQ(st1.size(), st2.size());
  EXPECT_EQ(st1.top(), st2.top());
}

TEST(test_stack, constructorMove) {
  s21::Stack<int> st1{1, 2, 3, 4, 5};
  s21::Stack<int> st2(std::move(st1));

  EXPECT_EQ(st2.size(), 5);
  EXPECT_EQ(st2.top(), 5);
  EXPECT_EQ(st1.size(), 0);
}

TEST(test_stack, operatorAssign) {
  s21::Stack<int> st1{1, 2, 3, 4, 5};
  s21::Stack<int> st2 = std::move(st1);

  EXPECT_EQ(st2.size(), 5);
  EXPECT_EQ(st2.top(), 5);
  EXPECT_EQ(st1.size(), 0);
}

TEST(test_stack, top) {
  s21::Stack<int> st1{1, 2, 3, 4, 5};
  s21::Stack<int> st2;

  EXPECT_EQ(st1.top(), 5);
  EXPECT_THROW(st2.top(), std::out_of_range);
}

TEST(test_stack, empty) {
  s21::Stack<int> st1{1, 2, 3, 4, 5};
  s21::Stack<int> st2;

  EXPECT_FALSE(st1.empty());
  EXPECT_TRUE(st2.empty());
}

TEST(test_stack, size) {
  s21::Stack<int> st1{1, 2, 3, 4, 5};
  s21::Stack<int> st2;

  EXPECT_EQ(st1.size(), 5);
  EXPECT_EQ(st2.size(), 0);
}

TEST(test_stack, push) {
  s21::Stack<int> st1{1, 2, 3, 4, 5};
  EXPECT_EQ(st1.size(), 5);
  EXPECT_EQ(st1.top(), 5);

  st1.push(6);
  EXPECT_EQ(st1.size(), 6);
  EXPECT_EQ(st1.top(), 6);

  st1.push(7);
  st1.push(8);
  st1.push(9);
  st1.push(10);
  st1.push(11);
  st1.push(13);
  st1.push(13);
  st1.push(14);
  st1.push(15);
  st1.push(16);
  EXPECT_EQ(st1.size(), 16);
  EXPECT_EQ(st1.top(), 16);
}

TEST(test_stack, pop) {
  s21::Stack<int> st1{1, 2, 3, 4, 5};
  EXPECT_EQ(st1.top(), 5);

  st1.pop();
  EXPECT_EQ(st1.size(), 4);
  EXPECT_EQ(st1.top(), 4);

  s21::Stack<int> st2;
  EXPECT_THROW(st2.top(), std::out_of_range);
}

TEST(test_stack, swap) {
  s21::Stack<int> st1{1, 2, 3, 4, 5};
  s21::Stack<int> st2{7, 7, 7};

  EXPECT_EQ(st1.top(), 5);
  EXPECT_EQ(st2.top(), 7);

  st1.swap(st2);
  EXPECT_EQ(st1.top(), 7);
  EXPECT_EQ(st2.top(), 5);

  s21::Stack<int> st3;
  EXPECT_THROW(st3.swap(st2), std::out_of_range);
}

TEST(test_stack, insert_many_back) {
  s21::Stack<int> st1;

  st1.insert_many_back(1, 2, 3, 4, 5);

  EXPECT_EQ(st1.top(), 5);
  st1.pop();
  EXPECT_EQ(st1.top(), 4);
  st1.pop();
  EXPECT_EQ(st1.top(), 3);
  st1.pop();
  EXPECT_EQ(st1.top(), 2);
  st1.pop();
  EXPECT_EQ(st1.top(), 1);
}

#include "test_containers.h"

TEST(test_list, constructorDefault) {
  s21::List<int> one;

  EXPECT_EQ(one.size(), 0);
}

TEST(test_list, constructorCopy) {
  s21::List<int> one;
  one.push_back(1);
  one.push_back(2);
  one.push_back(3);
  one.push_back(4);

  s21::List<int> two(one);

  EXPECT_EQ(two.size(), 4);
  EXPECT_EQ(one.size(), 4);
}

TEST(test_list, constructorCreateListOnValue) {
  s21::List<int> one(5);

  EXPECT_EQ(one.size(), 5);
}

TEST(test_list, constructorInitializer_list) {
  s21::List<int> one{1, 2, 3};

  EXPECT_EQ(one.size(), 3);
}

TEST(test_list, constructorMove) {
  s21::List<int> one;
  one.push_back(1);
  one.push_back(3);
  one.push_back(5);
  one.push_back(7);

  s21::List<int> two(std::move(one));

  EXPECT_EQ(two.size(), 4);
  EXPECT_EQ(one.size(), 0);
}

TEST(test_list, operatorAssignment) {
  s21::List<int> one;
  one.push_back(1);
  one.push_back(3);
  one.push_back(5);
  one.push_back(7);
  s21::List<int> two = one;

  EXPECT_EQ(two.size(), 4);
}

TEST(test_list, const_reference_front) {
  s21::List<int> one;
  one.push_back(1);
  one.push_back(3);
  one.push_back(5);
  one.push_back(7);

  EXPECT_EQ(one.front(), 1);
}

TEST(test_list, const_reference_back) {
  s21::List<int> one;
  one.push_back(1);
  one.push_back(3);
  one.push_back(5);
  one.push_back(7);

  EXPECT_EQ(one.back(), 7);
}

// надо сделать
TEST(test_list, iterator_begin) {
  s21::List<int> one;
  one.push_back(1);
  one.push_back(3);
  one.push_back(5);
  one.push_back(7);

  List<int>::iterator it = one.begin();

  EXPECT_EQ(*it, 1);
}

TEST(test_list, iterator_end) {
  s21::List<int> one;
  one.push_back(1);

  List<int>::iterator it = one.begin();
  it++;
  EXPECT_EQ(it, one.end());
}

TEST(test_list, empty) {
  s21::List<int> one;
  one.push_back(1);
  one.push_back(3);
  one.push_back(5);
  one.push_back(7);

  bool isEmpty = one.empty();

  EXPECT_EQ(isEmpty, 0);
}

TEST(test_list, clear) {
  s21::List<int> one;
  one.push_back(1);
  one.push_back(3);
  one.push_back(5);
  one.push_back(7);

  one.clear();

  EXPECT_EQ(one.size(), 0);
}

TEST(test_list, swap) {
  s21::List<int> one;
  one.push_back(1);
  one.push_back(3);
  one.push_back(5);
  one.push_back(7);

  s21::List<int> two;
  two.push_back(5);
  two.push_back(5);
  two.push_back(5);
  two.push_back(5);

  one.swap(two);

  EXPECT_EQ(one[0], 5);
  EXPECT_EQ(two[0], 1);
}

TEST(test_list, sort) {
  s21::List<int> one;
  one.push_back(7);
  one.push_back(3);
  one.push_back(5);
  one.push_back(1);

  one.sort();

  EXPECT_EQ(one[0], 1);
  EXPECT_EQ(one[3], 7);
}

TEST(test_list, merge) {
  s21::List<int> one;
  one.push_back(7);
  one.push_back(3);
  one.push_back(5);
  one.push_back(1);

  s21::List<int> two;
  two.push_back(10);
  two.push_back(11);

  one.merge(two);

  EXPECT_EQ(one[0], 1);
  EXPECT_EQ(one[4], 10);
  EXPECT_EQ(one[5], 11);
}

TEST(test_list, splice) {
  s21::List<int> one;
  one.push_back(1);
  one.push_back(2);
  one.push_back(3);
  one.push_back(6);

  s21::List<int> two;
  two.push_back(4);
  two.push_back(5);

  List<int>::iterator it = one.begin();
  ++it;
  ++it;

  one.splice(it, two);

  EXPECT_EQ(one[0], 1);
  EXPECT_EQ(one[1], 2);
  EXPECT_EQ(one[2], 3);
  EXPECT_EQ(one[3], 4);
  EXPECT_EQ(one[4], 5);
  EXPECT_EQ(one[5], 6);
}

TEST(test_list, reverse) {
  s21::List<int> one;
  one.push_back(1);
  one.push_back(2);
  one.push_back(3);
  one.push_back(4);

  one.reverse();

  EXPECT_EQ(one[0], 4);
  EXPECT_EQ(one[3], 1);
}

TEST(test_list, unique) {
  s21::List<int> one;
  one.push_back(1);
  one.push_back(1);
  one.push_back(2);
  one.push_back(2);
  one.push_back(3);
  one.push_back(3);
  one.push_back(4);
  one.push_back(4);
  one.push_back(5);
  one.push_back(5);

  one.unique();

  EXPECT_EQ(one[0], 1);
  EXPECT_EQ(one[1], 2);
  EXPECT_EQ(one[2], 3);
  EXPECT_EQ(one[3], 4);
  EXPECT_EQ(one[4], 5);
}

TEST(test_list, push_back) {
  s21::List<int> one;
  one.push_front(2);
  one.push_back(1);

  EXPECT_EQ(one[1], 1);
}

TEST(test_list, push_front) {
  s21::List<int> one;
  one.push_back(1);
  one.push_front(2);

  EXPECT_EQ(one[0], 2);
}

TEST(test_list, pop_back) {
  s21::List<int> one;
  one.push_back(1);
  one.push_back(2);
  one.pop_back();

  EXPECT_EQ(one.size(), 1);
  EXPECT_EQ(one[0], 1);
}

TEST(test_list, pop_front) {
  s21::List<int> one;
  one.push_back(1);
  one.push_back(2);
  one.pop_front();

  EXPECT_EQ(one.size(), 1);
  EXPECT_EQ(one[0], 2);
}

TEST(test_list, insert) {
  s21::List<int> one;
  one.push_back(2);
  one.push_back(3);
  one.insert(one.begin(), 1);
  one.insert(one.end(), 4);

  EXPECT_EQ(one[0], 1);
  EXPECT_EQ(one[3], 4);
}

TEST(test_list, erase) {
  s21::List<int> one;
  one.push_back(1);
  one.push_back(2);
  one.push_back(3);
  auto it = one.begin();
  ++it;
  one.erase(it);

  EXPECT_EQ(one[0], 1);
  EXPECT_EQ(one[1], 3);
  EXPECT_EQ(one.size(), 2);
}

TEST(test_list, max_size) {
  s21::List<int> one;
  EXPECT_GT(one.max_size(), 0);
}

TEST(test_list, insert_many) {
  s21::List<int> one;
  one.push_back(1);
  one.push_back(5);
  one.push_back(6);

  List<int>::iterator it = one.begin();
  ++it;
  one.insert_many(it, 2, 3, 4);

  EXPECT_EQ(one[0], 1);
  EXPECT_EQ(one[1], 2);
  EXPECT_EQ(one[2], 3);
  EXPECT_EQ(one[3], 4);
  EXPECT_EQ(one[4], 5);
  EXPECT_EQ(one[5], 6);
}

TEST(test_list, insert_many_back) {
  s21::List<int> one;
  one.push_back(1);
  one.push_back(2);
  one.push_back(3);

  one.insert_many_back(4, 5, 6);

  EXPECT_EQ(one[0], 1);
  EXPECT_EQ(one[1], 2);
  EXPECT_EQ(one[2], 3);
  EXPECT_EQ(one[3], 4);
  EXPECT_EQ(one[4], 5);
  EXPECT_EQ(one[5], 6);
}

TEST(test_list, insert_many_front) {
  s21::List<int> one;
  one.push_back(4);
  one.push_back(5);
  one.push_back(6);

  one.insert_many_front(1, 2, 3);

  EXPECT_EQ(one[0], 1);
  EXPECT_EQ(one[1], 2);
  EXPECT_EQ(one[2], 3);
  EXPECT_EQ(one[3], 4);
  EXPECT_EQ(one[4], 5);
  EXPECT_EQ(one[5], 6);
}

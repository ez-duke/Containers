#include "test_containers.h"

TEST(test_set, DefaultConstructor) {
  s21::Set<int> set;
  EXPECT_EQ(set.Size(), 0);
}

TEST(test_set, InitializerListConstructor) {
  s21::Set<int> set{1, 2, 0, 3, -1};
  EXPECT_EQ(set.Size(), 5);
  EXPECT_NE(set.Find(1), nullptr);
  EXPECT_NE(set.Find(2), nullptr);
  EXPECT_NE(set.Find(0), nullptr);
  EXPECT_NE(set.Find(3), nullptr);
  EXPECT_NE(set.Find(-1), nullptr);
  EXPECT_EQ(set.Find(-2), nullptr);
}

TEST(test_set, CopyConstructor) {
  s21::Set<int> copied{3, 2, 1};
  s21::Set<int> set(copied);
  EXPECT_EQ(set.Size(), 3);
  EXPECT_NE(set.Find(1), nullptr);
  EXPECT_NE(set.Find(2), nullptr);
  EXPECT_NE(set.Find(3), nullptr);
  EXPECT_EQ(set.Find(0), nullptr);
}

TEST(test_set, MoveConstructor) {
  s21::Set<int> moved{3, 2, 1};
  s21::Set<int> set(std::move(moved));
  EXPECT_EQ(set.Size(), 3);
  EXPECT_EQ(moved.Size(), 0);
  EXPECT_NE(set.Find(1), nullptr);
  EXPECT_NE(set.Find(2), nullptr);
  EXPECT_NE(set.Find(3), nullptr);
}

TEST(test_set, AssignOperator) {
  s21::Set<int> set{1, 2, 3, 4};
  s21::Set<int> set2 = set;
  EXPECT_EQ(set2.Size(), 4);
  EXPECT_NE(set2.Find(1), nullptr);
  EXPECT_NE(set2.Find(2), nullptr);
  EXPECT_NE(set2.Find(3), nullptr);
  EXPECT_NE(set2.Find(4), nullptr);
}

TEST(test_set, Begin) {
  s21::Set<int> set{-1, 2, 3, -2};
  EXPECT_EQ(set.Find(-2), set.Begin());
}

TEST(test_set, End) {
  s21::Set<int> set{-1, 2, 3, -2};
  EXPECT_EQ(set.Find(3), set.End());
}

TEST(test_set, Empty) {
  s21::Set<int> set{-1, 2, 3};
  EXPECT_EQ(0, set.Empty());
  s21::Set<int> setEmpty;
  EXPECT_EQ(1, setEmpty.Empty());
}

TEST(test_set, Size) {
  s21::Set<int> set{-1, 2, 3};
  EXPECT_EQ(3, set.Size());
}

TEST(test_set, Clear) {
  s21::Set<int> set{-1, 2, 3, 4};
  EXPECT_EQ(4, set.Size());
  set.Clear();
  EXPECT_EQ(0, set.Size());
  EXPECT_EQ(1, set.Empty());
}

TEST(test_set, Insert) {
  s21::Set<int> set{1, 2, 3, 4};
  set.Insert(-2);
  EXPECT_NE(set.Find(1), nullptr);
  EXPECT_NE(set.Find(2), nullptr);
  EXPECT_NE(set.Find(3), nullptr);
  EXPECT_NE(set.Find(4), nullptr);
  EXPECT_NE(set.Find(-2), nullptr);
  EXPECT_EQ(5, set.Size());

  set.Insert(-1);
  EXPECT_NE(set.Find(1), nullptr);
  EXPECT_NE(set.Find(2), nullptr);
  EXPECT_NE(set.Find(3), nullptr);
  EXPECT_NE(set.Find(4), nullptr);
  EXPECT_NE(set.Find(-2), nullptr);
  EXPECT_NE(set.Find(-1), nullptr);
  EXPECT_EQ(6, set.Size());

  set.Insert(5);
  EXPECT_NE(set.Find(1), nullptr);
  EXPECT_NE(set.Find(2), nullptr);
  EXPECT_NE(set.Find(3), nullptr);
  EXPECT_NE(set.Find(4), nullptr);
  EXPECT_NE(set.Find(-2), nullptr);
  EXPECT_NE(set.Find(-1), nullptr);
  EXPECT_NE(set.Find(5), nullptr);
  EXPECT_EQ(7, set.Size());
}

TEST(test_set, Erase) {
  s21::Set<int> set{-1, 2, 3, 4};
  set.Erase(set.Begin());
  EXPECT_EQ(set.Find(-1), nullptr);
  EXPECT_EQ(3, set.Size());

  set.Erase(set.End());
  EXPECT_EQ(set.Find(4), nullptr);
  EXPECT_EQ(2, set.Size());
}

TEST(test_set, Swap) {
  s21::Set<int> set{1, 2, 3, 4};
  s21::Set<int> set2{0, -1, -2, -3};
  set.Swap(set2);
  EXPECT_EQ(4, set.Size());
  EXPECT_EQ(4, set2.Size());
  EXPECT_NE(set2.Find(1), nullptr);
  EXPECT_NE(set2.Find(2), nullptr);
  EXPECT_NE(set2.Find(3), nullptr);
  EXPECT_NE(set2.Find(4), nullptr);
  EXPECT_EQ(set2.Find(0), nullptr);
  EXPECT_EQ(set2.Find(-1), nullptr);
  EXPECT_EQ(set2.Find(-2), nullptr);
  EXPECT_EQ(set2.Find(-3), nullptr);

  EXPECT_NE(set.Find(0), nullptr);
  EXPECT_NE(set.Find(-1), nullptr);
  EXPECT_NE(set.Find(-2), nullptr);
  EXPECT_NE(set.Find(-3), nullptr);
  EXPECT_EQ(set.Find(1), nullptr);
  EXPECT_EQ(set.Find(2), nullptr);
  EXPECT_EQ(set.Find(3), nullptr);
  EXPECT_EQ(set.Find(4), nullptr);
}

TEST(test_set, Merge) {
  s21::Set<int> set{1, 2, 3, 4};
  s21::Set<int> set2{3, 0, 2, -1, 1, -2};
  set.Merge(set2);
  EXPECT_EQ(7, set.Size());
  EXPECT_NE(set.Find(1), nullptr);
  EXPECT_NE(set.Find(2), nullptr);
  EXPECT_NE(set.Find(3), nullptr);
  EXPECT_NE(set.Find(4), nullptr);
  EXPECT_NE(set.Find(0), nullptr);
  EXPECT_NE(set.Find(-1), nullptr);
  EXPECT_NE(set.Find(-2), nullptr);
}

TEST(test_set, Find) {
  s21::Set<int> set{1, 2, 3, 4};
  EXPECT_NE(set.Find(1), nullptr);
  EXPECT_EQ(set.Find(-1), nullptr);
}

TEST(test_set, Contains) {
  s21::Set<int> set{1, 2, 3, 4};
  EXPECT_EQ(set.Contains(1), 1);
  EXPECT_EQ(set.Contains(5), 0);
}

TEST(test_set, InsertMany) {
  s21::Set<int> set{1, 7};
  set.Insert_many(2, 3, 4, 5, 6);
  EXPECT_EQ(7, set.Size());
  EXPECT_NE(set.Find(1), nullptr);
  EXPECT_NE(set.Find(2), nullptr);
  EXPECT_NE(set.Find(3), nullptr);
  EXPECT_NE(set.Find(4), nullptr);
  EXPECT_NE(set.Find(5), nullptr);
  EXPECT_NE(set.Find(6), nullptr);
  EXPECT_NE(set.Find(7), nullptr);
}

TEST(test_set_iterator, DefaultConstructor) {
  s21::BinaryTree<int, int>::Iterator iter;
  EXPECT_EQ(nullptr, iter.getPtr());
}

TEST(test_set_iterator, CopyConstructor) {
  s21::Set<int> set{1, 2, 3};
  s21::BinaryTree<int, int>::Iterator iter{set.Begin()};
  EXPECT_EQ(1, iter.getPtr()->value);
  s21::BinaryTree<int, int>::Iterator iterCopy(iter);
  EXPECT_EQ(1, iterCopy.getPtr()->value);
}

TEST(test_set_iterator, AccessOperator) {
  s21::Set<int> set{1, 2, 3};
  s21::BinaryTree<int, int>::Iterator iter{set.Begin()};
  EXPECT_EQ(1, *iter);
}

TEST(test_set_iterator, IncrementOperator) {
  s21::Set<int> set{1, 2, 3, -2, -1};
  s21::BinaryTree<int, int>::Iterator iter{set.Begin()};
  EXPECT_EQ(-1, *(++iter));
}

TEST(test_set_iterator, DecrementOperator) {
  s21::Set<int> set{1, 2, 3, -2, -1};
  s21::BinaryTree<int, int>::Iterator iter{set.End()};
  EXPECT_EQ(2, *(--iter));
}

TEST(test_set_iterator, EqualOperator) {
  s21::Set<int> set{1, 2, 3};
  s21::BinaryTree<int, int>::Iterator iter{set.Begin()};
  s21::BinaryTree<int, int>::Iterator iter2{set.End()};
  EXPECT_EQ(0, iter == iter2);
  s21::BinaryTree<int, int>::Iterator iter3{set.End()};
  EXPECT_EQ(1, iter2 == iter3);
}

TEST(test_set_iterator, NotEqualOperator) {
  s21::Set<int> set{1, 2, 3};
  s21::BinaryTree<int, int>::Iterator iter{set.Begin()};
  s21::BinaryTree<int, int>::Iterator iter2{set.End()};
  EXPECT_EQ(1, iter != iter2);
  s21::BinaryTree<int, int>::Iterator iter3{set.End()};
  EXPECT_EQ(0, iter2 != iter3);
}

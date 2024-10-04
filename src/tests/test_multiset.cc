#include "test_containers.h"

TEST(test_multiset, DefaultConstructor) {
  s21::Multiset<int> multiset;
  EXPECT_EQ(multiset.Size(), 0);
}

TEST(test_multiset, InitializerListConstructor) {
  s21::Multiset<int> multiset{1, 2, 0, 3, -1};
  EXPECT_EQ(multiset.Size(), 5);
  EXPECT_NE(multiset.Find(1), nullptr);
  EXPECT_NE(multiset.Find(2), nullptr);
  EXPECT_NE(multiset.Find(0), nullptr);
  EXPECT_NE(multiset.Find(3), nullptr);
  EXPECT_NE(multiset.Find(-1), nullptr);
  EXPECT_EQ(multiset.Find(-2), nullptr);
}

TEST(test_multiset, CopyConstructor) {
  s21::Multiset<int> copied{3, 2, 1};
  s21::Multiset<int> multiset(copied);
  EXPECT_EQ(multiset.Size(), 3);
  EXPECT_NE(multiset.Find(1), nullptr);
  EXPECT_NE(multiset.Find(2), nullptr);
  EXPECT_NE(multiset.Find(3), nullptr);
  EXPECT_EQ(multiset.Find(0), nullptr);
}

TEST(test_multiset, MoveConstructor) {
  s21::Multiset<int> moved{3, 2, 1};
  s21::Multiset<int> multiset(std::move(moved));
  EXPECT_EQ(multiset.Size(), 3);
  EXPECT_EQ(moved.Size(), 0);
  EXPECT_NE(multiset.Find(1), nullptr);
  EXPECT_NE(multiset.Find(2), nullptr);
  EXPECT_NE(multiset.Find(3), nullptr);
}

TEST(test_multiset, AssignOperator) {
  s21::Multiset<int> multiset{1, 2, 3, 4};
  s21::Multiset<int> multiset2 = multiset;
  EXPECT_EQ(multiset2.Size(), 4);
  EXPECT_NE(multiset2.Find(1), nullptr);
  EXPECT_NE(multiset2.Find(2), nullptr);
  EXPECT_NE(multiset2.Find(3), nullptr);
  EXPECT_NE(multiset2.Find(4), nullptr);
}

TEST(test_multiset, Begin) {
  s21::Multiset<int> multiset{-1, 2, 3, -2};
  EXPECT_EQ(multiset.Find(-2), multiset.Begin());
}

TEST(test_multiset, End) {
  s21::Multiset<int> multiset{-1, 2, 3, -2};
  EXPECT_EQ(multiset.Find(3), multiset.End());
}

TEST(test_multiset, Empty) {
  s21::Multiset<int> multiset{-1, 2, 3};
  EXPECT_EQ(0, multiset.Empty());
  s21::Multiset<int> setEmpty;
  EXPECT_EQ(1, setEmpty.Empty());
}

TEST(test_multiset, Size) {
  s21::Multiset<int> multiset{-1, 2, 3};
  EXPECT_EQ(3, multiset.Size());
}

TEST(test_multiset, Clear) {
  s21::Multiset<int> multiset{-1, 2, 3, 4};
  EXPECT_EQ(4, multiset.Size());
  multiset.Clear();
  EXPECT_EQ(0, multiset.Size());
  EXPECT_EQ(1, multiset.Empty());
}

TEST(test_multiset, Insert) {
  s21::Multiset<int> multiset{1, 2, 3, 4};
  multiset.Insert(-2);
  EXPECT_NE(multiset.Find(1), nullptr);
  EXPECT_NE(multiset.Find(2), nullptr);
  EXPECT_NE(multiset.Find(3), nullptr);
  EXPECT_NE(multiset.Find(4), nullptr);
  EXPECT_NE(multiset.Find(-2), nullptr);
  EXPECT_EQ(5, multiset.Size());

  multiset.Insert(-1);
  EXPECT_NE(multiset.Find(1), nullptr);
  EXPECT_NE(multiset.Find(2), nullptr);
  EXPECT_NE(multiset.Find(3), nullptr);
  EXPECT_NE(multiset.Find(4), nullptr);
  EXPECT_NE(multiset.Find(-2), nullptr);
  EXPECT_NE(multiset.Find(-1), nullptr);
  EXPECT_EQ(6, multiset.Size());

  multiset.Insert(5);
  EXPECT_NE(multiset.Find(1), nullptr);
  EXPECT_NE(multiset.Find(2), nullptr);
  EXPECT_NE(multiset.Find(3), nullptr);
  EXPECT_NE(multiset.Find(4), nullptr);
  EXPECT_NE(multiset.Find(-2), nullptr);
  EXPECT_NE(multiset.Find(-1), nullptr);
  EXPECT_NE(multiset.Find(5), nullptr);
  EXPECT_EQ(7, multiset.Size());
}

TEST(test_multiset, Erase) {
  s21::Multiset<int> multiset{-1, 2, 3, 4};
  multiset.Erase(multiset.Begin());
  EXPECT_EQ(multiset.Find(-1), nullptr);
  EXPECT_EQ(3, multiset.Size());

  multiset.Erase(multiset.End());
  EXPECT_EQ(multiset.Find(4), nullptr);
  EXPECT_EQ(2, multiset.Size());
}

TEST(test_multiset, Swap) {
  s21::Multiset<int> multiset{1, 2, 3, 4};
  s21::Multiset<int> multiset2{0, -1, -2, -3};
  multiset.Swap(multiset2);
  EXPECT_EQ(4, multiset.Size());
  EXPECT_EQ(4, multiset2.Size());
  EXPECT_NE(multiset2.Find(1), nullptr);
  EXPECT_NE(multiset2.Find(2), nullptr);
  EXPECT_NE(multiset2.Find(3), nullptr);
  EXPECT_NE(multiset2.Find(4), nullptr);
  EXPECT_EQ(multiset2.Find(0), nullptr);
  EXPECT_EQ(multiset2.Find(-1), nullptr);
  EXPECT_EQ(multiset2.Find(-2), nullptr);
  EXPECT_EQ(multiset2.Find(-3), nullptr);

  EXPECT_NE(multiset.Find(0), nullptr);
  EXPECT_NE(multiset.Find(-1), nullptr);
  EXPECT_NE(multiset.Find(-2), nullptr);
  EXPECT_NE(multiset.Find(-3), nullptr);
  EXPECT_EQ(multiset.Find(1), nullptr);
  EXPECT_EQ(multiset.Find(2), nullptr);
  EXPECT_EQ(multiset.Find(3), nullptr);
  EXPECT_EQ(multiset.Find(4), nullptr);
}

TEST(test_multiset, Merge) {
  s21::Multiset<int> multiset{1, 2, 3, 4};
  s21::Multiset<int> multiset2{3, 0, 2, -1, 1, -2};
  multiset.Merge(multiset2);
  EXPECT_EQ(7, multiset.Size());
  EXPECT_NE(multiset.Find(1), nullptr);
  EXPECT_NE(multiset.Find(2), nullptr);
  EXPECT_NE(multiset.Find(3), nullptr);
  EXPECT_NE(multiset.Find(4), nullptr);
  EXPECT_NE(multiset.Find(0), nullptr);
  EXPECT_NE(multiset.Find(-1), nullptr);
  EXPECT_NE(multiset.Find(-2), nullptr);
}

TEST(test_multiset, Count) {
  s21::Multiset<int> multiset{1, 2, 3, 4};
  multiset.Insert(2);
  EXPECT_EQ(2, multiset.Count(2));
  multiset.Insert(2);
  EXPECT_EQ(3, multiset.Count(2));
}

TEST(test_multiset, Find) {
  s21::Multiset<int> multiset{1, 2, 3, 4};
  EXPECT_NE(multiset.Find(1), nullptr);
  EXPECT_EQ(multiset.Find(-1), nullptr);
}

TEST(test_multiset, Contains) {
  s21::Multiset<int> multiset{1, 2, 3, 4};
  EXPECT_EQ(multiset.Contains(1), 1);
  EXPECT_EQ(multiset.Contains(5), 0);
}

TEST(test_multiset, EqualRange) {
  s21::Multiset<int> multiset{1, 2, 0, 3, -1};
  multiset.Insert(0);
  multiset.Insert(0);
  multiset.Insert(0);
  std::pair<s21::Multiset<int>::iterator, s21::Multiset<int>::iterator>
      iter_range = multiset.EqualRange(0);
  EXPECT_EQ(iter_range.first, multiset.Find(0));
  EXPECT_EQ(iter_range.second, multiset.Find(1));
}

TEST(test_multiset, LowerBound) {
  s21::Multiset<int> multiset{1, 2, 0, 3, -1};
  multiset.Insert(0);
  multiset.Insert(0);
  EXPECT_EQ(multiset.LowerBound(0), multiset.Find(0));
}

TEST(test_multiset, UpperBound) {
  s21::Multiset<int> multiset{1, 2, 0, 3, -1};
  multiset.Insert(0);
  EXPECT_EQ(multiset.UpperBound(0), multiset.Find(1));
}

TEST(test_multiset, InsertMany) {
  s21::Multiset<int> multiset{1, 7};
  multiset.Insert_many(2, 3, 4, 5, 6);
  EXPECT_EQ(7, multiset.Size());
  EXPECT_NE(multiset.Find(1), nullptr);
  EXPECT_NE(multiset.Find(2), nullptr);
  EXPECT_NE(multiset.Find(3), nullptr);
  EXPECT_NE(multiset.Find(4), nullptr);
  EXPECT_NE(multiset.Find(5), nullptr);
  EXPECT_NE(multiset.Find(6), nullptr);
  EXPECT_NE(multiset.Find(7), nullptr);
}

TEST(test_multiset_iterator, DefaultConstructor) {
  s21::BinaryTree<int, int>::Iterator iter;
  EXPECT_EQ(nullptr, iter.getPtr());
}

TEST(test_multiset_iterator, CopyConstructor) {
  s21::Multiset<int> multiset{1, 2, 3};
  s21::BinaryTree<int, int>::Iterator iter{multiset.Begin()};
  EXPECT_EQ(1, iter.getPtr()->value);
  s21::BinaryTree<int, int>::Iterator iterCopy(iter);
  EXPECT_EQ(1, iterCopy.getPtr()->value);
}

TEST(test_multiset_iterator, AccessOperator) {
  s21::Multiset<int> multiset{1, 2, 3};
  s21::BinaryTree<int, int>::Iterator iter{multiset.Begin()};
  EXPECT_EQ(1, *iter);
}

TEST(test_multiset_iterator, IncrementOperator) {
  s21::Multiset<int> multiset{1, 2, 0, 3, -1};
  multiset.Insert(0);
  s21::BinaryTree<int, int>::Iterator iter{multiset.Find(0)};
  EXPECT_EQ(1, *(++iter));
}

TEST(test_multiset_iterator, DecrementOperator) {
  s21::Multiset<int> multiset{1, 2, 3, -2, -1};
  s21::BinaryTree<int, int>::Iterator iter{multiset.End()};
  EXPECT_EQ(2, *(--iter));
}

TEST(test_multiset_iterator, EqualOperator) {
  s21::Multiset<int> multiset{1, 2, 3};
  s21::BinaryTree<int, int>::Iterator iter{multiset.Begin()};
  s21::BinaryTree<int, int>::Iterator iter2{multiset.End()};
  EXPECT_EQ(0, iter == iter2);
  s21::BinaryTree<int, int>::Iterator iter3{multiset.End()};
  EXPECT_EQ(1, iter2 == iter3);
}

TEST(test_multiset_iterator, NotEqualOperator) {
  s21::Multiset<int> multiset{1, 2, 3};
  s21::BinaryTree<int, int>::Iterator iter{multiset.Begin()};
  s21::BinaryTree<int, int>::Iterator iter2{multiset.End()};
  EXPECT_EQ(1, iter != iter2);
  s21::BinaryTree<int, int>::Iterator iter3{multiset.End()};
  EXPECT_EQ(0, iter2 != iter3);
}

#include "test_containers.h"

TEST(test_array, DefaultConstructor) {
  s21::Array<int, 2> arr;
  EXPECT_EQ(arr.Size(), 2);
}

TEST(test_array, InitializerListConstructor) {
  s21::Array<int, 5> arr{1, 2, 0, 3, -1};
  EXPECT_EQ(arr.Size(), 5);
  EXPECT_EQ(1, arr[0]);
  EXPECT_EQ(2, arr[1]);
  EXPECT_EQ(0, arr[2]);
  EXPECT_EQ(3, arr[3]);
  EXPECT_EQ(-1, arr[4]);
}

TEST(test_array, CopyConstructor) {
  s21::Array<int, 3> copied{3, 2, 1};
  s21::Array<int, 3> arr(copied);
  EXPECT_EQ(arr.Size(), 3);
  EXPECT_EQ(3, arr[0]);
  EXPECT_EQ(2, arr[1]);
  EXPECT_EQ(1, arr[2]);
}

TEST(test_array, MoveConstructor) {
  s21::Array<int, 3> moved{3, 2, 1};
  s21::Array<int, 3> arr(std::move(moved));
  EXPECT_EQ(arr.Size(), 3);
  EXPECT_EQ(3, arr[0]);
  EXPECT_EQ(2, arr[1]);
  EXPECT_EQ(1, arr[2]);
}

TEST(test_array, AssignOperator) {
  s21::Array<int, 4> arr{1, 2, 3, 4};
  s21::Array<int, 4> arr2 = arr;
  EXPECT_EQ(arr2.Size(), 4);
  EXPECT_EQ(1, arr2[0]);
  EXPECT_EQ(2, arr2[1]);
  EXPECT_EQ(3, arr2[2]);
  EXPECT_EQ(4, arr2[3]);
}

TEST(test_array, At) {
  s21::Array<int, 3> arr{1, 2, 3};
  EXPECT_EQ(1, arr.At(1LU));
  EXPECT_EQ(2, arr.At(2LU));
  EXPECT_EQ(3, arr.At(3LU));
  EXPECT_THROW(arr.At(4LU), std::out_of_range);
}

TEST(test_array, AccessOperator) {
  s21::Array<int, 3> arr{1, 2, 3};
  EXPECT_EQ(1, arr[0]);
  EXPECT_EQ(2, arr[1]);
  EXPECT_EQ(3, arr[2]);
}

TEST(test_array, Front) {
  s21::Array<int, 3> arr{-1, 2, 3};
  EXPECT_EQ(-1, arr.Front());
}

TEST(test_array, Back) {
  s21::Array<int, 3> arr{-1, 2, 3};
  EXPECT_EQ(3, arr.Back());
}

TEST(test_array, Data) {
  s21::Array<int, 3> arr{-1, 2, 3};
  int* iter = arr.Data();
  EXPECT_EQ(arr[0], *iter);
}

TEST(test_array, Begin) {
  s21::Array<int, 3> arr{-1, 2, 3};
  EXPECT_EQ(&arr[0], arr.Begin());
}

TEST(test_array, End) {
  s21::Array<int, 3> arr{-1, 2, 3};
  EXPECT_EQ(&arr[3], arr.End());
}

TEST(test_array, Empty) {
  s21::Array<int, 3> arr{-1, 2, 3};
  EXPECT_EQ(0, arr.Empty());
  s21::Array<int, 0> arrEmpty;
  EXPECT_EQ(1, arrEmpty.Empty());
}

TEST(test_array, Size) {
  s21::Array<int, 3> arr{-1, 2, 3};
  EXPECT_EQ(3, arr.Size());
}

TEST(test_array, MaxSize) {
  s21::Array<int, 4> arr{-1, 2, 3, 4};
  EXPECT_EQ(4, arr.MaxSize());
}

TEST(test_array, Swap) {
  s21::Array<int, 4> arr{1, 2, 3, 4};
  s21::Array<int, 4> arr2{0, -1, -2, -3};
  arr.Swap(arr2);
  EXPECT_EQ(4, arr.Size());
  EXPECT_EQ(4, arr2.Size());
  EXPECT_EQ(1, arr2[0]);
  EXPECT_EQ(2, arr2[1]);
  EXPECT_EQ(3, arr2[2]);
  EXPECT_EQ(4, arr2[3]);
  EXPECT_EQ(0, arr[0]);
  EXPECT_EQ(-1, arr[1]);
  EXPECT_EQ(-2, arr[2]);
  EXPECT_EQ(-3, arr[3]);
}

TEST(test_array, Fill) {
  s21::Array<int, 4> arr{1, 2, 3, 4};
  arr.Fill(1);
  EXPECT_EQ(1, arr[0]);
  EXPECT_EQ(1, arr[1]);
  EXPECT_EQ(1, arr[2]);
  EXPECT_EQ(1, arr[3]);
}

TEST(test_array_iterator, DefaultConstructor) {
  s21::Array<int, 3>::Iterator iter;
  EXPECT_EQ(nullptr, iter.getPtr());
}

TEST(test_array_iterator, CopyConstructor) {
  s21::Array<int, 3> arr{1, 2, 3};
  s21::Array<int, 3>::Iterator iter{arr.Data()};
  EXPECT_EQ(1, *(iter.getPtr()));
  s21::Array<int, 3>::Iterator iterCopy(iter);
  EXPECT_EQ(1, *(iterCopy.getPtr()));
}

TEST(test_array_iterator, AccessOperator) {
  s21::Array<int, 3> arr{1, 2, 3};
  s21::Array<int, 3>::Iterator iter{arr.Data()};
  EXPECT_EQ(arr[0], *iter);
}

TEST(test_array_iterator, IncrementOperator) {
  s21::Array<int, 3> arr{1, 2, 3};
  s21::Array<int, 3>::Iterator iter{arr.Data()};
  EXPECT_EQ(2, *(++iter));
}

TEST(test_array_iterator, DecrementOperator) {
  s21::Array<int, 3> arr{1, 2, 3};
  s21::Array<int, 3>::Iterator iter{arr.End()};
  EXPECT_EQ(3, *(--iter));
}

TEST(test_array_iterator, EqualOperator) {
  s21::Array<int, 3> arr{1, 2, 3};
  s21::Array<int, 3>::Iterator iter{arr.Begin()};
  s21::Array<int, 3>::Iterator iter2{arr.End()};
  EXPECT_EQ(0, iter == iter2);
  s21::Array<int, 3>::Iterator iter3{arr.End()};
  EXPECT_EQ(1, iter2 == iter3);
}

TEST(test_array_iterator, NotEqualOperator) {
  s21::Array<int, 3> arr{1, 2, 3};
  s21::Array<int, 3>::Iterator iter{arr.Begin()};
  s21::Array<int, 3>::Iterator iter2{arr.End()};
  EXPECT_EQ(1, iter != iter2);
  s21::Array<int, 3>::Iterator iter3{arr.End()};
  EXPECT_EQ(0, iter2 != iter3);
}

#include "test_containers.h"

TEST(test_vector, DefaultConstructor) {
  s21::Vector<int> vec;
  EXPECT_EQ(vec.Size(), 0);
  EXPECT_EQ(vec.Capacity(), 0);
}

TEST(test_vector, ConstructorWithSizeParameter) {
  s21::Vector<int> vec(4);
  EXPECT_EQ(vec.Size(), 0);
  EXPECT_EQ(vec.Capacity(), 4);
}

TEST(test_vector, InitializerListConstructor) {
  s21::Vector<int> vec{1, 2, 0, 3, -1};
  EXPECT_EQ(vec.Size(), 5);
  EXPECT_EQ(vec.Capacity(), 5);
  EXPECT_EQ(1, vec[0]);
  EXPECT_EQ(2, vec[1]);
  EXPECT_EQ(0, vec[2]);
  EXPECT_EQ(3, vec[3]);
  EXPECT_EQ(-1, vec[4]);
}

TEST(test_vector, CopyConstructor) {
  s21::Vector<int> copied{3, 2, 1};
  s21::Vector<int> vec(copied);
  EXPECT_EQ(vec.Size(), 3);
  EXPECT_EQ(vec.Capacity(), 3);
  EXPECT_EQ(3, vec[0]);
  EXPECT_EQ(2, vec[1]);
  EXPECT_EQ(1, vec[2]);
}

TEST(test_vector, MoveConstructor) {
  s21::Vector<int> moved{3, 2, 1};
  s21::Vector<int> vec(std::move(moved));
  moved.SetArrNullptr();
  EXPECT_EQ(vec.Size(), 3);
  EXPECT_EQ(vec.Capacity(), 3);
  EXPECT_EQ(3, vec[0]);
  EXPECT_EQ(2, vec[1]);
  EXPECT_EQ(1, vec[2]);
  EXPECT_EQ(moved.Size(), 0);
  EXPECT_EQ(moved.Capacity(), 0);
}

TEST(test_vector, AssignOperator) {
  s21::Vector<int> vec{1, 2, 3, 4};
  s21::Vector<int> vec2 = vec;
  EXPECT_EQ(vec2.Size(), 4);
  EXPECT_EQ(vec2.Capacity(), 4);
  EXPECT_EQ(1, vec2[0]);
  EXPECT_EQ(2, vec2[1]);
  EXPECT_EQ(3, vec2[2]);
  EXPECT_EQ(4, vec2[3]);
}

TEST(test_vector, At) {
  s21::Vector<int> vec{1, 2, 3};
  EXPECT_EQ(1, vec.At(1LU));
  EXPECT_EQ(2, vec.At(2LU));
  EXPECT_EQ(3, vec.At(3LU));
  EXPECT_THROW(vec.At(4LU), std::out_of_range);
}

TEST(test_vector, AccessOperator) {
  s21::Vector<int> vec{1, 2, 3};
  EXPECT_EQ(1, vec[0]);
  EXPECT_EQ(2, vec[1]);
  EXPECT_EQ(3, vec[2]);
}

TEST(test_vector, Front) {
  s21::Vector<int> vec{-1, 2, 3};
  EXPECT_EQ(-1, vec.Front());
}

TEST(test_vector, Back) {
  s21::Vector<int> vec{-1, 2, 3};
  EXPECT_EQ(3, vec.Back());
}

TEST(test_vector, Data) {
  s21::Vector<int> vec{-1, 2, 3};
  int* iter = vec.Data();
  EXPECT_EQ(vec[0], *iter);
}

TEST(test_vector, Begin) {
  s21::Vector<int> vec{-1, 2, 3};
  EXPECT_EQ(&vec[0], vec.Begin());
}

TEST(test_vector, End) {
  s21::Vector<int> vec{-1, 2, 3};
  EXPECT_EQ(&vec[3], vec.End());
}

TEST(test_vector, Empty) {
  s21::Vector<int> vec{-1, 2, 3};
  EXPECT_EQ(0, vec.Empty());
  s21::Vector<int> vecEmpty;
  EXPECT_EQ(1, vecEmpty.Empty());
}

TEST(test_vector, Size) {
  s21::Vector<int> vec{-1, 2, 3};
  EXPECT_EQ(3, vec.Size());
}

TEST(test_vector, Reserve) {
  s21::Vector<int> vec{-1, 2, 3, 4};
  vec.Reserve(6);
  EXPECT_EQ(6, vec.Capacity());
  EXPECT_EQ(4, vec.Size());
  EXPECT_EQ(-1, vec[0]);
  EXPECT_EQ(2, vec[1]);
  EXPECT_EQ(3, vec[2]);
  EXPECT_EQ(4, vec[3]);
  EXPECT_EQ(0, vec[4]);
}

TEST(test_vector, Capacity) {
  s21::Vector<int> vec{-1, 2, 3};
  EXPECT_EQ(3, vec.Capacity());
  s21::Vector<int> vec2;
  EXPECT_EQ(0, vec2.Capacity());
  s21::Vector<int> vec3(7);
  EXPECT_EQ(7, vec3.Capacity());
}

TEST(test_vector, ShrinkToFit) {
  s21::Vector<int> vec{-1, 2, 3, 4};
  vec.Reserve(6);
  EXPECT_EQ(6, vec.Capacity());
  EXPECT_EQ(4, vec.Size());
  vec.ShrinkToFit();
  EXPECT_EQ(4, vec.Capacity());
  EXPECT_EQ(4, vec.Size());
}

TEST(test_vector, Clear) {
  s21::Vector<int> vec{-1, 2, 3, 4};
  EXPECT_EQ(4, vec.Size());
  EXPECT_EQ(4, vec.Capacity());
  vec.Clear();
  EXPECT_EQ(0, vec.Size());
  EXPECT_EQ(4, vec.Capacity());
}

TEST(test_vector, Insert) {
  s21::Vector<int> vec{1, 2, 3, 4};
  vec.Insert(vec.Begin(), -2);
  EXPECT_EQ(-2, vec[0]);
  EXPECT_EQ(1, vec[1]);
  EXPECT_EQ(2, vec[2]);
  EXPECT_EQ(3, vec[3]);
  EXPECT_EQ(4, vec[4]);
  EXPECT_EQ(5, vec.Size());
  EXPECT_EQ(8, vec.Capacity());

  vec.Insert(vec.Begin() + 1, -1);
  EXPECT_EQ(-2, vec[0]);
  EXPECT_EQ(-1, vec[1]);
  EXPECT_EQ(1, vec[2]);
  EXPECT_EQ(2, vec[3]);
  EXPECT_EQ(3, vec[4]);
  EXPECT_EQ(4, vec[5]);
  EXPECT_EQ(6, vec.Size());
  EXPECT_EQ(8, vec.Capacity());

  vec.Insert(vec.Begin() + 2, 0);
  EXPECT_EQ(-2, vec[0]);
  EXPECT_EQ(-1, vec[1]);
  EXPECT_EQ(0, vec[2]);
  EXPECT_EQ(1, vec[3]);
  EXPECT_EQ(2, vec[4]);
  EXPECT_EQ(3, vec[5]);
  EXPECT_EQ(4, vec[6]);
  EXPECT_EQ(7, vec.Size());
  EXPECT_EQ(8, vec.Capacity());

  EXPECT_THROW(vec.Insert(vec.Begin() + 10, -3), std::out_of_range);
}

TEST(test_vector, Erase) {
  s21::Vector<int> vec{-1, 2, 3, 4};
  EXPECT_THROW(vec.Erase(vec.Begin() + 10), std::out_of_range);
  vec.Erase(vec.Begin());
  EXPECT_EQ(2, vec[0]);
  EXPECT_EQ(3, vec[1]);
  EXPECT_EQ(4, vec[2]);
  EXPECT_EQ(3, vec.Size());
  EXPECT_EQ(4, vec.Capacity());

  vec.Erase(vec.Begin() + 1);
  EXPECT_EQ(2, vec[0]);
  EXPECT_EQ(4, vec[1]);
  EXPECT_EQ(2, vec.Size());
  EXPECT_EQ(4, vec.Capacity());
}

TEST(test_vector, PushBack) {
  s21::Vector<int> vec{-1, 2, 3, 4};
  vec.PushBack(5);
  EXPECT_EQ(-1, vec[0]);
  EXPECT_EQ(2, vec[1]);
  EXPECT_EQ(3, vec[2]);
  EXPECT_EQ(4, vec[3]);
  EXPECT_EQ(5, vec[4]);
  EXPECT_EQ(5, vec.Size());
  EXPECT_EQ(8, vec.Capacity());
}

TEST(test_vector, PopBack) {
  s21::Vector<int> vec{-1, 2, 3, 4};
  vec.PopBack();
  EXPECT_EQ(-1, vec[0]);
  EXPECT_EQ(2, vec[1]);
  EXPECT_EQ(3, vec[2]);
  EXPECT_EQ(3, vec.Size());
  EXPECT_EQ(4, vec.Capacity());
}

TEST(test_vector, Swap) {
  s21::Vector<int> vec{1, 2, 3, 4};
  s21::Vector<int> vec2{0, -1, -2, -3};
  vec.Swap(vec2);
  EXPECT_EQ(4, vec.Size());
  EXPECT_EQ(4, vec.Capacity());
  EXPECT_EQ(4, vec2.Size());
  EXPECT_EQ(4, vec2.Capacity());
  EXPECT_EQ(1, vec2[0]);
  EXPECT_EQ(2, vec2[1]);
  EXPECT_EQ(3, vec2[2]);
  EXPECT_EQ(4, vec2[3]);
  EXPECT_EQ(0, vec[0]);
  EXPECT_EQ(-1, vec[1]);
  EXPECT_EQ(-2, vec[2]);
  EXPECT_EQ(-3, vec[3]);
}

TEST(test_vector, InsertMany) {
  s21::Vector<int> vec{1, 7};
  s21::Vector<int>::iterator pos = vec.Begin() + 1;
  vec.Insert_many(pos, 2, 3, 4, 5, 6);
  EXPECT_EQ(7, vec.Size());
  EXPECT_EQ(8, vec.Capacity());
  EXPECT_EQ(1, vec[0]);
  EXPECT_EQ(2, vec[1]);
  EXPECT_EQ(3, vec[2]);
  EXPECT_EQ(4, vec[3]);
  EXPECT_EQ(5, vec[4]);
  EXPECT_EQ(6, vec[5]);
  EXPECT_EQ(7, vec[6]);
  EXPECT_EQ(0, vec[7]);
}

TEST(test_vector, InsertManyBack) {
  s21::Vector<int> vec{1, 2, 3, 4};
  vec.Insert_many_back(2, 1, 4);
  EXPECT_EQ(7, vec.Size());
  EXPECT_EQ(8, vec.Capacity());
  EXPECT_EQ(1, vec[0]);
  EXPECT_EQ(2, vec[1]);
  EXPECT_EQ(3, vec[2]);
  EXPECT_EQ(4, vec[3]);
  EXPECT_EQ(2, vec[4]);
  EXPECT_EQ(1, vec[5]);
  EXPECT_EQ(4, vec[6]);
  EXPECT_EQ(0, vec[7]);
}

TEST(test_vector_iterator, DefaultConstructor) {
  s21::Vector<int>::Iterator iter;
  EXPECT_EQ(nullptr, iter.getPtr());
}

TEST(test_vector_iterator, CopyConstructor) {
  s21::Vector<int> vec{1, 2, 3};
  s21::Vector<int>::Iterator iter{vec.Data()};
  EXPECT_EQ(1, *(iter.getPtr()));
  s21::Vector<int>::Iterator iterCopy(iter);
  EXPECT_EQ(1, *(iterCopy.getPtr()));
}

TEST(test_vector_iterator, AccessOperator) {
  s21::Vector<int> vec{1, 2, 3};
  s21::Vector<int>::Iterator iter{vec.Data()};
  EXPECT_EQ(vec[0], *iter);
}

TEST(test_vector_iterator, IncrementOperator) {
  s21::Vector<int> vec{1, 2, 3};
  s21::Vector<int>::Iterator iter{vec.Data()};
  EXPECT_EQ(2, *(++iter));
}

TEST(test_vector_iterator, DecrementOperator) {
  s21::Vector<int> vec{1, 2, 3};
  s21::Vector<int>::Iterator iter{vec.End()};
  EXPECT_EQ(3, *(--iter));
}

TEST(test_vector_iterator, EqualOperator) {
  s21::Vector<int> vec{1, 2, 3};
  s21::Vector<int>::Iterator iter{vec.Begin()};
  s21::Vector<int>::Iterator iter2{vec.End()};
  EXPECT_EQ(0, iter == iter2);
  s21::Vector<int>::Iterator iter3{vec.End()};
  EXPECT_EQ(1, iter2 == iter3);
}

TEST(test_vector_iterator, NotEqualOperator) {
  s21::Vector<int> vec{1, 2, 3};
  s21::Vector<int>::Iterator iter{vec.Begin()};
  s21::Vector<int>::Iterator iter2{vec.End()};
  EXPECT_EQ(1, iter != iter2);
  s21::Vector<int>::Iterator iter3{vec.End()};
  EXPECT_EQ(0, iter2 != iter3);
}

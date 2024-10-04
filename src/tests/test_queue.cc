#include "test_containers.h"

TEST(test_queue, DefaultConstructor) {
  s21::Queue<int> q;
  EXPECT_EQ(q.Size(), 0);
}

TEST(test_queue, InitializerListConstructor) {
  s21::Queue<int> q{1, 2, 3, 4, 5};
  EXPECT_EQ(q.Size(), 5);
  EXPECT_EQ(q.Front(), 1);
  EXPECT_EQ(q.Back(), 5);
}

TEST(test_queue, CopyConstructor) {
  s21::Queue<int> q{1, 2, 3, 4, 5};
  s21::Queue<int> q2(q);
  EXPECT_EQ(q.Size(), q2.Size());
  EXPECT_EQ(q.Front(), q2.Front());
  EXPECT_EQ(q.Back(), q2.Back());
}

TEST(test_queue, MoveConstructor) {
  s21::Queue<int> q{1, 2, 3, 4, 5};
  s21::Queue<int> q2(std::move(q));
  EXPECT_EQ(q2.Size(), 5);
  EXPECT_EQ(q2.Front(), 1);
  EXPECT_EQ(q2.Back(), 5);
  EXPECT_EQ(q.Size(), 0);
}

TEST(test_queue, AssignOperator) {
  s21::Queue<int> q{1, 2, 3, 4, 5};
  s21::Queue<int> q2 = std::move(q);
  EXPECT_EQ(q2.Size(), 5);
  EXPECT_EQ(q2.Front(), 1);
  EXPECT_EQ(q2.Back(), 5);
  EXPECT_EQ(q.Size(), 0);
}

TEST(test_queue, Front) {
  s21::Queue<int> q{1, 2, 3, 4, 5};
  s21::Queue<int> q2;

  EXPECT_EQ(q.Front(), 1);
  EXPECT_THROW(q2.Front(), std::out_of_range);
}

TEST(test_queue, Back) {
  s21::Queue<int> q{1, 2, 3, 4, 5};
  s21::Queue<int> q2;

  EXPECT_EQ(q.Back(), 5);
  EXPECT_THROW(q2.Back(), std::out_of_range);
}

TEST(test_queue, Empty) {
  s21::Queue<int> q{1, 2, 3, 4, 5};
  s21::Queue<int> q2;

  EXPECT_FALSE(q.Empty());
  EXPECT_TRUE(q2.Empty());
}

TEST(test_queue, Size) {
  s21::Queue<int> q{1, 2, 3, 4, 5};
  s21::Queue<int> q2;

  EXPECT_EQ(q.Size(), 5);
  EXPECT_EQ(q2.Size(), 0);
}

TEST(test_queue, Push) {
  s21::Queue<int> q{1, 2, 3, 4, 5};
  EXPECT_EQ(q.Size(), 5);
  EXPECT_EQ(q.Back(), 5);

  q.Push(6);
  EXPECT_EQ(q.Size(), 6);
  EXPECT_EQ(q.Back(), 6);

  q.Push(7);
  q.Push(8);
  q.Push(9);
  q.Push(10);
  q.Push(11);
  q.Push(13);
  q.Push(13);
  q.Push(14);
  q.Push(15);
  q.Push(16);
  EXPECT_EQ(q.Size(), 16);
  EXPECT_EQ(q.Back(), 16);
}

TEST(test_queue, Pop) {
  s21::Queue<int> q{1, 2, 3, 4, 5};
  EXPECT_EQ(q.Front(), 1);

  q.Pop();
  EXPECT_EQ(q.Size(), 4);
  EXPECT_EQ(q.Front(), 2);

  s21::Queue<int> q2;
  EXPECT_THROW(q2.Pop(), std::logic_error);
}

TEST(test_queue, Swap) {
  s21::Queue<int> q{1, 2, 3, 4, 5};
  s21::Queue<int> q2{9, 8, 7};
  EXPECT_EQ(q.Front(), 1);
  EXPECT_EQ(q2.Front(), 9);
  EXPECT_EQ(q.Back(), 5);
  EXPECT_EQ(q2.Back(), 7);

  q.Swap(q2);
  EXPECT_EQ(q.Front(), 9);
  EXPECT_EQ(q2.Front(), 1);
  EXPECT_EQ(q.Back(), 7);
  EXPECT_EQ(q2.Back(), 5);
}

TEST(test_queue, InsertManyBack) {
  s21::Queue<int> q{1, 2};
  q.InsertManyBack(3, 4, 5, 6);
  EXPECT_EQ(q.Size(), 6);
  EXPECT_EQ(q.Front(), 1);
  EXPECT_EQ(q.Back(), 6);
}

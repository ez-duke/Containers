#ifndef S21_ARRAY
#define S21_ARRAY

#include <initializer_list>
#include <iostream>
#include <utility>

namespace s21 {

template <class T, size_t N>
class Array {
 private:
  size_t size = N;
  T arr[N] = {};

 public:
  // Member types
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = T*;
  using const_iterator = const T*;
  using size_type = size_t;

  // Member functions
  Array() {}

  explicit Array(std::initializer_list<value_type> const& items) {
    std::copy(items.begin(), items.end(), this->arr);
  }

  Array(const Array& a) { std::copy(a.arr, a.arr + N, this->arr); }

  Array(Array&& a) {
    this->size = a.size;
    std::move(a.arr, a.arr + N, this->arr);
    a.size = 0;
  }

  ~Array() {}

  Array& operator=(Array&& a) {
    std::copy(a.arr, a.arr + N, this->arr);
    return *this;
  }

  // Element access
  reference At(size_type pos) {
    if (pos - 1 < this->size)
      return this->arr[pos - 1];
    else
      throw(std::out_of_range("Incorrect input, index is out of range\n"));
  }

  reference operator[](size_type pos) { return this->arr[pos]; }

  const_reference Front() { return this->arr[0]; }

  const_reference Back() { return this->arr[this->size - 1]; }

  iterator Data() { return this->arr; }

  // Iterators

  iterator Begin() { return this->arr; }
  iterator End() { return this->arr + size; }

  // Capacity
  bool Empty() { return Size() == 0; }

  size_type Size() { return this->size; }

  size_type MaxSize() { return this->size; }

  // Modifiers
  void Swap(Array& other) {
    std::swap(this->size, other.size);
    std::swap(this->arr, other.arr);
  }

  void Fill(const_reference value) {
    std::fill(this->arr, this->arr + N, value);
  }

  // Iterators
  class Iterator {
   private:
    iterator ptr;

   public:
    iterator getPtr() { return this->ptr; }

    Iterator() { this->ptr = nullptr; }

    explicit Iterator(iterator _ptr) { this->ptr = _ptr; }

    reference operator*() { return *(this->ptr); }

    Iterator& operator++() {
      ++this->ptr;
      return *this;
    }

    Iterator& operator--() {
      --this->ptr;
      return *this;
    }

    bool operator==(const Iterator other) { return other.ptr == this->ptr; }

    bool operator!=(const Iterator other) { return other.ptr != this->ptr; }
  };
};

}  // namespace s21

#endif

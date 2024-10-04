#ifndef S21_VECTOR
#define S21_VECTOR

#include <initializer_list>
#include <iostream>
#include <utility>

namespace s21 {

template <class T>
class Vector {
 private:
  size_t size;
  size_t capacity;
  T* arr;

 public:
  // Member types
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = T*;
  using const_iterator = const T*;
  using size_type = size_t;

  // Member functions
  Vector() {
    this->size = 0;
    this->capacity = 0;
    this->arr = nullptr;
  }

  explicit Vector(size_type n) {
    this->size = 0;
    this->capacity = n;
    this->arr = new value_type[n + 1]();
  }

  explicit Vector(std::initializer_list<value_type> const& items) {
    this->size = items.size();
    this->capacity = items.size();
    this->arr = new value_type[items.size() + 1];
    std::copy(items.begin(), items.end(), this->arr);
  }

  Vector(const Vector& v) {
    this->size = v.size;
    this->capacity = v.capacity;
    this->arr = new value_type[v.capacity + 1]();
    std::copy(v.arr, v.arr + v.size, this->arr);
  }

  Vector(Vector&& v) {
    this->size = v.size;
    this->capacity = v.capacity;
    std::swap(this->arr, v.arr);
    v.size = 0;
    v.capacity = 0;
  }

  ~Vector() {
    if (this->arr != nullptr) delete[] this->arr;
  }

  Vector& operator=(Vector&& v) {
    if (this != &v) {
      this->Swap(v);
    }
    return *this;
  }

  // Element access
  reference At(size_type pos) {
    if (pos > this->size)
      throw(std::out_of_range("Incorrect input, index is out of range\n"));
    return this->arr[pos - 1];
  }

  reference operator[](size_type pos) { return this->arr[pos]; }

  const_reference Front() { return this->arr[0]; }

  const_reference Back() { return this->arr[this->size - 1]; }

  value_type* Data() { return this->arr; }

  // Iterators

  iterator Begin() { return this->arr; }

  iterator End() { return this->arr + size; }

  // Capacity
  bool Empty() { return Size() == 0; }

  size_type Size() { return this->size; }

  size_type MaxSize() {
    return std::numeric_limits<size_type>::max() / sizeof(value_type);
  }

  void Reserve(size_type new_capacity) {
    if (new_capacity > this->capacity) {
      this->capacity = new_capacity;
      value_type* new_arr = new value_type[new_capacity + 1]();
      std::copy(this->Begin(), this->End(), new_arr);
      delete[] this->arr;
      this->arr = new_arr;
      new_arr = nullptr;
    }
  }

  size_type Capacity() { return this->capacity; }

  void ShrinkToFit() {
    if (this->size < this->capacity) {
      this->capacity = this->size;
      value_type* new_arr = new value_type[this->capacity + 1]();
      std::copy(this->Begin(), this->End(), new_arr);
      delete[] this->arr;
      this->arr = new_arr;
      new_arr = nullptr;
    }
  }

  // Modifiers
  void Clear() { this->size = 0; }

  iterator Insert(const_iterator pos, const_reference value) {
    size_type newPos = pos - this->Begin();

    if (newPos > this->size)
      throw(std::out_of_range("Incorrect input, index is out of range\n"));

    if (this->size == this->capacity) {
      this->Reserve(this->capacity ? this->capacity * 2 : 1);
    }

    for (size_type i = this->size; i > newPos; --i) {
      this->arr[i] = this->arr[i - 1];
    }

    this->arr[newPos] = value;
    this->size += 1;
    return newPos + this->Begin();
  }

  void Erase(const_iterator pos) {
    if (pos > this->End())
      throw(std::out_of_range("Incorrect input, index is out of range\n"));
    for (size_type i = pos - this->Begin(); i < this->size - 1; ++i) {
      this->arr[i] = this->arr[i + 1];
    }
    this->size -= 1;
  }

  void PushBack(const_reference value) { this->Insert(this->End(), value); }

  void PopBack() { this->Erase(this->End()); }

  void Swap(Vector& other) {
    std::swap(this->size, other.size);
    std::swap(this->capacity, other.capacity);
    std::swap(this->arr, other.arr);
  }

  // Insert many
  template <class... Args>
  iterator Insert_many(iterator pos, Args&&... args) {
    Vector<value_type> parser{args...};
    for (size_type i = 0; i < parser.Size(); ++i) {
      pos = this->Insert(pos, parser[i]);
      ++pos;
    }
    return pos;
  }

  template <class... Args>
  void Insert_many_back(Args&&... args) {
    this->Insert_many(this->End(), args...);
  }

  void SetArrNullptr() { this->arr = nullptr; }

  // Iterators
  class Iterator {
   private:
    iterator ptr;

   public:
    Iterator() { this->ptr = nullptr; }

    explicit Iterator(iterator _ptr) { this->ptr = _ptr; }

    iterator getPtr() { return this->ptr; }

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

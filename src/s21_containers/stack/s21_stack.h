#include "stack_interface.h"

template <class T>
s21::Stack<T>::Stack() {
  m_size = 0;
  m_capacity = 0;
  arr = nullptr;
}

template <class T>
s21::Stack<T>::Stack(std::initializer_list<value_type> const& items) {
  m_size = items.size();
  m_capacity = items.size() + 10;
  arr = new T[m_capacity];
  if (arr == nullptr) throw std::out_of_range("Memory allocation error.");
  std::copy(items.begin(), items.end(), arr);
}

template <class T>
s21::Stack<T>::Stack(const Stack& other) {
  this->m_size = other.m_size;
  this->m_capacity = other.m_capacity;
  this->arr = new T[other.m_capacity];
  if (arr == nullptr) throw std::out_of_range("Memory allocation error.");
  std::copy(other.arr, other.arr + other.m_size, arr);
}

template <class T>
s21::Stack<T>::Stack(Stack&& other) {
  this->m_size = other.m_size;
  this->m_capacity = other.m_capacity;
  this->arr = new T[other.m_capacity];
  if (arr == nullptr) throw std::out_of_range("Memory allocation error.");
  std::copy(other.arr, other.arr + other.m_size, arr);

  delete[] other.arr;
  other.arr = nullptr;
  other.m_size = 0;
  other.m_capacity = 0;
}

template <class T>
s21::Stack<T>::~Stack() {
  if (arr != nullptr) {
    delete[] arr;
  }
  arr = nullptr;
  m_size = 0;
  m_capacity = 0;
}

template <class T>
s21::Stack<T> s21::Stack<T>::operator=(Stack<T>&& other) {
  if (this != &other) {
    delete[] this->arr;
    this->m_size = other.m_size;
    this->m_capacity = other.m_capacity;
    this->arr = other.arr;

    delete[] other.arr;
    other.arr = nullptr;
    other.m_size = 0;
    other.m_capacity = 0;
  }
  return *this;
}

template <class T>
typename s21::Stack<T>::const_reference s21::Stack<T>::top() const {
  if (m_size > 0) {
    return arr[m_size - 1];
  } else {
    throw std::out_of_range("Top element returning error. Stack is empty.");
  }
}

template <class T>
bool s21::Stack<T>::empty() const {
  bool isEmpty = 0;
  if (m_size == 0) isEmpty = 1;
  return isEmpty;
}

template <class T>
typename s21::Stack<T>::size_type s21::Stack<T>::size() const {
  return m_size;
}

template <class T>
void s21::Stack<T>::push(typename Stack<T>::const_reference value) {
  if (m_size == m_capacity) {
    T* arrBuff = new T[m_capacity + 10];
    std::copy(arr, arr + m_size, arrBuff);
    delete[] arr;
    arr = arrBuff;
    m_capacity += 10;
  }
  m_size++;
  arr[m_size - 1] = value;
}

template <class T>
void s21::Stack<T>::pop() {
  if (this->empty())
    throw std::out_of_range("Top element popping error. Stack is empty.");
  if (m_size > 0) {
    m_size--;
    T* arrBuff = new T[m_capacity];
    for (size_type i = 0; i < m_size; ++i) {
      arrBuff[i] = arr[i];
    }
    delete[] arr;
    arr = arrBuff;
  }
}

template <class T>
void s21::Stack<T>::swap(Stack& other) {
  if (!this->empty() && !other.empty()) {
    T* arrBuff = new T[this->m_capacity];
    std::copy(this->arr, this->arr + this->m_size, arrBuff);
    size_t m_sizeBuff = this->m_size;
    size_t m_capacityBuff = this->m_capacity;
    delete[] this->arr;

    this->m_size = other.m_size;
    this->m_capacity = other.m_capacity;
    this->arr = other.arr;

    other.m_size = m_sizeBuff;
    other.m_capacity = m_capacityBuff;
    other.arr = arrBuff;
  } else {
    throw std::out_of_range(
        "Swapping error. First or second or both stacks are empty.");
  }
}

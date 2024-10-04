#ifndef S21_LIST_H
#define S21_LIST_H

#include <initializer_list>
#include <iostream>
#include <limits>
#include <utility>

#include "../vector/s21_vector.h"

namespace s21 {

template <typename T>
class List {
 public:
  struct Node {
    using value_type = T;
    using reference = T&;

    explicit Node(value_type data, Node* pNext = nullptr,
                  Node* pPrev = nullptr) {
      this->data = data;
      this->pNext = pNext;
      this->pPrev = pPrev;
    }

    Node* pNext;
    Node* pPrev;
    value_type data;

    bool operator==(const Node& other) const {
      return this->data == other.data;
    }
    bool operator!=(const Node& other) const { return data != other.data; }
  };

  class ListIterator {
   public:
    using value_type = T;
    using reference = T&;
    ListIterator& operator++() {
      auto temp = head;
      head = head->pNext;
      if (head) head->pPrev = temp;
      return *this;
    }
    ListIterator operator++(int) {
      ListIterator temp(*this);
      ++(*this);
      return temp;
    }

    ListIterator& operator--() {
      auto temp = head;
      head = head->pPrev;
      if (head) head->pNext = temp;
      return *this;
    }
    ListIterator operator--(int) {
      ListIterator temp(*this);
      --(*this);
      return temp;
    }
    ListIterator operator-(const size_t value) {
      Node* tmp = head;
      for (size_type i = 0; i < value; i++) {
        tmp = tmp->pPrev;
      }
      ListIterator res(tmp);
      return res;
    }

    bool operator<(const ListIterator& other) const {
      Node* current = head;
      Node* otherCurrent = other.head;
      bool flag = true;
      while (current != nullptr && otherCurrent != nullptr) {
        if (current->pNext == nullptr && otherCurrent->pNext != nullptr) {
          flag = true;
        }
        if (current->pNext != nullptr && otherCurrent->pNext == nullptr) {
          flag = false;
        }
        if (current->pNext != nullptr && otherCurrent->pNext != nullptr) {
          if (current->data < otherCurrent->data) {
            flag = true;
          }
          if (otherCurrent->data < current->data) {
            flag = false;
          }
          current = current->pNext;
          otherCurrent = otherCurrent->pNext;
        }
      }

      // Если один из итераторов достиг конца списка, тот, который дойдет до
      // конца раньше, считается меньше
      return flag;
    }

    bool operator==(const ListIterator& other) const {
      return head == other.head;
    }
    bool operator!=(const ListIterator& other) const {
      return !(*this == other);
    }

    explicit ListIterator(Node* node) : head(node) {}
    reference operator*() { return this->head->data; }

    Node* getHead() const { return head; }

   private:
    Node* head;
  };

  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = ListIterator;
  using const_iterator = const ListIterator;
  using size_type = size_t;

  List();
  explicit List(size_type n);
  explicit List(std::initializer_list<value_type> const& items);
  List(const List& l);
  List(List&& l);
  ~List();
  List<T>& operator=(List&& l);

  T& operator[](const int index);
  // доступ к элементу
  const_reference front();
  const_reference back();

  iterator begin();
  iterator end();

  // Список вместимости
  bool empty();
  size_type size() { return sizeList; };
  size_type max_size() {
    return std::numeric_limits<size_type>::max() / sizeof(value_type);
  }

  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(T data);
  void push_front(T data);
  void clear();
  void pop_back();
  void pop_front();
  void swap(List& other);
  void merge(List& other);
  void splice(iterator pos, List& other);
  void reverse();
  void unique();
  void sort();

  template <class... Args>
  iterator insert_many(const_iterator pos, Args&&... args) {
    List<value_type> parser{args...};
    iterator it = pos;
    if (it.getHead()->pPrev) --it;

    this->splice(it, parser);

    return it;
  }

  template <class... Args>
  void insert_many_back(Args&&... args) {
    List<value_type> parser{args...};
    iterator it = this->begin();
    while (it.getHead()->pNext != nullptr) ++it;

    this->splice(it, parser);
  }

  template <class... Args>
  void insert_many_front(Args&&... args) {
    s21::Vector<value_type> parser{args...};
    for (size_type i = 0; i < parser.Size(); ++i) {
      this->push_front(parser[parser.Size() - i - 1]);
    }
  }

  int sizeList;
  Node* head;
  Node* tail;

 private:
  // функции помощи
  void swapNodes(Node* a, Node* b);
};

}  // namespace s21

#endif

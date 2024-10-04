#ifndef STACK_INTERFACE_H
#define STACK_INTERFACE_H

#include <initializer_list>

namespace s21 {
template <class T>
class Stack {
 private:
  size_t m_size;
  size_t m_capacity;
  T *arr;

 public:
  // Stack Member type
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  // Stack Member functions - методы для взаимодействия с классом
  Stack();  // default constructor, creates empty stack
  explicit Stack(std::initializer_list<value_type> const
                     &items);  // initializer list constructor, creates stack
                               // initizialized using std::initializer_list
  Stack(const Stack &other);   // copy constructor
  Stack(Stack &&other);        // move constructor
  ~Stack();                    // destructor
  Stack operator=(
      Stack &&other);  // assignment operator overload for moving object

  // Stack Element access - методы для доступа к элементам класса
  const_reference top() const;  // accesses the top element

  // Stack Capacity - методы для доступа к информации о наполнении контейнера
  bool empty() const;      // checks whether the container is empty
  size_type size() const;  // returns the number of elements

  // Stack Modifiers - методы для изменения контейнера
  void push(const_reference value);  // inserts element at the top
  void pop();                        // removes the top element
  void swap(Stack &other);           // swaps the contents

  // Part 3 - appends new elements to the end of the container
  template <class... Args>
  void insert_many_back(
      Args &&...args) {  // Args&&... - это упаковка (pack) аргументов
    ((push(std::forward<Args>(args))),
     ...);  // fold expression (расширение пакета)
  }  // args становится упаковкой {/1 элемент/, /2 элемент/, /13 элемент/, ...}
     // и соответствующее количество раз вызывает push
};
}  // namespace s21

#endif

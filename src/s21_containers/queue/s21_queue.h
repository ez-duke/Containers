#ifndef S21_QUEUE
#define S21_QUEUE

#include "../vector/s21_vector.h"

namespace s21 {

template <class T>
class Queue {
 public:
  // Member types
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

 private:
  struct Node {
    T value;
    Node* next = nullptr;
    Node() {}
    explicit Node(const_reference item) : value(item) {}
  };

  size_type size = 0;
  Node* head = nullptr;
  Node* tail = nullptr;

 public:
  // Member functions
  Queue() {}

  explicit Queue(std::initializer_list<value_type> const& items) {
    for (auto i = items.begin(); i != items.end(); ++i) this->Push(*i);
  }

  Queue(const Queue& q) {
    Node* iter = q.head;

    for (size_type i = 0; i < q.size; ++i) {
      this->Push(iter->value);
      iter = iter->next;
    }
  }

  Queue(Queue&& q) {
    this->head = q.head;
    this->tail = q.tail;
    this->size = q.size;

    q.head = nullptr;
    q.tail = nullptr;
    q.size = 0;
  }

  ~Queue() {
    while (this->size > 0) {
      this->Pop();
    }
  }

  Queue& operator=(Queue&& q) {
    if (this != &q) {
      this->Swap(q);
    }
    return *this;
  }

  // Element access
  const_reference Front() {
    if (this->head == nullptr)
      throw std::out_of_range("Can't access head which is nullptr");
    return this->head->value;
  }

  const_reference Back() {
    if (this->tail == nullptr)
      throw std::out_of_range("Can't access tail which is nullptr");
    return this->tail->value;
  }

  // Capacity
  bool Empty() { return Size() == 0; }

  size_type Size() { return this->size; }

  // Modifiers
  void Push(const_reference value) {
    Node* new_node = new Node;
    new_node->value = value;

    if (this->size == 0) {
      this->head = new_node;
      this->tail = new_node;
    } else {
      this->tail->next = new_node;
      this->tail = new_node;
    }

    ++this->size;
  }

  void Pop() {
    if (this->size < 1) throw std::logic_error("Queue is already empty!\n");

    if (this->size == 1) {
      delete this->head;
    } else {
      Node* tmp = this->head;
      this->head = this->head->next;
      delete tmp;
    }

    --this->size;
  }

  void Swap(Queue& other) {
    std::swap(this->size, other.size);
    std::swap(this->head, other.head);
    std::swap(this->tail, other.tail);
  }

  // Insert many
  template <class... Args>
  void InsertManyBack(Args&&... args) {
    s21::Vector<value_type> parser{args...};
    for (size_type i = 0; i < parser.Size(); ++i) {
      this->Push(parser[i]);
    }
  }
};

}  // namespace s21

#endif

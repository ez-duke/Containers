#include "list_interface.h"

using namespace s21;

template <typename T>
List<T>::List() {
  this->sizeList = 0;
  this->head = nullptr;
  this->tail = nullptr;
}

template <typename T>
List<T>::~List() {
  while (sizeList) {
    pop_front();
  }
}

template <typename T>
List<T>::List(size_type n) {
  if (n == 0) {
    head = nullptr;
    tail = nullptr;
    sizeList = 0;
    return;
  }

  head = new Node(T());
  List<T>::Node* currentHead = head;

  for (size_type i = 0; i < n - 1; ++i) {
    List<T>::Node* newNode = new Node(T());
    currentHead->pNext = newNode;
    currentHead = newNode;
  }

  currentHead->pNext = nullptr;
  sizeList = n;
}

template <typename T>
List<T>::List(const List& l) {
  if (l.sizeList > 0) {
    this->head = new List<T>::Node(l.head->data);
    this->tail = nullptr;
    List<T>::Node* currentHead = this->head;
    List<T>::Node* currentLHead = l.head->pNext;

    while (currentHead != nullptr && currentLHead != nullptr) {
      currentHead->pNext = new List<T>::Node(currentLHead->data);
      currentHead =
          currentHead->pNext;  // переходим на новый элемент текущего списка
      currentLHead =
          currentLHead
              ->pNext;  // переходим на новый элемент копируюемого списка

      if (currentLHead == nullptr) {
        currentHead->pNext = nullptr;
      }
    }
    sizeList = l.sizeList;
  }
}

template <typename T>
List<T>::List(List&& l) {
  if (l.sizeList > 0) {
    this->head = std::move(l.head);
    this->tail = nullptr;
    this->sizeList = l.sizeList;

    l.head = nullptr;
    l.sizeList = 0;
  }
}

template <typename T>
List<T>::List(std::initializer_list<value_type> const& items) {
  head = nullptr;
  tail = nullptr;
  sizeList = 0;

  for (auto const& i : items) {
    push_back(i);
  }
}

template <typename T>
void List<T>::push_front(T data) {
  List<T>::Node* bufferHead = this->head;
  head = new List<T>::Node(data, bufferHead);
  sizeList++;
}

template <typename T>
void List<T>::push_back(T data) {
  if (this->head == nullptr) {
    this->head = new List<T>::Node(data);
  } else {
    List<T>::Node* current = this->head;
    while (current->pNext != nullptr) {
      current = current->pNext;
    }
    current->pNext = new List<T>::Node(data);
  }
  sizeList++;
}

template <typename T>
void List<T>::pop_front() {
  List<T>::Node* buffer = head;
  head = head->pNext;
  delete buffer;

  sizeList--;
}

template <typename T>
void List<T>::pop_back() {
  if (this->head == nullptr) {
    return;  // List is empty, nothing to pop
  }

  Node* second_to_last = nullptr;
  Node* last_node = this->head;

  while (last_node->pNext != nullptr) {
    second_to_last = last_node;
    last_node = last_node->pNext;
  }

  // Handle the case where the list has only one node
  if (second_to_last == nullptr) {
    delete this->head;
    this->head = nullptr;
  } else {
    delete last_node;
    second_to_last->pNext = nullptr;
  }

  sizeList--;
}

template <typename T>
typename List<T>::iterator List<T>::insert(iterator pos,
                                           const_reference value) {
  if (pos == end()) {
    push_back(value);
    return end();
  }

  Node* prev = pos.getHead()->pPrev;
  Node* next = pos.getHead()->pNext;
  Node* current = pos.getHead();

  Node* newNode = new Node(value, next);
  if (prev == nullptr) {
    this->head = newNode;
  } else {
    prev->pNext = newNode;
  }
  newNode->pNext = current;

  sizeList++;

  return iterator(newNode);
}

template <typename T>
void List<T>::erase(iterator pos) {
  if (pos == begin()) {
    pop_front();
  } else {
    List<T>::Node* current = head;

    while (current != nullptr && current->pNext != pos.getHead()) {
      current = current->pNext;
    }

    if (current == nullptr || current->pNext == nullptr) {
      throw std::out_of_range("Position out of range");
    }

    List<T>::Node* toDelete = current->pNext;

    current->pNext = toDelete->pNext;

    delete toDelete;
    sizeList--;
  }
}

template <typename T>
T& List<T>::operator[](const int index) {
  int counter = 0;

  List<T>::Node* current = this->head;
  while (current != nullptr) {
    if (counter == index) {
      return current->data;
    } else {
      current = current->pNext;
      counter++;
    }
  }
  throw std::out_of_range("Index out of range");
}

template <typename T>
List<T>& List<T>::operator=(List<T>&& other) {
  this->head = other.head;
  this->tail = nullptr;
  this->sizeList = other.sizeList;

  other.head = nullptr;
  other.sizeList = 0;
  return *this;
}

template <typename T>
const T& List<T>::front() {
  if (this->head == nullptr) {
    throw std::out_of_range("List is empty");
  }
  return this->head->data;
}

template <typename T>
const T& List<T>::back() {
  if (this->head == nullptr) {
    throw std::out_of_range("List is empty");
  }
  List<T>::Node* current = this->head;
  for (int i = 0; i < this->sizeList - 1; ++i) {
    current = current->pNext;
  }
  return current->data;
}

template <typename T>
bool List<T>::empty() {
  bool flag = true;
  if (this->head != nullptr) {
    flag = false;
  } else {
    flag = true;
  }
  return flag;
}

template <typename T>
void List<T>::clear() {
  if (this->head != nullptr) {
    List<T>::Node* current = this->head;
    while (current != nullptr) {
      List<T>::Node* next = current->pNext;
      delete current;
      current = next;
    }
  }

  this->head = nullptr;
  this->sizeList = 0;
}

template <typename T>
void List<T>::swap(List& other) {
  std::swap(this->head, other.head);
  this->sizeList = other.sizeList;
  other.sizeList = this->sizeList;
}

template <typename T>
void List<T>::sort() {
  List<T>::Node* current = this->head;
  while (current != nullptr && current->pNext != nullptr) {
    List<T>::Node* nextNode = current->pNext;
    while (nextNode != nullptr) {
      if (current->data > nextNode->data) {
        swapNodes(current, nextNode);
      }
      nextNode = nextNode->pNext;
    }
    current = current->pNext;
  }
}

template <typename T>
void List<T>::swapNodes(List<T>::Node* a, List<T>::Node* b) {
  T temp = a->data;
  a->data = b->data;
  b->data = temp;
}

// тут сега
template <typename T>
void List<T>::merge(List& other) {
  if (this->head == nullptr || other.head == nullptr) return;
  // находим конец текущего списка
  List<T>::Node* current = this->head;
  while (current != nullptr && current->pNext != nullptr) {
    current = current->pNext;
  }

  List<T>::Node* lastEllementCurrentList = current;

  // Объединяем остальной список к текущему
  while (other.head != nullptr) {
    lastEllementCurrentList->pNext = other.head;
    lastEllementCurrentList = lastEllementCurrentList->pNext;
    other.head = other.head->pNext;
  }
  this->sizeList = this->sizeList + other.sizeList;
  other.sizeList = 0;
  sort();
}

template <typename T>
void List<T>::splice(iterator pos, List& other) {
  List<T>::Node* temp = pos.getHead()->pNext;

  pos.getHead()->pNext = other.head;
  iterator it = pos;
  while (it.getHead()->pNext != nullptr) ++it;
  it.getHead()->pNext = temp;
  sizeList += other.sizeList;

  other.sizeList = 0;
}

template <typename T>
void List<T>::reverse() {
  List<T>::Node* buffer = this->head;
  List<T>::Node* newNode = nullptr;

  while (buffer != nullptr) {
    List<T>::Node* nextNode = buffer->pNext;
    buffer->pNext = newNode;
    newNode = buffer;
    buffer = nextNode;
  }
  head = newNode;
}

template <typename T>
typename List<T>::iterator List<T>::begin() {
  if (size() == 0) return end();
  return iterator(head);
}

template <typename T>
typename List<T>::iterator List<T>::end() {
  return iterator(nullptr);
}

template <typename T>
void List<T>::unique() {
  if (begin() == end()) return;

  iterator currentElement = begin();

  while (currentElement != end()) {
    bool foundDuplicate = true;
    iterator nextElement = iterator(currentElement.getHead()->pNext);
    while (nextElement != end() && foundDuplicate) {
      if (*currentElement == *nextElement) {
        iterator buffer = iterator(nextElement.getHead()->pNext);
        erase(nextElement);
        nextElement = buffer;
      } else {
        foundDuplicate = false;
      }
    }
    ++currentElement;
  }
}

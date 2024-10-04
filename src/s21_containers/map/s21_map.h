#include "map_interface.h"

using namespace s21;

template <class Key, class T>
Map<Key, T>::Map() {
  this->root = nullptr;
}

template <class Key, class T>
Map<Key, T>::Map(std::initializer_list<value_type> const &items) {
  std::pair<typename Map<Key, T>::iterator, bool> iter_status;
  for (auto i = items.begin(); i < items.end(); i++) {
    if (i == items.begin())
      iter_status = this->insert(*i);
    else
      this->insert(*i);
  }
  this->root = iter_status.first;
}

template <class Key, class T>
Map<Key, T>::Map(const Map &other) : BinaryTree<key_type, mapped_type>(other) {}

template <class Key, class T>
Map<Key, T>::Map(Map &&other)
    : BinaryTree<key_type, mapped_type>(std::move(other)) {}

template <class Key, class T>
Map<Key, T>::~Map() {}

template <class Key, class T>
Map<Key, T> Map<Key, T>::operator=(Map<Key, T> &&other) {
  if (this != &other) {
    this->clear();
    this->root = other.root;
    this->size = other.size;

    other.size = 0;
    other.root = nullptr;
  }
  return *this;
}

template <class Key, class T>
typename Map<Key, T>::mapped_type &Map<Key, T>::at(const key_type &key) {
  auto node_to_find = this->FindNode(*this->root, key);
  if (!node_to_find) {
    throw std::out_of_range("Key not found");
  }
  return node_to_find->value;
}

template <class Key, class T>
typename Map<Key, T>::mapped_type &Map<Key, T>::operator[](
    const key_type &key) {
  auto node_to_find = this->FindNode(*this->root, key);
  if (!node_to_find) {
    std::pair<typename Map<Key, T>::iterator, bool> iter_status =
        insert(std::make_pair(key, T()));
    node_to_find = iter_status.first;
  }
  return node_to_find->value;
}

template <class Key, class T>
typename Map<Key, T>::iterator Map<Key, T>::begin() {
  return this->root->FindMin(this->root);
}

template <class Key, class T>
typename Map<Key, T>::iterator Map<Key, T>::end() {
  return this->root->FindMax(this->root);
}

template <class Key, class T>
bool Map<Key, T>::empty() const {
  bool isEmpty = true;
  if (this->Size() != 0) isEmpty = false;
  return isEmpty;
}

template <class Key, class T>
typename Map<Key, T>::size_type Map<Key, T>::Size() const {
  return this->size;
}

template <class Key, class T>
typename Map<Key, T>::size_type Map<Key, T>::max_size() {
  return std::numeric_limits<size_type>::max() / sizeof(value_type);
}

template <class Key, class T>
void Map<Key, T>::clear() {
  if (this->root != nullptr) {
    this->size = 0;
    this->RecursiveDelete(this->root);
    this->root = nullptr;
  }
}

template <class Key, class T>
std::pair<typename Map<Key, T>::iterator, bool> Map<Key, T>::insert(
    typename Map<Key, T>::const_reference value) {
  std::pair<typename Map<Key, T>::iterator, bool> iter_status =
      this->InsertNode(*this->root, value.first, value.second, false);
  return iter_status;
}

template <class Key, class T>
std::pair<typename Map<Key, T>::iterator, bool> Map<Key, T>::insert(
    const key_type &key, const mapped_type &obj) {
  std::pair<typename Map<Key, T>::iterator, bool> iter_status =
      this->InsertNode(*this->root, key, obj, false);
  return iter_status;
}

template <class Key, class T>
std::pair<typename Map<Key, T>::iterator, bool> Map<Key, T>::insert_or_assign(
    const key_type &key, const mapped_type &obj) {
  auto node_to_find = this->FindNode(*this->root, key);
  if (node_to_find) {
    erase(node_to_find);
    std::pair<typename Map<Key, T>::iterator, bool> iter_status =
        insert(key, obj);
    iter_status.second = false;
    return iter_status;
  }
  return insert(key, obj);
}

template <class Key, class T>
void Map<Key, T>::erase(iterator pos) {
  this->EraseNode(pos);
}

template <class Key, class T>
void Map<Key, T>::swap(Map &other) {
  std::swap(this->root, other.root);
  std::swap(this->size, other.size);
}

template <class Key, class T>
void Map<Key, T>::merge(const Map &other) {
  this->InsertRecursively(other.root);
}

template <class Key, class T>
bool Map<Key, T>::contains(const Key &key) {
  bool isFound = false;
  const auto *node_to_find = this->FindNode(*this->root, key);
  if (node_to_find) isFound = true;
  return isFound;
}

template <class Key, class T>
typename Map<Key, T>::iterator Map<Key, T>::find(const key_type &key) {
  return this->FindNode(*this->root, key);
}

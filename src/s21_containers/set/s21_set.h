#ifndef S21_SET
#define S21_SET

#include "../tree/s21_tree.h"
#include "../vector/s21_vector.h"

namespace s21 {

template <class Key>
class Set : public BinaryTree<Key, Key> {
 public:
  // Member types
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename BinaryTree<key_type, value_type>::iterator;
  using const_iterator =
      typename BinaryTree<key_type, value_type>::const_iterator;
  using size_type = size_t;

  // Member functions
  Set() { this->root = nullptr; }

  explicit Set(std::initializer_list<value_type> const &items) {
    std::pair<iterator, bool> iter_status;
    for (auto i = items.begin(); i < items.end(); ++i) {
      if (i == items.begin())
        iter_status = this->Insert(*i);
      else
        this->Insert(*i);
    }
    this->root = iter_status.first;
  }

  Set(const Set &s) : BinaryTree<key_type, value_type>(s) {}

  Set(Set &&s) : BinaryTree<key_type, value_type>(std::move(s)) {}

  ~Set() {}

  Set &operator=(Set &&s) {
    if (this != &s) {
      this->Swap(s);
    }
    return *this;
  }

  // Iterators
  iterator Begin() { return this->root->FindMin(this->root); }

  iterator End() { return this->root->FindMax(this->root); }

  // Capacity
  bool Empty() { return this->Size() == 0; }

  size_type Size() { return this->size; }

  size_type MaxSize() {
    return std::numeric_limits<size_type>::max() / sizeof(value_type);
  }

  // Modifiers
  void Clear() {
    if (this->root != nullptr) {
      this->size = 0;
      this->RecursiveDelete(this->root);
      this->root = nullptr;
    }
  }

  virtual std::pair<iterator, bool> Insert(const value_type &key) {
    std::pair<iterator, bool> iter_status =
        this->InsertNode(*this->root, key, key, false);
    return iter_status;
  }

  void Erase(iterator pos) { this->EraseNode(pos); }

  void Swap(Set &other) {
    std::swap(this->root, other.root);
    std::swap(this->size, other.size);
  }

  void Merge(const Set &other) { this->InsertRecursively(other.root); }

  // Lookup
  iterator Find(const key_type &key) {
    return this->FindNode(*this->root, key);
  }

  bool Contains(const key_type &key) { return this->Find(key) != nullptr; }

  // Insert many
  template <class... Args>
  s21::Vector<std::pair<iterator, bool>> Insert_many(Args &&...args) {
    s21::Vector<value_type> parser{args...};
    s21::Vector<std::pair<iterator, bool>> insertion_vector;
    for (size_type i = 0; i < parser.Size(); ++i) {
      insertion_vector.PushBack(this->Insert(parser[i]));
    }
    return insertion_vector;
  }
};

}  // namespace s21

#endif

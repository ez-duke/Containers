#ifndef S21_MULTISET
#define S21_MULTISET

#include "../../s21_containers/set/s21_set.h"

namespace s21 {

template <class Key>
class Multiset : public Set<Key> {
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
  Multiset() { this->root = nullptr; }

  explicit Multiset(std::initializer_list<value_type> const &items) {
    std::pair<iterator, bool> iter_status;
    for (auto i = items.begin(); i < items.end(); ++i) {
      if (i == items.begin())
        iter_status = this->Insert(*i);
      else
        this->Insert(*i);
    }
    this->root = iter_status.first;
  }

  Multiset(const Multiset &s) : Set<key_type>(s) {}

  Multiset(Multiset &&s) : Set<key_type>(std::move(s)) {}

  ~Multiset() {}

  Multiset &operator=(Multiset &&s) {
    if (this != &s) {
      this->Swap(s);
    }
    return *this;
  }

  std::pair<iterator, bool> Insert(const value_type &key) override {
    std::pair<iterator, bool> iter_status =
        this->InsertNode(*this->root, key, key, true);
    return iter_status;
  }

  void Swap(Multiset &other) {
    std::swap(this->root, other.root);
    std::swap(this->size, other.size);
  }

  void Merge(const Multiset &other) { this->InsertRecursively(other.root); }

  // Lookup
  size_type Count(const Key &key) {
    iterator iter = this->Find(key);
    size_type count = 0;

    if (iter != nullptr) count = 1;
    while (iter->right != nullptr && iter->key == iter->right->key) {
      iter = iter->right;
      ++count;
    }
    return count;
  }

  std::pair<iterator, iterator> EqualRange(const Key &key) {
    std::pair<iterator, iterator> iter_range{this->LowerBound(key),
                                             this->UpperBound(key)};
    return iter_range;
  }

  iterator LowerBound(const Key &key) {
    iterator iter = this->Find(key);
    return iter;
  }

  iterator UpperBound(const Key &key) {
    iterator iter = this->FindBigger(key, this->Find(key));
    return iter;
  }
};

}  // namespace s21

#endif

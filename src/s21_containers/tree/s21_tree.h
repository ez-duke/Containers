#ifndef S21_TREE
#define S21_TREE

#include <initializer_list>
#include <iostream>
#include <utility>

namespace s21 {

template <class Key, class Val>
class BinaryTree {
 protected:
  struct Node {
    Node* parent = nullptr;
    Node* left = nullptr;
    Node* right = nullptr;
    Key key;
    Val value;

    Node() {}

    Node(const Key& key, const Val& value, Node* parent) {
      this->key = key;
      this->value = value;
      this->parent = parent;
    }

    ~Node() {
      delete left;
      delete right;
    }

    void Swap(Node& other) {
      std::swap(this->parent, other.parent);
      std::swap(this->left, other.left);
      std::swap(this->right, other.right);
      std::swap(this->key, other.key);
      std::swap(this->value, other.value);
    }

    Node& operator=(Node&& n) {
      if (this != &n) {
        this->Swap(n);
      }
      return *this;
    }

    Node* FindMin(Node* node) {
      Node* pos = node;
      if (pos != nullptr) {
        while (pos->parent != nullptr) {
          pos = pos->parent;
        }
        while (pos->left != nullptr) {
          pos = pos->left;
        }
      }
      return pos;
    }

    Node* FindMax(Node* node) {
      Node* pos = node;
      if (pos != nullptr) {
        while (pos->parent != nullptr) {
          pos = pos->parent;
        }
        while (pos->right != nullptr) {
          pos = pos->right;
        }
      }
      return pos;
    }
  };

  Node* FindBigger(const Key& key_, Node* iter) {
    auto init_key = key_;

    // пропускаем одинаковые значения
    while (iter->right != nullptr && init_key == iter->key) {
      iter = iter->right;
    }

    // находим нужное значение и возвращаем его
    if (iter->right != nullptr) {
      iter = iter->right;

      if (iter->left != nullptr && iter->key < iter->left->key) {
        iter = iter->left;
      }
      return iter;
    }

    // иначе идём наверх
    while (iter->parent != nullptr && init_key >= iter->parent->value) {
      iter = iter->parent;
    }

    // ищем большее значение
    if (iter->parent != nullptr) {
      iter = iter->parent;
    } else {
      iter = iter->right;
    }

    // ищем возможное менее большее значение
    if (iter->left != nullptr && init_key < iter->left->key) {
      iter = iter->left;
    }
    return iter;
  }

  Node* root = nullptr;
  size_t size = 0;

 public:
  // Member types
  using key_type = Key;
  using value_type = Val;
  using reference = Val&;
  using const_reference = const Val&;
  using iterator = Node*;
  using const_iterator = const Node*;
  using size_type = size_t;

  // Member functions
  BinaryTree() {}

  BinaryTree(const key_type& key, const value_type& value) {
    iterator new_node = new Node;
    new_node->key = key;
    new_node->value = value;
    this->root = new_node;
  }

  BinaryTree(const BinaryTree& s) {
    this->root = this->CopyTree(s.root, this->root);
  }

  BinaryTree(BinaryTree&& s) {
    this->root = s.root;
    this->size = s.size;
    s.size = 0;
    s.root = nullptr;
  }

  ~BinaryTree() { delete root; }

  iterator FindNode(Node& node, const key_type& key) {
    iterator pos = nullptr;
    if (key == node.key) {
      pos = &node;
    } else if (key > node.key) {
      if (node.right == nullptr) {
        pos = nullptr;
      } else {
        pos = this->FindNode(*node.right, key);
      }
    } else {
      if (node.left == nullptr) {
        pos = nullptr;
      } else {
        pos = this->FindNode(*node.left, key);
      }
    }
    return pos;
  }

  std::pair<iterator, bool> InsertNode(Node& parent, const key_type& key,
                                       const value_type& value,
                                       bool allowDuplicates) {
    std::pair<iterator, bool> iter_status{nullptr, false};

    if (this->root == nullptr) {
      iter_status.first = new Node(key, value, nullptr);

      this->root = iter_status.first;
      iter_status.second = true;
      this->size++;
    } else if (key == parent.key) {
      if (allowDuplicates) {
        iter_status.first = new Node(key, value, &parent);

        iter_status.first->right = parent.right;
        if (parent.right != nullptr) {
          parent.right->parent = iter_status.first;
        }
        parent.right = iter_status.first;
        iter_status.second = true;
        this->size++;
      }  // else iter_status.second = false;
    } else if (key > parent.key) {
      if (parent.right == nullptr) {
        iter_status.first = new Node(key, value, &parent);

        parent.right = iter_status.first;
        iter_status.second = true;
        this->size++;
      } else if (parent.right->key > key) {
        iter_status.first = new Node(key, value, &parent);

        iter_status.first->right = parent.right;
        parent.right->parent = iter_status.first;
        parent.right = iter_status.first;
        iter_status.second = true;
        this->size++;
      } else {
        iter_status =
            this->InsertNode(*parent.right, key, value, allowDuplicates);
      }
    } else {
      if (parent.left == nullptr) {
        iter_status.first = new Node(key, value, &parent);

        parent.left = iter_status.first;
        iter_status.second = true;
        this->size++;
      } else if (parent.left->key < key) {
        iter_status.first = new Node(key, value, &parent);

        iter_status.first->left = parent.left;
        parent.left->parent = iter_status.first;
        parent.left = iter_status.first;
        iter_status.second = true;
        this->size++;
      } else {
        iter_status =
            this->InsertNode(*parent.left, key, value, allowDuplicates);
      }
    }
    return iter_status;
  }

  void EraseNode(iterator pos) {
    iterator child = nullptr;
    if (pos != nullptr) {
      if (pos->left == nullptr && pos->right == nullptr) {
        ;  // nothing
      } else if (pos->left != nullptr && pos->right != nullptr) {
        pos->left->parent = pos->parent;
        pos->right->parent = pos->left;
        child = pos->left;
      } else if (pos->left != nullptr) {
        pos->left->parent = pos->parent;
        child = pos->left;
      } else {  // if (pos->right != nullptr)
        pos->right->parent = pos->parent;
        child = pos->right;
      }

      if (pos->parent != nullptr) {
        if (pos->parent->key < pos->key) {
          pos->parent->right = child;
        } else {
          pos->parent->left = child;
        }
      } else {
        this->root = child;
      }

      pos->left = nullptr;
      pos->right = nullptr;
      pos->parent = nullptr;
      this->size--;
      delete pos;
    }
  }

  void InsertRecursively(iterator node) {
    if (node == nullptr) return;

    this->InsertNode(*this->root, node->key, node->value, false);
    this->InsertRecursively(node->left);
    this->InsertRecursively(node->right);
  }

  void RecursiveDelete(iterator node) {
    if (node == nullptr) return;

    this->RecursiveDelete(node->left);
    this->RecursiveDelete(node->right);
    node->left = nullptr;
    node->right = nullptr;
    delete node;
  }

  iterator CopyTree(iterator node, iterator parent) {
    if (node == nullptr) return node;

    Node* new_node = new Node(node->key, node->value, parent);

    new_node->left = CopyTree(node->left, new_node);
    new_node->right = CopyTree(node->right, new_node);
    ++this->size;
    return new_node;
  }

  // Iterators
  class Iterator {
   private:
    iterator ptr;

   public:
    Iterator() { this->ptr = nullptr; }

    explicit Iterator(iterator _ptr) { this->ptr = _ptr; }

    iterator getPtr() { return this->ptr; }

    reference operator*() { return ptr->key; }

    Iterator& operator++() {
      if (this->ptr == this->ptr->FindMax(this->ptr))
        throw(std::out_of_range("Incorrect input, index is out of range\n"));

      auto init_key = this->ptr->key;

      // пропускаем одинаковые значения
      while (this->ptr->right != nullptr && init_key == this->ptr->key) {
        this->ptr = this->ptr->right;
      }

      // находим нужное значение и возвращаем его
      if (this->ptr->right != nullptr) {
        this->ptr = this->ptr->right;

        if (this->ptr->left != nullptr &&
            this->ptr->key < this->ptr->left->key) {
          this->ptr = this->ptr->left;
        }
        return *this;
      }

      // иначе идём наверх
      while (this->ptr->parent != nullptr &&
             init_key >= this->ptr->parent->value) {
        this->ptr = this->ptr->parent;
      }

      // ищем большее значение
      if (this->ptr->parent != nullptr) {
        this->ptr = this->ptr->parent;
      } else {
        this->ptr = this->ptr->right;
      }

      // ищем возможное менее большее значение
      if (this->ptr->left != nullptr && init_key < this->ptr->left->key) {
        this->ptr = this->ptr->left;
      }
      return *this;
    }

    Iterator& operator--() {
      if (this->ptr == this->ptr->FindMin(this->ptr))
        throw(std::out_of_range("Incorrect input, index is out of range\n"));

      if (this->ptr->left != nullptr) {
        this->ptr = this->ptr->left;
        if (this->ptr->right != nullptr &&
            this->ptr->key < this->ptr->right->key) {
          this->ptr = this->ptr->right;
        }
      }
      while (this->ptr->parent != nullptr &&
             this->ptr->parent->left != nullptr &&
             (this->ptr->parent->left == this->ptr ||
              this->ptr->key <= this->ptr->parent->key)) {
        this->ptr = this->ptr->parent;
      }
      if (this->ptr->left != nullptr) {
        this->ptr = this->ptr->left;
        if (this->ptr->right != nullptr &&
            this->ptr->key < this->ptr->right->key) {
          this->ptr = this->ptr->right;
        }
      } else {
        while (this->ptr->parent != nullptr &&
               this->ptr->parent->left != nullptr &&
               (this->ptr->parent->left == this->ptr ||
                this->ptr->key <= this->ptr->parent->key)) {
          this->ptr = this->ptr->parent;
        }
        if (this->ptr->parent != nullptr) this->ptr = this->ptr->parent;
      }
      if (this->ptr->left != nullptr) {
        this->ptr = this->ptr->left;
        if (this->ptr->right != nullptr &&
            this->ptr->key < this->ptr->right->key) {
          this->ptr = this->ptr->right;
        }
      }
      return *this;
    }

    bool operator==(const Iterator other) { return other.ptr == this->ptr; }

    bool operator!=(const Iterator other) { return other.ptr != this->ptr; }
  };
};

}  // namespace s21

#endif

#ifndef MAP_INTERFACE_H
#define MAP_INTERFACE_H

#include <initializer_list>
#include <limits>

#include "../tree/s21_tree.h"
#include "../vector/s21_vector.h"

namespace s21 {

template <class Key, class T>
class Map : public BinaryTree<Key, T> {
 public:
  // Map Member type
  using key_type = Key;   // the first template parameter
  using mapped_type = T;  //  the second template parameter
  using value_type = std::pair<const key_type, mapped_type>;  // Key-value pair
  using reference =
      value_type &;  // defines the type of the reference to an element
  using const_reference =
      const value_type &;  // defines the type of the constant reference
  using iterator = typename BinaryTree<key_type, mapped_type>::
      iterator;  // or MapIterator<Key, T>; defines the type for iterating
                 // through the container
  using const_iterator = typename BinaryTree<key_type, mapped_type>::
      const_iterator;  // or MapConstIterator<Key, T>; defines the constant type
                       // for iterating through the container
  using size_type = size_t;  // defines the type of the container size

  // Map Member functions - методы для взаимодействия с классом
  Map();  // default constructor, creates empty stack
  explicit Map(std::initializer_list<value_type> const
                   &items);    // initializer list constructor, creates stack
                               // initizialized using std::initializer_list
  Map(const Map &other);       // copy constructor
  Map(Map &&other);            // move constructor
  ~Map();                      // destructor
  Map operator=(Map &&other);  // assignment operator overload for moving object

  // Map Element access - методы для доступа к элементам класса
  mapped_type &at(
      const key_type &key);  // access specified element with bounds checking
  mapped_type &operator[](
      const key_type &key);  // access or insert specified element

  // Map Iterators - методы для итерирования по элементам класса (доступ к
  // итераторам)
  iterator begin();  // returns an iterator to the beginning
  iterator end();    // returns an iterator to the end

  // Map Capacity - методы для доступа к информации о наполнении контейнера
  bool empty() const;      // checks whether the container is empty
  size_type Size() const;  // returns the number of elements
  size_type max_size();    // returns the maximum possible number of elements

  // Map Modifiers - методы для изменения контейнера
  void clear();  // clears the contents
  std::pair<iterator, bool> insert(
      const_reference value);  // inserts node and returns iterator to where the
                               // element is in the container and bool denoting
                               // whether the insertion took place
  std::pair<iterator, bool> insert(
      const key_type &key,
      const mapped_type
          &obj);  // inserts value by key and returns iterator to where the
                  // element is in the container and bool denoting whether the
                  // insertion took place
  std::pair<iterator, bool> insert_or_assign(
      const key_type &key,
      const mapped_type &obj);   // inserts an element or assigns to the current
                                 // element if the key already exists
  void erase(iterator pos);      // erases element at pos
  void swap(Map &other);         // swaps the contents
  void merge(const Map &other);  // splices nodes from another container

  // Map Lookup - методы, осуществляющие просмотр контейнера
  bool contains(const Key &key);  // checks if there is an element with key
                                  // equivalent to key in the container

  // Helpers
  iterator find(const key_type &key);

  // Part 3 - inserts new elements into the container
  template <class... Args>
  s21::Vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    s21::Vector<std::pair<Map<Key, T>::iterator, bool>> insertion_vector;

    for (const auto &arg : {args...}) {
      std::pair<Map<Key, T>::iterator, bool> result = this->insert(arg);
      insertion_vector.PushBack(result);
    }

    return insertion_vector;
  }
};
}  // namespace s21

#endif

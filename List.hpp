#pragma once

#include <memory>
#include <list>
#include "Traits.h"

namespace ft {

template<class T>
class List;

template<class Iter>
class BidirectionalListIt;
//	------------------------------------- LIST NODE -----------------------------------------
template<class T>
class NodeList {
 public:
  typedef T value_type;
 private:
  NodeList<T> *next;
  NodeList<T> *prev;
  value_type value;
  NodeList() : next(nullptr), prev(nullptr), value(value_type()) {}
  NodeList(const value_type &value) : next(nullptr), prev(nullptr), value(value) {} //todo
  //todo copy constructor
  friend class List<T>;
  friend class BidirectionalListIt<T>;

  NodeList &operator=(const NodeList<value_type> &obj) {
    next = obj.next;
    prev = obj.prev;
  }
 public:

  bool operator==(const NodeList &rhs) const {
    return value == rhs.value;
  }

  bool operator!=(const NodeList &rhs) const {
    return !(rhs == *this);
  }

  bool operator<(const NodeList &rhs) const {
    return value < rhs.value;
  }

  bool operator>(const NodeList &rhs) const {
    return rhs < *this;
  }

  bool operator<=(const NodeList &rhs) const {
    return !(rhs < *this);
  }

  bool operator>=(const NodeList &rhs) const {
    return !(*this < rhs);
  }
};

// -------------------------------------- TAGS -------------------------------------
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

//	------------------------------------- LIST ITERATOR -----------------------------------------
template<class Iter>
class BidirectionalListIt {
 private:
  NodeList<Iter> *ptr;
  friend class List<Iter>;
 public:
  typedef std::ptrdiff_t difference_type;
  typedef Iter value_type;
  typedef Iter const const_value_type;
  typedef ft::bidirectional_iterator_tag iterator_category;
  typedef value_type &reference;
  typedef value_type *pointer;
  typedef const_value_type &const_reference;
  typedef const_value_type *const_pointer;
  typedef size_t size_type;

  explicit BidirectionalListIt() throw(): ptr(nullptr) {}
  explicit BidirectionalListIt(NodeList<Iter> *p) throw(): ptr(p) {}
  explicit BidirectionalListIt(const NodeList<const Iter> *p) throw(): ptr(const_cast<NodeList<const Iter> *>(p)) {}
  BidirectionalListIt(const BidirectionalListIt &p) throw(): ptr(p.ptr) {}
  ~BidirectionalListIt() {}

  BidirectionalListIt &operator=(const BidirectionalListIt &rhs) {
    ptr = rhs.ptr;
    return *this;
  }

  reference operator*() {
    return this->ptr->value;
  }

  const_reference operator*() const {
    return this->ptr->value;
  }

  pointer operator->() {
    return &(this->ptr->value);
  }

  const_pointer operator->() const {
    return &(this->ptr->value);
  }

  bool operator==(const BidirectionalListIt &rhs) const {
    return ptr == rhs.ptr;
  }

  bool operator!=(const BidirectionalListIt &rhs) const {
    return !(rhs == *this);
  }

  bool operator<(const BidirectionalListIt &rhs) const {
    return ptr < rhs.ptr;
  }

  bool operator>(const BidirectionalListIt &rhs) const {
    return rhs < *this;
  }

  bool operator<=(const BidirectionalListIt &rhs) const {
    return !(rhs < *this);
  }

  bool operator>=(const BidirectionalListIt &rhs) const {
    return !(*this < rhs);
  }

  BidirectionalListIt<Iter> &operator++() {
    ptr = ptr->next;
    return *this;
  }

  BidirectionalListIt<Iter> operator++(int) {
    BidirectionalListIt<Iter> clone(*this);
    ptr = ptr->next;
    return clone;
  }

  BidirectionalListIt<Iter> &operator--() {
    ptr = ptr->prev;
    return *this;
  }

  BidirectionalListIt<Iter> operator--(int) {
    BidirectionalListIt<Iter> clone(*this);
    ptr = ptr->prev;
    return clone;
  }
};

//	------------------------------------- LIST CONTAINER -----------------------------------------
template<class T>
class List {
 public:
  typedef T value_type;
  typedef T &reference;
  typedef const T &const_reference;
  typedef T *pointer;
  typedef const T *const_pointer;
  typedef ptrdiff_t difference_type;
  typedef size_t size_type;
  typedef BidirectionalListIt<T> iterator;
  typedef BidirectionalListIt<T> const_iterator;
  typedef bidirectional_iterator_tag iterator_category;

 private:
  NodeList<value_type> *shadow;
  size_type currentSize;

 public:
  explicit List() : shadow(new NodeList<value_type>()), currentSize(0) {
    shadow->next = shadow;
    shadow->prev = shadow;
  }

  explicit List(size_type n, const value_type &val = value_type()) : List(){
    shadow_constructor(n, val, ft::type_true());
  }

  template<class InputIterator>
  List(InputIterator first, InputIterator last) : List() {
    shadow_constructor(first, last, ft::type_is_primitive<InputIterator>());
  }

 private:
  template<class InputIterator>
  void shadow_constructor(InputIterator first, InputIterator last, ft::type_false) {
    insert(begin(), first, last);
  }

  void shadow_constructor(size_type n, const value_type &val, ft::type_true) {
    insert(begin(), n, val);
  }

 public:
  List(const List &x) {
    this();
    insert(begin(), x.begin(), x.end());
  }

  ~List() {
    clear();
    delete shadow;
  }

  // ------------------- ITERATORS ----------------------
  iterator begin() {
    return iterator(shadow->next);
  }

  iterator end() {
    return iterator(shadow);
  }

  iterator begin() const {
    return iterator(shadow->next);
  }

  iterator end() const {
    return iterator(shadow);
  }

  value_type &at(int idx) {
    NodeList<value_type> *ptr = shadow->next;
    for (int i = 0; i < idx; i++) {
      ptr = ptr->next;
    }
    return ptr->value;
  }

  void push_back(value_type const &value) {
    insert(end(), value);
  }

  void push_front(value_type const &value) {
    insert(begin(), value);
  }

  // single element
  iterator insert(iterator position, const value_type &val) {
    NodeList<value_type> *insert_node = new NodeList<value_type>();
    insert_node->value = val;
    if (currentSize == 0) {
      shadow->next = insert_node;
      shadow->prev = insert_node;
      insert_node->next = shadow;
      insert_node->prev = shadow;
    } else {
      NodeList<value_type> *pos = position.ptr;
      insert_node->next = pos;
      insert_node->prev = pos->prev;
      insert_node->prev->next = insert_node;
      insert_node->next->prev = insert_node;
    }
    ++currentSize;
    return iterator(insert_node);
  }

  // fill
  void insert(iterator position, size_type n, const value_type &val) {
    iterator tmp = position;
    for (size_type i = 0; i < n; i++) {
      ++position;
      insert(tmp, val);
    }
  }

  // range [first,last)
  template<class InputIterator>
  void insert(iterator position, InputIterator first, InputIterator last) {
    iterator tmp = position;
    while (first != last) {
      ++position;
      insert(tmp, *first);
      ++first;
    }
  }

  size_type size() const {
    return currentSize;
  }

  bool empty() const {
    return currentSize == 0;
  }

  size_type max_size() const {
    return SIZE_MAX / sizeof(NodeList<T>);
  }

  reference front() {
    return shadow->next->value;
  }

  const_reference front() const {
    return shadow->next->value;
  }

  reference back() {
    return shadow->prev->value;
  }

  const_reference back() const {
    return shadow->prev->value;
  }

 private:
  template<class InputIterator>
  void shadow_assign(InputIterator first, InputIterator last, ft::type_false) {
    iterator it = begin();
//    currentSize = 0;
    while (first != last) {
      if (it == end()) {
        insert(it, first, last);
        return;
      }
      *it = *(first);
//      ++currentSize;
      ++it;
      ++first;
    }
    if (it != end()) {
      erase(it, end());
    }
  }

  void shadow_assign(size_type n, const value_type &val, ft::type_true) {
    iterator it = begin();
    iterator tmp = it;
//    currentSize = 0;
    if (it == end()) {
      insert(begin(), n, val);
      return;
    }
    for (size_type i = 0; i < n; i++) {
      if (it == end()) {
        insert(it, n - i - 1, val);
        return;
      }
      ++it;
      *tmp = val;
      tmp = it;
    }
    if (it != end()) {
      erase(it, end());
    }
  }

 public:
  template<class InputIterator>
  void assign(InputIterator first, InputIterator last) {
    shadow_assign(first, last, ft::type_is_primitive<InputIterator>());
  }

  void assign(size_type n, const value_type &val) {
    shadow_assign(n, val, ft::type_true());
  }

  iterator erase(iterator position) {
    NodeList<value_type> *pos = position.ptr;
    currentSize--;
    NodeList<value_type> *prev = pos->prev;
    prev->next = pos->next;
    pos->next->prev = prev;
    delete pos;
    return iterator(prev->next);
  }

  iterator erase(iterator first, iterator last) {
    iterator tmp = first;
    while (first != last) {
      ++first;
      erase(tmp);
      tmp = first;
    }
    return iterator(first);
  }

  void clear() {
    erase(begin(), end());
  }

  void swap (List& x) {
    NodeList<value_type> *tmp = shadow;
    shadow = x.shadow;
    x.shadow = tmp;

    size_type tmpSize = currentSize;
    currentSize = x.currentSize;
    x.currentSize = tmpSize;
  }

};

//todo list operator==, operator<= etc
}

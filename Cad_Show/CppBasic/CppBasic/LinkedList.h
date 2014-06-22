#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

template<typename T>
class LinkedNode {
public:
  LinkedNode() :
      previous_(NULL),
      next_(NULL) 
      {;}
  LinkedNode(LinkedNode<T>* next, LinkedNode<T>* previous):
      next_(next),
      previous_(previous) 
      {;}

  // Inset this into List before node
  void InsertBefore(LinkedNode<T>* node) {
    this->next_ = node;
    this->previous_ = node->previous_;
    node->previous_->next_ = this;
    node->previous_ = this;
  }

  void InsertAffter(LinkedNode<T>* node) {
    this->next_ = node->next_;
    this->previous_ = node;
    node->next_->previous_ = this;
    node->next_ = this;
  }

  // remove this 
  void RemoveFormList() {
    this->previous_->next_ = this->next_;
    this->next_->previous_ = this->previous_;
  }

  LinkedNode<T> previous() {
    return previous_;
  }

  LinkedNode<T>next() {
    return next_;
  }

  T* value() {
   return static_cast<T*>this;
  }

  const T* value() const {
    return static_cast<const T*>this;
  }

  void set(LinkedNode<T> *previous, LinkNode<T>*next) {
    previous_ = previous;
    next_ = next;
  }
private:
  LinkedNode<T> *previous_;
  LinkedNode<T> *next_;
};


template<typename T>
class LinkedList {
public:
  LinkedList() {
    
  }
  // add new element at end of list
  void Append(LinkedNode<T>* node) {
    node->InsertBefore(&root_);
  }

  LinkedNode<T>* head() const {
    return root_.next();
  }
  LinkedNode<T>* tail() const {
    return root_.previous();
  }

  const LinkedNode<T>* end() const {
    return &root_;
  }

  bool IsEmpty() const {
    return (head() == next());
  }
private:
  LinkedNode<T> root_;
};


#endif // LINKED_LIST_H_

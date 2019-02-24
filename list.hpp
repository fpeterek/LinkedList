//
//  list.hpp
//  linked_list
//
//  Created by Filip Peterek on 22/02/2019.
//  Copyright © 2019 Filip Peterek. All rights reserved.
//

#ifndef list_hpp
#define list_hpp

#include <memory>
#include <cstdint>
#include <exception>
#include <stdexcept>
#include <iterator>
#include <functional>


/*************************************************************************/
/*                                                                       */
/* ********************************************************************* */
/* **************************** Declaration **************************** */
/* ********************************************************************* */
/*                                                                       */
/*************************************************************************/


template <typename T>
class List {
    
    struct Node {
        
        Node * next;
        T item;
        
        template<typename... args>
        Node(args&... a);
        
        template<typename... args>
        Node(args&&... a);
        
        template<typename... args>
        Node(const args&... a);
        
        Node(const Node & node);
        Node(Node & node);
        Node(Node && node);
        
    };
    
    typedef Node* node_ptr;
    
    size_t len = 0;
    node_ptr head = nullptr;
    node_ptr back = nullptr;
    
    /* Node retreival */
    
    // node_ptr & find_last_ptr();
    // node_ptr find_last_node();
    node_ptr node_at(const size_t index);
    const node_ptr node_at(const size_t index) const;
    
    /* Utility */
    
    void checkIndexRange(const size_t index) const;
    
    /* Node insertion */
    
    List<T> & push_back_node(node_ptr node);
    List<T> & push_node(node_ptr node);
    List<T> & insert_node(const size_t index, node_ptr node);
    
public:
    
    /* Element access */
    
    T & at(const size_t index);
    T & operator[](const size_t index);
    const T & at(const size_t index) const;
    const T & operator[](const size_t index) const;
    
    T & first();
    const T & first() const;
    
    T & last();
    const T & last() const;
    
    /* Push back */
    
    List<T> & push_back(const T & item);
    List<T> & push_back(T & item);
    List<T> & push_back(T && item);

    template<typename... args>
    List<T> & push_back(args&... a);
    
    template<typename... args>
    List<T> & push_back(args&&... a);
    
    template<typename... args>
    List<T> & push_back(const args&... a);
    
    /* Push front */
    
    List<T> & push(const T & item);
    List<T> & push(T & item);
    List<T> & push(T && item);
    
    template<typename... args>
    List<T> & push(args&... a);
    
    template<typename... args>
    List<T> & push(args&&... a);
    
    template<typename... args>
    List<T> & push(const args&... a);
    
    /* Insert at index */
    
    List<T> & insert(const size_t index, const T & item);
    List<T> & insert(const size_t index, T & item);
    List<T> & insert(const size_t index, T && item);
    
    template<typename... args>
    List<T> & insert(const size_t index, args&... a);
    
    template<typename... args>
    List<T> & insert(const size_t index, args&&... a);
    
    template<typename... args>
    List<T> & insert(const size_t index, const args&... a);
    
    /* Remove elements */
    
    T pop_front();
    T pop_back();
    T remove(const size_t index);
    
    /* List concatenation */
    
    List<T> concatenate(const List<T> & l) const;
    List<T> operator+(const List<T> & l) const;
    List<T> concatenate(List<T> && l) const;
    List<T> operator+(List<T> && l) const;
    
    /* Append list */
    
    List<T> & append(const List<T> & l);
    List<T> & operator+=(const List<T> & l);
    List<T> & append(List<T> && l);
    List<T> & operator+=(List<T> && l);
    
    /* Assignment */
    
    List<T> & assign(const List<T> & l);
    List<T> & operator=(const List<T> & l);
    List<T> & assign(List<T> && l);
    List<T> & operator=(List<T> && l);
    
    /* Utility */
    
    size_t size() const;
    
    List<T> map(std::function<T(const T&)> fun) const;
    
    template<typename Acc>
    Acc fold(std::function<void(Acc & acc, const T&)> fun, Acc initVal) const;
    
    List<T> filter(std::function<bool(const T&)> fun) const;
    
    List<T> & clear();
    
    /* Constructors */
    
    List<T>();
    List<T>(const List<T> & orig);
    List<T>(List<T> && orig);
    
    /* Destructor */
    
    ~List<T>();
    
};

/**************************************************************************/
/*                                                                        */
/* ********************************************************************** */
/* *************************** Implementation *************************** */
/* ********************************************************************** */
/*                                                                        */
/**************************************************************************/


/********************************************************************/
/*                                                                  */
/*                               Node                               */
/*                                                                  */
/********************************************************************/

/* Node constructors */

template<typename T>
template <typename... args>
List<T>::Node::Node(args&... a) : item(a...) { }

template<typename T>
template <typename... args>
List<T>::Node::Node(args&&... a) : item(a...) { }

template<typename T>
template <typename... args>
List<T>::Node::Node(const args&... a) : item(a...) { }

template<typename T>
List<T>::Node::Node(const Node & node) : item(node.item) { }

template<typename T>
List<T>::Node::Node(Node & node) : item(node.item) { }

template<typename T>
List<T>::Node::Node(Node && node) : item(node.item) { }


/*********************************************************************/
/*                                                                   */
/*                              List<T>                              */
/*                                                                   */
/*********************************************************************/

/**********************/
/*      Internal      */
/**********************/

/* Node retrieval */

/*

template<typename T>
typename List<T>::node_ptr & List<T>::find_last_ptr() {
    
    node_ptr ptr = find_last_node();
    if (ptr == nullptr) {
        return head;
    }
    return ptr->next;
    
}

template<typename T>
typename List<T>::node_ptr List<T>::find_last_node() {
    
    if (head == nullptr) {
        return nullptr;
    }
    
    node_ptr ptr;
    for (ptr = head; ptr->next != nullptr; ptr = ptr->next);
    return ptr;
    
}
 
 */

template<typename T>
typename List<T>::node_ptr List<T>::node_at(const size_t index) {
    
    node_ptr ptr = head;
    for (size_t i = 0; i < index; ++i) {
        ptr = ptr->next;
    }
    return ptr;
    
}

template<typename T>
const typename List<T>::node_ptr List<T>::node_at(const size_t index) const {
    
    node_ptr ptr = head;
    for (size_t i = 0; i < index; ++i) {
        ptr = ptr->next;
    }
    return ptr;
    
}

/* Utility */

template<typename T>
void List<T>::checkIndexRange(const size_t index) const {
    if (index >= len) {
        throw std::out_of_range("List index out of range.");
    }
}

/* Node insertion */

template<typename T>
List<T> & List<T>::push_back_node(node_ptr node) {
    if (head == nullptr) {
        head = node;
    }
    if (back) {
        back->next = node;
    }
    back = node;
    ++len;
    return *this;
}

template<typename T>
List<T> & List<T>::push_node(node_ptr node) {
    node_ptr first = head;
    if (head == nullptr) {
        back = node;
    }
    head = node;
    head->next = first;
    ++len;
    return *this;
}

template<typename T>
List<T> & List<T>::insert_node(const size_t index, node_ptr node) {
    
    checkIndexRange(index);
    if (index == len - 1) {
        return push_back_node(node);
    }
    if (index == 0) {
        return push_node(node);
    }
    
    node_ptr ptr = node_at(index - 1);
    node_ptr next = ptr->next;
    ptr->next = node;
    ptr->next->next = next;
    ++len;
    return *this;
    
}

/**********************/
/*       Public       */
/**********************/

/* Element access */

template<typename T>
T & List<T>::at(const size_t index) {
    checkIndexRange(index);
    return node_at(index)->item;
}

template<typename T>
T & List<T>::operator[](const size_t index) {
    return at(index);
}

template<typename T>
const T & List<T>::at(const size_t index) const {
    checkIndexRange(index);
    return node_at(index)->item;
}

template<typename T>
const T & List<T>::operator[](const size_t index) const {
    return at(index);
}

template<typename T>
T & List<T>::first() {
    
    if (head == nullptr) {
        throw std::out_of_range("Calling List<T>::first() on an empty List");
    }
    
    return head->item;
    
}

template<typename T>
const T & List<T>::first() const {
    
    if (head == nullptr) {
        throw std::out_of_range("Calling List<T>::first() on an empty List");
    }
    
    return head->item;
    
}

template<typename T>
T & List<T>::last() {
    
    if (back == nullptr) {
        throw std::out_of_range("Calling List<T>::last() on an empty List");
    }
    
    return back->item;
    
}

template<typename T>
const T & List<T>::last() const {
    
    if (back == nullptr) {
        throw std::out_of_range("Calling List<T>::last() on an empty List");
    }
    
    return back->item;
    
}

/* Item insertion */

template<typename T>
List<T> & List<T>::push_back(const T & item) {
    return push_back_node(new Node(item));
}

template<typename T>
List<T> & List<T>::push_back(T & item) {
    return push_back_node(new Node(item));
}

template<typename T>
List<T> & List<T>::push_back(T && item) {
    return push_back_node(new Node(item));
}

template<typename T>
template<typename... args>
List<T> & List<T>::push_back(args&... a) {
    return push_back_node(new Node(a...));
}

template<typename T>
template<typename... args>
List<T> & List<T>::push_back(args&&... a) {
    return push_back_node(new Node(a...));
}

template<typename T>
template<typename... args>
List<T> & List<T>::push_back(const args&... a) {
    return push_back_node(new Node(a...));
}

template<typename T>
List<T> & List<T>::push(const T & item) {
    return push_node(new Node(item));
}

template<typename T>
List<T> & List<T>::push(T & item) {
    return push_node(new Node(item));
}

template<typename T>
List<T> & List<T>::push(T && item) {
    return push_node(new Node(item));
}

template<typename T>
template<typename... args>
List<T> & List<T>::push(args&... a) {
    return push_node(new Node(a...));
}

template<typename T>
template<typename... args>
List<T> & List<T>::push(args&&... a) {
    return push_node(new Node(a...));
}

template<typename T>
template<typename... args>
List<T> & List<T>::push(const args&... a) {
    return push_node(new Node(a...));
}

template<typename T>
List<T> & List<T>::insert(const size_t index, const T & item) {
    return insert_node(index, new Node(item));
}

template<typename T>
List<T> & List<T>::insert(const size_t index, T & item) {
    return insert_node(index, new Node(item));
}

template<typename T>
List<T> & List<T>::insert(const size_t index, T && item) {
    return insert_node(index, new Node(item));
}

template<typename T>
template<typename... args>
List<T> & List<T>::insert(const size_t index, args&... a) {
    return insert_node(index, new Node(a...));
}

template<typename T>
template<typename... args>
List<T> & List<T>::insert(const size_t index, args&&... a) {
    return insert_node(index, new Node(a...));
}

template<typename T>
template<typename... args>
List<T> & List<T>::insert(const size_t index, const args&... a) {
    return insert_node(index, new Node(a...));
}

/* Item extraction */

template<typename T>
T List<T>::pop_front() {
    
    if (head == nullptr) {
        throw std::runtime_error("");
    }
    
    node_ptr temp = head;
    T retval(std::move(temp->item));
    head = head->next;
    --len;
    delete temp;
    
    if (head == nullptr) {
        back = nullptr;
    }
    
    return retval;
    
}

template<typename T>
T List<T>::pop_back() {
    
    if (head == nullptr) {
        throw std::runtime_error("");
    }
    if (len == 1) {
        return pop_front();
    }
    
    node_ptr ptr = node_at(len - 2);
    T retval(std::move(ptr->item));
    delete ptr->next;
    ptr->next = nullptr;
    back = ptr;
    --len;
    return retval;
    
}

template<typename T>
T List<T>::remove(const size_t index) {
    
    checkIndexRange(index);
    if (not index) {
        return pop_front();
    }
    if (index == len - 1) {
        return pop_back();
    }
    
    node_ptr ptr = node_at(index - 1);
    T retval(std::move(ptr->next->item));
    node_ptr next = ptr->next->next;
    delete ptr->next;
    ptr->next = next;
    --len;
    return retval;
    
}

/* List concatenation */

template<typename T>
List<T> List<T>::concatenate(const List<T> & l) const {
    List<T> copy = List<T>(*this);
    copy += l;
    return copy;
}

template<typename T>
List<T> List<T>::operator+(const List<T> & l) const {
    return concatenate(l);
}

template<typename T>
List<T> List<T>::concatenate(List<T> && l) const {
    List<T> copy = List<T>(*this);
    copy += l;
    return copy;
}

template<typename T>
List<T> List<T>::operator+(List<T> && l) const {
    return concatenate(l);
}

template<typename T>
List<T> & List<T>::append(const List<T> & l) {
    for (size_t i = 0; i < l.len; ++i) {
        push_back(l[i]);
    }
    return *this;
}

template<typename T>
List<T> & List<T>::operator+=(const List<T> & l) {
    return append(l);
}

template<typename T>
List<T> & List<T>::append(List<T> && l) {
    
    back->next = l.head;
    len += l.len;
    
    l.head = nullptr;
    l.len = 0;
    
    return *this;
    
}

template<typename T>
List<T> & List<T>::operator+=(List<T> && l) {
    return append(l);
}

/* Assignment */

template<typename T>
List<T> & List<T>::assign(const List<T> & l) {
    
    clear();
    for (size_t i = 0; i < l.len; ++i) {
        push_back(l[i]);
    }
    return *this;
    
}

template<typename T>
List<T> & List<T>::operator=(const List<T> & l) {
    return assign(l);
}

template<typename T>
List<T> & List<T>::assign(List<T> && l) {
    len = l.len;
    head = l.head;
    l.head = nullptr;
    l.len = 0;
    return *this;
}

template<typename T>
List<T> & List<T>::operator=(List<T> && l) {
    return assign(l);
}

/* Utility functions */

template<typename T>
size_t List<T>::size() const {
    return len;
}

template<typename T>
List<T> List<T>::map(std::function<T(const T&)> fun) const {
    
    List<T> l;
    
    for (size_t i = 0; i < len; ++i) {
        l.push_back(fun(at(i)));
    }
    
    return l;
    
}

template<typename T>
template<typename Acc>
Acc List<T>::fold(std::function<void(Acc & acc, const T&)> fun,
                  Acc initVal) const {
    
    for (size_t i = 0; i < len; ++i) {
        fun(initVal, at(i));
    }
    
    return initVal;
    
}

template<typename T>
List<T> List<T>::filter(std::function<bool(const T&)> fun) const {
    
    List<T> l;
    
    for (size_t i = 0; i < len; ++i) {
        
        const T & item = at(i);
        if (fun(item)) {
            l.push_back(item);
        }
        
    }
    
    return l;
    
}

template<typename T>
List<T> & List<T>::clear() {
    
    while(head != nullptr) {
        pop_front();
    }
    
    len = 0;
    
    return *this;
}

/* Constructors */

template<typename T>
List<T>::List() { }

template<typename T>
List<T>::List(const List<T> & orig) {
    assign(orig);
}

template<typename T>
List<T>::List(List<T> && orig) {
    assign(orig);
}

/* Destructor */

template<typename T>
List<T>::~List<T>() {
    clear();
}

#endif /* list_hpp */

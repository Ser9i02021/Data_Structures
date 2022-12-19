//! Copyright [2022] <Sergio Bonini>
#ifndef STRUCTURES_LINKED_LIST_H
#define STRUCTURES_LINKED_LIST_H

#include <cstdint>


namespace structures {

//! ...
template<typename T>
class LinkedList {
 public:
    //! ...
    LinkedList();  // construtor padrão
    //! ...
    ~LinkedList();  // destrutor
    //! ...
    void clear();  // limpar lista
    //! ...
    void push_back(const T& data);  // inserir no fim
    //! ...
    void push_front(const T& data);  // inserir no início
    //! ...
    void insert(const T& data, std::size_t index);  // inserir na posição
    //! ...
    void insert_sorted(const T& data);  // inserir em ordem
    //! ...
    T& at(std::size_t index);  // acessar um elemento na posição index
    //! ...
    T pop(std::size_t index);  // retirar da posição
    //! ...
    T pop_back();  // retirar do fim
    //! ...
    T pop_front();  // retirar do início
    //! ...
    void remove(const T& data);  // remover específico
    //! ...
    bool empty() const;  // lista vazia
    //! ...
    bool contains(const T& data) const;  // contém
    //! ...
    std::size_t find(const T& data) const;  // posição do dado
    //! ...
    std::size_t size() const;  // tamanho da lista

 private:
    class Node {  // Elemento
     public:
        explicit Node(const T& data):
            data_{data}
        {}

        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}

        T& data() {  // getter: dado
            return data_;
        }

        const T& data() const {  // getter const: dado
            return data_;
        }

        Node* next() {  // getter: próximo
            return next_;
        }

        const Node* next() const {  // getter const: próximo
            return next_;
        }

        void next(Node* node) {  // setter: próximo
            next_ = node;
        }

     private:
        T data_;
        Node* next_{nullptr};
    };

    Node* end() {  // último nodo da lista
        auto it = head;
        for (auto i = 1u; i < size(); ++i) {
            it = it->next();
        }
        return it;
    }

    Node* head{nullptr};
    std::size_t size_{0u};
};

}  // namespace structures

#endif

template<typename T>
structures::LinkedList<T>::LinkedList() {
    head = nullptr;
    size_ = 0;
}

template<typename T>
structures::LinkedList<T>::~LinkedList() {
    clear();
}

template<typename T>
void structures::LinkedList<T>::clear() {
    while (!empty()) {
        pop_front();
    }
}

template<typename T>
void structures::LinkedList<T>::push_back(const T& data) {
    if (empty()) {
        return push_front(data);
    }
    Node *novo = new Node(data);
    Node *p;
    p = head;
    while (p -> next() != nullptr) {
        p = p -> next();
    }
    p -> next(novo);
    size_++;
}

template<typename T>
void structures::LinkedList<T>::push_front(const T& data) {
    Node *novo = new Node(data);
    novo -> next(head);
    head = novo;
    size_++;
}

template<typename T>
void structures::LinkedList<T>::insert(const T& data, std::size_t index) {
    if (index > size_) {
        throw std::out_of_range("index inválido");
    }
    if (index == 0) {
        return push_front(data);
    } else if (index == size_) {
        return push_back(data);
    } else {
        Node *novo = new Node(data);
        Node *p = head;
        for (int i = 1; i < static_cast<int>(index); i++) {
            p = p -> next();
        }
        novo -> next(p -> next());
        p -> next(novo);
        size_++;
    }
}

template<typename T>
void structures::LinkedList<T>::insert_sorted(const T& data) {
    if (empty()) {
        return push_front(data);
    }
    Node *p = head;
    if (data <= p -> data()) {
        return push_front(data);
    }
    p = p -> next();
    Node *novo = new Node(data);
    Node *q = head;
    while (p != nullptr && data > p -> data()) {
        q = q -> next();
        p = p -> next();
    }
    novo -> next(q -> next());
    q -> next(novo);
    size_++;
}

template<typename T>
T& structures::LinkedList<T>::at(std::size_t index) {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    }
    if (index > size_) {
        throw std::out_of_range("index inválido");
    }
    Node *p = head;
    if (index == 0) {
        return p -> data();
    }
    p = p -> next();
    for (int i = 1; i < static_cast<int>(index); i++) {
        p = p -> next();
    }
    return p -> data();
}

template<typename T>
T structures::LinkedList<T>::pop(std::size_t index) {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    }
    if (index > size_ - 1) {
        throw std::out_of_range("index inválido");
    }
    if (index == 0) {
        return pop_front();
    }
    if (index == size_ - 1) {
        return pop_back();
    }
    Node *p = head;
    Node *aux;
    for (int i = 1; i < static_cast<int>(index); i++) {
        p = p -> next();
    }
    aux = p -> next();
    T saida = aux -> data();
    p -> next(aux -> next());
    delete aux;
    size_--;
    return saida;
}

template<typename T>
T structures::LinkedList<T>::pop_back() {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    }
    if (size_ == 1) {
        return pop_front();
    }
    Node *p = head;
    Node *aux;
    for (int i = 1; i < static_cast<int>(size_) - 1; i++) {
        p = p -> next();
    }
    T saida;
    aux = p -> next();
    saida = aux -> data();
    delete aux;
    p -> next(nullptr);
    size_--;
    return saida;
}

template<typename T>
T structures::LinkedList<T>::pop_front() {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    }
    Node *p = head;
    head = p -> next();
    T saida;
    saida = p -> data();
    delete p;
    size_--;
    return saida;
}

template<typename T>
void structures::LinkedList<T>::remove(const T& data) {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    }
    Node *p = head;
    for (int i = 0; i < static_cast<int>(size_); i++) {
        if (p -> data() == data) {
            pop(i);
            break;
        }
        p = p -> next();
    }
}

template<typename T>
bool structures::LinkedList<T>::empty() const {
    return (size_ == 0);
}

template<typename T>
bool structures::LinkedList<T>::contains(const T& data) const {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    }
    Node *p = head;
    for (int i = 0; i < static_cast<int>(size_); i++) {
        if (p -> data() == data) {
            return true;
        }
        p = p -> next();
    }
    return false;
}

template<typename T>
std::size_t structures::LinkedList<T>::find(const T& data) const {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    }
    Node *p = head;
    for (int i = 0; i < static_cast<int>(size_); i++) {
        if (p -> data() == data) {
            return i;
        }
        p = p -> next();
    }
    return size_;
}

template<typename T>
std::size_t structures::LinkedList<T>::size() const {
    return size_;
}




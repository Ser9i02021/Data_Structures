//! Copyright [2022] <Sergio Bonini>
namespace structures {

template<typename T>
class DoublyLinkedList {
 public:
    DoublyLinkedList();
    ~DoublyLinkedList();
    void clear();

    void push_back(const T& data);  // insere no fim
    void push_front(const T& data);  // insere no início
    void insert(const T& data, std::size_t index);  // insere na posição
    void insert_sorted(const T& data);  // insere em ordem

    T pop(std::size_t index);  // retira da posição
    T pop_back();  // retira do fim
    T pop_front();  // retira do início
    void remove(const T& data);  // retira específico

    bool empty() const;  // lista vazia
    bool contains(const T& data) const;  // contém

    T& at(std::size_t index);  // acesso a um elemento (checando limites)
    const T& at(std::size_t index) const;  // getter constante a um elemento

    std::size_t find(const T& data) const;  // posição de um dado
    std::size_t size() const;  // tamanho

 private:
    class Node {  // implementar cada um dos métodos de Node
     public:
        explicit Node(const T& data) {
            data_ = data;
        }
        Node(const T& data, Node* next) {
            data_ = data;
            next_ = next;
        }
        Node(const T& data, Node* prev, Node* next) {
            data_ = data;
            prev_ = prev;
            next_ = next;
        }

        T& data() {
            return data_;
        }
        const T& data() const {
            return data_;
        }

        Node* prev() {
            return prev_;
        }
        const Node* prev() const {
            return prev_;
        }

        void prev(Node* node) {
            prev_ = node;
        }

        Node* next() {
            return next_;
        }
        const Node* next() const {
            return next_;
        }

        void next(Node* node) {
            next_ = node;
        }

     private:
        T data_;
        Node* prev_;
        Node* next_;
    };

    Node* head;  // primeiro da lista
    Node* tail;  // ultimo da lista
    std::size_t size_;
};

}  // namespace structures

template<typename T>
structures::DoublyLinkedList<T>::DoublyLinkedList() {
    head = nullptr;
    tail = nullptr;
    size_ = 0;
}

template<typename T>
structures::DoublyLinkedList<T>::~DoublyLinkedList() {
    clear();
}

template<typename T>
void structures::DoublyLinkedList<T>::clear() {
    while (!empty()) {
        pop_front();
    }
}

template<typename T>
void structures::DoublyLinkedList<T>::push_back(const T& data) {
    if (empty()) {
        return push_front(data);
    }
    Node *novo = new Node(data);
    novo -> prev(tail);
    tail -> next(novo);
    tail = novo;
    size_++;
}

template<typename T>
void structures::DoublyLinkedList<T>::push_front(const T& data) {
    Node *novo = new Node(data);
    novo -> prev(nullptr);
    novo -> next(head);
    if (empty()) {
        tail = novo;
    } else {
        head -> prev(novo);
    }
    head = novo;
    size_++;
}

template<typename T>
void structures::DoublyLinkedList<T>::insert(const T& data, std::size_t index) {
    if (index > size_) {
        throw std::out_of_range("index inválido");
    }
    if (index == 0) {
        return push_front(data);
    } else if (index == size_ - 1) {
        return push_back(data);
    } else {
        Node *novo = new Node(data);
        Node *p;
        if (index < size_ / 2) {
            p = head;
            for (int i = 1; i < static_cast<int>(index); i++) {
                p = p -> next();
            }
        } else {
            p = tail;
            for (auto i = size_ - 1; i >= index; i--) {
                p = p -> prev();
            }
        }
        novo -> next(p -> next());
        novo -> prev(p);
        (novo -> next()) -> prev(novo);
        p -> next(novo);
        size_++;
    }
}

template<typename T>
void structures::DoublyLinkedList<T>::insert_sorted(const T& data) {
    if (empty()) {
        return push_front(data);
    }
    Node *p = head;
    if (data <= p -> data()) {
        return push_front(data);
    }
    p = p -> next();
    int i = 1;
    while (p != nullptr && data > p -> data()) {
        p = p -> next();
    }
    return insert(data, i);
}

template<typename T>
T structures::DoublyLinkedList<T>::pop(std::size_t index) {
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
    Node *p;
    if (index < size_ / 2) {
        p = head;
        for (int i = 1; i <= static_cast<int>(index); i++) {
            p = p -> next();
        }
    } else {
        p = tail;
        for (auto i = size_ - 1; i > index; i--) {
            p = p -> prev();
        }
    }
    (p -> prev()) -> next(p -> next());
    (p -> next()) -> prev(p -> prev());
    T saida = p -> data();
    delete p;
    size_--;
    return saida;
}

template<typename T>
T structures::DoublyLinkedList<T>::pop_back() {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    }
    if (size_ == 1) {
        return pop_front();
    }
    Node *p = tail;
    T saida = p -> data();
    tail = p -> prev();
    tail -> next(nullptr);
    delete p;
    size_--;
    return saida;
}

template<typename T>
T structures::DoublyLinkedList<T>::pop_front() {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    }
    Node *p = head;
    T saida = p -> data();
    if (static_cast<int>(size_) == 1) {
        head = nullptr;
        tail = nullptr;
    } else {
        (p -> next()) -> prev(nullptr);
        head = p -> next();
    }
    delete p;
    size_--;
    return saida;
}

template<typename T>
void structures::DoublyLinkedList<T>::remove(const T& data) {
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
bool structures::DoublyLinkedList<T>::empty() const {
    return (size_ == 0);
}

template<typename T>
bool structures::DoublyLinkedList<T>::contains(const T& data) const {
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
T& structures::DoublyLinkedList<T>::at(std::size_t index) {
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
    if (index == size_ - 1) {
        p = tail;
        return p -> data();
    }
    if (index < size_ / 2) {
        p = p -> next();
        for (int i = 1; i < static_cast<int>(index); i++) {
            p = p -> next();
        }
    } else {
        p = tail;
        for (auto i = size_ - 1; i > index; i--) {
            p = p -> prev();
        }
    }
    return p -> data();
}

template<typename T>
const T& structures::DoublyLinkedList<T>::at(std::size_t index) const {
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
    if (index == size_ - 1) {
        p = tail;
        return p -> data();
    }
    if (index < size_ / 2) {
        p = p -> next();
        for (int i = 1; i < static_cast<int>(index); i++) {
            p = p -> next();
        }
    } else {
        p = tail;
        for (auto i = size_ - 1; i > index; i--) {
            p = p -> prev();
        }
    }
    return p -> data();
}

template<typename T>
std::size_t structures::DoublyLinkedList<T>::find(const T& data) const {
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
std::size_t structures::DoublyLinkedList<T>::size() const {
    return size_;
}



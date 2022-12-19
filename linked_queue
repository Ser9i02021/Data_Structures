//! Copyright [2022] <Rondinelly Martins Silva>

namespace structures {


template<typename T>
class LinkedQueue {
 public:
    LinkedQueue();
    ~LinkedQueue();
    void clear();  // limpar
    void enqueue(const T& data);  // enfilerar
    T dequeue();  // desenfilerar
    T& front() const;  // primeiro dado
    T& back() const;  // último dado
    bool empty() const;  // fila vazia
    std::size_t size() const;  // tamanho

 private:
    class Node{  // Elemento
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
        void next(Node* node) {
            next_ = node;
        }

     private:
        T data_;
        Node* next_{nullptr};
    };
    Node* end() {  // último nodo da lista
        auto it = head;
        for (auto i = 1u; i < size();  ++i) {
            it = it->next();
        }
        return it;
    }
    Node* head;  // nodo-cabeça
    Node* tail;  // nodo-fim
    std::size_t size_;  // tamanho
};

}  // namespace structures

template<typename T>  // construtor
structures::LinkedQueue<T>::LinkedQueue() {
    head = nullptr;
    tail = nullptr;
    size_ = 0;
}

template<typename T>  // destrutor
structures::LinkedQueue<T>::~LinkedQueue() {
    Node* temporario;
    while (head != nullptr) {
        temporario = head;
        head = head->next();
        delete temporario;
        size_--;
    }
    tail = nullptr;
}

template<typename T>
void structures::LinkedQueue<T>::clear() {
    Node* temp;
    while (head != nullptr) {
        temp = head;
        head = head->next();
        delete temp;
        size_--;
    }
    if (tail != nullptr) {
        tail = nullptr;
    }
}

template<typename T>
void structures::LinkedQueue<T>::enqueue(const T& data) {
    Node* novoitem;
    novoitem = new Node(data);
    if (empty()) {
        head = novoitem;
    } else {
        tail->next(novoitem);
    }
    tail = novoitem;
    size_++;
}

template<typename T>
T structures::LinkedQueue<T>::dequeue() {
    if (empty()) {
        throw std::out_of_range("Fila vazia");
    } else {
        Node* temp;
        T aux;
        temp = head;
        aux = temp->data();
        head = head->next();
        size_--;
        delete temp;
        if (head == nullptr) {
            tail = nullptr;
        }
        return aux;
    }
}

template<typename T>
T& structures::LinkedQueue<T>::front() const {
    if (!empty()) {
    return head->data();
    } else {
        throw std::out_of_range("Fila vazia");
    }
}

template<typename T>
T&structures::LinkedQueue<T>::back() const {
    if (!empty()) {
    return tail->data();
    } else {
        throw std::out_of_range("Fila vazia");
    }
}

template<typename T>
bool structures::LinkedQueue<T>::empty() const {
    return (head == nullptr && tail == nullptr);
}

template<typename T>
std::size_t structures::LinkedQueue<T>::size() const {
    return size_;
}

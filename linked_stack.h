//! Copyright [2022] <Rondinelly Martins Silva>

namespace structures {

template<typename T>
class LinkedStack {
 public:
        LinkedStack();
        ~LinkedStack();
        void clear();  // limpa pilha
        void push(const T& data);  // empilha
        T pop();  // desempilha
        T& top() const;  // dado no topo
        bool empty() const;  // pilha vazia
        std::size_t size() const;  // tamanho da pilha

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
    T* contents;
};
}  // namespace structures

template<typename T>  // construtor padrao
structures::LinkedStack<T>::LinkedStack() {
    head = NULL;  // head aponta para nulo
    size_ = 0;
}

template<typename T>  // destrutor
structures::LinkedStack<T>::~LinkedStack() {
    Node* temporario;  // define um node temporario
    while (head != NULL) {  // enquanto head nao apontar para nulo
                            // enquanto ainda tiver algum item na pilha
        temporario = head;  // node temporario aponta para o topo da pilha
        head = head->next();  // head aponta para o proximo da pilha
        delete temporario;  // retira o elemento do topo da pilha
    }
}

template<typename T>  // limpa pilha
void structures::LinkedStack<T>::clear() {
    if (empty()) {
        throw std::out_of_range("Pilha vazia");
    } else {
        while (head != NULL) {
            Node* temp;  // instacia ponteiro tipo node
            temp = head;  // temp aponta para o elemento do topo
            head = head->next();  // head aponta para o proximo elemento
            size_--;  // decrementa size_
            delete temp;  // deleta o nó
        }
    }
}

template<typename T>  // empilha
void structures::LinkedStack<T>::push(const T& data) {
    Node* novoitem;  // define node novoitem
    novoitem = new Node(data);  // aloca memoria dinamicamente
                                // node->data recebe data
    //  novoitem->data() = data;
    novoitem->next(head);  // o ponteiro next de novoitem aponta para head
    head = novoitem;  //
    size_++;
}

template<typename T>  // desempilha
T structures::LinkedStack<T>::pop() {
    if (empty()) {
        throw std::out_of_range("Pilha vazia");
    } else {
        Node* retorna;  // cria poteiro tipo node
        retorna = head;  // faz esse poteiro apontar para o topo da pilha
        head = head->next();  // o topo da pilha aponta para quem esta em baixo
        size_--;  // decrementa size
        return retorna->data();
    }
}

template<typename T>  // dado no topo
T& structures::LinkedStack<T>::top() const {
    if (empty()) {
        throw std::out_of_range("Pilha vazia");
    } else {
        return head->data();
    }
}


template<typename T>  // pilha vazia
bool structures::LinkedStack<T>::empty() const {
    return (head == NULL);
}

template<typename T>  // tamanho da pilha
std::size_t structures::LinkedStack<T>::size() const {
    return size_;
}

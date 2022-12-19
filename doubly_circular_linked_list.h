//! Copyright [2022] <Sergio Bonini>
namespace structures {

template<typename T>
class DoublyCircularList {
 public:
    DoublyCircularList();
    ~DoublyCircularList();

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
    class Node {
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

    Node* head;
    std::size_t size_;
};

}  // namespace structures

template<typename T>  // Construtor
structures::DoublyCircularList<T>::DoublyCircularList() {
    head = nullptr;
    size_ = 0;
}

template<typename T>  // Destrutor
structures::DoublyCircularList<T>::~DoublyCircularList() {
    clear();
}

template<typename T>  // Esvaziador
void structures::DoublyCircularList<T>::clear() {
    while (!empty()) {
        pop_front();
    }
}

template<typename T>  // Insere no fim
void structures::DoublyCircularList<T>::push_back(const T &data) {
    Node *novo = new Node(data);
    if (empty()) {
        novo->next(novo);
        novo->prev(novo);
        head = novo;
    } else {
        novo->next(head);
        head->prev(novo);
        novo->prev(head->prev());
        (head->prev())->next(novo);
    }
    size_++;
}

template<typename T>  // Insere no início
void structures::DoublyCircularList<T>::push_front(const T &data) {
    Node *novo = new Node(data);
    if (empty()) {
        head = novo;
        novo->prev(novo);
        novo->next(novo);
    } else {
        novo->prev(head->prev());
        novo->next(head);
        head->prev(novo);
        (head->prev())->next(novo);
        head = novo;
    }
    size_++;
}

template<typename T>  // Insere em certa posição
void structures::DoublyCircularList<T>::insert(const T &data, std::size_t index) {
    if (index < 0) {
        throw std::out_of_range("Index inválido");
    }
    if (index == 0) {
        return push_front(data);
    }
    if (index == size()) {
        return push_back(data);
    }
    Node *p;
    Node *novo = new Node(data);
    if (index < size()/2) {
        p = head->next();
        for (int i = 1; i <= static_cast<int>(index); i++) {
            p = p->next();
        }
    } else {
        p = head->prev();
        for (int i = size() - 1; i <= static_cast<int>(index); i--) {
            p = p->prev();
        }
    }
    (p->prev())->next(novo);
    novo->prev(p->prev());
    novo->next(p);
    p->prev(novo);
    size_++;
}

template<typename T>  // Insere ordenadamente
void structures::DoublyCircularList<T>::insert_sorted(const T &data) {
    if (empty()) {
        return push_front(data);
    }
    Node *novo = new Node(data);
    novo = head;
    int i = 0;
    while (data > novo->data()) {
        i++;
        if (novo->next() != nullptr) {
            break;
        }
        novo = novo->next();
    }
    return insert(data, i);
}

template<typename T>  // Retira de um certo index
T structures::DoublyCircularList<T>::pop(std::size_t index) {
    if (index < 0) {
        throw std::out_of_range("Index inválido");
    }
    if (index == 0) {
        return pop_front();
    }
    if (index == size() - 1) {
        return pop_back();
    }
    Node *p;
    if (index < size()/2) {
        p = head->next();
        for (int i = 1; i <= static_cast<int>(index); i++) {
            p = p->next();
        }
    } else {
        p = head->prev();
        for (int i = size() - 1; i <= static_cast<int>(index); i--) {
            p = p->prev();
        }
    }
    T aux;
    aux = p->data();
    (p->prev())->next(p->next());
    (p->next())->prev(p->prev());
    delete p;
    size_--;
    return aux;
}

template<typename T>  // Retira do fim
T structures::DoublyCircularList<T>::pop_back() {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    }
    Node *p;
    p = head->prev();
    T aux;
    aux = p->data();
    (p->prev())->next(p->next());
    (p->next())->prev(p->prev());
    delete p;
    size_--;
    return aux;
}

template<typename T>  // Retira do início
T structures::DoublyCircularList<T>::pop_front() {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    }
    Node *p;
    p = head;
    T aux;
    aux = p->data();
    (p->prev())->next(p->next());
    (p->next())->prev(p->prev());
    delete p;
    size_--;
    return aux;
}

template<typename T>  // Remove elemento
void structures::DoublyCircularList<T>::remove(const T &data) {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    }
    bool not_found = false;
    Node *p;
    p = head;
    int i = 0;
    while (p->data() != data) {
        i++;
        if (p->next() != nullptr) {
            not_found = true;
            break;
        }
        p = p->next();
    }
    if (!not_found) {
        pop(i);
    }
}

template<typename T>  // Verifica se a lista está vazia
bool structures::DoublyCircularList<T>::empty() const {
    return (size() == 0);
}

template<typename T>  // Verifica se a lista contém o dado fornecido
bool structures::DoublyCircularList<T>::contains(const T& data) const {
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

template<typename T>  // Retorna o elemento do index fornecido
T& structures::DoublyCircularList<T>::at(std::size_t index) {
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
        p = p->prev();
        return p -> data();
    }
    if (index < size_ / 2) {
        p = p -> next();
        for (int i = 1; i < static_cast<int>(index); i++) {
            p = p -> next();
        }
    } else {
        p = p->prev();
        for (auto i = size_ - 1; i > index; i--) {
            p = p -> prev();
        }
    }
    return p -> data();
}

template<typename T>  // Retorna o elemento do index fornecido
const T& structures::DoublyCircularList<T>::at(size_t index) const {
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
        p = p->prev();
        return p -> data();
    }
    if (index < size_ / 2) {
        p = p -> next();
        for (int i = 1; i < static_cast<int>(index); i++) {
            p = p -> next();
        }
    } else {
        p = p->prev();
        for (auto i = size_ - 1; i > index; i--) {
            p = p -> prev();
        }
    }
    return p -> data();
}

template<typename T>  // Retorna a posição do dado
std::size_t structures::DoublyCircularList<T>::find(const T& data) const {
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

template<typename T>  // Retorna o tamanho da lista
std::size_t structures::DoublyCircularList<T>::size() const {
    return size_;
}


#include <iostream>

template <typename Tnode>
class List {
private:
    template <typename Tvalue>
    struct Node {
        Tvalue value;
        Node *R;
        Node(Tvalue v = Tvalue(), Node *R = nullptr) : value(v), R(R) {}
    };
    std::size_t len;

public:
    struct list_iterator {
        Node<Tnode> *elem;
        list_iterator(Node<Tnode> *elem = nullptr) : elem(elem) {}

        Tnode &operator*() {
            return elem->value;
        }
        list_iterator &operator++() {
            elem = elem->R;
            return *this;
        }
        list_iterator operator++(int) {
            list_iterator tmp = *this;
            elem = elem->R;
            return tmp;
        }
        Node<Tnode> *operator->() {
            return elem;
        }
        bool operator!=(const list_iterator &other) const {
            return elem != other.elem;
        }
        bool operator==(const list_iterator &other) const {
            return elem == other.elem;
        }
    };
    list_iterator first, last;
    List() : first(new Node<Tnode>()), len(0) {
        last = first;
    }
    List<Tnode>::list_iterator begin() const {
        return first;
    }
    List<Tnode>::list_iterator end() const {
        return last;
    }
    std::size_t size() const {
        return len;
    }

    void push_back(int x) {
        last->value = x;
        Node<Tnode> *elem = new Node<Tnode>();
        last->R = elem;
        ++last;
        ++len;
    }
    ~List() {
        while (first != nullptr) {
            list_iterator tmp = first++;
            delete tmp.elem;
        }
        delete last.elem;
    }
};

template <typename Iter>
Iter merge(Iter a, Iter b) {
    Iter st = nullptr, pref = nullptr;
    while (a != nullptr || b != nullptr) {
        if (b == nullptr || (a != nullptr && *a < *b)) {
            if (st == nullptr) {
                st = a;
            } else {
                pref->R = a.elem;
            }
            pref = a;
            ++a;
        } else {
            if (st == nullptr) {
                st = b;
            } else {
                pref->R = b.elem;
            }
            pref = b;
            ++b;
        }
    }
    return st;
}

template <typename Iter>
Iter _merge_sort(Iter L, Iter R, int len) {
    if (len == 1) {
        L->R = nullptr;
        return L;
    }
    auto M = L;
    for (int i = 0; i < len / 2; ++i)
        ++M;
    Iter a = _merge_sort(L, M, len / 2);
    Iter b = _merge_sort(M, R, (len + 1) / 2);
    return merge(a, b);
}

template <typename Iter>
Iter merge_sort(const Iter& s, const Iter& f) {
    int len = 0;
    Iter a = s;
    while (a != f) {
        ++a;
        ++len;
    }
    return _merge_sort(s, f, len);
}

int main() {
    int n;
    std::cin >> n;
    List<int> lst;
    for (int i = 0; i < n; ++i) {
        int a;
        std::cin >> a;
        lst.push_back(a);
    }
    auto ind = merge_sort(lst.begin(), lst.end());
    lst.first = ind;
    while (ind.elem != nullptr) {
        std::cout << ind->value << ' ';
        ++ind;
    }
    return 0;
}

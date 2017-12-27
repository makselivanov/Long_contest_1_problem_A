#include<iostream>

class List {
private:
    struct Node {
        int value;
        Node *R;
        Node(int v = 0, Node *R = nullptr) : value(v), R(R) {}
    };
    std::size_t len;

public:
    struct list_iterator {
        Node *elem;
        list_iterator(Node *elem = nullptr) : elem(elem) {}

        int &operator*() {
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
        Node *operator->() {
            return elem;
        }
        bool operator!=(const list_iterator &other) const {
            return elem != other.elem;
        }
    };
    list_iterator first, last;
    List() : first(new Node()), len(0) {
        last = first;
    }
    list_iterator begin() {
        return first;
    }
    list_iterator end() {
        return last;
    }
    std::size_t size() {
        return len;
    }

    void push_back(int x) {
        last->value = x;
        Node *elem = new Node(0);
        last->R = elem;
        ++last;
        ++len;
    }
    ~List() {
        while (first != last) {
            list_iterator tmp = first++;
            delete (tmp.elem);
        }
        delete (last.elem);
    }
};

void merge_sort(List::list_iterator L, List::list_iterator R, int len) {
    if (len == 1)
        return;
    int cnt = len / 2;
    auto M = L;
    for (int i = 0; i < cnt - 1; ++i)
        ++M;
    merge_sort(L, M, cnt);
    merge_sort(M->R, R, len - cnt);
    int vec[len];
    int indL = 0, indR = 0;
    List::list_iterator LL = L, RR = M->R;
    while (indL < cnt || indR < len - cnt) {
        if (indR == len - cnt || (indL < cnt && *LL < *RR)) {
            vec[indL + indR] = *LL;
            ++LL;
            ++indL;
        } else {
            vec[indL + indR] = *RR;
            ++RR;
            ++indR;
        }
    }
    M = L;
    for (int i = 0; i < len; ++i, ++M) {
        *M = vec[i];
    }
}

int main() {
    int n;
    std::cin >> n;
    List lst;
    for (int i = 0; i < n; ++i) {
        int a;
        std::cin >> a;
        lst.push_back(a);
    }
    merge_sort(lst.begin(), lst.end(), n);
    auto ind = lst.begin();
    while (ind != lst.end()) {
        std::cout << ind->value << ' ';
        ++ind;
    }
}

#ifndef TDOUBLY_LIST_H
#define TDOUBLY_LIST_H

#include <stdexcept>
#include <utility>
#include <vector>
#include <iostream> // <-- ДОБАВЛЕНО для std::cout в Print()

template<typename T>
class TDoublyList {
    struct TNode {
        T value;
        TNode* pNext;
        TNode* pPrev;
    };

    TNode* pFirst;
    TNode* pLast;
    size_t sz;

public:
    TDoublyList() : pFirst(nullptr), pLast(nullptr), sz(0) {}

    TDoublyList(const std::vector<T>& v) : pFirst(nullptr), pLast(nullptr), sz(0) {
        for (size_t i = 0; i < v.size(); ++i) {
            PushBack(v[i]);
        }
    }

    TDoublyList(const TDoublyList& list) : pFirst(nullptr), pLast(nullptr), sz(list.sz) {
        if (list.pFirst == nullptr) return;

        pFirst = new TNode{ list.pFirst->value, nullptr, nullptr };
        TNode* pCurrent = pFirst;
        TNode* pOther = list.pFirst->pNext;

        while (pOther != nullptr) {
            pCurrent->pNext = new TNode{ pOther->value, nullptr, pCurrent };
            pCurrent = pCurrent->pNext;
            pOther = pOther->pNext;
        }
        pLast = pCurrent;
    }

    TDoublyList(TDoublyList&& list) noexcept
        : pFirst(list.pFirst), pLast(list.pLast), sz(list.sz) {
        list.pFirst = nullptr;
        list.pLast = nullptr;
        list.sz = 0;
    }

    TDoublyList& operator=(const TDoublyList& list) {
        if (this != &list) {
            TDoublyList tmp(list);
            Swap(tmp);
        }
        return *this;
    }

    TDoublyList& operator=(TDoublyList&& list) noexcept {
        if (this != &list) {
            Clear();
            pFirst = list.pFirst;
            pLast = list.pLast;
            sz = list.sz;

            list.pFirst = nullptr;
            list.pLast = nullptr;
            list.sz = 0;
        }
        return *this;
    }

    ~TDoublyList() {
        Clear();
    }

    void Clear() {
        TNode* p = pFirst;
        while (p != nullptr) {
            TNode* pNext = p->pNext;
            delete p;
            p = pNext;
        }
        pFirst = nullptr;
        pLast = nullptr;
        sz = 0;
    }

    void Swap(TDoublyList& other) noexcept {
        std::swap(pFirst, other.pFirst);
        std::swap(pLast, other.pLast);
        std::swap(sz, other.sz);
    }

    void PushFront(const T& value) {
        TNode* pNew = new TNode{ value, pFirst, nullptr };
        if (pFirst != nullptr) {
            pFirst->pPrev = pNew;
        }
        else {
            pLast = pNew;
        }
        pFirst = pNew;
        sz++;
    }

    void PushBack(const T& value) {
        TNode* pNew = new TNode{ value, nullptr, pLast };
        if (pLast != nullptr) {
            pLast->pNext = pNew;
        }
        else {
            pFirst = pNew;
        }
        pLast = pNew;
        sz++;
    }

    void PopFront() {
        if (sz == 0) {
            throw std::out_of_range("List is empty");
        }

        TNode* pToDelete = pFirst;
        pFirst = pFirst->pNext;

        if (pFirst != nullptr) {
            pFirst->pPrev = nullptr;
        }
        else {
            pLast = nullptr;
        }

        delete pToDelete;
        sz--;
    }

    void PopBack() {
        if (sz == 0) {
            throw std::out_of_range("List is empty");
        }

        TNode* pToDelete = pLast;
        pLast = pLast->pPrev;

        if (pLast != nullptr) {
            pLast->pNext = nullptr;
        }
        else {
            pFirst = nullptr;
        }

        delete pToDelete;
        sz--;
    }

    bool Remove(const T& value) {
        TNode* pCurrent = pFirst;

        while (pCurrent != nullptr && pCurrent->value != value) {
            pCurrent = pCurrent->pNext;
        }

        if (pCurrent == nullptr) {
            return false;
        }

        if (pCurrent->pPrev != nullptr) {
            pCurrent->pPrev->pNext = pCurrent->pNext;
        }
        else {
            pFirst = pCurrent->pNext;
        }

        if (pCurrent->pNext != nullptr) {
            pCurrent->pNext->pPrev = pCurrent->pPrev;
        }
        else {
            pLast = pCurrent->pPrev;
        }

        delete pCurrent;
        sz--;
        return true;
    }

    void Erase(size_t index) {
        if (index >= sz) {
            throw std::out_of_range("Index out of range");
        }

        TNode* pCurrent = nullptr;
        if (index < sz / 2) {
            pCurrent = pFirst;
            for (size_t i = 0; i < index; ++i) {
                pCurrent = pCurrent->pNext;
            }
        }
        else {
            pCurrent = pLast;
            for (size_t i = sz - 1; i > index; --i) {
                pCurrent = pCurrent->pPrev;
            }
        }

        if (pCurrent->pPrev != nullptr) {
            pCurrent->pPrev->pNext = pCurrent->pNext;
        }
        else {
            pFirst = pCurrent->pNext;
        }

        if (pCurrent->pNext != nullptr) {
            pCurrent->pNext->pPrev = pCurrent->pPrev;
        }
        else {
            pLast = pCurrent->pPrev;
        }

        delete pCurrent;
        sz--;
    }

    // ==========================================
    // ДОБАВЛЕННЫЕ МЕТОДЫ ДЛЯ РАБОТЫ ОЧЕРЕДИ
    // ==========================================

    T& Front() {
        if (sz == 0) throw std::out_of_range("List is empty");
        return pFirst->value;
    }

    T& Back() {
        if (sz == 0) throw std::out_of_range("List is empty");
        return pLast->value;
    }

    bool IsEmpty() const {
        return sz == 0;
    }

    size_t Size() const {
        return sz;
    }

    // Для удобства проверки (вывод списка)
    void Print() const {
        TNode* p = pFirst;
        while (p != nullptr) {
            std::cout << p->value << " <-> ";
            p = p->pNext;
        }
        std::cout << "nullptr\n";
    }
};
#endif // TDOUBLY_LIST_H

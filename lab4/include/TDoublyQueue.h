#ifndef TDOUBLY_QUEUE_H
#define TDOUBLY_QUEUE_H

#include "TDoublyList.h"

template<typename T>
class TDoublyQueue {
private:
    TDoublyList<T> list; // Используем нашу структуру как хранилище

public:
    // Конструктор по умолчанию
    TDoublyQueue() = default;

    // Добавление в конец (как в обычной очереди)
    void PushBack(const T& value) {
        list.PushBack(value);
    }

    // Добавление в начало
    void PushFront(const T& value) {
        list.PushFront(value);
    }

    // Извлечение из начала (как в обычной очереди)
    T PopFront() {
        T val = list.Front();
        list.PopFront();
        return val;
    }

    // Извлечение с конца
    T PopBack() {
        T val = list.Back();
        list.PopBack();
        return val;
    }

    // Просмотр первого элемента (без извлечения)
    T& Front() {
        return list.Front();
    }

    // Просмотр последнего элемента (без извлечения)
    T& Back() {
        return list.Back();
    }

    // Проверка на пустоту
    bool IsEmpty() const {
        return list.IsEmpty();
    }

    // Получить размер
    size_t Size() const {
        return list.Size();
    }

    // Очистка
    void Clear() {
        list.Clear();
    }
};

#endif // TDOUBLY_QUEUE_H
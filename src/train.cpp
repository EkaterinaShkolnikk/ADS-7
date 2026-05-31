// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() : first(nullptr), countOp(0) {}


void Train::addCar(bool light) {
    Car* newCar  = new Car;
    newCar->light = light;
    newCar->next  = nullptr;
    newCar->prev  = nullptr;

    if (!first) {
        first = newCar;
        first->next = newCar;
        first->prev = newCar;
    } else {
        // Вставляем перед first (т.е. в «хвост» кольца)
        Car* tail    = first->prev;
        tail->next   = newCar;
        newCar->prev = tail;
        newCar->next = first;
        first->prev  = newCar;
    }
}

int Train::getLength() {
    Car* cur = first;
 
    // Включаем маяк (он мог быть выключен изначально)
    cur->light = true;

    int count = 1;

    while (true) {
        cur = cur->next;
        countOp++;

        if (!cur->light) {
            count++;
        } else {
            // Нашли включённый вагон: выключаем
            cur->light = false;

            // Возвращаемся назад на count шагов
            for (int i = 0; i < count; i++) {
                cur = cur->prev;
                countOp++;
            }

            if (!cur->light) {
                // Вернулись к выключенному маяку — count и есть длина поезда
                return count;
            } else {
                // Маяк ещё горит — продолжаем движение
                count = 1;
            }
        }
    }
}
int Train::getOpCount() {
    return countOp;
}

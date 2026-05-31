// Copyright 2022 NNTU-CS
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "train.h"
 

int measureOps(int n, int mode) {
    Train train;
    for (int i = 0; i < n; i++) {
        bool state;
        if      (mode == 0) state = false;
        else if (mode == 1) state = true;
        else                state = (rand() % 2 == 0);
        train.addCar(state);
    }
    train.getLength();
    return train.getOpCount();
}
 
int main() {
    srand(static_cast<unsigned>(time(nullptr)));
 

    {
        Train t;
        for (int i = 0; i < 60; i++) t.addCar(false);
        std::cout << "Длина поезда (ожидается 60): " << t.getLength() << std::endl;
        std::cout << "Число шагов: "                 << t.getOpCount() << std::endl;
    }
 

    std::ofstream csv("result/data.csv");
    csv << "n,ops_off,ops_on,ops_rand\n";
 
    const int STEP    =  5;
    const int MAX_N   = 200;
    const int REPEATS =  7;   
 
    for (int n = 2; n <= MAX_N; n += STEP) {
        int ops_off = measureOps(n, 0);
        int ops_on  = measureOps(n, 1);
 
        long long sum = 0;
        for (int r = 0; r < REPEATS; r++) sum += measureOps(n, 2);
        int ops_rand = static_cast<int>(sum / REPEATS);
 
        csv << n << "," << ops_off << "," << ops_on << "," << ops_rand << "\n";
    }
 
    csv.close();
    std::cout << "Данные записаны в result/data.csv" << std::endl;
    return 0;
}

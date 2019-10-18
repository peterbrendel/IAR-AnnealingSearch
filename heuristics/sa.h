#pragma once

template<class T>
class Simanneal {
private:
    int maxT;
    int minT;
    int iterations;
    int updates;

    T best_state;
    T state;

public:
    Simanneal(int maxT, int minT, int iterations, int updates);
};

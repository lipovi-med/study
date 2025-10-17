#include "counter.h"

    Counter::Counter() { cntr = 1; }
    Counter::Counter(int cntr) { this->cntr = cntr; }
    void Counter::increase() {
        cntr++;
    }
    void Counter::reduce() {
        cntr--;
    }
    int Counter::show_result() const {
        return cntr;
    }

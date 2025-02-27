#pragma once

class Counter
{
private:
    int cntr;
public:
    Counter();
    Counter(int cntr);
    void increase();
    void reduce();
    int show_result() const;
};
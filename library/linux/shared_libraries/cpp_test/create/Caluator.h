#ifndef __CALUATOR_H_
#define __CALUATOR_H_

class Caluator
{
    Caluator();
    ~Caluator();

    template <typename T>
    T add(T a, T b);

    template <typename T>
    T subtract(T a, T b);

    template <typename T>
    T multiply(T a, T b);

    template <typename T>
    T divide(T a, T b);
};

#endif  // end of __CALUATOR_H
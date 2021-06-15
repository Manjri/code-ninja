#include <iostream>
#include <cstdio>

class bigInt{

public:
    bigInt();
    ~bigInt();
    bigInt();
    printInt();
    max(bigInt a, bigInt b);   //returns greater of 2 big ints
    min(bigInt a, bigInt b);   //returns minimum of 2 big ints
    add(bigInt a, bigInt b);   // a+ b
    subr(bigInt a, bigInt b);   //a-b
    mult(bigInt a, bigInt b);   //a*b
    div(bigInt a, bigInt b);    //a/b

private:
    vector<int> bigint;

    //overload operations like 

};
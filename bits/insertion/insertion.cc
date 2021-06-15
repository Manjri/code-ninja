#include <iostream>
#include <cstdio>

using namespace std;
uint32_t insertnumber(uint32_t N, uint32_t M, uint32_t i, uint32_t j){

    uint32_t rightmask = (1 << i) - 1; //all bits 0 expect for right of i's which are 1
    uint32_t w = ~0;
    uint32_t leftmask = (w << (j+1));
    uint32_t mask = leftmask | rightmask; //clear out bits from i-j but keep rest as 1 to retain the remainign original num

    uint32_t n = N & mask;
    n = n | (M << i);
    return n;
}

int main(){

    /*Input: N = 100 0000 0000, m = 10011, i = 2, j = 6
    Output: N = 1000 10011 00 */
    uint32_t n = 0x400; //10000000000 binary
    uint32_t m = 0x13; //10011;
    uint32_t i = 0x2;
    uint32_t j = 0x6;
    uint32_t number = insertnumber(n, m, i, j);
    uint32_t expectednumber =  0x44C; // 10001001100

    if(number != expectednumber){
        cout<<"Incorrect! you answer "<< number <<" expected: "<<expectednumber <<endl;
    }
    else{
        cout<<"correct! "<<endl;
    }
    return 0;
}
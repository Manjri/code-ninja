/*
 * Given a positive integer n, print the next smallest and the previous 
 * largest number that have the same number of 1 bits in their binary representation.
 * n = 5(0101), greater = 6 (0110), smaller = 3(0011)
 * n = 11(1011), greater = 13(1101), smaller = 7(0111)
 smaller:  flip leftmost 1 to 0 and the next 0 to 1.
 0101 -------------> 0011
 1011 -------------> 0111 

 greater: flip rightmost 0 to 1 and the next 1 to 0
 0101 ---------------> 0110 
 1011 ---------------> 1101

https://www.geeksforgeeks.org/closest-next-smaller-greater-numbers-number-set-bits/
 */
#include <stdio.h>
#include <iostream>
#include <vector>
#include <utility>

int next_smaller(int n){

    return -1;
}

int next_greater(int n){
    return -1;
}
int main()
{

    int s = next_smaller(5);
    int g = next_greater(5);

    if(s != 3){
        cout<<"wrong! smaller should be "<< 3 <<endl;
    }
    if(g != 6){
        cout<<"wrong! greater should be "<< 6 <<endl;
    }

    s = next_smaller(11);
    g = next_greater(11);

    if(s != 7){
        cout<<"wrong! smaller should be "<< 7 <<endl;
    }
    if(g != 13){
        cout<<"wrong! greater should be "<< 13 <<endl;
    }


    return 0;
}
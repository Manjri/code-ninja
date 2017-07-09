#include <cstdio>

int count_bits( int a, int b)
{
    int count = 0;

    int n = a ^ b;
    while(n != 0)
    {
        if((n & 0x1) == 1)
        {
            count++;
        }
        n = n>>1;
    }
    return count;
}

int main() 
{

	printf("%x\n", count_bits(31, 14)); //extract bits from 1 to 3rd position, including 3.
    return 1;

}
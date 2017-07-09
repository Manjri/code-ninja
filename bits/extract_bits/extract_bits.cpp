#include <cstdio>

int extract_bits(int num, int startpos, int endpos)
{
   // int leftmask = (1 << startpos) - 1;
    int rightmask = (1 << (endpos+1)) - 1; // from endpos to rightend all bits wl be 1
   
    
    int extractedbits = ((num & rightmask) >> startpos );
    return extractedbits;
}

int main() 
{
	int num = 0xFFFC; // ‭1111 1111 1111 1100‬
	printf("%x\n", num);
	printf("%x\n", extract_bits(num, 1, 3)); //extract bits from 1 to 3rd position, including 3.
    return 1;

}
#include <stdio.h>
#include <cstdint>
#include <cmath>

//IMP: keep in mind, memcpy works with void* but while impleanting it you need to work on byte level so type cast void* to char*
void *mymemcpy(void *d, void *s, size_t sz){

    //cast  void pointers into char pointers and handle in bytes
    //uint8_t size = sz * sizeof(uint8_t); //uint8_t is just 1 bytes so dont need it
    char *pd = (char *)d;
    char *ps = (char *)s;

    for(int i = 0; i < sz; i++){
        pd[i] = ps[i];
    }

    return d;
}

/*

Two cases of overlap:

| d - s | < sz

CASE 1: d > s

     <------- sz --------> 
               <------- sz -------->
     ...............................
     ^         ^
     s         d

CASE 2: d < s

     <------- sz --------> 
               <------- sz -------->
     ...............................
     ^         ^
     d         s

 */

int memcpy2(void *d, void *s, size_t sz){

    char *pd = (char *)d;
    char *ps = (char *)s;

    bool is_overlap = (abs(ps - pd) < abs(sz)); //true

    // there is no overlap, or there is overlap but source address is greater than dest,
    // ie overlap in the end so copy from beginning.
    if ((is_overlap == false ) || (ps > pd)) {
        printf("no overlap between source: %p  destination %p  for size %d \n", ps, pd, sz);
        printf("copying from beginning \n");
        for (uint8_t i = 0; i <= sz; i++) {
            pd[i] = ps[i];
        }
    } else {
        printf("there is overlap \n");
    /* there is overlap. check which direction. if source address is less than dest, ie source starts before dest
    * then copy from the end. else copy from beginning. */
        printf("copying from end \n");
        for(int i = sz-1; i >= 0; i--){
            pd[i] = ps[i];
        }
    }
    return 0;
}


//no need to check overlap. just compare the starting address of source and dest to decide direction of copy
void memcpy3(void* d, void* s, int size){
    char *pd = (char *)d;
    char *ps = (char *)s;

    if(ps < pd){
        //copy fomr end
        for(int i = size; i >=0; i--){
            pd[i] = ps[i];
        }
    }
    else{// dstrat...........sourcestart.........dend......sourceend
        //copy form beg
        for(int i = 0; i <= size; i++){
            pd[i] = ps[i];
        }

    }
}


int main(){

    char source[] = "Hello World";
    char destination[100];

    int sz = sizeof(source);
    printf("*********test 1 *********\n");

    memcpy2(destination, source, sz);

    for(int i = 0; i < sz; i++){
        printf("  %c ", destination[i]);
    }
    printf("\n");

    char s[256] = "abcdefghijk";
    char *d = &s[5];

    printf("*********test 2 *********\n");
    int p = memcpy2(d, s, 11);

    printf("Destination: \n");
    for(int i = 0; i < 11; i++){
        printf("  %c ", d[i]);
    }
    printf("\n");
    printf("Source: \n");
    for(int i = 0; i < 25; i++){
        printf(" %c ", s[i]);
    }
    printf("\n"); 
    return 0;
}
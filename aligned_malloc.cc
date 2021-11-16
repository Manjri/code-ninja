#include <iostream>
#include <cstdio>

using namespace std;

/* intptr_t is an integer that has same size as size of pointer on platform. had to switch to this bcz % wont work with ptrs
 * whenever you want to do airthmatic operation on a pointer like comparison/multiply/division/bit manipulation, should use
 * inptr_t to treat ptr as a number. but imp to note: you cannot typecast a intptr to other pointer ( ? )
 */

void* aligned_malloc(int size, int align){

    int pointer_size = sizeof(void*);
    int num_total_bytes = size + align - 1 + pointer_size;

    intptr_t p = (intptr_t)malloc(num_total_bytes);
    p += align + pointer_size;
    intptr_t q = p - (p % align);

//store void* p
    
    intptr_t *temp = (intptr_t*)(q - pointer_size);
    *temp = p;
    return (void*)q;
}

void aligned_free(void* p){

    //extract the pointer which was stored before this p and call free on it
    intptr_t q = (intptr_t)p - sizeof(void*);
    void *orig_ptr = *(void**)q;
    free(orig_ptr);
}

int main(){

    cout<<"return 5 bytes memory with alignment of 4 " <<endl;
    int size = 5;
    int align = 4;
    void* ptr = aligned_malloc(size, align);

//test if ptr%4 == 0 
    cout<<"aligned maloc returned " << ptr << endl;
    intptr_t x = (intptr_t)ptr;

    if(x % 4 == 0){
        cout<<"aligned "<<endl;
    }
    else{
        cout<<"not aligned "<<endl;
    }

    cout<<"free memory "<<endl;
    aligned_free(ptr);
    return 0;
}

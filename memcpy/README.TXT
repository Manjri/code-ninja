Implement memcpy function with overlap protection. ie if source and destination address overlap.

void *memcpy(void *dest, void *src, int size);

https://stackoverflow.com/questions/13095488/how-to-implement-overlap-checking-memcpy-in-c

1. no overlap
2. overlap but still can be copied
assume always can be copied
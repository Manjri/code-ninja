#ifndef _UTILS_H_
#define _UTILS_H_

#define BUF_SIZE 512
#define LOG(fmt, args...)  do { \
  fprintf(stderr, "%s:%d, " fmt "\n", __func__, __LINE__, ##args); \
} while(0)

const int PORT = 9014;

#endif
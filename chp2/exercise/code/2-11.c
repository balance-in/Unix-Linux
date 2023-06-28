/**
 * @file 2-11.c
 * @author balance (2570682750@qq.com)
 * @brief 修改cp1，使其在源文件和目标文件相同时能够处理。
 * @version 0.1
 * @date 2023-02-08
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUFFERSIZE 4096
#define COPYMODE 0644

void oops(char *s1, char *s2);

int main(int argc, char *argv[]) {
  int in_fd, out_fd, nchars;
  char buf[BUFFERSIZE];

  if (argc != 3) {  // check args
    fprintf(stderr, "usage: %s source destination\n", *argv);
  }

  if (strcmp(argv[1], argv[2]) == 0) {
    printf("%s and %s are the same file\n", argv[1], argv[2]);
    return 1;
  }

  if ((in_fd = open(argv[1], O_RDONLY)) == -1) {
    oops("Cannot open ", argv[1]);
    return 1;
  }
  if ((out_fd = creat(argv[2], COPYMODE)) == -1) {
    oops("Cannot creat ", argv[2]);
    return 1;
  }
  while ((nchars = read(in_fd, buf, BUFFERSIZE)) > 0) {
    if (write(out_fd, buf, nchars) != nchars) {
      oops("Write error to ", argv[2]);
      return 1;
    }
  }
  if (nchars == -1) oops("Read error from ", argv[1]);

  if (close(in_fd) == -1 || close(out_fd) == -1)
    oops("Error closing files ", "");
  return 0;
}

void oops(char *s1, char *s2) { printf("Error: %s%s", s1, s2); }
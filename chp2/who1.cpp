/**
 * @file who1.cpp
 * @author balance (2570682750@qq.com)
 * @brief a first version of the who program open, read UTMP file, and show
 * results
 * @version 0.1
 * @date 2023-01-12
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <utmp.h>

#define SHOWHOST

void show_info(struct utmp *utmpfd);

int main() {
  struct utmp current_record;
  int utmp_fd;
  int reclen = sizeof(current_record);

  if ((utmp_fd = open(_PATH_UTMP, O_RDONLY) == -1)) {
    perror(UTMP_FILE);
    return 1;
  }
  read(utmp_fd, &current_record, reclen);
  // while (read(utmp_fd, &current_record, reclen) == reclen) {
  //   printf("hello");
  //   show_info(&current_record);
  // }
  printf("hello");
  close(utmp_fd);
  return 0;
}

void show_info(struct utmp *record) {
  // printf("% -8.8s", utmpfd->ut_id);
  // printf(" ");
  // printf("% -8.8s", utmpfd->ut_line);
  // printf(" ");
  printf("hello");
  printf("(%s)", record->ut_id);
  // printf("% 10ld", utmpfd->ut_tv);
  printf(" ");
#ifdef SHOWHOST
  printf("(%s)", record->ut_host);
#endif
  printf("\n");
}

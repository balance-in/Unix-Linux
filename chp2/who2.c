/**
 * @file who1.cpp
 * @author balance (2570682750@qq.com)
 * @brief a first version of the who program open, read UTMP file, and show
 * results
 * @version 0.2
 * @date 2023-01-12
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <fcntl.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <utmp.h>

// #define SHOWHOST

void show_info(struct utmp *utmpfd);
void showtime(time_t time);

int main() {
  struct utmp current_record;
  int utmp_fd;
  int reclen = sizeof(current_record);

  if ((utmp_fd = open(_PATH_UTMP, O_RDONLY)) == -1) {
    perror(_PATH_UTMP);
    return 1;
  }
  read(utmp_fd, &current_record, reclen);
  while (read(utmp_fd, &current_record, reclen) == reclen) {
    show_info(&current_record);
  }
  close(utmp_fd);
  return 0;
}

void show_info(struct utmp *record) {
  if (record->ut_type != USER_PROCESS) {
    return;
  }
  printf("% -8.8s", record->ut_user);
  printf(" ");
  printf("% -8.8s", record->ut_line);
  printf(" ");
  // get time of login
  time_t timestamp = record->ut_tv.tv_sec;
  // struct tm *info;
  // info = localtime(&timestamp);
  // printf("%d-%d-%d", info->tm_year + 1900, info->tm_mon + 1, info->tm_mday);
  showtime(timestamp);
#ifdef SHOWHOST
  printf("(%s)", record->ut_host);
#endif
  printf("\n");
}
// time_t  ->  timeval    localtime(本地时间),gmtime(UTC时间)
void showtime(time_t time) {
  char *cp;
  cp = ctime(&time);

  printf("%12.12s", cp + 4);
}

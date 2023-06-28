/**
 * @file print_wtmp.c
 * @author balance (2570682750@qq.com)
 * @brief 打印wtmp文件所有记录
 * @version 0.1
 * @date 2023-04-12
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <utmp.h>
#include <utmpx.h>

int main() {
  utmpname(WTMP_FILE);

  struct utmp* wt;
  time_t ti;
  setutent();

  while ((wt = getutent()) != NULL) {
    printf("%8.8s\t", wt->ut_user);
    printf("%8.8s\t", wt->ut_line);
    ti = wt->ut_time;
    printf("%s", ctime(&ti));
  }

  endutent();
  return 0;
}
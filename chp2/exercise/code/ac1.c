/**
 * @file ac1.c
 * @author balance (2570682750@qq.com)
 * @brief 实现ac命令显示用户连接/登录时间
 * @version 0.1
 * @date 2023-02-14
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

#define NRECS 16
#define NULLUT ((struct utmp *)NULL)
#define UTSIZE (sizeof(struct utmp))
#define RECORDSIZE 2048

int fd_utmp = -1;
int num_recs;
int cur_recs;
char utmpbuf[NRECS * UTSIZE];

int utmp_reload();
int utmp_open(char *filename);
struct utmp *utmp_next();
void utmp_close();

static double total_time = 0;
time_t login_time, logout_time;

struct utmp_record {
  short ut_type;
  char ut_user[UT_NAMESIZE];
  char ut_line[UT_LINESIZE];
  int32_t login_sec;
  int32_t logout_sec;
  double diff;
};

struct utmp_record record[RECORDSIZE];
int num_record = 0;

int main() {
  if (utmp_open(WTMP_FILE) == -1) {
    perror(WTMP_FILE);
    return -1;
  }

  memset(record, 0, sizeof(struct utmp_record) * RECORDSIZE);

  struct utmp *utbuf;

  while((utbuf = utmp_next()) != NULLUT){
    
  }

  return 0;
}

void ac_info() {
  struct utmp *utmp_login, *utmp_logout;
  utmpname(WTMP_FILE);
  setutent();
  while ((utmp_login = getutent()) != NULL) {
    if (utmp_login->ut_type == USER_PROCESS) {
      login_time = utmp_login->ut_time;
      printf("%-8.8s\t%s", utmp_login->ut_line, ctime(&login_time));
      if ((utmp_logout = getutline(utmp_login)) != NULL) {
        printf("%-8.8s\t%-8.8s", utmp_logout->ut_user, utmp_login->ut_line);
        printf("%d", utmp_login->ut_type);
        time_t tt = utmp_logout->ut_time;
        printf("%s", ctime(&tt));
        printf("------------\n");
        // if (utmp_logout->ut_type == DEAD_PROCESS) {
        //   logout_time = utmp_logout->ut_time;
        //   printf("%-8.8s\t%s", utmp_logout->ut_user, ctime(&logout_time));
        //   total_time += difftime(logout_time, login_time);
        // }
      }
    }
  }
  endutent();
}
/*
  functions to buffer reads from utmp file
  utmp_open(filename) -- open file
  utmp_next()         -- return pointer to next struct
  utmp_close()        -- close file
*/
int utmp_open(char *filename) {
  fd_utmp = open(filename, O_RDONLY);
  num_recs = cur_recs = 0;
  return fd_utmp;
}

int utmp_reload() {
  int amt_read;
  amt_read = read(fd_utmp, utmpbuf, NRECS * UTSIZE);
  num_recs = amt_read / UTSIZE;
  cur_recs = 0;
  return num_recs;
}

struct utmp *utmp_next() {
  struct utmp *recp;
  if (fd_utmp == -1) {
    return NULLUT;
  }
  if (cur_recs == num_recs && utmp_reload() == 0) {
    return NULLUT;
  }
  recp = (struct utmp *)&utmpbuf[cur_recs * UTSIZE];
  cur_recs++;
  return recp;
}

void utmp_close() {
  if (fd_utmp != -1) {
    close(fd_utmp);
  }
}
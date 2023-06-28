/**
 * @file who3.c
 * @author balance (2570682750@qq.com)
 * @brief  who with buffered reads, surpresses empty records, formats time
 * nicely, buffers input
 * @version 0.3
 * @date 2023-02-07
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <utmp.h>

#define NRECS 16
#define NULLUT ((struct utmp *)NULL)
#define UTSIZE (sizeof(struct utmp))

static char utmpbuf[NRECS * UTSIZE];
static int num_recs;
static int cur_recs;
static int fd_utmp = -1;

void show_info(struct utmp *utmpfd);
void showtime(time_t time);
int utmp_reload();
int utmp_open(char *filename);
struct utmp *utmp_next();
void utmp_close();

int main() {
  struct utmp *utbufp;

  if (utmp_open(_PATH_UTMP) == -1) {
    perror(_PATH_UTMP);
    return 1;
  }
  while ((utbufp = utmp_next()) != NULLUT) {
    show_info(utbufp);
  }
  utmp_close();
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
/**
 * @brief marks a utmp record as logged out
 *
 * @param line
 * @return int -1 on error, 0 on success
 */
int logout_tty(char *line) {
  int fd;
  struct utmp rec;
  int len = sizeof(struct utmp);
  int retval = -1;

  if ((fd = open(UTMP_FILE, O_RDWR)) == -1) return -1;
  // search and replace
  while (read(fd, &rec, len) == len) {
    if (strncmp(rec.ut_line, line, sizeof(rec.ut_line)) == 0) {
      rec.ut_type = DEAD_PROCESS;
      if (lseek(fd, -len, SEEK_CUR) != -1) {
        if (write(fd, &rec, len) == len) {
          retval = 0;
        }
      }
      break;
    }
  }
  // close file
  if (close(fd) == -1) retval = -1;
  return retval;
}
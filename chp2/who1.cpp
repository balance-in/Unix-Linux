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

int main() {
  struct utmp current_record;
  int utmp_fd;
  int reclen = sizeof(current_record);
}

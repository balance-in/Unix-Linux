/**
 * @file 2-10.c
 * @author balance (2570682750@qq.com)
 * @brief 实现whoami命令
 * @version 0.1
 * @date 2023-02-08
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <pwd.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  uid_t my_uid;
  my_uid = getuid();  // 获取当前用户实际ID
  struct passwd *my_info;
  my_info = getpwuid(my_uid);  // 通过用户ID查找passwd文件获取用户名
  if (my_info == (struct passwd *)NULL) {
    perror("getuid");
    return 1;
  }
  printf("%s\n", my_info->pw_name);
}
#ifndef _COMMON_H_
#define _COMMON_H_

#include<unistd.h>
#include<stdlib.h>
#include<pwd.h>
#include<errno.h>
#include<signal.h>
#include<fcntl.h>
#include<sys/syscall.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/socket.h>
#include<sys/time.h>
#include<sys/sendfile.h>
#include<linux/capability.h>
#include<time.h>
#include<dirent.h>
#include<netinet/in.h>
#include<netdb.h>
#include<shadow.h>
#include<crypt.h>
#include<stype.h>
#include<string.h>

#define ERR_EXIT(m) \
    do { \
        perror(m); \
        exit(EXIT_FAILURE); \
    } while (0)

#define MAX_COMMAND_LINE  1024
#define MAX_COMMAND 32
#define MAX_ARG 1024
#define MINIFTP_CONF "miniftp.conf"

#endif/*_COMMON_H_*/
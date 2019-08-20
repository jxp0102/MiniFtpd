#ifndef _SYSUTIL_H_
#define _SYSUTIL_H_

#include"common.h"
int tcp_server(const char *host,unsigned short port);

int getlocalip(char *ip);   //获取本地IP

void activate_nonblock(int fd); //将一个文件描述符设置成非阻塞的
void deactivate_nonblock(int fd);//去掉文件描述符的非阻塞

int read_timeout(int fd,unsigned int wait_seconds);//读超时封装
int write_timeout(int fd,unsigned int wait_seconds);//写超时的封装
int accept_timeout(int fd,struct sockaddr_in *addr,unsigned int wait_seconds);//接受超时封装
int connect_timeout(int fd,struct sockaddr_in *addr,unsigned int wait_seconds);//连接超时封装

ssize_t readn(int fd,void *buf,size_t count);
ssize_t writen(int fd,const void *buf,size_t count);
ssize_t recv_peek(int sockfd,void *buf,size_t len);
ssize_t readline(int sockfd,void *buf,size_t maxline);

void send_fd(int sock_fd,int fd);
int recv_fd(const int sock_fd);

const char *statbuf_get_perms(struct stat *sbuf);
const char *statbuf_get_date(struct stat *sbuf);

int lock_file_read(int fd);
int lock_file_write(int fd);
int unlock_file(int fd);

long get_time_sec(void);
long get_time_usec(void);
void nano_sleep(double seconds);

void active_oobinline(int fd);  //紧急带外数据的传输 
void active_sigurg(int fd);
#endif /*_SYSUTIL_H_*/

#ifndef _SYSUTIL_H_
#define _SYSUTIL_H_

#include"common.h"
int tcp_server(const char *host,unsigned short port);

int getlocalip(char *ip);   //��ȡ����IP

void activate_nonblock(int fd); //��һ���ļ����������óɷ�������
void deactivate_nonblock(int fd);//ȥ���ļ��������ķ�����

int read_timeout(int fd,unsigned int wait_seconds);//����ʱ��װ
int write_timeout(int fd,unsigned int wait_seconds);//д��ʱ�ķ�װ
int accept_timeout(int fd,struct sockaddr_in *addr,unsigned int wait_seconds);//���ܳ�ʱ��װ
int connect_timeout(int fd,struct sockaddr_in *addr,unsigned int wait_seconds);//���ӳ�ʱ��װ

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

void active_oobinline(int fd);  //�����������ݵĴ��� 
void active_sigurg(int fd);
#endif /*_SYSUTIL_H_*/

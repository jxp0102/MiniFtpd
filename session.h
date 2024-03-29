#ifndef _SESSION_H_
#define _SESSION_H_
#include"common.h"

typedef struct session
{
	//控制连接
	uid_t uid;
	int ctrl_fd;
	char cmdline[MAX_COMMAND_LINE];
	char cmd[MAX_COMMAND];
	char arg[MAX_ARG];

	//数据连接
	struct sockaddr_in *port_addr;
	int pasv_listen_fd;
	int data_fd;
	int data_process;
	//限速
	unsigned int bw_upload_rate_max; //最大上传速率
	unsigned int bw_download_rate_max;  //最大下载速率
	long bw_transfer_start_sec;  //开始传输的时间秒数
	long bw_transfer_start_usec;  //开始传输的时间微秒数

	//父子进程通道 
	int parent_fd;
	int child_fd;

	//FTP协议状态
	int is_ascii;
	long long restart_pos;
	char *rnfr_name;
	int abor_received;
}session_t;
void begin_session(session_t *sess);

#endif
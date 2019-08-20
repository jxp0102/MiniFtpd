#ifndef _SESSION_H_
#define _SESSION_H_
#include"common.h"

typedef struct session
{
	//��������
	uid_t uid;
	int ctrl_fd;
	char cmdline[MAX_COMMAND_LINE];
	char cmd[MAX_COMMAND];
	char arg[MAX_ARG];

	//��������
	struct sockaddr_in *port_addr;
	int pasv_listen_fd;
	int data_fd;
	int data_process;
	//����
	unsigned int bw_upload_rate_max; //����ϴ�����
	unsigned int bw_download_rate_max;  //�����������
	long bw_transfer_start_sec;  //��ʼ�����ʱ������
	long bw_transfer_start_usec;  //��ʼ�����ʱ��΢����

	//���ӽ���ͨ�� 
	int parent_fd;
	int child_fd;

	//FTPЭ��״̬
	int is_ascii;
	long long restart_pos;
	char *rnfr_name;
	int abor_received;
}session_t;
void begin_session(session_t *sess);

#endif
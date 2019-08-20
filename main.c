
#include"common.h"
#include"sysutil.h"
#include"session.h"
#include"str.h"
#include"tunable.h"
#include"parseconf.h"
#include"ftpproto.h"
#include"ftpcodes.h"


extern session_t *p_sess;

int main(void)
{
	/*
	char *str1="     a b";
	char *str2="     ";
	if(str_all_space(str1))
		printf("str1 all space\n");
	else
		printf("str1 not all sapce\n");
	if(str_all_space(str2))
		printf("str2 all space\n");
	else
		printf("str2 not all space\n");
	//char *str3="abcDef";  //ָ��ָ��һ���ַ����������������ܱ��޸ģ�����ֶδ���
	char str[]="abcDef";
	str_upper(str3);
	printf("str3=%s\n",str3);
	long long result=str_to_longlong("12345678910");
	printf("result=%ll\n",result);
	int n=str_octal_to_unit("0711");
	printf("n=%d\n",n);
	*/
	parseconf_load_file("MINIFTP_CONF");
	printf("tunable_pasv_enable=%d\n",tunable_pasv_enable);
	printf("tunable_port_enable=%d\n",tunable_port_enable);
	printf("tunable_listen_port=%u\n",tunable_listen_port);
	printf("tunable_max_clients=%u\n",tunable_max_clients);
	printf("tunable_max_per_ip=%u\n",tunable_max_per_ip);
	printf("tunable_accept_timeout=%u\n",tunable_accept_timeout);
	printf("tunable_connect_timeout=%u\n",tunable_connect_timeout);
	printf("tunable_idle_session_timeout=%u\n",tunable_idle_session_timeout);
	printf("tunabel_data_connection_timeout=%u\n",tunable_data_connection_timeout);
	printf("tunable_local_umask=0%o\n",tunable_local_umask);
	printf("tunable_upload_max_rate",tunable_upload_max_rate);
	printf("tunable_download_max_rate",tunable_download_max_rate);

	if(tunable_listen_address==NULL)
		printf("tunable_listen_address=NULL\n");
	else
		printf("tunable_listen_address=%s\n",tunable_listen_address);
	if(getuid()!=0)
	{
		printf("mimftpd:must be started as root\n");
		exit(EXIT_FAILURE);
	} //�ж��Ƿ�Ϊroot�û�
	




	list_common();
	/*
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
*/

	session_t sess=
	{
		/*���ƽ���*/
		0,-1, ..., ...,...,
		/*��������*/
		NULL,-1,-1,0,
		/*����*/
		0��0��0��0��
		/*���ӽ���ͨ��*/
		-1,-1,
		/*FTPЭ��״̬*/
		0,0��NULL,0
	};
		p_sess=&sess;

    sess.bw_upload_rate_max=tunable_upload_max_rate;
	sess.bw_download_rate_max=tunable_download_max_rate;
	

    signal(SIGCHLD,SIG_IGN);
	int listenfd=tcp_server(tunable_listen_address,tunable_listen_port);//����������
	int conn;
	pid_t pid;
	while(1)
	{
		conn=accept_timeout(listenfd,NULL,0);//���ܿͻ��˵�����

		if(conn==-1)
			ERR_EXIT("accept_timeout");

		pid=fork();//�����Ժ󴴽�һ�����̳���
		if(pid==-1)
			ERR_EXIT("fork.");
		if(pid==0)
		{
			close(listenfd);
			sess.ctrl_fd=conn;
			begin_session(&sess);//������ӽ��̵Ļ���ʼһ���Ự���˺����з����Ѵ������׽���
		}
		else
			close(conn);//����Ǹ����̹ر��׽��ֵĻ��ص�accept���������Ŀͻ���
	}
	return 0;
}
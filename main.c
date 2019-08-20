
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
	//char *str3="abcDef";  //指针指向一个字符串常量，常量不能被修改（会出现段错误）
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
	} //判断是否为root用户
	




	list_common();
	/*
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
*/

	session_t sess=
	{
		/*控制进程*/
		0,-1, ..., ...,...,
		/*数据连接*/
		NULL,-1,-1,0,
		/*限速*/
		0，0，0，0，
		/*父子进程通道*/
		-1,-1,
		/*FTP协议状态*/
		0,0，NULL,0
	};
		p_sess=&sess;

    sess.bw_upload_rate_max=tunable_upload_max_rate;
	sess.bw_download_rate_max=tunable_download_max_rate;
	

    signal(SIGCHLD,SIG_IGN);
	int listenfd=tcp_server(tunable_listen_address,tunable_listen_port);//启动服务器
	int conn;
	pid_t pid;
	while(1)
	{
		conn=accept_timeout(listenfd,NULL,0);//接受客户端的连接

		if(conn==-1)
			ERR_EXIT("accept_timeout");

		pid=fork();//连接以后创建一个进程出来
		if(pid==-1)
			ERR_EXIT("fork.");
		if(pid==0)
		{
			close(listenfd);
			sess.ctrl_fd=conn;
			begin_session(&sess);//如果是子进程的话开始一个会话，此函数中放入已创建的套接字
		}
		else
			close(conn);//如果是父进程关闭套接字的话回到accept连接其他的客户端
	}
	return 0;
}
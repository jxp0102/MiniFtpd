#include"common.h"
#include"session.h"
#include"ftpproto.h"
#include"privparent.h"
#include"privsock.h"
#include"sysutil.h"


void begin_session(session_t *sess)
{
	active_oobline(sess->ctrl_fd);
	/*
	int sockfds[2];
	if((socketpair(AF_UNIX,SOCK_STREAM,0,sockfds))<0)
		ERR_EXIT("socketpair");
	*/

	pid_t pid;
	pid=fork();
	if(pid<0)
		ERR_EXIT("fork");

	if(pid==0)
	{
		//子进程，ftp服务进程(控制连接->接收ftp发送过来的命令请求和数据连接->处理一些数据请求)
	    /*
		close(sockfds[0]);
		sess->child_fd=sockfds[1];
		*/
		priv_sock_set_child_context(sess)
		handle_child(sess);
	}
	else
	{
		

		//父进程，nobody进程（辅助服务进程，不直接与外界传输）
		
		/*
		close(sockfds[1]);
		sess->parent_fd=sockfds[0];
		*/
		priv_sock_set_parent_context(sess)
		handle_parent(sess);
	}
}
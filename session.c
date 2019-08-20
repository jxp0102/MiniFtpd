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
		//�ӽ��̣�ftp�������(��������->����ftp���͹����������������������->����һЩ��������)
	    /*
		close(sockfds[0]);
		sess->child_fd=sockfds[1];
		*/
		priv_sock_set_child_context(sess)
		handle_child(sess);
	}
	else
	{
		

		//�����̣�nobody���̣�����������̣���ֱ������紫�䣩
		
		/*
		close(sockfds[1]);
		sess->parent_fd=sockfds[0];
		*/
		priv_sock_set_parent_context(sess)
		handle_parent(sess);
	}
}
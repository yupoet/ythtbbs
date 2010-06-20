#include "bbslib.h"

int
bbsmsg_main()
{
	char buf[MAX_MSG_SIZE];
	char msgbuf[MAX_MSG_SIZE * 2];
	int count, i;
	struct msghead head;
	html_header(1);
	//check_msg();
	printf("<body>");
	if (!loginok || isguest)
		http_fatal("匆匆过客无法查看短消息, 请先登录");
	changemode(LOOKMSGS);
	count = get_msgcount(0, currentuser->userid);
	if (count == 0)
		http_fatal("没有任何短消息");
	for (i = 0; i < count; i++) {
		load_msghead(0, currentuser->userid, &head, i);
		load_msgtext(currentuser->userid, &head, buf);
		translate_msg(buf, &head, msgbuf, 0);
		noansi = 1;
		hprintf("%s", msgbuf);
		noansi = 0;
	}
	u_info->unreadmsg = 0;
	printf
	    ("<a onclick='return confirm(\"你真的要清除所有短消息吗?\")' href=bbsdelmsg>清除所有短消息</a> ");
	printf("<a href=bbsmailmsg>寄回所有信息</a>");
	http_quit();
	return 0;
}

#ifndef SERVER_H
#define SERVER_H
#include<stdio.h>
#include<WinSock2.h>
#include<ctime>
#include<string>
#include<iostream>
#include<list>
#include<sstream>
#include<fstream>
#include<vector>
#include<map>
#include <conio.h>
using namespace std;

#pragma comment(lib,"ws2_32.lib")

//#define PORT 5050
#define BUFSIZE 1024
#define MAX_CONN 5
#define CLOSE_SECOND 0.5//超过秒数无请求则关闭socket
//#define VIRTURAL_ADDR "C:/Users/朱志成/Desktop/server_v/"

typedef list<SOCKET> ListCONN;
typedef list<SOCKET> ListConErr;

class server {
private:
	//初始化系统socket服务
	int server_initialize(WORD w, WSADATA &wsaData, SOCKET &s, SOCKADDR_IN &srvAddr);
	//发送文件
	int sendfile(SOCKET & clientconn, string filename);
	//文件未找到时返回的响应报文
	int send_error_code(SOCKET & clientconn);
	//关闭系统socket服务
	void Close(SOCKET &s);
	//报文解析
	string http_parser(string);
	//在字符串中删除指定字符
	void string_delete(string &st1, char c);

public:
	server();
	~server();
	void start();

private:
	WSADATA wsaData;
	SOCKADDR_IN srvAddr, clientAddr;
	SOCKET srvSock;
	u_long uNonBlock;

	ListCONN conList;		//保存所有有效的会话SOCKET
	ListCONN::iterator itor;
	ListConErr conErrList;	//保存所有失效的会话SOCKET
	ListConErr::iterator itor1;
	map<SOCKET, clock_t> conn_isvalid;//记录socket的有效情况

	FD_SET rfds;

	int nRC;
	int AddrLen = sizeof(sockaddr);
	char recvBuf[BUFSIZ];
	bool server_start = true;//记录srv开启信号
	char input;//记录键盘输入事件
	u_short PORT;
	string IP_ADDR;
	string VIRTURAL_ADDR;
public:
};

#endif // SERVER_H

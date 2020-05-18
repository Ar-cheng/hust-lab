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
#define CLOSE_SECOND 0.5//����������������ر�socket
//#define VIRTURAL_ADDR "C:/Users/��־��/Desktop/server_v/"

typedef list<SOCKET> ListCONN;
typedef list<SOCKET> ListConErr;

class server {
private:
	//��ʼ��ϵͳsocket����
	int server_initialize(WORD w, WSADATA &wsaData, SOCKET &s, SOCKADDR_IN &srvAddr);
	//�����ļ�
	int sendfile(SOCKET & clientconn, string filename);
	//�ļ�δ�ҵ�ʱ���ص���Ӧ����
	int send_error_code(SOCKET & clientconn);
	//�ر�ϵͳsocket����
	void Close(SOCKET &s);
	//���Ľ���
	string http_parser(string);
	//���ַ�����ɾ��ָ���ַ�
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

	ListCONN conList;		//����������Ч�ĻỰSOCKET
	ListCONN::iterator itor;
	ListConErr conErrList;	//��������ʧЧ�ĻỰSOCKET
	ListConErr::iterator itor1;
	map<SOCKET, clock_t> conn_isvalid;//��¼socket����Ч���

	FD_SET rfds;

	int nRC;
	int AddrLen = sizeof(sockaddr);
	char recvBuf[BUFSIZ];
	bool server_start = true;//��¼srv�����ź�
	char input;//��¼���������¼�
	u_short PORT;
	string IP_ADDR;
	string VIRTURAL_ADDR;
public:
};

#endif // SERVER_H

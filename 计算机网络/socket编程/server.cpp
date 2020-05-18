#include "server.h"

void server::Close(SOCKET &s)
{
	::closesocket(s);
	::WSACleanup();
}

int server::server_initialize(WORD w, WSADATA &wsaData, SOCKET &s, SOCKADDR_IN &srvAddr)
{
	cout << "intput listen PORT:  ";
	cin >> PORT;
	cout << "input listen IP_ADDR:   ";
	cin >> IP_ADDR;
	cout << "input listen VIRTUAL_ADDR:(end with \\)";
	cin >> VIRTURAL_ADDR;
	cout << endl;
	int nRC = WSAStartup(w, &wsaData);
	if (nRC)
	{
		cout << "server initialize winsock error!" << endl;
		return -2;
	}
	if (wsaData.wVersion != 0x0101)
	{
		cout << "Server's winsock version errot!" << endl;
		WSACleanup();
		return -1;
	}
	cout << "Server's winsock initialized!" << endl;


	//创建TCPsocket
	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s == INVALID_SOCKET)
	{
		cout << "server creat socket error!" << endl;
		WSACleanup();
		return -1;
	}
	cout << "Server TCP socket creat OK!\n";

	//绑定socket to Server's IP and port 5050
	srvAddr.sin_family = AF_INET;
	srvAddr.sin_port = htons(PORT);
	srvAddr.sin_addr.S_un.S_addr = inet_addr(IP_ADDR.c_str());
	//srvAddr.sin_addr.S_un.S_addr = INADDR_ANY;
	nRC = ::bind(s, (SOCKADDR *)&srvAddr, sizeof(SOCKADDR));
	if (nRC == SOCKET_ERROR)
	{
		cout << "Server socket bind error! \n";
		closesocket(s);
		WSACleanup();
		return -1;
	}
	cout << "Server socket bind OK!\n";

	//开始监听过程
	nRC = listen(s, MAX_CONN);
	if (nRC == SOCKET_ERROR)
	{
		cout << "Server socket listen error!\n";
		closesocket(s);
		WSACleanup();
		return -1;
	}
	cout << "Server start listen port " << PORT << endl;
	//将srvSock设为非阻塞模式以监听客户连接请求
	u_long uNonBlock;
	uNonBlock = 1;
	ioctlsocket(s, FIONBIO, &uNonBlock);
	cout << endl;
	return 0;
}

string server::http_parser(string temp) {
	/*string temp;
	temp.append(buf);*/
	if (temp.size() == 0)
	{
		temp.clear();
		return temp;
	}
	//GET请求处理
	string filename;
	string http_request = temp.substr(temp.find("GET"), temp.find("\r\n") - temp.find("GET"));
	string_delete(http_request, ' ');
	if (http_request.find("?") != http_request.npos)
	{
		filename = http_request.substr(http_request.find("GET") + 3, http_request.find("?") - http_request.find("GET") - 3);
	}
	else
		filename = http_request.substr(http_request.find("GET") + 3, http_request.find("HTTP") - http_request.find("GET") - 3);
	while (filename[0] == '/')
		filename.erase(filename.begin());
	return filename;
}

void server::string_delete(string &st1, char c)
{
	string::iterator tmp = find(st1.begin(), st1.end(), c);
	while (tmp != st1.end())
	{
		auto x = st1.erase(tmp);
		tmp = find(x, st1.end(), c);
	}
}

int server::sendfile(SOCKET & clientconn, string filename) {
	int tlen;
	ifstream infile;
	infile.open(VIRTURAL_ADDR + filename, ios::binary);
	if (!infile) {

		return -1;
	}
	infile.seekg(0, ios::end);
	int size = infile.tellg();
	infile.seekg(0, ios::beg);
	stringstream ss;
	ss << infile.rdbuf();
	infile.close();
	string contents(ss.str());
	char *p_bufs = (char *)malloc(size + 1024);

	if (filename.find("jpg") != filename.npos)
		tlen = sprintf(p_bufs, "HTTP/1.1 200 OK\r\n"
			"Server: hsoap/2.8\r\n"
			"Content-Type: image/jpeg\r\n"
			"Content-Length: %d\r\n"
			"Connection: keep-alive\r\n\r\n",
			size);
	else if (filename.find("png") != filename.npos)
		tlen = sprintf(p_bufs, "HTTP/1.1 200 OK\r\n"
			"Server: hsoap/2.8\r\n"
			"Content-Type: image/png\r\n"
			"Content-Length: %d\r\n"
			"Connection: keep-alive\r\n\r\n",
			size);
	else if (filename.find("html") != filename.npos)
		tlen = sprintf(p_bufs, "HTTP/1.1 200 OK\r\n"
			"Server: hsoap/2.8\r\n"
			"Content-Type: text/html\r\n"
			"Content-Length: %d\r\n"
			"Connection: keep-alive\r\n\r\n",
			size);
	else if (filename.find("txt") != filename.npos)
		tlen = sprintf(p_bufs, "HTTP/1.1 200 OK\r\n"
			"Server: hsoap/2.8\r\n"
			"Content-Type: text/plain;charset=utf-8\r\n"
			"Content-Length: %d\r\n"
			"Connection: keep-alive\r\n\r\n",
			size);
	else if (filename.find("css") != filename.npos)
		tlen = sprintf(p_bufs, "HTTP/1.1 200 OK\r\n"
			"Server: hsoap/2.8\r\n"
			"Content-Type: text/css\r\n"
			"Content-Length: %d\r\n"
			"Connection: keep-alive\r\n\r\n",
			size);
	else if (filename.find("js") != filename.npos)
		tlen = sprintf(p_bufs, "HTTP/1.1 200 OK\r\n"
			"Server: hsoap/2.8\r\n"
			"Content-Type: application/ecmascript\r\n"
			"Content-Length: %d\r\n"
			"Connection: keep-alive\r\n\r\n",
			size);
	else if (filename.find("mp4") != filename.npos)
		tlen = sprintf(p_bufs, "HTTP/1.1 200 OK\r\n"
			"Server: hsoap/2.8\r\n"
			"Content-Type: audio/mp4\r\n"
			"Content-Length: %d\r\n"
			"Connection: keep-alive\r\n\r\n",
			size);
	else if (filename.find("mp3") != filename.npos)
		tlen = sprintf(p_bufs, "HTTP/1.1 200 OK\r\n"
			"Server: hsoap/2.8\r\n"
			"Content-Type: 	audio/mp3\r\n"
			"Content-Length: %d\r\n"
			"Connection: keep-alive\r\n\r\n",
			size);
	else
		tlen = sprintf(p_bufs, "HTTP/1.1 200 OK\r\n"
			"Server: hsoap/2.8\r\n"
			"Content-Type: text/plain\r\n"
			"Content-Length: %d\r\n"
			"Connection: keep-alive\r\n\r\n",
			size);
	memcpy(p_bufs + tlen, contents.c_str(), size);
	send(clientconn, p_bufs, tlen + size, 0);
	free(p_bufs);
	return 0;
}

int server::send_error_code(SOCKET & clientconn) {
	int tlen;
	char *p_bufs = (char *)malloc(1024);
	string error = "file not exsit!";
	tlen = sprintf(p_bufs, "HTTP/1.1 404 Not Found OK\r\n"
		"Server: hsoap/2.8\r\n"
		"Content-Type: text/plain\r\n"
		"Content-Length: %d\r\n"
		"Connection: keep-alive\r\n\r\n",
		error.length());
	memcpy(p_bufs + tlen, error.c_str(), error.size());
	send(clientconn, p_bufs, tlen+error.size(), 0);
	return 0;
}

server::server() {
}

server::~server() {
	Close(srvSock);
}

void server::start() {
	server_initialize(0x0101, wsaData, srvSock, srvAddr);
		while (1) {
			if (_kbhit()) {//如果有按键按下，则_kbhit()函数返回真
				input = _getch();//使用_getch()函数获取按下的键值
				if (input == 'p') { break; }//当按下P时退出
			}
			//从conList中删除已经产生错误的会话SOCKET
			for (itor1 = conErrList.begin(); itor1 != conErrList.end(); itor1++)
			{
				itor = find(conList.begin(), conList.end(), *itor1);
				if (itor != conList.end())
					conList.erase(itor);
			}
			conErrList.clear();//清空错误套接字集合
			//清空read套接字集合
			FD_ZERO(&rfds);
			//设置等待客户连接请求
			FD_SET(srvSock, &rfds);

			//cout <<endl<< "-----------------" << endl;
			for (itor = conList.begin(); itor != conList.end(); itor++)
			{
				//把所有会话SOCKET设为非阻塞模式
				uNonBlock = 1;
				ioctlsocket(*itor, FIONBIO, &uNonBlock);
				//设置等待会话SOKCET可接受数据或可发送数据
				FD_SET(*itor, &rfds);
				//cout << *itor<<": "<< conn_isvalid[*itor]<<"--";
			}
			// 开始等待
			struct timeval tv;
			tv.tv_sec = 1;
			tv.tv_usec = 0;
			int nTotal = select(0, &rfds, NULL, NULL, &tv);
			//如果srvSock收到连接请求，接受客户连接请求
			if (FD_ISSET(srvSock, &rfds))
			{
				nTotal--;
				//产生会话SOCKET
				SOCKET connSock = accept(srvSock,
					(LPSOCKADDR)&clientAddr,
					&AddrLen);
				if (connSock == INVALID_SOCKET)
				{
					printf("Server accept connection request error!\n");
					closesocket(srvSock);
					WSACleanup();
					return;
				}
				//将产生的会话SOCKET保存在conList中
				conList.insert(conList.end(), connSock);
				//加入轮询列表计数
				conn_isvalid.insert(pair<SOCKET, clock_t>(connSock, clock()));
			}
			if (nTotal > 0)
			{
				for (itor = conList.begin(); itor != conList.end(); itor++)
				{
					if (FD_ISSET(*itor, &rfds))
					{
						nRC = recv(*itor, recvBuf, BUFSIZ, 0);
						if (nRC == SOCKET_ERROR)
						{
							//接受数据错误
							//记录下产生错误的会话SOCKET
							conErrList.insert(conErrList.end(), *itor);
						}
						else
						{
							//接收数据成功,解析请求
							recvBuf[nRC] = '\0';
							if (strlen(recvBuf) == 0)
								continue;
							conn_isvalid[*itor] = clock();
							//printf("recvBuf:   %s\n", recvBuf);
							string temp;
							temp.append(recvBuf);
							//解析http请求
							string http_request = temp.substr(temp.find("GET"), temp.find("\r\n") - temp.find("GET"));
							string filename = http_parser(http_request);
							getpeername(*itor, (SOCKADDR *)&clientAddr, &AddrLen);
							cout << "connSock:		" << *itor << endl;
							printf("IP:   %s     ", inet_ntoa(clientAddr.sin_addr));
							printf("PORT: %d\n", clientAddr.sin_port);
							cout << "http request:		" << http_request << endl;
							cout << "find file :		" << VIRTURAL_ADDR << filename << endl;
							if (filename.size() > 0)
							{
								if (sendfile(*itor, filename) == -1)
								{
									cout << "请求的文件不存在!" << endl;
									send_error_code(*itor);
								}
								else
									cout << "send file success!" << endl;
							}
							else if (filename.size() == 0)
							{
								cout << "请求访问:		index.html" << endl;
								if (sendfile(*itor, "index.html") == -1)
								{
									cout << "index.html 发送失败!" << endl;
								}
								cout << "index.html 发送成功！ " << endl;
							}
							cout << endl;
						}
					}
				}
			}
			//清理超时socket
			for (itor = conList.begin(); itor != conList.end(); itor++){
				if ((clock() - conn_isvalid[*itor]) / CLOCKS_PER_SEC > CLOSE_SECOND) {
					conn_isvalid.erase(*itor);
					closesocket(*itor);
					conErrList.push_back(*itor);
				}
			}
		}
		cout << "正在关闭浏览器socket..."<<endl;
		for (itor = conList.begin(); itor != conList.end(); itor++)
			closesocket(*itor);
		cout << "关闭server socket..." << endl;
		Close(srvSock);
		cout << "server 已关闭！"<<endl;
		Sleep(3000);
}

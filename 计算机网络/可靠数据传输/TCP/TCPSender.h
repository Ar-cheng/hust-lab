#ifndef TCP_SENDER_H
#define TCP_SENDER_H
#include "RdtSender.h"
#include<list>
#define WINDOW_SIZE 4//窗口编码，2位
#define ORDER_SIZE 8//序号编码，3位

using namespace std;

class TCPSender :public RdtSender
{
private:
	int base;						//发送窗口头
	int nextseqnum;					//下一个发送的序号
	list<Packet> sndpkt;		//已发送的数据包
	bool waitingState;				// 是否处于滑动窗口已满等待Ack的状态
	int repeat_count;				//记录ack的重复次数，用于快速重传
public:

	bool getWaitingState();
	bool send(const Message &message);						//发送应用层下来的Message，由NetworkServiceSimulator调用,如果发送方成功地将Message发送到网络层，返回true;如果因为发送方处于等待正确确认状态而拒绝发送Message，则返回false
	void receive(const Packet &ackPkt);						//接受确认Ack，将被NetworkServiceSimulator调用	
	void timeoutHandler(int seqNum);					//Timeout handler，将被NetworkServiceSimulator调用

public:
	TCPSender();
	virtual ~TCPSender();
};

#endif


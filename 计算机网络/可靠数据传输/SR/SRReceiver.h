#ifndef SR_RECEIVER_H
#define SR_RECEIVER_H
#include "RdtReceiver.h"
#include<list>
#define WINDOW_SIZE 4
#define ORDER_SIZE 8

using namespace std;
class SRReceiver :public RdtReceiver
{
private:
	int rcvbase;
	Packet sndpkt;
	int pkt_count;
	list<Packet> rcvpkt;//缓存接收分组
public:
	SRReceiver();
	virtual ~SRReceiver();

public:
	
	void receive(const Packet &packet);	//接收报文，将被NetworkService调用
};

#endif


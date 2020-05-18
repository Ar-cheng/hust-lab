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
	list<Packet> rcvpkt;//������շ���
public:
	SRReceiver();
	virtual ~SRReceiver();

public:
	
	void receive(const Packet &packet);	//���ձ��ģ�����NetworkService����
};

#endif


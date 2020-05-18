#ifndef SR_SENDER_H
#define SR_SENDER_H
#include "RdtSender.h"
#include<list>
#define WINDOW_SIZE 4//���ڴ�С
#define ORDER_SIZE 8//��ų���
using namespace std;

class SRSender :public RdtSender
{
private:
	int base;						//���ʹ���ͷ
	int nextseqnum;					//��һ�����͵����
	list<Packet> sndpkt;		//�ѷ��͵����ݰ�
	list<int> sndack; //�ȴ��յ���ack
	bool waitingState;				// �Ƿ��ڻ������������ȴ�Ack��״̬
public:

	bool getWaitingState();
	bool send(const Message &message);						//����Ӧ�ò�������Message����NetworkServiceSimulator����,������ͷ��ɹ��ؽ�Message���͵�����㣬����true;�����Ϊ���ͷ����ڵȴ���ȷȷ��״̬���ܾ�����Message���򷵻�false
	void receive(const Packet &ackPkt);						//����ȷ��Ack������NetworkServiceSimulator����	
	void timeoutHandler(int seqNum);					//Timeout handler������NetworkServiceSimulator����

public:
	SRSender();
	virtual ~SRSender();
};

#endif


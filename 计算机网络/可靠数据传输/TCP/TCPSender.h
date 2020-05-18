#ifndef TCP_SENDER_H
#define TCP_SENDER_H
#include "RdtSender.h"
#include<list>
#define WINDOW_SIZE 4//���ڱ��룬2λ
#define ORDER_SIZE 8//��ű��룬3λ

using namespace std;

class TCPSender :public RdtSender
{
private:
	int base;						//���ʹ���ͷ
	int nextseqnum;					//��һ�����͵����
	list<Packet> sndpkt;		//�ѷ��͵����ݰ�
	bool waitingState;				// �Ƿ��ڻ������������ȴ�Ack��״̬
	int repeat_count;				//��¼ack���ظ����������ڿ����ش�
public:

	bool getWaitingState();
	bool send(const Message &message);						//����Ӧ�ò�������Message����NetworkServiceSimulator����,������ͷ��ɹ��ؽ�Message���͵�����㣬����true;�����Ϊ���ͷ����ڵȴ���ȷȷ��״̬���ܾ�����Message���򷵻�false
	void receive(const Packet &ackPkt);						//����ȷ��Ack������NetworkServiceSimulator����	
	void timeoutHandler(int seqNum);					//Timeout handler������NetworkServiceSimulator����

public:
	TCPSender();
	virtual ~TCPSender();
};

#endif


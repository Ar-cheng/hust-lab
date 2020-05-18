#include "pch.h"
#include "Global.h"
#include "TCPSender.h"


TCPSender::TCPSender()
{
	this->base = 0;
	this->nextseqnum = 0;
	this->waitingState = false;
	this->repeat_count = 0;
}


TCPSender::~TCPSender()
{
}


bool TCPSender::getWaitingState() {
	if (sndpkt.size() == WINDOW_SIZE)
		waitingState = true;
	else 
		waitingState = false;
	return waitingState;
}


bool TCPSender::send(const Message &message) {
	if (sndpkt.size() == WINDOW_SIZE) { //������������
		waitingState = true;
		return false;
	}
	else
	{
		Packet temp;
		temp.acknum = -1;
		temp.seqnum = nextseqnum;
		temp.checksum = 0;
		memcpy(temp.payload, message.data, sizeof(message.data));//�������ݵ���������
		temp.checksum = pUtils->calculateCheckSum(temp);//��������
		sndpkt.push_back(temp);
		pUtils->printPacket("���ͷ����ͱ���", temp);
		pns->sendToNetworkLayer(RECEIVER, temp);		//����ģ�����绷����sendToNetworkLayer��ͨ������㷢�͵��Է�
		if (this->base == this->nextseqnum) {
			pns->startTimer(SENDER, Configuration::TIME_OUT, 1);//�������ͷ���ʱ��
		}
		nextseqnum = (nextseqnum + 1)%ORDER_SIZE;
		return true;
	}
}

void TCPSender::receive(const Packet &ackPkt) {
	int checksum = pUtils->calculateCheckSum(ackPkt);
	if(checksum == ackPkt.checksum)//ack���������ȷ
	{
		pUtils->printPacket("\n���ͷ���ȷ�յ�ack��",ackPkt);
		if((ackPkt.acknum - this->base +ORDER_SIZE )%ORDER_SIZE < WINDOW_SIZE&&ackPkt.acknum != this->base)//
		{	

			this->base = ackPkt.acknum;//�ۼ�ȷ�ϻ�������
			while (sndpkt.size() > 0 && sndpkt.front().seqnum != ackPkt.acknum)
				sndpkt.pop_front();
			pns->stopTimer(SENDER, 1);//�رն�ʱ��
			if (this->base != this->nextseqnum) {//����δȷ�ϵģ�������ʱ��
				pns->stopTimer(SENDER, 1);//������ʱ��
				pns->startTimer(SENDER, Configuration::TIME_OUT, 1);
			}
			this->repeat_count = 0;

			cout << "��������Ϊ:";
			for (list<Packet>::iterator itor1 = sndpkt.begin(); itor1 != sndpkt.end(); itor1++)
				cout << " " << itor1->seqnum;
			cout << endl;
		}
		else if(ackPkt.acknum == this->base)//�����ش�����
		{
			this->repeat_count +=1;
			if(this->repeat_count >= 3)//�ش�base���ݰ�
			{
				pUtils->printPacket("\n�����ش�����",sndpkt.front());
				cout << endl;
				pns->sendToNetworkLayer(RECEIVER, sndpkt.front());	//���·������ݰ�
				pns->stopTimer(SENDER,1);//������ʱ��
				pns->startTimer(SENDER,Configuration::TIME_OUT,1);
				this->repeat_count = 0;
			}
		}
	}
}

void TCPSender::timeoutHandler(int seqNum) {
	//ֻ��һ����ʱ��
	pns->stopTimer(SENDER, 1);										//���ȹرն�ʱ��
	pns->startTimer(SENDER, Configuration::TIME_OUT, 1);			//�����������ͷ���ʱ��
	cout << "���Ͷ�ʱ����ʱ"<< endl;
	pUtils->printPacket("�ط�����", sndpkt.front());
	pns->sendToNetworkLayer(RECEIVER, sndpkt.front());	//���·������ݰ�
}

#include "pch.h"
#include "Global.h"
#include "GBNSender.h"


GBNSender::GBNSender()
{
	this->base = 0;
	this->nextseqnum = 0;
	this->waitingState = false;
}


GBNSender::~GBNSender()
{
}

bool GBNSender::getWaitingState() {
	if (sndpkt.size() == WINDOW_SIZE)
		waitingState = true;
	else waitingState = false;
	return waitingState;
}

bool GBNSender::send(const Message &message) {
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
		memcpy(temp.payload,message.data,sizeof(message.data));//�������ݵ���������
		temp.checksum = pUtils->calculateCheckSum(temp);//��������
		sndpkt.push_back(temp);
		pUtils->printPacket("���ͷ����ͱ���", temp);
		pns->sendToNetworkLayer(RECEIVER,temp);		//����ģ�����绷����sendToNetworkLayer��ͨ������㷢�͵��Է�
		if (this->base == this->nextseqnum) {
			pns->startTimer(SENDER, Configuration::TIME_OUT, 1);//�������ͷ���ʱ��
		}
		nextseqnum = (nextseqnum + 1) % ORDER_SIZE ;
		return true;
	}
}

void GBNSender::receive(const Packet &ackPkt) {
	int checksum = pUtils->calculateCheckSum(ackPkt);
	if(checksum == ackPkt.checksum)//ack���������ȷ
	{
		if ((ackPkt.acknum - base + ORDER_SIZE) % ORDER_SIZE < WINDOW_SIZE) {
			this->base = (ackPkt.acknum + 1) % ORDER_SIZE;//�ۼ�ȷ��
			if (sndpkt.size() < WINDOW_SIZE)//�������ڻ�����δ��
				this->waitingState = false;
			pUtils->printPacket("���ͷ���ȷ�յ�ack��", ackPkt);
			int count = 0;//��¼���ڻ�������
			for (list<Packet>::iterator itor1 = sndpkt.begin(); itor1 != sndpkt.end(); itor1++) {
				count++;
				if (itor1->seqnum == ackPkt.acknum)
					break;
			}
			
			for (int i = 0; i < count; i++)
				sndpkt.pop_front();

			cout << "��������Ϊ:";
			for (list<Packet>::iterator itor1 = sndpkt.begin(); itor1 != sndpkt.end(); itor1++)
				cout << " " << itor1->seqnum;
			cout << endl;


			if (this->nextseqnum == this->base)//�ѽ������رն�ʱ��
			{
				this->waitingState = false;
				pns->stopTimer(SENDER, 1);
			}
			else//������ʱ��
			{
				this->waitingState = false;
				pns->stopTimer(SENDER, 1);
				pns->startTimer(SENDER, Configuration::TIME_OUT, 1);
			}
		}
	}
}

void GBNSender::timeoutHandler(int seqNum) {
	//ֻ��һ����ʱ��
	pns->stopTimer(SENDER, 1);										//���ȹرն�ʱ��
	cout << "���Ͷ�ʱ����ʱ" << endl;
	pns->startTimer(SENDER, Configuration::TIME_OUT, 1);			//�����������ͷ���ʱ��
 	for (list<Packet>::iterator itor1 = sndpkt.begin(); itor1 != sndpkt.end(); itor1++) {
		{
			pUtils->printPacket("�ط��ϴη��͵ı���", *itor1);
			pns->sendToNetworkLayer(RECEIVER, *itor1);	//���·������ݰ�
		}
	}
}

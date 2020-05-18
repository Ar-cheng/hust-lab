#include "pch.h"
#include "Global.h"
#include "SRSender.h"


SRSender::SRSender()
{
	this->base = 0;
	this->nextseqnum = 0;
	this->waitingState = false;
}


SRSender::~SRSender()
{
}

bool SRSender::getWaitingState() {
	if (sndpkt.size() == WINDOW_SIZE)
		waitingState = true;
	else waitingState = false;
	return waitingState;
}

bool SRSender::send(const Message &message) {
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
		sndack.push_back(temp.seqnum);
		pUtils->printPacket("���ͷ����ͱ���", temp);

		cout << "��������Ϊ:";
		for (list<Packet>::iterator itor1 = sndpkt.begin(); itor1 != sndpkt.end(); itor1++)
			cout << " " << itor1->seqnum;
		cout << endl;

		cout << "�����ڵȴ���ack��:";
		for (list<int>::iterator itor1 = sndack.begin(); itor1 != sndack.end(); itor1++)
			cout << " " << *itor1;
		cout << endl;

		pns->sendToNetworkLayer(RECEIVER, temp);		//����ģ�����绷����sendToNetworkLayer��ͨ������㷢�͵��Է�
		pns->startTimer(SENDER, Configuration::TIME_OUT, temp.seqnum);//ÿ�����ľ��м�ʱ��
		nextseqnum = (nextseqnum + 1) % ORDER_SIZE;
		return true;
	}
}

void SRSender::receive(const Packet &ackPkt) {
	int checksum = pUtils->calculateCheckSum(ackPkt);
	if (checksum == ackPkt.checksum)//ack���������ȷ
	{
		if ((ackPkt.acknum - base + ORDER_SIZE) % ORDER_SIZE < WINDOW_SIZE) {
			for (list<int>::iterator itor1 = sndack.begin(); itor1 != sndack.end(); itor1++) {
				if (*itor1 == ackPkt.acknum) {
					sndack.erase(itor1);
					pns->stopTimer(SENDER,ackPkt.acknum);
					break;
				}
			}
			if (sndack.size() != 0)
			{
				while (sndpkt.front().seqnum != sndack.front())//�������ڵ��������յ�������ack֮��
					sndpkt.pop_front();
				base = sndack.front();
			}
			else {//�������ھ����յ�ȷ��
				sndpkt.clear();
				base = nextseqnum;
			}
			pUtils->printPacket("���ͷ���ȷ�յ�ack��", ackPkt);

			cout << "��������Ϊ:";
			for (list<Packet>::iterator itor1 = sndpkt.begin(); itor1 != sndpkt.end(); itor1++)
				cout << " " << itor1->seqnum;
			cout << endl;

			cout << "�����ڵȴ���ack��:";
			for (list<int>::iterator itor1 = sndack.begin(); itor1 != sndack.end(); itor1++)
				cout << " " << *itor1;
			cout << endl;
		}
	}
}

void SRSender::timeoutHandler(int seqNum) {
	pns->stopTimer(SENDER, seqNum);										//���ȹرն�ʱ��
	cout << "���Ͷ�ʱ����ʱ" << endl;
	//��ƥ�䷢�͵ı���
	list<Packet>::iterator itor1;
	for (itor1 = sndpkt.begin(); itor1 != sndpkt.end();) {
		if (itor1->seqnum == seqNum)
			break;
		else
			itor1++;
	}
	pUtils->printPacket("�ط��ϴη��͵ı���", *itor1);
	pns->startTimer(SENDER, Configuration::TIME_OUT, seqNum);			//�����������ͷ���ʱ��
	pns->sendToNetworkLayer(RECEIVER, *itor1);	//���·������ݰ�
}

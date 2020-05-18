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
	if (sndpkt.size() == WINDOW_SIZE) { //滑动窗口已满
		waitingState = true;
		return false;
	}
	else
	{
		Packet temp;
		temp.acknum = -1;
		temp.seqnum = nextseqnum;
		temp.checksum = 0;
		memcpy(temp.payload, message.data, sizeof(message.data));//拷贝数据到滑动窗口
		temp.checksum = pUtils->calculateCheckSum(temp);//计算检验和
		sndpkt.push_back(temp);
		sndack.push_back(temp.seqnum);
		pUtils->printPacket("发送方发送报文", temp);

		cout << "滑动窗口为:";
		for (list<Packet>::iterator itor1 = sndpkt.begin(); itor1 != sndpkt.end(); itor1++)
			cout << " " << itor1->seqnum;
		cout << endl;

		cout << "窗口内等待的ack有:";
		for (list<int>::iterator itor1 = sndack.begin(); itor1 != sndack.end(); itor1++)
			cout << " " << *itor1;
		cout << endl;

		pns->sendToNetworkLayer(RECEIVER, temp);		//调用模拟网络环境的sendToNetworkLayer，通过网络层发送到对方
		pns->startTimer(SENDER, Configuration::TIME_OUT, temp.seqnum);//每个报文均有计时器
		nextseqnum = (nextseqnum + 1) % ORDER_SIZE;
		return true;
	}
}

void SRSender::receive(const Packet &ackPkt) {
	int checksum = pUtils->calculateCheckSum(ackPkt);
	if (checksum == ackPkt.checksum)//ack包检验和正确
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
				while (sndpkt.front().seqnum != sndack.front())//滑动窗口到所有已收到的连续ack之后
					sndpkt.pop_front();
				base = sndack.front();
			}
			else {//滑动窗口均已收到确认
				sndpkt.clear();
				base = nextseqnum;
			}
			pUtils->printPacket("发送方正确收到ack包", ackPkt);

			cout << "滑动窗口为:";
			for (list<Packet>::iterator itor1 = sndpkt.begin(); itor1 != sndpkt.end(); itor1++)
				cout << " " << itor1->seqnum;
			cout << endl;

			cout << "窗口内等待的ack有:";
			for (list<int>::iterator itor1 = sndack.begin(); itor1 != sndack.end(); itor1++)
				cout << " " << *itor1;
			cout << endl;
		}
	}
}

void SRSender::timeoutHandler(int seqNum) {
	pns->stopTimer(SENDER, seqNum);										//首先关闭定时器
	cout << "发送定时器超时" << endl;
	//先匹配发送的报文
	list<Packet>::iterator itor1;
	for (itor1 = sndpkt.begin(); itor1 != sndpkt.end();) {
		if (itor1->seqnum == seqNum)
			break;
		else
			itor1++;
	}
	pUtils->printPacket("重发上次发送的报文", *itor1);
	pns->startTimer(SENDER, Configuration::TIME_OUT, seqNum);			//重新启动发送方定时器
	pns->sendToNetworkLayer(RECEIVER, *itor1);	//重新发送数据包
}

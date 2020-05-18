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
		memcpy(temp.payload,message.data,sizeof(message.data));//拷贝数据到滑动窗口
		temp.checksum = pUtils->calculateCheckSum(temp);//计算检验和
		sndpkt.push_back(temp);
		pUtils->printPacket("发送方发送报文", temp);
		pns->sendToNetworkLayer(RECEIVER,temp);		//调用模拟网络环境的sendToNetworkLayer，通过网络层发送到对方
		if (this->base == this->nextseqnum) {
			pns->startTimer(SENDER, Configuration::TIME_OUT, 1);//启动发送方定时器
		}
		nextseqnum = (nextseqnum + 1) % ORDER_SIZE ;
		return true;
	}
}

void GBNSender::receive(const Packet &ackPkt) {
	int checksum = pUtils->calculateCheckSum(ackPkt);
	if(checksum == ackPkt.checksum)//ack包检验和正确
	{
		if ((ackPkt.acknum - base + ORDER_SIZE) % ORDER_SIZE < WINDOW_SIZE) {
			this->base = (ackPkt.acknum + 1) % ORDER_SIZE;//累计确认
			if (sndpkt.size() < WINDOW_SIZE)//滑动窗口滑动后未满
				this->waitingState = false;
			pUtils->printPacket("发送方正确收到ack包", ackPkt);
			int count = 0;//记录窗口滑动个数
			for (list<Packet>::iterator itor1 = sndpkt.begin(); itor1 != sndpkt.end(); itor1++) {
				count++;
				if (itor1->seqnum == ackPkt.acknum)
					break;
			}
			
			for (int i = 0; i < count; i++)
				sndpkt.pop_front();

			cout << "滑动窗口为:";
			for (list<Packet>::iterator itor1 = sndpkt.begin(); itor1 != sndpkt.end(); itor1++)
				cout << " " << itor1->seqnum;
			cout << endl;


			if (this->nextseqnum == this->base)//已结束，关闭定时器
			{
				this->waitingState = false;
				pns->stopTimer(SENDER, 1);
			}
			else//重启定时器
			{
				this->waitingState = false;
				pns->stopTimer(SENDER, 1);
				pns->startTimer(SENDER, Configuration::TIME_OUT, 1);
			}
		}
	}
}

void GBNSender::timeoutHandler(int seqNum) {
	//只有一个定时器
	pns->stopTimer(SENDER, 1);										//首先关闭定时器
	cout << "发送定时器超时" << endl;
	pns->startTimer(SENDER, Configuration::TIME_OUT, 1);			//重新启动发送方定时器
 	for (list<Packet>::iterator itor1 = sndpkt.begin(); itor1 != sndpkt.end(); itor1++) {
		{
			pUtils->printPacket("重发上次发送的报文", *itor1);
			pns->sendToNetworkLayer(RECEIVER, *itor1);	//重新发送数据包
		}
	}
}

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
		pUtils->printPacket("发送方发送报文", temp);
		pns->sendToNetworkLayer(RECEIVER, temp);		//调用模拟网络环境的sendToNetworkLayer，通过网络层发送到对方
		if (this->base == this->nextseqnum) {
			pns->startTimer(SENDER, Configuration::TIME_OUT, 1);//启动发送方定时器
		}
		nextseqnum = (nextseqnum + 1)%ORDER_SIZE;
		return true;
	}
}

void TCPSender::receive(const Packet &ackPkt) {
	int checksum = pUtils->calculateCheckSum(ackPkt);
	if(checksum == ackPkt.checksum)//ack包检验和正确
	{
		pUtils->printPacket("\n发送方正确收到ack包",ackPkt);
		if((ackPkt.acknum - this->base +ORDER_SIZE )%ORDER_SIZE < WINDOW_SIZE&&ackPkt.acknum != this->base)//
		{	

			this->base = ackPkt.acknum;//累计确认滑动窗口
			while (sndpkt.size() > 0 && sndpkt.front().seqnum != ackPkt.acknum)
				sndpkt.pop_front();
			pns->stopTimer(SENDER, 1);//关闭定时器
			if (this->base != this->nextseqnum) {//还有未确认的，重启定时器
				pns->stopTimer(SENDER, 1);//重启定时器
				pns->startTimer(SENDER, Configuration::TIME_OUT, 1);
			}
			this->repeat_count = 0;

			cout << "滑动窗口为:";
			for (list<Packet>::iterator itor1 = sndpkt.begin(); itor1 != sndpkt.end(); itor1++)
				cout << " " << itor1->seqnum;
			cout << endl;
		}
		else if(ackPkt.acknum == this->base)//快速重传机制
		{
			this->repeat_count +=1;
			if(this->repeat_count >= 3)//重传base数据包
			{
				pUtils->printPacket("\n快速重传报文",sndpkt.front());
				cout << endl;
				pns->sendToNetworkLayer(RECEIVER, sndpkt.front());	//重新发送数据包
				pns->stopTimer(SENDER,1);//重启定时器
				pns->startTimer(SENDER,Configuration::TIME_OUT,1);
				this->repeat_count = 0;
			}
		}
	}
}

void TCPSender::timeoutHandler(int seqNum) {
	//只有一个定时器
	pns->stopTimer(SENDER, 1);										//首先关闭定时器
	pns->startTimer(SENDER, Configuration::TIME_OUT, 1);			//重新启动发送方定时器
	cout << "发送定时器超时"<< endl;
	pUtils->printPacket("重发报文", sndpkt.front());
	pns->sendToNetworkLayer(RECEIVER, sndpkt.front());	//重新发送数据包
}

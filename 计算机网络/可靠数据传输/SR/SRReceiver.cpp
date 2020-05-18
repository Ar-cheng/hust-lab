#include "pch.h"
#include "Global.h"
#include "SRReceiver.h"

SRReceiver::SRReceiver()
{
	rcvbase = 0;
	sndpkt.acknum = -1;//-1表示接收方确认无效
	sndpkt.seqnum = -1;
	pkt_count = 0;
	memset(sndpkt.payload, 0, Configuration::PAYLOAD_SIZE);
	sndpkt.checksum = pUtils->calculateCheckSum(sndpkt);
}

SRReceiver::~SRReceiver()
{
}

void SRReceiver::receive(const Packet &packet) {
	int checksum;
	int flag = 0;
	int count = 0;
	int rcvbase_last = rcvbase;
	checksum = pUtils->calculateCheckSum(packet);

	if (checksum == packet.checksum) {

		sndpkt.acknum = packet.seqnum;
		sndpkt.seqnum = -1;
		sndpkt.checksum = pUtils->calculateCheckSum(sndpkt);

		pUtils->printPacket("\n接收方发送确认报文：", sndpkt);

		pns->sendToNetworkLayer(SENDER, sndpkt);

		if ((packet.seqnum - rcvbase + ORDER_SIZE) % ORDER_SIZE >= WINDOW_SIZE)
			return;//不在窗口内忽略该分组

		list<Packet>::iterator itor1;

		for (itor1 = rcvpkt.begin(); itor1 != rcvpkt.end(); itor1++) {
			if (packet.seqnum == itor1->seqnum) {
				flag = 1; 
				break;
			}
			else if ((packet.seqnum - rcvbase + ORDER_SIZE) % ORDER_SIZE < (itor1->seqnum - rcvbase + ORDER_SIZE) % ORDER_SIZE)
				break;
		}

		if (itor1 == rcvpkt.end()) {//在后面末尾插入
			rcvpkt.push_back(packet);
			pkt_count++;
		}

		else if (flag == 0) {//缓存中不存在该分组
			rcvpkt.insert(itor1, packet);
			pkt_count++;
		}


		if (rcvpkt.begin()->seqnum == rcvbase) {
			for (itor1 = rcvpkt.begin(); itor1 != rcvpkt.end() && itor1->seqnum == rcvbase; itor1++) {
				Message sendmessage;
				memset(sendmessage.data, 0, Configuration::PAYLOAD_SIZE);
				memcpy(sendmessage.data, (*itor1).payload, sizeof(itor1->payload));
				pns->delivertoAppLayer(RECEIVER, sendmessage);
				rcvbase = (rcvbase + 1) % ORDER_SIZE;
				count++;
			}
		}

		cout << "\n接收方缓存窗口为：";
		for (itor1 = rcvpkt.begin(); itor1 != rcvpkt.end(); itor1++) {
			cout <<" "<< itor1->seqnum;
		}
		cout << endl<<endl;

		if (itor1 == rcvpkt.end() && rcvbase == rcvbase_last)
			count = 0;

		int packetcount_old = pkt_count;

		for (int i = 0; i < count; i++) {
			rcvpkt.pop_front();
			pkt_count--;
		}
	}
	else {
		pUtils->printPacket("\n\n接收方没有正确收到发送方的报文，数据校验错误，忽略该分组", packet);
	}
}
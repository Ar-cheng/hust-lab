// SR.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include "Global.h"
#include "RdtSender.h"
#include "RdtReceiver.h"
#include "SRSender.h"
#include "SRReceiver.h"


int main(int argc, char* argv[])
{
	RdtSender *ps = new SRSender();
	RdtReceiver * pr = new SRReceiver();
	//	pns->setRunMode(0);  //VERBOS模式
	pns->setRunMode(1);  //安静模式
	pns->init();
	pns->setRtdSender(ps);
	pns->setRtdReceiver(pr);
	pns->setInputFile("C:\\Users\\朱志成\\Desktop\\可靠数据传输\\input.txt");
	pns->setOutputFile("C:\\Users\\朱志成\\Desktop\\可靠数据传输\\output.txt");

	pns->start();

	delete ps;
	delete pr;
	delete pUtils;									//指向唯一的工具类实例，只在main函数结束前delete
	delete pns;										//指向唯一的模拟网络环境类实例，只在main函数结束前delete

	return 0;
}

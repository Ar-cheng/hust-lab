#include"server.h"

int main() {
	while (1) {
		char input;
		system("cls");
		cout << "\ns:启动服务器;   p:停止服务器\n\n";
		input = _getch();//使用_getch()函数获取按下的键值
		if (input == 's') {
			server myserver;
			myserver.start();
		}//当按下s时启动服务器
	}
}
#include"server.h"

int main() {
	while (1) {
		char input;
		system("cls");
		cout << "\ns:����������;   p:ֹͣ������\n\n";
		input = _getch();//ʹ��_getch()������ȡ���µļ�ֵ
		if (input == 's') {
			server myserver;
			myserver.start();
		}//������sʱ����������
	}
}
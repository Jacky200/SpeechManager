#include"SpeechManager.h"

int main() {
	srand((unsigned int)time(NULL));

	SpeechManager sm;
	while (true)
	{
		sm.Show_Menu();
		cout << "����������ѡ��:" << endl;
		int choice = 0;
		cin >> choice;
		switch (choice)
		{
		case 1: //��ʼ����
			sm.SpeechStart();
			break;
		case 2: //�鿴�����¼ 
			sm.Show_Winner();
			break;
		case 3: //���ϵͳ��Ϣ
			sm.Speech_Clear();
			break;
		case 4: //�˳�����
			sm.ExitSystem();
			break;
		default:
			cout << "�����������������" << endl;
			break;
		}

		system("pause");
		system("cls");
	}
	return 0;
}
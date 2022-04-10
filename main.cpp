#include"SpeechManager.h"

int main() {
	srand((unsigned int)time(NULL));

	SpeechManager sm;
	while (true)
	{
		sm.Show_Menu();
		cout << "请输入您的选择:" << endl;
		int choice = 0;
		cin >> choice;
		switch (choice)
		{
		case 1: //开始比赛
			sm.SpeechStart();
			break;
		case 2: //查看往届记录 
			sm.Show_Winner();
			break;
		case 3: //清空系统信息
			sm.Speech_Clear();
			break;
		case 4: //退出程序
			sm.ExitSystem();
			break;
		default:
			cout << "输入错误，请重新输入" << endl;
			break;
		}

		system("pause");
		system("cls");
	}
	return 0;
}
#include"Speecher.h"
#include<vector>
#include<map>
#include<algorithm>
#include<deque>
#include<numeric>
#include<fstream>
#include<ctime>


#define FILEPATH "speech.csv"


class SpeechManager {
public:
	//���캯��
	SpeechManager();

	//�˵���ʾ����
	void Show_Menu();

	//�˳�ϵͳ����
	void ExitSystem();

	//��ʼ������
	void SpeechInit();

	//��ʼ����
	void SpeechStart();

	//��������ѡ�ֺ���
	void CreateSpeecher();

	//��ǩ����
	void SpeechDraw(vector<int>& s);
	

	//�����֣�ȡǰ3������v2����

	void SpeechScore(vector<int>& s);

	
	//��ʾ�ھ�����������ʾ��������
	void Show_Over(const vector<int>& s);

	//������Ϣ���ļ���
	void Winner_Save();

	//�鿴����Ļ�ʤ��Ϣ
	void Show_Winner();

	//����ĵ�
	void Speech_Clear();

	//��������
	~SpeechManager();

	//�����������

	//������������


	bool FileIsEmpty=true;//�ļ��Ƿ�Ϊ��
	 
	vector<int>v1;  //��һ�α�����Ա�ĳ�ǩ��

	vector<int>v2; //�ڶ��α�����Ա�ĳ�ǩ��

	vector<int>Vectory; //����ʤ�ߵĺ�

	map<int ,Speecher>mp;//��ǩ����ѡ��

	vector<string>Winer;//��¼�Ͷ�ȡ��ʤ����

	int Round=0 ; //�ڼ��ֱ���

	int Term = 1;//�ڼ���
};
#include"SpeechManager.h"

SpeechManager::SpeechManager()
{
	ifstream ifs;
	ifs.open(FILEPATH, ios::in);
	if (!ifs.is_open()) {//�ļ�������
		this->FileIsEmpty = true;
		this->Term = 0;
		this->SpeechInit();
		this->Winer.clear();
		return;
	}
	char ch;
	ifs >> ch;
	if (ifs.eof()) {//�ļ����ڣ�����Ϊ��
		this->FileIsEmpty = true;
		this->Term = 0;
		this->SpeechInit();
		this->Winer.clear();
		return;
	}
	ifs.putback(ch);//���ظոյ�һ���ֽ�
	string data;
	
	while (getline(ifs,data)) {
		int pos = -1;
		int start = 0;
		while (true)
		{
			pos = data.find(",", start);
			if (pos == -1) {
				break; //û�У�����
			}
			else {
				string temp = data.substr(start, pos-start);
				Winer.push_back(temp);
			}
			start = pos + 1;
		}
		string temp = data.substr(start, data.size());
		Winer.push_back(temp);
	}
	this->FileIsEmpty = false;
	this->Term = Winer.size() / 9;
	this->SpeechInit();
	
}

void SpeechManager::Show_Menu()
{
	cout << "*********************************" << endl;
	cout << "********** ��ӭ�μӱ��� *********" << endl;
	cout << "********** 1.��ʼ���� ***********" << endl;
	cout << "********** 2.�鿴��¼ ***********" << endl;
	cout << "********** 3.���ϵͳ ***********" << endl;
	cout << "********** 4.�˳����� ***********" << endl;
	cout << "*********************************" << endl;
}

void SpeechManager::ExitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}

void SpeechManager::SpeechStart()
{
	//��ӳ�Ա
	this->CreateSpeecher();
	//��ʼ��һ�ֳ�ǩ
	this->Round = 1;
	this->SpeechDraw(v1);

	//���б������鲢���д��
	this->SpeechScore(v1);
	//��ʼ�ڶ��ֳ�ǩ
	this->Round++;
	this->SpeechDraw(v2);
	//���о����Ĵ��
	this->SpeechScore(v2);
	//��ʾ�ھ��Ǿ�����
	this->Show_Over(Vectory);

	//������Ϣ���ļ���
	this->Winner_Save();

	SpeechInit();
}

void SpeechManager::CreateSpeecher()
{
	string str_name = "ABCDEFGHIJKl";
	for (int i = 0; i < 12; i++) {
		v1.push_back(10001 + i);//���뵽v1������
		string name = "ѡ��";
		name += str_name[i];
		mp.insert(make_pair(10001 + i, Speecher(name)));
	}
}

void SpeechManager::SpeechDraw(vector<int>& s)
{
	cout << "-------��ǩ�������-------" << endl;
	random_shuffle(s.begin(), s.end());
	for (vector<int>::iterator it = s.begin(); it != s.end(); it++) {
		cout << (*it) << " ";
	}
	cout << endl;
	system("pause");
}


void SpeechManager::SpeechScore(vector<int>& s)
{
	deque<double>Score;
	multimap<double, int,greater<double>>mulmp;//��¼�����ͳ�ǩ�ŵĹ�ϵ
	if (this->Round == 1) {
		int num = 0;
		for (vector<int>::iterator it = s.begin(); it != s.end(); it++) {
			for (int i = 0; i < 10; i++) {
				double score = (rand() % 401 + 600) / 10.f;
				Score.push_back(score);
			}
			sort(Score.begin(), Score.end(), greater<double>());//����
			Score.pop_back();
			Score.pop_front();
			double total = accumulate(Score.begin(), Score.end(), 0.0f);
			double avg = total / (double)Score.size();
			num++;

			mp[*it].m_Score[0] = avg;

			mulmp.insert(pair<double, int>(avg, *it));

			if (num % 6 == 0) {
				if (num / 6 == 1) {
					cout << "��һ���Ա�ķ���Ϊ:" << endl;
					for (multimap<double, int, greater<double>>::iterator its = mulmp.begin(); its != mulmp.end(); its++) {
						cout << mp[its->second].m_Name <<" ǩ��: "<<its->second << " ����:" << its->first << endl;
					}

					//��ǰ�����ı�ŷŵ�v2������
					int count = 0;
					for (multimap<double, int, greater<double>>::iterator its = mulmp.begin(); count < 3; its++,count++) {
						v2.push_back(its->second);
					}
					mulmp.clear();//���
				}
				else {
					cout << "�ڶ����Ա�ķ���Ϊ:" << endl;
					for (multimap<double, int, greater<double>>::iterator its = mulmp.begin(); its != mulmp.end(); its++) {
						cout << mp[its->second].m_Name  <<" ǩ��: " << its->second<<" ����:" << its->first << endl;
					}

					//��ǰ�����ı�ŷŵ�v2������
					int count = 0;
					for (multimap<double, int, greater<double>>::iterator its = mulmp.begin(); count < 3; its++, count++) {
						v2.push_back(its->second);
					}
					mulmp.clear();//���
				}
			}
		}
	}
	else {
		for (vector<int>::iterator it = s.begin(); it != s.end(); it++) {
			for (int i = 0; i < 10; i++) {
				double score = (rand() % 401 + 600) / 10.f;
				Score.push_back(score);
			}
			sort(Score.begin(), Score.end(), greater<double>());
			Score.pop_back();
			Score.pop_front();

			double total = accumulate(Score.begin(), Score.end(), 0.0f);
			double avg = total / (double)Score.size();

			mp[*it].m_Score[1] = avg;

			mulmp.insert(make_pair(avg, *it));
		}

		for (multimap<double, int, greater<double>>::iterator its = mulmp.begin(); its != mulmp.end(); its++) {
			cout << mp[its->second].m_Name<<"ǩ��: "<<its->second << " ����" << its->first << endl;
		}

		int count = 0;
		for (multimap<double, int, greater<double>>::iterator itss = mulmp.begin(); count<3;count++, itss++) {
			Vectory.push_back(itss->second);
		}
	}

	system("pause");
}


void SpeechManager::SpeechInit()
{
	this->v1.clear();
	this->v2.clear();
	this->Vectory.clear();
	this->mp.clear();
	this->Round = 0;
}

void SpeechManager::Show_Over(const vector<int>& s)
{
	cout << "----��"<<this->Term+1 << "���������----" << endl;
	int count = 0;
	for (vector<int>::const_iterator it = s.begin(); it != s.end(); it++,count++) {
		if (count == 0) {
			cout << "�ھ�:" << mp[*it].m_Name <<" ǩ��:"<<*it << " ����:" << mp[*it].m_Score[1] << endl;
		}
		else if (count == 1) {
			cout << "�Ǿ�:" << mp[*it].m_Name << " ǩ��:" << *it << " ����:" << mp[*it].m_Score[1] << endl;
		}
		else {
			cout << "����:" << mp[*it].m_Name << " ǩ��:" << *it << " ����:" << mp[*it].m_Score[1] << endl;
		}
		
	}
}

void SpeechManager::Winner_Save()
{
	ofstream ofs;
	ofs.open(FILEPATH, ios::out | ios::app);
	for (vector<int>::iterator it = Vectory.begin(); it != Vectory.end(); it++) {
		ofs << (*it) << "," << mp[*it].m_Name<<"," << mp[*it].m_Score[1] << endl;
		Winer.push_back(to_string(*it));
		Winer.push_back(mp[*it].m_Name);
		Winer.push_back(to_string(mp[*it].m_Score[1]));
	}
	cout << "�ѱ���ɹ�" << endl;
	this->FileIsEmpty = false;
	this->Term = Winer.size() / 9;
	ofs.close();
}

void SpeechManager::Show_Winner()
{
	if (this->FileIsEmpty) {
		cout << "��ǰϵͳ����Ϊ��,�뿪ʼ���б���" << endl;
	}
	else {
		cout << "һ��������" << this->Term << "������" << endl;
		int num = 0;
		for (vector<string>::iterator it = Winer.begin(); it != Winer.end(); it = it + 9) {
			cout << "*�ھ� ǩ��:" << *it << " ����:" << *(it + 1) << " ����:" << *(it + 2) <<
				" *�Ǿ� ǩ��:" << *(it + 3) << " ����:" << *(it + 4) << " ����:" << *(it + 5) <<
				" *���� ǩ��:" << *(it + 6) << " ����:" << *(it + 7) << " ����:" << *(it + 8) << endl;
		}
	}
}


void SpeechManager::Speech_Clear()
{
	cout << "�Ƿ�ȷ�����ϵͳ��Ϣ?" << endl;
	cout << "1.ȷ��" << endl;
	cout << "2.������ҳ��" << endl;
	int select = 0;
	cin >> select;
	if (select == 1) {
		ofstream ofs;
		ofs.open(FILEPATH, ios::trunc);
		this->Winer.clear();
		this->FileIsEmpty = true;
		this->Term = 0;
		this->SpeechInit();
		cout << "����ɹ�" << endl;
		return;
	}
	else {
		return;
	}
}

SpeechManager::~SpeechManager()
{

}
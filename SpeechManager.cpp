#include"SpeechManager.h"

SpeechManager::SpeechManager()
{
	ifstream ifs;
	ifs.open(FILEPATH, ios::in);
	if (!ifs.is_open()) {//文件不存在
		this->FileIsEmpty = true;
		this->Term = 0;
		this->SpeechInit();
		this->Winer.clear();
		return;
	}
	char ch;
	ifs >> ch;
	if (ifs.eof()) {//文件存在，但是为空
		this->FileIsEmpty = true;
		this->Term = 0;
		this->SpeechInit();
		this->Winer.clear();
		return;
	}
	ifs.putback(ch);//读回刚刚的一个字节
	string data;
	
	while (getline(ifs,data)) {
		int pos = -1;
		int start = 0;
		while (true)
		{
			pos = data.find(",", start);
			if (pos == -1) {
				break; //没有，号了
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
	cout << "********** 欢迎参加比赛 *********" << endl;
	cout << "********** 1.开始比赛 ***********" << endl;
	cout << "********** 2.查看记录 ***********" << endl;
	cout << "********** 3.清空系统 ***********" << endl;
	cout << "********** 4.退出程序 ***********" << endl;
	cout << "*********************************" << endl;
}

void SpeechManager::ExitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}

void SpeechManager::SpeechStart()
{
	//添加成员
	this->CreateSpeecher();
	//开始第一轮抽签
	this->Round = 1;
	this->SpeechDraw(v1);

	//进行比赛分组并进行打分
	this->SpeechScore(v1);
	//开始第二轮抽签
	this->Round++;
	this->SpeechDraw(v2);
	//进行决赛的打分
	this->SpeechScore(v2);
	//显示冠军亚军季军
	this->Show_Over(Vectory);

	//保存信息到文件中
	this->Winner_Save();

	SpeechInit();
}

void SpeechManager::CreateSpeecher()
{
	string str_name = "ABCDEFGHIJKl";
	for (int i = 0; i < 12; i++) {
		v1.push_back(10001 + i);//插入到v1容器中
		string name = "选手";
		name += str_name[i];
		mp.insert(make_pair(10001 + i, Speecher(name)));
	}
}

void SpeechManager::SpeechDraw(vector<int>& s)
{
	cout << "-------抽签结果如下-------" << endl;
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
	multimap<double, int,greater<double>>mulmp;//记录分数和抽签号的关系
	if (this->Round == 1) {
		int num = 0;
		for (vector<int>::iterator it = s.begin(); it != s.end(); it++) {
			for (int i = 0; i < 10; i++) {
				double score = (rand() % 401 + 600) / 10.f;
				Score.push_back(score);
			}
			sort(Score.begin(), Score.end(), greater<double>());//降序
			Score.pop_back();
			Score.pop_front();
			double total = accumulate(Score.begin(), Score.end(), 0.0f);
			double avg = total / (double)Score.size();
			num++;

			mp[*it].m_Score[0] = avg;

			mulmp.insert(pair<double, int>(avg, *it));

			if (num % 6 == 0) {
				if (num / 6 == 1) {
					cout << "第一组成员的分数为:" << endl;
					for (multimap<double, int, greater<double>>::iterator its = mulmp.begin(); its != mulmp.end(); its++) {
						cout << mp[its->second].m_Name <<" 签号: "<<its->second << " 分数:" << its->first << endl;
					}

					//将前三名的编号放到v2容器中
					int count = 0;
					for (multimap<double, int, greater<double>>::iterator its = mulmp.begin(); count < 3; its++,count++) {
						v2.push_back(its->second);
					}
					mulmp.clear();//清空
				}
				else {
					cout << "第二组成员的分数为:" << endl;
					for (multimap<double, int, greater<double>>::iterator its = mulmp.begin(); its != mulmp.end(); its++) {
						cout << mp[its->second].m_Name  <<" 签号: " << its->second<<" 分数:" << its->first << endl;
					}

					//将前三名的编号放到v2容器中
					int count = 0;
					for (multimap<double, int, greater<double>>::iterator its = mulmp.begin(); count < 3; its++, count++) {
						v2.push_back(its->second);
					}
					mulmp.clear();//清空
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
			cout << mp[its->second].m_Name<<"签号: "<<its->second << " 分数" << its->first << endl;
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
	cout << "----第"<<this->Term+1 << "届比赛结束----" << endl;
	int count = 0;
	for (vector<int>::const_iterator it = s.begin(); it != s.end(); it++,count++) {
		if (count == 0) {
			cout << "冠军:" << mp[*it].m_Name <<" 签号:"<<*it << " 分数:" << mp[*it].m_Score[1] << endl;
		}
		else if (count == 1) {
			cout << "亚军:" << mp[*it].m_Name << " 签号:" << *it << " 分数:" << mp[*it].m_Score[1] << endl;
		}
		else {
			cout << "季军:" << mp[*it].m_Name << " 签号:" << *it << " 分数:" << mp[*it].m_Score[1] << endl;
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
	cout << "已保存成功" << endl;
	this->FileIsEmpty = false;
	this->Term = Winer.size() / 9;
	ofs.close();
}

void SpeechManager::Show_Winner()
{
	if (this->FileIsEmpty) {
		cout << "当前系统内容为空,请开始举行比赛" << endl;
	}
	else {
		cout << "一共举行了" << this->Term << "场比赛" << endl;
		int num = 0;
		for (vector<string>::iterator it = Winer.begin(); it != Winer.end(); it = it + 9) {
			cout << "*冠军 签号:" << *it << " 姓名:" << *(it + 1) << " 分数:" << *(it + 2) <<
				" *亚军 签号:" << *(it + 3) << " 姓名:" << *(it + 4) << " 分数:" << *(it + 5) <<
				" *季军 签号:" << *(it + 6) << " 姓名:" << *(it + 7) << " 分数:" << *(it + 8) << endl;
		}
	}
}


void SpeechManager::Speech_Clear()
{
	cout << "是否确认清空系统信息?" << endl;
	cout << "1.确认" << endl;
	cout << "2.返回主页面" << endl;
	int select = 0;
	cin >> select;
	if (select == 1) {
		ofstream ofs;
		ofs.open(FILEPATH, ios::trunc);
		this->Winer.clear();
		this->FileIsEmpty = true;
		this->Term = 0;
		this->SpeechInit();
		cout << "清除成功" << endl;
		return;
	}
	else {
		return;
	}
}

SpeechManager::~SpeechManager()
{

}
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
	//构造函数
	SpeechManager();

	//菜单显示函数
	void Show_Menu();

	//退出系统函数
	void ExitSystem();

	//初始化函数
	void SpeechInit();

	//开始比赛
	void SpeechStart();

	//创建参赛选手函数
	void CreateSpeecher();

	//抽签函数
	void SpeechDraw(vector<int>& s);
	

	//分组打分，取前3名放入v2函数

	void SpeechScore(vector<int>& s);

	
	//显示冠军函数，并提示比赛结束
	void Show_Over(const vector<int>& s);

	//保存信息到文件中
	void Winner_Save();

	//查看往届的获胜信息
	void Show_Winner();

	//清空文档
	void Speech_Clear();

	//析构函数
	~SpeechManager();

	//定义程序属性

	//添加随机数种子


	bool FileIsEmpty=true;//文件是否为空
	 
	vector<int>v1;  //第一次比赛人员的抽签号

	vector<int>v2; //第二次比赛人员的抽签号

	vector<int>Vectory; //最后决胜者的号

	map<int ,Speecher>mp;//抽签号与选手

	vector<string>Winer;//记录和读取获胜的人

	int Round=0 ; //第几轮比赛

	int Term = 1;//第几届
};
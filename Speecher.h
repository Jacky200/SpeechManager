#pragma once
#include<string>
#include<iostream>
using namespace std;
class Speecher {
public:
	Speecher() {};
	Speecher(string name) {
		this->m_Name = name;
	}
	string m_Name;
	double m_Score[2] = {0};
};
#include <iostream>
#include <vector>
#include <sstream>
#include <math.h>
using namespace std;
template <class Type>


Type stringToNum(const string& str)
{
	istringstream iss(str);
	Type num;
	iss >> num;
	return num;
}
string doubleToString(double num)
{
	char str[256];
	sprintf(str, "%lf", num);
	string result = str;
	return result;
}
string strcl(const char * a, const char *  b) {
	int i = 0;
	do
	{
		i++;
	} while (a[i - 1] == b[i - 1]);
	char *p = new char[i];
	for (int k = 0;k < i;k++) {
		p[k] = a[k];
	}
	p[i - 1] = 0;
	return p;
}
string Calculate_3(string Text) {
	unsigned int i = 0, SiNum = 0;
	vector<int>Sign;
	string SigText = "", TempText = "", Result = "";
	vector<string>Js(2);

	TempText = Text;
	if (TempText.find("^") != -1) {//乘方计算
		while (i <= TempText.length()) {
			int t = i - 1;if (t < 0)t = 0;
			SigText = TempText.substr(t, 1);
			if (SigText == "+" || SigText == "-" && i > 1 || SigText == "*" || SigText == "/") {
				Sign.push_back(i);
				i++;
			}
			else if (SigText == "^") {
				SiNum = Sign.size();
				if (SiNum > 0) {
					Js[0] = TempText.substr(Sign[SiNum - 1], i - Sign[SiNum - 1] - 1);
					Js[1] = TempText.substr(TempText.length() - (TempText.length() - i), TempText.length() - i);
					Result = doubleToString(pow(stringToNum<double>(Js[0]), stringToNum<double>(Js[1])));
					Js[1] = strcl(doubleToString(stringToNum<double>(Js[1])).c_str(), Js[1].c_str());
					TempText = TempText.replace(Sign[SiNum - 1], Js[0].length() + Js[1].length() + 1, Result);
					i = Sign[SiNum - 1] + 1;
				}
				else {
					Js[0] = TempText.substr(0, i - 1);
					Js[1] = TempText.substr(TempText.length() - (TempText.length() - i), TempText.length() - i);
					Result = doubleToString(pow(stringToNum<double>(Js[0]), stringToNum<double>(Js[1])));
					Js[1] = strcl(doubleToString(stringToNum<double>(Js[1])).c_str(), Js[1].c_str());
					TempText = TempText.replace(0, Js[0].length() + Js[1].length() + 1, Result);
					i = 1;
				}
			}
			else {
				i++;
			}
		}

	}
	i = 1;
	Sign.clear();
	if (TempText.find("*") != -1 || TempText.find("/") != -1) {//乘除计算
		while (i <= TempText.length()) {
			int t = i - 1;if (t < 0)t = 0;
			SigText = TempText.substr(t, 1);
			if (SigText == "+" || SigText == "-" && i > 1) {
				Sign.push_back(i);
				i++;
			}
			else if (SigText == "*") {
				SiNum = Sign.size();
				if (SiNum > 0) {
					Js[0] = TempText.substr(Sign[SiNum - 1], i - Sign[SiNum - 1] - 1);
					Js[1] = TempText.substr(TempText.length() - (TempText.length() - i), TempText.length() - i);
					Result = doubleToString(stringToNum<double>(Js[0])*stringToNum<double>(Js[1]));
					Js[1] = strcl(doubleToString(stringToNum<double>(Js[1])).c_str(), Js[1].c_str());
					TempText = TempText.replace(Sign[SiNum - 1], Js[0].length() + Js[1].length() + 1, Result);
					i = Sign[SiNum - 1] + 1;
				}
				else {
					Js[0] = TempText.substr(0, i - 1);
					Js[1] = TempText.substr(TempText.length() - (TempText.length() - i), TempText.length() - i);
					Result = doubleToString(stringToNum<double>(Js[0])*stringToNum<double>(Js[1]));
					Js[1] = strcl(doubleToString(stringToNum<double>(Js[1])).c_str(), Js[1].c_str());
					TempText = TempText.replace(0, Js[0].length() + Js[1].length() + 1, Result);
					i = 1;
				}
			}
			else if (SigText == "/") {
				SiNum = Sign.size();
				if (SiNum > 0) {
					Js[0] = TempText.substr(Sign[SiNum - 1], i - Sign[SiNum - 1] - 1);
					Js[1] = TempText.substr(TempText.length() - (TempText.length() - i), TempText.length() - i);
					if (stringToNum<double>(Js[1]) == 0)
						return NULL;
					Result = doubleToString(stringToNum<double>(Js[0]) / stringToNum<double>(Js[1]));
					Js[1] = strcl(doubleToString(stringToNum<double>(Js[1])).c_str(), Js[1].c_str());
					TempText = TempText.replace(Sign[SiNum - 1], Js[0].length() + Js[1].length() + 1, Result);
					i = Sign[SiNum - 1] + 1;
				}
				else {
					Js[0] = TempText.substr(0, i - 1);
					Js[1] = TempText.substr(TempText.length() - (TempText.length() - i), TempText.length() - i);
					if (stringToNum<double>(Js[1]) == 0)
						return NULL;
					Result = doubleToString(stringToNum<double>(Js[0]) / stringToNum<double>(Js[1]));
					Js[1] = strcl(doubleToString(stringToNum<double>(Js[1])).c_str(), Js[1].c_str());
					TempText = TempText.replace(0, Js[0].length() + Js[1].length() + 1, Result);
					i = 1;
				}
			}
			else {
				i++;
			}
		}

	}
	i = 1;
	while (i <= TempText.length()) {//加减计算
		int t = i - 1;if (t < 0)t = 0;
		SigText = TempText.substr(t, 1);
		if (SigText == "+") {
			Js[0] = TempText.substr(0, i - 1);
			Js[1] = TempText.substr(TempText.length() - (TempText.length() - i), TempText.length() - i);
			Result = doubleToString(stringToNum<double>(Js[0]) + stringToNum<double>(Js[1]));
			Js[1] = strcl(doubleToString(stringToNum<double>(Js[1])).c_str(), Js[1].c_str());
			TempText = TempText.replace(0, Js[0].length() + Js[1].length() + 1, Result);
			i = 1;
		}
		else if (SigText == "-" && i>1) {
			Js[0] = TempText.substr(0, i - 1);
			Js[1] = TempText.substr(TempText.length() - (TempText.length() - i), TempText.length() - i);
			Result = doubleToString(stringToNum<double>(Js[0]) - stringToNum<double>(Js[1]));
			Js[1] = strcl(doubleToString(stringToNum<double>(Js[1])).c_str(), Js[1].c_str());
			TempText = TempText.replace(0, Js[0].length() + Js[1].length() + 1, Result);
			i = 1;
		}
		else {
			i++;
		}
	}
	return TempText;
}

string Calculate_2(string Text) {
	string TempText = Text, SigText = "", SwText = "", SwReText = "";
	unsigned int i = 1, ZkNum = 0, Asc = 0;
	vector<int>Zk;

	while (i <= TempText.length()) {
		int t = i - 1;if (t < 0)t = 0;
		SigText = TempText.substr(t, 1);
		if (SigText == "(") {
			Zk.push_back(i);
			i++;
		}
		else if (SigText == ")") {
			ZkNum = Zk.size();
			if (ZkNum > 0) {
				SwText = TempText.substr(Zk[ZkNum - 1], i - Zk[ZkNum - 1] - 1);
				SwReText = Calculate_3(SwText);
				if (SwReText == "")
					return NULL;
				TempText = TempText.replace(Zk[ZkNum - 1] - 1, SwText.length() + 2, SwReText);
				i = Zk[ZkNum - 1] + 1;
				Zk.erase(Zk.begin() + ZkNum - 1);
			}
			else {
				TempText = TempText.replace(i - 1, 1, NULL);
			}
		}
		else if (Asc == 92) {
			TempText = TempText.replace(i - 1, 1, "\\");
			i++;
		}
		else {
			Asc = SigText[0];
			if ((Asc < 46 || Asc>57) && Asc != 42 && Asc != 43 && Asc != 45 && Asc != 92 && Asc != 94) {
				TempText = TempText.replace(i - 1, 1, NULL);
			}
			else {
				i++;
			}
		}

	}
	ZkNum = Zk.size();
	if (ZkNum > 0) {
		for (i = 0;i < ZkNum;i++) {
			TempText = TempText.replace(Zk[ZkNum - i] - 1, 1, NULL);
		}
	}
	return Calculate_3(TempText);
}
int main() {
	cout << "欢迎使用<简单计算器>,本程序支持十进制的加减乘除及乘方运算!" << endl;
	string input;
	while (true) {
		cout << "请输入需运算的表达式:" << endl;
		cin >> input;
		string ret = Calculate_2(input);
		cout << "运算结果:" << ret << endl;
	}
	system("pause");
	return 0;
}
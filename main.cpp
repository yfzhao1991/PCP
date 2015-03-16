#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>

using namespace std;

class domino
{
public:
	int number;
	string up;
	string down;
	void set(int a, string str1, string str2)
	{
		number = a;
		up = str1;
		down = str2;;
	}
};

class state
{
public:
	string up;
	string down;
	void set1(string str1,string str2)
	{
		up = "";
		string s = str2;
		s.resize(str2.length() - str1.length());
		down = s;
	}
	void set2(string str1,string str2)
	{
		string s = str1;
		s.resize(str1.length() - str2.length());
		up = s;
		down = "";
	}
	bool operator <(state const& other) const
	{
		if (up == other.up)
			return down < other.down;
		else 
			return up < other.up;
	}
};

vector<domino> dominos;
map<state, vector<int> > stwsq;
queue<state> states;
int b, c, f;
bool found = false;
bool infinite = false;

void setstate(state& sta,int number, bool& isstate)
{
	if (sta.up == sta.down)
		found = true;
	else if (sta.up.length() > sta.down.length())
	{
		if (sta.up.substr(sta.up.length() - sta.down.length(), sta.down.length()) == sta.down)
		{
			sta.set2(sta.up, sta.down);
			states.push(sta);
			isstate = true;
		}
	}
	else if (sta.up.length()< sta.down.length())
	{
		if (sta.down.substr(sta.down.length() - sta.up.length(), sta.up.length()) == sta.up)
		{
			sta.set1(sta.up, sta.down);
			states.push(sta);
			isstate = true;
		}
	}
}

void setstate2(state& sta, int number, bool& isstate)
{
	if (sta.up == sta.down)
		found = true;
	else if (sta.up.length() > sta.down.length())
	{
		if (sta.up.substr(sta.up.length() - sta.down.length(), sta.down.length()) == sta.down)
		{
			sta.set2(sta.up, sta.down);
			isstate = true;
		}
	}
	else if (sta.up.length()< sta.down.length())
	{
		if (sta.down.substr(sta.down.length() - sta.up.length(), sta.up.length()) == sta.up)
		{
			sta.set1(sta.up, sta.down);
			isstate = true;
		}
	}
}

bool BFS()
{
	int count = 0;
	while (!states.empty())
	{
		state sta = states.front();
		states.pop();
		for (int i = 0; i < dominos.size(); i++)
		{
			state sta1;
			bool isstate = false;
			sta1.up = dominos[i].up + sta.up;
			sta1.down = dominos[i].down + sta.down;
			setstate(sta1, dominos[i].number, isstate);
			if (found == true)
			{
				cout << endl << "Answer found." << endl;
				cout << "Answer is D" << dominos[i].number << " ";
				for (int j = stwsq[sta].size() - 1; j >= 0; j--)
					cout << "D" << stwsq[sta][j] << " ";
				cout << endl;
				return true;
			}
			if (states.size()>b||count>c)
			{
				infinite = true;
				return false;
			}
			if (isstate)
			{
				count++;
				stwsq[sta1] = stwsq[sta];
				stwsq[sta1].push_back(dominos[i].number);
				if (!f&&count < 100)
				{
					for (int j = stwsq[sta].size() - 1; j >= 0; j--)
						cout << "D" << stwsq[sta][j] << " ";
					cout << "/";
				}
			}
		}
	}
	return false;
}

bool DFS(int depth, state sta)
{ 
	for (int i = 0; i < dominos.size(); i++)
	{
		state sta1;
		bool isstate = false;
		sta1.up = dominos[i].up + sta.up;
		sta1.down = dominos[i].down + sta.down;
		setstate2(sta1, dominos[i].number, isstate);
		if (found == true)
		{
			cout << endl << "Answer found." << endl;
			cout << "Answer is D" << dominos[i].number << " ";
			for (int j = stwsq[sta].size() - 1; j >= 0; j--)
				cout << "D" << stwsq[sta][j] << " ";
			cout << endl;
			return true;
		}
		if (depth>1&&isstate)
			return DFS(depth - 1, sta);
	}
	return false;
}

bool IDS()
{
	while (!states.empty())
	{
		state sta = states.front();
		states.pop();
		for (int i = 1; i < 10;i++)
			if (DFS(i, sta)) 
				return true;
	}
	return false;
}

void threshold()
{
	if (b < 1000)
		b = 1000;
	else if (b > 5000)
		b = 5000;
	if (c < 1000)
		c = 1000;
	else if (c > 5000)
		c = 5000;
}

int main()
{
	fstream fin("input.txt");
	if (!fin.is_open())
	{
		cout << "Error opening file" << endl;
		exit(0);
	}
	fin>>b>>c>>f;
	threshold();
	while (!fin.eof())
	{
		int num;
		string str1, str2;
		domino d;
		state sta;
		bool isstate = false;
		fin >> num >> str1 >> str2;
		d.set(num,str1,str2);
		dominos.push_back(d);
		sta.up = d.up;
		sta.down = d.down;
		setstate(sta,d.number,isstate);
		if (found == true)
		{
			cout << "D" << d.number << endl;
			return 0;
		}
		if (isstate)
			stwsq[sta].push_back(d.number);
	}
	if (!BFS())
		if (!infinite)
			cout <<endl<<"No solution exists."<< endl;
		else
		{
			cout <<endl<< "No solution was found within BFS limits of search." << endl;
			cout << "Go to iterative deepening depth-first search." << endl;
			if (!IDS())
				cout << "No solution was found within limits of iterative deepening depth-first search." << endl;
		}
	return 0;
}

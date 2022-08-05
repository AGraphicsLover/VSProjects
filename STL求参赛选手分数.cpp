#include<iostream>
#include<vector>
#include<deque>
using namespace std;
class player
{
public:
	char name;
	double average_score = 0;
	deque<double>score;
	player();
	player(char c, deque<double>& deq) :name(c), score(deq) {};
	player operator =(const player& p)const;
};
player::player(){}
player player::operator=(const player& p)const
{
	player temp_player;
	temp_player.name = p.name;
	temp_player.average_score = p.average_score;
	temp_player.score = p.score;
	return temp_player;
}
void sort_score(vector<player>& p)
{
	bool times = false;
	for (int i = 0; i < p.size(); i++)
	{
		for (int j = 0; j < p[i].score.size(); j++)
		{
			for (int k = j + 1; k < p[i].score.size(); k++)
			{
				if (p[i].score[j] > p[i].score[k])
				{
					int temp = p[i].score[j];
					p[i].score[j] = p[i].score[k];
					p[i].score[k] = temp;
					times = true;
				}
				if (!times)
					break;
			}
		}
	}
}
void sort_average_score(vector<player>& p)
{
	bool times = false;
	for (int i = 0; i < p.size(); i++)
	{
		for (int j = i + 1; j < p.size(); j++)
		{
			if (p[i].average_score > p[j].average_score)
			{
				player temp;
				temp = p[i];
				p[i] = p[j];
				p[j] = temp;
				times = true;
			}
			if (!times)
				break;
		}
	}
}
void display(vector<player>& p)
{
	for (int i = 4; i >=0; i--)
	{
		cout << "Name: " << p[i].name << "  " << "Score: " << p[i].average_score << endl;
	}
}
int main()
{
	vector<player> vec_player;
	for (int i=0;i<5;i++)
	{
		char name_cin;
		double score_cin;
		deque<double>de;
		cout << "请输入第" << i + 1 << "位player的名字:";
		cin >> name_cin;
		cout << "请输入10位裁判的打分：";
		for (int j = 0; j < 10; j++)
		{
			cin >> score_cin;
			de.push_back(score_cin);
		}
		player player_cin(name_cin, de);
		vec_player.insert(vec_player.end(), 1, player_cin);
	}
	sort_score(vec_player);
	for (int i = 0; i < 5; i++)
	{
		vec_player[i].score.pop_front();
		vec_player[i].score.pop_back();
	}
	for (int i = 0; i < 5; i++)
	{
		double sum = 0;
		for (int j = 0; j < vec_player[i].score.size(); j++)
		{
			sum += vec_player[i].score[j];
		}
		vec_player[i].average_score = sum / vec_player[i].score.size();
	}
	sort_average_score(vec_player);
	cout << "The score list is:" << endl;
	display(vec_player);
	return 0;
}
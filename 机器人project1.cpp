#include<iostream>
using namespace std;
class Warehouse
{
	int x, y;
public:
	Warehouse() { cin >> x; cin >> y; };
	int get_x() { return x; }
	int get_y() { return y; }
};
class instruction
{
	int rob_num;
	char action;
	int repeat;
public:
	int get_rob_num()
	{
		return rob_num;
	}
	char get_action()
	{
		return action;
	}
	int get_repeat()
	{
		return repeat;
	}
	void set_instr()
	{
		cin >> rob_num >> action >> repeat;
	}
};
class Robot
{
	int location_x;
	int location_y;
	char forward;
	int forward_num;
public:
	Robot() :location_x(0), location_y(0), forward('E'), forward_num(0) {};
	void set_robot()
	{
		cin >> location_x >> location_y >> forward;
		if (forward == 'E')
			forward_num = 0;
		if (forward == 'N')
			forward_num = 90;
		if (forward == 'W')
			forward_num = 180;
		if (forward == 'S')
			forward_num = 270;
	}
	void adjust_for()
	{
		while (forward_num >= 360)
			forward_num -= 360;
		while (forward_num < 0)
			forward_num += 360;
	}
	bool judge_w(Warehouse &w)
	{
		if (location_x > w.get_x() || location_x < 1)
			return false;
		if (location_y > w.get_y() || location_y < 1)
			return false;
		return true;
	}
	friend bool judge_r(Robot &r1, Robot &r2);
	int change(instruction& in, Warehouse& w)
	{
		if (in.get_action() == 'L')
		{
			forward_num += (90 * in.get_repeat());
			adjust_for();
		}
		if (in.get_action() == 'R')
		{
			forward_num -= (90 * in.get_repeat());
			adjust_for();
		}
		if (in.get_action() == 'F')
		{
			for (int j = 0; j < in.get_repeat(); j++)
			{
				if (forward_num == 0)
					location_x++;
				if (forward_num == 90)
					location_y++;
				if (forward_num == 180)
					location_x--;
				if (forward_num == 270)
					location_y--;
				if (judge_w(w))
				{
					continue;
				}
				else
				{
					return 2;
				}
			}
		}
		return 1;
	}
	int change(instruction& in, Warehouse& w, Robot& r2)
	{
		if (in.get_action() == 'L')
		{
			forward_num += (90 * in.get_repeat());
			adjust_for();
		}
		if (in.get_action() == 'R')
		{
			forward_num -= (90 * in.get_repeat());
			adjust_for();
		}
		if (in.get_action() == 'F')
		{
			for (int j = 0; j < in.get_repeat(); j++)
			{
				if (forward_num == 0)
					location_x ++;
				if (forward_num == 90)
					location_y ++;
				if (forward_num == 180)
					location_x --;
				if (forward_num == 270)
					location_y --;
				if (judge_w(w) && judge_r(*this, r2))
					continue;
				else if (judge_r(*this, r2))
					return 2;
				else
					return 3;
			}
		}
		return 1;
	}
};
bool judge_r(Robot &r1, Robot &r2)
{
	if (r1.location_x == r2.location_x && r1.location_y == r2.location_y)
		return false;
	else
		return true;
}
int main()
{
	int num_test, num_robot, num_instr;
	cin >> num_test;
	for (int i = 0; i < num_test; i++)
	{
		Warehouse ware;
		cin >> num_robot >> num_instr;
		Robot* p = new Robot[num_robot];
		for (int i = 0; i < num_robot; i++)
		{
			p[i].set_robot();
		}
		instruction* q = new instruction[num_instr];
		for (int i = 0; i < num_instr; i++)
		{
			q[i].set_instr();
		}
		int m = 0;
		for (int i = 0; i < num_instr; i++)
		{
			if (num_robot == 1)
			{
				if (p[q[i].get_rob_num()].change(q[i], ware) == 2)
				{
					cout << "Robot " << q[i].get_rob_num() << " crashes into the wall" << endl;
					m++;
					break;
				}
			}
			else
			{
				for (int j = 0; j < num_robot; j++)
				{
					if (q[i].get_rob_num() != j + 1)
					{
						int n = p[q[i].get_rob_num() - 1].change(q[i], ware, p[j]);
						if (n == 3)
						{
							cout << "Robot " << q[i].get_rob_num() << " crashes into robot " << j + 1 << endl;
							m++;
							break;
						}
						else if( n == 2)
						{
							cout << "Robot " << q[i].get_rob_num() << " crashes into the wall" << endl;
							m++;
							break;
						}
					}
				}
			}
			if (m == 1)
				break;
		}
		if (m == 0)
			cout << "OK" << endl;
	}
	return 0;
}
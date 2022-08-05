#include<iostream>
using namespace std;
int main()
{
	int a, b, i;
	cout << "在1到9这9个整数中选择一个数：（其实你可以从1到9一直输入）" << endl;
	for (i = 1; i <= 9; i++)
	{
		cin >> a;
		switch(a)
		{
			case 1:
				cout << "你好，陈小莺，能不能借一生说话。我想对你说的话，想在你面前说的话，可能一辈子都说不完，你愿意听吗？" << endl;
				break;
			case 2:
				cout << "承蒙你出现，够我欢喜余生。" << endl;
				break;
			case 3:
				cout << "持剑背靠路边树，我在等风也等你。" << endl;
				break;
			case 4:
				cout << "你不用分清东南西北，只需等我找到你。" << endl;
				break;
			case 5:
				cout << "说不清为什么爱你，但你就是我不爱别人的理由。" << endl;
				break;
			case 6:
				cout << "听到一些事，明明不相干的，也会在心中拐好几个弯想到你。" << endl;
				break;
			case 7:
				cout << "也许人生苦难，可是你就是我坚持下去的理由。" << endl;
				break;
			case 8:
				cout << "与你牵手的手指，夜里，独自合十。然后，梦里，全是你的侧影。" << endl;
				break;
			case 9:
				cout << "有个地方叫马尔代夫，我想在适当的时候带你去那个地方。" << endl;
				cout << "在那儿我们走过漫漫长夜，天色露白时交换一个亲吻，然后我在我们一起写的那本书上写下：" << endl;
				cout << "“我在马尔代夫想念每个清晨的吻。就像是说我在所有老去的时光里，热爱温柔深情的你。”" << endl;
				break;
		
			default:
				cout << "傻瓜啊，只有数字1到9才有用哦！" << endl;
				break;
		}
	}
	cout << "傻瓜，好爱你呀！比心:" << endl;
	float x, y;
	for (y = 2; y >= -2; y -= 0.06)
	{
		for (x = -1.2; x <= 1.2; x += 0.025)
		{
			if (((x * x + y * y - 1) * (x * x + y * y - 1) * (x * x + y * y - 1) - y * y * y * x * x) <= 0)
				cout << "*";
			else
				cout << " ";
		}
		cout << "\n";
	}
	return 0;
}
#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
using namespace std;

vector<char>Cube[7];	//각 면의 색상번호
int T;

void change(char Where, char Dir) {
	//위: 1, 아: 2, 앞: 3, 뒤: 4, 왼: 5, 오: 6
	if (Where == 'U')
	{
		if (Dir == '+')
		{
			char Tmp1, Tmp2, Tmp3;
			Tmp1 = Cube[6].at(0);
			Tmp2 = Cube[6].at(1);
			Tmp3 = Cube[6].at(2);

			Cube[6].at(0) = Cube[4].at(0);
			Cube[6].at(1) = Cube[4].at(1);
			Cube[6].at(2) = Cube[4].at(2);

			Cube[4].at(0) = Cube[5].at(0);
			Cube[4].at(1) = Cube[5].at(1);
			Cube[4].at(2) = Cube[5].at(2);

			Cube[5].at(0) = Cube[3].at(0);
			Cube[5].at(1) = Cube[3].at(1);
			Cube[5].at(2) = Cube[3].at(2);

			Cube[3].at(0) = Tmp1;
			Cube[3].at(1) = Tmp2;
			Cube[3].at(2) = Tmp3;
		}
		else
		{
			char Tmp1, Tmp2, Tmp3;
			Tmp1 = Cube[6].at(0);
			Tmp2 = Cube[6].at(1);
			Tmp3 = Cube[6].at(2);

			Cube[6].at(0) = Cube[3].at(0);
			Cube[6].at(1) = Cube[3].at(1);
			Cube[6].at(2) = Cube[3].at(2);

			Cube[3].at(0) = Cube[5].at(0);
			Cube[3].at(1) = Cube[5].at(1);
			Cube[3].at(2) = Cube[5].at(2);

			Cube[5].at(0) = Cube[4].at(0);
			Cube[5].at(1) = Cube[4].at(1);
			Cube[5].at(2) = Cube[4].at(2);

			Cube[4].at(0) = Tmp1;
			Cube[4].at(1) = Tmp2;
			Cube[4].at(2) = Tmp3;
		}
	}
	else if (Where == 'D')    // 아랫면
	{
		if (Dir == '+')    // 시계방향으로
		{
			char Tmp1, Tmp2, Tmp3;
			Tmp1 = Cube[3].at(6);
			Tmp2 = Cube[3].at(7);
			Tmp3 = Cube[3].at(8);

			Cube[3].at(6) = Cube[5].at(6);
			Cube[3].at(7) = Cube[5].at(7);
			Cube[3].at(8) = Cube[5].at(8);

			Cube[5].at(6) = Cube[4].at(6);
			Cube[5].at(7) = Cube[4].at(7);
			Cube[5].at(8) = Cube[4].at(8);

			Cube[4].at(6) = Cube[6].at(6);
			Cube[4].at(7) = Cube[6].at(7);
			Cube[4].at(8) = Cube[6].at(8);

			Cube[6].at(6) = Tmp1;
			Cube[6].at(7) = Tmp2;
			Cube[6].at(8) = Tmp3;
		}
		else
		{
			char Tmp1, Tmp2, Tmp3;
			Tmp1 = Cube[3].at(6);
			Tmp2 = Cube[3].at(7);
			Tmp3 = Cube[3].at(8);

			Cube[3].at(6) = Cube[6].at(6);
			Cube[3].at(7) = Cube[6].at(7);
			Cube[3].at(8) = Cube[6].at(8);

			Cube[6].at(6) = Cube[4].at(6);
			Cube[6].at(7) = Cube[4].at(7);
			Cube[6].at(8) = Cube[4].at(8);

			Cube[4].at(6) = Cube[5].at(6);
			Cube[4].at(7) = Cube[5].at(7);
			Cube[4].at(8) = Cube[5].at(8);

			Cube[5].at(6) = Tmp1;
			Cube[5].at(7) = Tmp2;
			Cube[5].at(8) = Tmp3;
		}
	}
	else if (Where == 'F')
	{
		if (Dir == '+')    // 시계방향으로
		{
			char Tmp1, Tmp2, Tmp3;
			Tmp1 = Cube[1].at(6);
			Tmp2 = Cube[1].at(7);
			Tmp3 = Cube[1].at(8);

			Cube[1].at(6) = Cube[5].at(8);
			Cube[1].at(7) = Cube[5].at(5);
			Cube[1].at(8) = Cube[5].at(2);

			Cube[5].at(8) = Cube[2].at(2);
			Cube[5].at(5) = Cube[2].at(1);
			Cube[5].at(2) = Cube[2].at(0);

			Cube[2].at(2) = Cube[6].at(0);
			Cube[2].at(1) = Cube[6].at(3);
			Cube[2].at(0) = Cube[6].at(6);

			Cube[6].at(0) = Tmp1;
			Cube[6].at(3) = Tmp2;
			Cube[6].at(6) = Tmp3;
		}
		else
		{
			char Tmp1, Tmp2, Tmp3;
			Tmp1 = Cube[1].at(6);
			Tmp2 = Cube[1].at(7);
			Tmp3 = Cube[1].at(8);

			Cube[1].at(6) = Cube[6].at(0);
			Cube[1].at(7) = Cube[6].at(3);
			Cube[1].at(8) = Cube[6].at(6);

			Cube[6].at(0) = Cube[2].at(2);
			Cube[6].at(3) = Cube[2].at(1);
			Cube[6].at(6) = Cube[2].at(0);

			Cube[2].at(2) = Cube[5].at(8);
			Cube[2].at(1) = Cube[5].at(5);
			Cube[2].at(0) = Cube[5].at(2);

			Cube[5].at(8) = Tmp1;
			Cube[5].at(5) = Tmp2;
			Cube[5].at(2) = Tmp3;
		}
	}
	else if (Where == 'B') // 뒷면
	{
		if (Dir == '+')    // 시계방향으로
		{
			char Tmp1, Tmp2, Tmp3;
			Tmp1 = Cube[1].at(0);
			Tmp2 = Cube[1].at(1);
			Tmp3 = Cube[1].at(2);

			Cube[1].at(0) = Cube[6].at(2);
			Cube[1].at(1) = Cube[6].at(5);
			Cube[1].at(2) = Cube[6].at(8);

			Cube[6].at(2) = Cube[2].at(8);
			Cube[6].at(5) = Cube[2].at(7);
			Cube[6].at(8) = Cube[2].at(6);

			Cube[2].at(8) = Cube[5].at(6);
			Cube[2].at(7) = Cube[5].at(3);
			Cube[2].at(6) = Cube[5].at(0);

			Cube[5].at(6) = Tmp1;
			Cube[5].at(3) = Tmp2;
			Cube[5].at(0) = Tmp3;
		}
		else
		{
			// 1 = 위 | 2 = 아래 | 3 = 앞 | 4 = 뒤 | 5 = 왼 | 6 = 오

			char Tmp1, Tmp2, Tmp3;
			Tmp1 = Cube[1].at(0);
			Tmp2 = Cube[1].at(1);
			Tmp3 = Cube[1].at(2);

			Cube[1].at(0) = Cube[5].at(6);
			Cube[1].at(1) = Cube[5].at(3);
			Cube[1].at(2) = Cube[5].at(0);

			Cube[5].at(6) = Cube[2].at(8);
			Cube[5].at(3) = Cube[2].at(7);
			Cube[5].at(0) = Cube[2].at(6);

			Cube[2].at(8) = Cube[6].at(2);
			Cube[2].at(7) = Cube[6].at(5);
			Cube[2].at(6) = Cube[6].at(8);

			Cube[6].at(2) = Tmp1;
			Cube[6].at(5) = Tmp2;
			Cube[6].at(8) = Tmp3;
		}
	}
	else if (Where == 'L')
	{
		if (Dir == '+')    // 시계방향으로
		{
			char Tmp1, Tmp2, Tmp3;
			Tmp1 = Cube[3].at(0);
			Tmp2 = Cube[3].at(3);
			Tmp3 = Cube[3].at(6);

			Cube[3].at(0) = Cube[1].at(0);
			Cube[3].at(3) = Cube[1].at(3);
			Cube[3].at(6) = Cube[1].at(6);

			Cube[1].at(0) = Cube[4].at(8);
			Cube[1].at(3) = Cube[4].at(5);
			Cube[1].at(6) = Cube[4].at(2);

			Cube[4].at(8) = Cube[2].at(0);
			Cube[4].at(5) = Cube[2].at(3);
			Cube[4].at(2) = Cube[2].at(6);

			Cube[2].at(0) = Tmp1;
			Cube[2].at(3) = Tmp2;
			Cube[2].at(6) = Tmp3;
		}
		else
		{
			char Tmp1, Tmp2, Tmp3;
			Tmp1 = Cube[3].at(0);
			Tmp2 = Cube[3].at(3);
			Tmp3 = Cube[3].at(6);

			Cube[3].at(0) = Cube[2].at(0);
			Cube[3].at(3) = Cube[2].at(3);
			Cube[3].at(6) = Cube[2].at(6);

			Cube[2].at(0) = Cube[4].at(8);
			Cube[2].at(3) = Cube[4].at(5);
			Cube[2].at(6) = Cube[4].at(2);

			Cube[4].at(8) = Cube[1].at(0);
			Cube[4].at(5) = Cube[1].at(3);
			Cube[4].at(2) = Cube[1].at(6);

			Cube[1].at(0) = Tmp1;
			Cube[1].at(3) = Tmp2;
			Cube[1].at(6) = Tmp3;
		}
	}
	else if (Where == 'R')
	{
		if (Dir == '+')    // 시계방향으로
		{
			char Tmp1, Tmp2, Tmp3;
			Tmp1 = Cube[3].at(2);
			Tmp2 = Cube[3].at(5);
			Tmp3 = Cube[3].at(8);

			Cube[3].at(2) = Cube[2].at(2);
			Cube[3].at(5) = Cube[2].at(5);
			Cube[3].at(8) = Cube[2].at(8);

			Cube[2].at(2) = Cube[4].at(6);
			Cube[2].at(5) = Cube[4].at(3);
			Cube[2].at(8) = Cube[4].at(0);

			Cube[4].at(6) = Cube[1].at(2);
			Cube[4].at(3) = Cube[1].at(5);
			Cube[4].at(0) = Cube[1].at(8);

			Cube[1].at(2) = Tmp1;
			Cube[1].at(5) = Tmp2;
			Cube[1].at(8) = Tmp3;
		}
		else
		{
			char Tmp1, Tmp2, Tmp3;
			Tmp1 = Cube[3].at(2);
			Tmp2 = Cube[3].at(5);
			Tmp3 = Cube[3].at(8);

			Cube[3].at(2) = Cube[1].at(2);
			Cube[3].at(5) = Cube[1].at(5);
			Cube[3].at(8) = Cube[1].at(8);

			Cube[1].at(2) = Cube[4].at(6);
			Cube[1].at(5) = Cube[4].at(3);
			Cube[1].at(8) = Cube[4].at(0);

			Cube[4].at(6) = Cube[2].at(2);
			Cube[4].at(3) = Cube[2].at(5);
			Cube[4].at(0) = Cube[2].at(8);

			Cube[2].at(2) = Tmp1;
			Cube[2].at(5) = Tmp2;
			Cube[2].at(8) = Tmp3;
		}
	}
}

int aspect(char s) {
	if (s == 'U')return 1;
	else if (s == 'D')return 2;
	else if (s == 'F')return 3;
	else if (s == 'B')return 4;
	else if (s == 'L')return 5;
	else return 6;
}

void solve(char s, char d) {
	int as = aspect(s);

	//해당하는 면 회전
	if (d == '+') {
		char t = Cube[as][0];
		Cube[as][0] = Cube[as][6];
		Cube[as][6] = Cube[as][8];
		Cube[as][8] = Cube[as][2];
		Cube[as][2] = t;

		t = Cube[as][1];
		Cube[as][1] = Cube[as][3];
		Cube[as][3] = Cube[as][7];
		Cube[as][7] = Cube[as][5];
		Cube[as][5] = t;
	}
	else {
		char t = Cube[as][0];
		Cube[as][0] = Cube[as][2];
		Cube[as][2] = Cube[as][8];
		Cube[as][8] = Cube[as][6];
		Cube[as][6] = t;

		t = Cube[as][1];
		Cube[as][1] = Cube[as][5];
		Cube[as][5] = Cube[as][7];
		Cube[as][7] = Cube[as][3];
		Cube[as][3] = t;
	}


}

void init() {
	for (int i = 1; i <= 6; i++)
		Cube[i].clear();
	//위, 아, 앞, 뒤, 왼, 오
	for (int i = 0; i < 9; i++) {
		Cube[1].push_back('w');
		Cube[2].push_back('y');
		Cube[3].push_back('r');
		Cube[4].push_back('o');
		Cube[5].push_back('g');
		Cube[6].push_back('b');
	}
}

int main() {
	int n;
	cin >> T;

	while (T--) {
		init();
		cin >> n;
		for (int i = 0; i < n; i++) {
			string str;
			cin >> str;
			solve(str[0], str[1]);
			change(str[0], str[1]);
		}
		for (int i = 0; i < 3; i++)
			cout << Cube[1][i];
		cout << endl;
		for (int i = 3; i < 6; i++)
			cout << Cube[1][i];
		cout << endl;
		for (int i = 6; i < 9; i++)
			cout << Cube[1][i];
		cout << endl;
	}

	return 0;
}
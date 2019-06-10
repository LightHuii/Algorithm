#include<iostream>
#include<algorithm>
using namespace std;

int gear[5][8];
int status[5] = { 0, };

//오른쪽 shift
void rotate_c(int *ary) {
	int tmp = ary[7];

	for (int i = 6; i >= 0; i--)
		ary[i + 1] = ary[i];
	ary[0] = tmp;
}

//왼 쪽 shift
void rotate_r(int *ary) {
	int tmp = ary[0];

	for (int i = 0; i < 7; i++)
		ary[i] = ary[i + 1];
	ary[7] = tmp;
}

int main() {
	int K;
	int gear_num, dir;
	for (int i = 1; i <= 4; i++)
		for (int j = 0; j < 8; j++)
			scanf("%1d", &gear[i][j]);

	cin >> K;
	for (int i = 0; i < K; i++) {
		cin >> gear_num >> dir;

		//첫 바퀴 돌리기
		if (gear_num == 1) {
			if (dir == 1)
				status[1] = 1;
			else
				status[1] = -1;
		}
		else if (gear_num == 2) {
			if (dir == 1)
				status[2] = 1;
			else
				status[2] = -1;
		}
		else if (gear_num == 3) {
			if (dir == 1)
				status[3] = 1;
			else
				status[3] = -1;
		}
		else if (gear_num == 4) {
			if (dir == 1)
				status[4] = 1;
			else
				status[4] = -1;
		}

		int pre = gear_num, curr;
		for (int j = 0; j < 2; j++) {
			if (gear_num <= 2) {
				curr = pre + 1;
				if (status[pre] == 0 || (status[pre] != 0 && gear[pre][2] == gear[curr][6]))break;
				if (status[pre] == 1)
					status[curr] = -1;
				else
					status[curr] = 1;
				pre = curr;
			}
			else if (gear_num >= 3) {
				curr = pre - 1;
				if (status[pre] == 0 || (status[pre] != 0 && gear[pre][6] == gear[curr][2]))break;
				if (status[pre] == 1)
					status[curr] = -1;
				else
					status[curr] = 1;
				pre = curr;
			}
		}

		bool flag = false;
		if (gear_num == 1 || gear_num == 3) {
			curr = 4;
			pre = 3;
			if (status[pre] == 0 || (status[pre] != 0 && gear[pre][2] == gear[curr][6]))flag = true;
			if (status[pre] == 1 && !flag)
				status[curr] = -1;
			else if (status[pre] == -1 && !flag)
				status[curr] = 1;
		}
		else if (gear_num == 2 || gear_num == 4) {
			curr = 1;
			pre = 2;
			if (status[pre] == 0 || (status[pre] != 0 && gear[pre][6] == gear[curr][2]))flag = true;
			if (status[pre] == 1 && !flag)
				status[curr] = -1;
			else if (status[pre] == -1 && !flag)
				status[curr] = 1;
		}

		for (int i = 1; i <= 4; i++) {
			if (status[i] == 0)continue;
			else if (status[i] == 1)
				rotate_c(gear[i]);
			else if (status[i] == -1)
				rotate_r(gear[i]);
		}

		status[1] = 0;
		status[2] = 0;
		status[3] = 0;
		status[4] = 0;
	}
	//점수
	int rst = 0;
	if (gear[1][0] == 1)rst += 1;
	if (gear[2][0] == 1)rst += 2;
	if (gear[3][0] == 1)rst += 4;
	if (gear[4][0] == 1)rst += 8;
	cout << rst << endl;

	return 0;
}
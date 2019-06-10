#include<iostream>
#include<algorithm>
#include<string>
using namespace std;

int N;
string s1;
string target, str;

//스위치 수행 함수
void switch_ball(int idx) {
	if (s1[idx] == '0')	s1[idx] = '1';
	else s1[idx] = '0';

	if (idx > 0) {
		if (s1[idx - 1] == '0')	s1[idx - 1] = '1';
		else s1[idx - 1] = '0';
	}

	if (idx < N - 1) {
		if (s1[idx + 1] == '0')	s1[idx + 1] = '1';
		else s1[idx + 1] = '0';
	}
}

int main() {
	int rst = INT32_MAX;
	int cnt = 0;
	cin >> N >> str >> target;

	//idx0 부분 바꾸고 진행
	s1 = str;

	switch_ball(0);
	cnt = 1;	//한 번 실행했으므로 1

	//1부터 이전 idx가 target과 다르면 수행하고, 아니면 지나간다
	for (int i = 1; i < N; i++) {
		if (target[i - 1] != s1[i - 1]) {
			switch_ball(i);
			cnt++;
		}
	}
	
	//target과 같은지 확인
	bool flag = true;
	for (int i = 0; i < N; i++) {
		if (s1[i] != target[i])
			flag = false;
	}

	if (flag)
		rst = min(rst, cnt);

	//idx0 바꾸지 않고 진행
	s1 = str;
	cnt = 0;
	flag = true;

	for (int i = 1; i < N; i++) {
		if (target[i - 1] != s1[i - 1]) {
			switch_ball(i);
			cnt++;
		}
	}

	flag = true;
	for (int i = 0; i < N; i++) {
		if (s1[i] != target[i])
			flag = false;
	}

	if (flag)
		rst = min(rst, cnt);
	
	if (rst == INT32_MAX)cout << -1 << endl;
	else
		cout << rst << endl;

	return 0;
}
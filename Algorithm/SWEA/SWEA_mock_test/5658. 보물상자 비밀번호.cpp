#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

#define MAX 29
int T;
int N, K;
char Hex[MAX];
vector<int>v;	//10진수 변환 후 저장

				//start부터 N/4개
int trans(int start) {
	int len = N / 4;
	int h = 1;
	int num, rst = 0;
	int cnt = len - 1;
	int idx = start;

	while (cnt >= 0) {
		idx = (start + cnt) % N;

		switch (Hex[idx])
		{
		case 'F': num = 15;
			break;
		case 'E': num = 14;
			break;
		case 'D': num = 13;
			break;
		case 'C': num = 12;
			break;
		case 'B': num = 11;
			break;
		case 'A': num = 10;
			break;
		default: num = Hex[idx] - '0';
			break;
		}

		rst += num*h;
		h *= 16;
		cnt--;
	}
	return rst;
}

int main() {
	cin >> T;
	int tcnt = T;

	while (tcnt--) {
		cin >> N >> K;

		for (int i = 0; i < N; i++)
			cin >> Hex[i];

		int tmp;
		//각 수의 시작 범위 지정, 회전 횟수
		for (int s = 0; s < N / 4; s++) {
			//4개의 면
			for (int i = 0; i < 4; i++) {
				tmp = trans(s + i*N / 4);

				//cout << "tmp: " << tmp << endl;

				//중복 확인
				if (!v.empty()) {
					bool flag = true;
					for (int j = 0; j < (int)v.size(); j++) {
						if (tmp == v[j]) {
							flag = false;
							break;
						}
					}
					//중복된 값이 없다면
					if (flag)
						v.push_back(tmp);
				}
				else
					v.push_back(tmp);
			}
		}

		//정렬(오름차순)
		if (!v.empty()) {
			sort(v.begin(), v.end());
			cout << '#' << T - tcnt << ' ' << v[(int)v.size() - K] << endl;
		}
		v.clear();
	}

}
​
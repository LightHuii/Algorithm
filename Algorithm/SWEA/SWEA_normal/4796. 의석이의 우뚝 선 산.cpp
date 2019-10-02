#include <iostream>
#include <algorithm>
using namespace std;

#define MAX 50000
int N, T;
int height[MAX];

int main(void)
{
	cin >> T;
	int Ttmp = T;
	while (Ttmp--) {
		cin >> N;
		for (int i = 0; i < N; i++)
			cin >> height[i];
		
		//두 개의 index
		int idx1 = 0, idx2 = 1;
		int rst = 0;
		while (idx1 < N && idx2 < N) {
			int left = 0, right = 0;

			//idx2 증가하며 왼쪽 부분 개수 세기
			while (idx2 < N && height[idx2 - 1] < height[idx2]) {
				left++;
				idx2++;
			}

			//우뚝 솟은 산 조건에 맞지 않다면
			if (left == 0 || idx2 == N) {
				if (idx2 == N)break;
				else {
					idx1 = idx2;
					idx2 = idx1 + 1;
					continue;
				}
			}

			//왼쪽 조건이 맞다면
			idx1 = idx2 - 1;
			while (idx2 < N && height[idx2 - 1] > height[idx2]) {
				right++;
				idx2++;
			}

			//일단 조건은 하나라도 만족함
			rst += left * right;

			//만약 다음 계산을 해야 한다면
			if (idx2 < N) 
				idx1 = idx2 - 1;
		}
		cout << '#' << T - Ttmp << ' ' << rst << endl;
	}
	return 0;
}
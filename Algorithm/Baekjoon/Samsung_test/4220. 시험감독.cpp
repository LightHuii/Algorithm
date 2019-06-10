#include<iostream>
using namespace std;

#define MAX 1000000
int N;
int room[MAX];	//시험장별 학생 수
int B, C;
int B_num = 0;

//최악의 경우 약 10^6 * 10^6이므로 long long형
long long C_num = 0;	//각각 총 감독관과 부감독관의 수

int main() {
	cin >> N;

	//입력
	for (int i = 0; i < N; i++)
		cin >> room[i];
	cin >> B >> C;

	for (int i = 0; i < N; i++) {
		//일단 각 학생 수를 B만큼 뺀다
		if (room[i] >= B) {
			room[i] -= B;

			if (room[i] > 0) {
				//나눠 떨어질 때는 몫을,
				if (room[i] % C == 0)
					C_num += room[i] / C;
				//나머지가 남으면 1을 더해준다.
				else
					C_num += (room[i] / C) + 1;
			}
		}
		else
			room[i] = 0;
	}

	//총 감독관의 수는 시험장의 수와 같다.
	B_num = N;

	cout << B_num + C_num << endl;
}
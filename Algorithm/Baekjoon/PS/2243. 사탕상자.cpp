#include<iostream>
#include<algorithm>
using namespace std;

#define MAX 2100000
int tree[MAX] = { 0, };
int n, A, B, C;

int main(void)
{
	scanf("%d", &n);
	int deg = 0;	//차수
	int two = 1;

	//차수 구하기
	while (1000000 > two) {
		two *= 2;
		deg++;
	}

	for (int i = 0; i < n; i++) {
		scanf("%d", &A);

		//사탕 빼기
		if (A == 1) {
			scanf("%d", &B);
			int curr = 1;
			while (1) {
				if (tree[curr * 2] >= B) {
					//만약 0이면 다른 방향으로 이동
					if (tree[curr * 2] == 0)curr = curr * 2 + 1;
					else
						curr *= 2;	//왼쪽 자식으로 이동
				}
				else {
					//만약 0이면 다른 방향으로 이동
					if (tree[curr * 2 + 1] == 0)curr = curr * 2;
					else {
						//오른 쪽 자식으로 이동한다. 그 전에 목표 값을 왼쪽 자식 노드로 빼줘서 오른쪽 자식에서 바로 구할 수 있게 해준다.
						B -= tree[curr * 2];
						curr = curr * 2 + 1;
					}
				}
				//리프 노드에 도달하면 끝
				if (curr >= two && curr < two * 2)break;
			}

			//출력 및 빼기
			printf("%d\n", curr - two + 1);
			while (curr > 0) {
				tree[curr]--;
				curr /= 2;
			}
		}
		//사탕 넣기 or 빼기
		else {
			scanf("%d %d", &B, &C);

			int curr = two + B - 1;
			while (curr > 0) {
				tree[curr] += C;
				curr /= 2;
			}
		}
	}

	return 0;
}

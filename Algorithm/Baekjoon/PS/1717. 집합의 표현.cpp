#include <iostream>
#include <algorithm>
#include<vector>
using namespace std;

#define MAX 1100000
int n, m;
bool flag = false;
int parent[MAX] = { 0, };

int find(int a) {
	if (parent[a] == a)
		return a;
	else
		//그룹 대표를 찾고나서, parent 배열도 갱신한다.
		//같은 연산을 반복할 때 O(1)로 접근 가능
		return parent[a] = find(parent[a]);
}

int main()
{
	int cmd, a, b;
	scanf("%d %d", &n, &m);

	//자기 자신을 parent로 설정
	for (int i = 0; i <= n; i++)
		parent[i] = i;

	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &cmd, &a, &b);
		if (cmd == 0) {
			//unite
			int p1 = find(a);
			int p2 = find(b);
			parent[p2] = p1;
		}
		else {
			//부모가 같다면 == 같은 그룹이라면
			if (find(a) == find(b))
				printf("yes\n");
			else
				printf("no\n");
		}
	}

	return 0;
}
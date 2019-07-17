#include <iostream>
#include <algorithm>
using namespace std;

#define MAX 100001

typedef struct _e {
	int n1, n2;
	int weight;
}edge;

//연산자 오버로딩 - 구조체의 우선순위 지정 가능
bool tmp(edge& a, edge& b) {
	return a.weight < b.weight;
}

int N, M;
int parent[1001] = { 0, };

int find(int a) {
	if (a == parent[a])return a;
	else
		return parent[a] = find(parent[a]);
}

void unite(int a, int b) {
	int P1 = find(a);
	int P2 = find(b);
	parent[P2] = P1;
}

int main()
{
	int a, b, c;
	cin >> N >> M;

	for (int i = 1; i <= N; i++)
		parent[i] = i;

	edge E[MAX];
	for (int i = 0; i < M; i++) {
		cin >> a >> b >> c;
		E[i].n1 = a;
		E[i].n2 = b;
		E[i].weight = c;
	}

	//weight 기준으로 오름차순 정렬 -> 가장 낮은 weight부터 연결할 수 있다.
	sort(E, E + M, tmp);

	int sum = 0;
	for (int i = 0; i < M; i++) {
		a = E[i].n1;
		b = E[i].n2;
		if (find(a) != find(b)) {
			unite(a, b);
			sum += E[i].weight;
		}
	}

	cout << sum << endl;

	return 0;
}
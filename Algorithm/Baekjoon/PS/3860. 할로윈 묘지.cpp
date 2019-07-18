#include <iostream>
#include <algorithm>
#include <vector>
#include <memory.h>
#include <tuple>
using namespace std;

#define MAX 31
#define INF 50000000
typedef struct a {
	pair<int, int>ghost;		//귀신 통로 출구
	int time;		//귀신 통로 시간
	bool stone;		//묘비
	bool ghost_ent;	//귀신 입구 
}node;

int dist[MAX][MAX];
vector<tuple<pair<int, int>, pair<int, int>, int>>edge;	//from(y, x), to, weight

node map[MAX][MAX];
int W, H, G, X, Y, E;
int X1, X2, Y1, Y2;
int T;
int dy[] = { 0,0,-1,1 };
int dx[] = { -1,1,0,0 };

int main()
{
	while (1) {
		cin >> W >> H;
		if (W == 0 && H == 0)break;

		//초기화
		memset(map, 0, sizeof(map));
		edge.clear();
		for (int i = 0; i < H; i++)
			for (int j = 0; j < W; j++)
				dist[i][j] = INF;
		dist[0][0] = 0;	//시작점은 (0, 0)

		//묘비 정보
		cin >> G;
		for (int i = 0; i < G; i++) {
			cin >> X1 >> Y1;
			map[Y1][X1].stone = true;
		}

		//귀신 구멍 입력
		cin >> E;
		for (int i = 0; i < E; i++) {
			cin >> X1 >> Y1 >> X2 >> Y2 >> T;
			map[Y1][X1].ghost = make_pair(Y2, X2);
			map[Y1][X1].time = T;
			map[Y1][X1].ghost_ent = true;
		}

		//edge 설정
		int edge_cnt = 0;
		for (int y = 0; y < H; y++) {
			for (int x = 0; x < W; x++) {
				//귀신 구멍 입구가 아니고 묘비도 아니고, 도착 지점도 아니라면
				if (!map[y][x].ghost_ent && !map[y][x].stone && (y != H - 1 || x != W - 1)) {
					for (int i = 0; i < 4; i++) {
						int ny = y + dy[i];
						int nx = x + dx[i];
						if (ny < 0 || ny >= H || nx < 0 || nx >= W || map[ny][nx].stone)continue;
						edge.push_back(make_tuple(make_pair(y, x), make_pair(ny, nx), 1));
						edge_cnt++;
					}
				}
				//귀신 구멍 입구라면
				else if (map[y][x].ghost_ent) {
					int ny = map[y][x].ghost.first;
					int nx = map[y][x].ghost.second;
					edge.push_back(make_tuple(make_pair(y, x), make_pair(ny, nx), map[y][x].time));
					edge_cnt++;
				}
			}
		}

		//벨만 포드
		bool flag = false;
		for (int i = 0; i < H * W - G; i++) {		//전체 노드 - 묘비 수
			for (int j = 0; j < edge_cnt; j++) {	//모든 엣지에 대해
				int y1, x1, y2, x2, w;
				y1 = get<0>(edge[j]).first;
				x1 = get<0>(edge[j]).second;	//from
				y2 = get<1>(edge[j]).first;
				x2 = get<1>(edge[j]).second;	//to
				w = get<2>(edge[j]);

				/*if (i == 0)
					cout << "from: " << y1 << ", " << x1 << ", to: " << y2 << ", " << x2 << endl;*/

				if (dist[y1][x1] != INF && dist[y2][x2] > dist[y1][x1] + w) {
					dist[y2][x2] = dist[y1][x1] + w;
					if (i == H * W - G - 1)
						flag = true;
				}
			}
		}
		//cout << "edge: " << edge_cnt << endl;

		if (!flag && dist[H - 1][W - 1] == INF)
			cout << "Impossible" << endl;
		else if (flag)
			cout << "Never" << endl;
		else
			cout << dist[H - 1][W - 1] << endl;
	}

	return 0;
}
#include <iostream>
#include <algorithm>

using namespace std;

int gcd(int a, int b) {
	if (a % b == 0)return b;
	return gcd(b, a % b);
}

int main()
{
	int A, B, C, D, E, F;
	cin >> A >> B >> C >> D;

	E = A * D + B * C;
	F = B * D;

	int g = gcd(F, E);
	cout << E / g << ' ' << F / g << endl;

	return 0;
}
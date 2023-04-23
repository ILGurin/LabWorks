//CodeForses 69A
#include <iostream>

using namespace std;

int main()
{
	int n, x, y, z, nx = 0, ny = 0, nz = 0;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> x >> y >> z;
		nx += x;
		ny += y;
		nz += z;
	}
	if (nx == 0 && ny == 0 && nz == 0) cout << "YES";
	else cout << "NO";
	return 0;
}
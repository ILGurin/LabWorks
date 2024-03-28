#include <iostream>
#include <string>
#include "Ship.h"
using namespace std;

int main() {
	setlocale(LC_ALL, "ru");
	ship ship1 = ship("name1");
	steamer ship2 = steamer("name2", 40);
	sailboat ship3 = sailboat("name3", 15);
	corvette ship4 = corvette("name4", 17);
	ship2.show();
	cout << "------------------------------------------" << endl;
	ship3.show();
	cout << "------------------------------------------" << endl;
	ship::printHead();
	return 0;
}
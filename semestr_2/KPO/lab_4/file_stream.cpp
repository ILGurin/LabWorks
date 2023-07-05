#include <iostream>
#include <string>
#include <algorithm>
#include <fstream> 

using namespace std;

int main() {
    string str;
    ifstream ifstr;
    ifstr.open("input.txt");
    ofstream ofstr;
    ofstr.open("output.txt");
    ifstr >> str;
    string str2 = str;
   
    for (int i = 0; i < str.size(); i++) {
        str2[i] = str[str.size() - (i+1)];
    }
    cout << str2;
    ofstr << str2; 
    ifstr.close();
    ofstr.close();
    return 0;
}
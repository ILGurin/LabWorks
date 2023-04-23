#include <iostream>
#include <set>
#include <string>
#include <fstream>
#include <sstream>
#include <iterator>

using namespace std;

int main(){
    set<string> mySet;
    ifstream ifst("input_2.txt");
    string text;
    getline(ifst, text);
    istringstream iss(text);
    string word;
    while(iss >> word){
        mySet.insert(word);
    }
    ofstream ofst("output_2.txt");
    for (const auto &i:mySet){
        cout << i << endl;
    }
    return 0;
}
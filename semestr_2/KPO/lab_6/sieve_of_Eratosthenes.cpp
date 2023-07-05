#include <iostream>

using namespace std;

int main(){
    int n;
    cin >> n;
    bool* sieve = new bool[n+1];
    for(int i = 2; i < n+1; i++){
        sieve[i] = true;
    }
    int x = 2;
    while(x*x <= n){
        if(sieve[x]){
            for(int y = x*x; y <= n; y+=x){
                sieve[y] = false;
            }
        }
        x+=1;
    }
    for(int i = 2; i < n+1; i++){
        if(sieve[i]){
            cout << i << '\t';
        }
    }
    return 0;
}
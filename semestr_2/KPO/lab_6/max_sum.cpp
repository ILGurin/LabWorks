#include <iostream>
#include <vector>

using namespace std;

int main(){
    vector<int> numbers = {2, -5, 2, 2, -1, 3, -1, 2, -5, 4};
    int bSum = 0, bStart = 0, bEnd = 0, cSum = 0;

    for(int current_end = 0; current_end < numbers.size(); current_end++){
        if(cSum <= 0){
            cSum = numbers[current_end];
            bStart = current_end;
        }
        else{
            cSum += numbers[current_end];
        }

        if(cSum > bSum){
            bSum = cSum;
            bEnd = current_end + 1;
        }
    } 

    vector<int> result(numbers.begin() + bStart, numbers.begin() + bEnd);
    
    for(int x:result){
        cout << x << " ";
    }
    return 0;
}
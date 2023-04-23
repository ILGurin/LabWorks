#include <fstream>
#include <stack>

using namespace std;

bool check_brackets(string expression) {
  stack<char> brackets;
  for (char c : expression) {
    string arr = {", xyz1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvw"};
    bool a = true;
    for(int i = 0; i < arr.size(); i++){
        if(c == arr[i]){
            a = false;
            break;
        }
    }
    if(a == false){
        continue;
    }
    if (c == '[' || c == '(' || c == '{') {
      brackets.push(c);
      continue;
    }
    if (brackets.empty())
      return false;
    if (c == ']' && brackets.top() != '[')
      return false;
    if (c == ')' && brackets.top() != '(')
      return false;
    if (c == '}' && brackets.top() != '{')
      return false;
    brackets.pop();
  }
  return brackets.empty();
}
int main() {
  ifstream ifst("input.txt");
  ofstream ofst("output.txt");
  while (ifst) {
    string expression;
    ifst >> expression;
    if (ifst.eof() && expression.empty())
      break;
    if (check_brackets(expression)) {
      ofst << "ok";
    }
    else {
      ofst << "error";
    }
  }
}
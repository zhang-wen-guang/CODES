#include <string>
#include <stack>
#include <iostream>
#include <unordered_map>

using namespace std;

class Solution {
public:
    string reverseParentheses(string s) {
        std::stack<int> mystack;
        std::unordered_map<int, int> match;
        int left = 0;

        for (int i = 0; i < s.size(); ++i)
        {
            if (s[i] == '(')
                mystack.push(i);

            if (s[i] == ')') {
                left = mystack.top();
                match.emplace(left, i);
                match.emplace(i, left);
                mystack.pop();
            }
        }

        mystack.push(-1);
        int p = 0, dir = 1;
        std::string res = "";
        while (p < s.size()) {
            if (s[p] != '(' && s[p] != ')' ) {
                res.push_back(s[p]);
                p += dir;
            }
            if (s[p] == '(') {
                if (p == mystack.top()) {
                    p = match[p] + 1;
                    dir = 1;
                    mystack.pop();
                } else {
                    mystack.push(p);
                    p = match[p] - 1;
                    dir = -1;
                }

            }
            if (s[p] == ')') {
                if (p == mystack.top()) {
                    p = match[p] - 1;
                    dir = -1;
                    mystack.pop();
                } else {
                    mystack.push(p);
                    p = match[p] + 1;
                    dir = 1;
                }
            }
        }
        return res;
    }
};

int main()
{
    string s = "a(bcdefghijkl(mno)p)q";

    Solution sol;
    std::string res = sol.reverseParentheses(s);
    std::cout << res << std::endl;
}
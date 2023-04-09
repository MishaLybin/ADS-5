// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include <tstack.h>

int priority(char x) {
    if (x == '(')
        return 0;
    else if (x == ')')
        return 1;
    else if (x == '+' || x == '-')
        return 2;
    else if (x == '*' || x == '/')
        return 3;
    else if (x == ' ')
        return -1;
    else
        return -2;
}

std::string infx2pstfx(std::string find) {
  TStack<char, 100> stack1;
    std::string N;
    for (int i = 0; i < find.size(); ++i) {
        if (priority(find[i]) == 0) {
            stack1.push(find[i]);
        } else if (priority(find[i]) > stack1.get()
                   && !stack1.isEmpty()) {
            stack1.push(find[i]);
        } else if (stack1.isEmpty() && priority(find[i]) != -2) {
            stack1.push(find[i]);
        } else {
            if (priority(find[i]) == 1) {
                while (priority(stack1.get()) != 0) {
                    N += stack1.pop();
                    N += ' ';
                }
                stack1.pop();
            } else if (priority(find[i]) == -2
                       && i != find.size() - 1) {
                int j;
                for (j = i; priority(find[j]) == -2; ++j) {
                    N += find[j];
                }
                i += j - i - 1;
                N += ' ';
            } else {
                while (priority(stack1.get()) >=
                       priority(find[i])
                       && priority(find[i]) != -2) {
                    N += stack1.pop();
                    N += ' ';
                }
                stack1.push(inf[i]);
            }
        }
        if (i == inf.size() - 1) {
            while (!stack1.isEmpty()) {
                N += stack1.pop();
                N += ' ';
            }
        }
    }
    N.pop_back();
    return N;
}

int eval(std::string pref) {
  TStack<int, 100> stack2;
    for (char a : pref) {
        if (isdigit(a)) {
            stack2.push(a - '0');
        } else if (a == ' ') {
            continue;
        } else {
            int second = stack2.pop();
            int first = stack2.pop();
            switch (a) {
            case ('+'):
                stack2.push(first + second);
                break;
            case ('-'):
                stack2.push(first - second);
                break;
            case ('*'):
                stack2.push(first * second);
                break;
            case ('/'):
                stack2.push(first / second);
                break;
            }
        }
    }
    return stack2.get();
}

// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

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

std::string infx2pstfx(std::string inf) {
  TStack<char, 100> stack1;
    std::string N;
    for (int i = 0; i < inf.size(); ++i) {
        if (priority(inf[i]) == 0) {
            stack1.push(inf[i]);
        } else if (priority(inf[i]) > stack1.get()
                   && !stack1.isEmpty()) {
            stack1.push(inf[i]);
        } else if (stack1.isEmpty() && priority(inf[i]) != -2) {
            stack1.push(inf[i]);
        } else {
            if (priority(inf[i]) == 1) {
                while (priority(stack1.get()) != 0) {
                    N += stack1.pop();
                    N += ' ';
                }
                stack1.pop();
            } else if (priority(inf[i]) == -2
                       && i != inf.size() - 1) {
                int j;
                for (j = i; priority(inf[j]) == -2; ++j) {
                    N += inf[j];
                }
                i += j - i - 1;
                N += ' ';
            } else {
                while (priority(stack1.get()) >=
                       priority(inf[i])
                       && priority(inf[i]) != -2) {
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
    for (char symb : pref) {
        if (isdigit(symb)) {
            stack2.push(symb - '0');
        } else if (symb == ' ') {
            continue;
        } else {
            int second = stack2.pop();
            int first = stack2.pop();
            switch (symb) {
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

// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int priority(char x) {
    switch (x) {
        case '(':
            return 0;
        case ')':
            return 1;
        case '+':
            return 2;
        case '-':
            return 2;
        case '*':
            return 3;
        case '/':
            return 3;
        default:
            return -1;
    }
}

std::string infx2pstfx(std::string fin) {
  TStack<char, 100> stack1;
    std::string n;
    for (int i = 0; i < fin.size(); ++i) {
        if (priority(fin[i]) == 0) {
            stack1.push(fin[i]);
        } else if (priority(fin[i]) > stack1.get()
                   && !stack1.isEmpty()) {
            stack1.push(fin[i]);
        } else if (stack1.isEmpty() && priority(fin[i]) != -2) {
            stack1.push(fin[i]);
        } else {
            if (priority(fin[i]) == 1) {
                while (priority(stack1.get()) != 0) {
                    n += stack1.pop();
                    n += ' ';
                }
                stack1.pop();
            } else if (priority(inf[i]) == -2
                       && i != fin.size() - 1) {
                int j;
                for (j = i; priority(fin[j]) == -2; ++j) {
                    n += fin[j];
                }
                i += j - i - 1;
                n += ' ';
            } else {
                while (priority(stack1.get()) >=
                       priority(fin[i])
                       && priority(fin[i]) != -2) {
                    n += stack1.pop();
                    n += ' ';
                }
                stack1.push(fin[i]);
            }
        }
        if (i == fin.size() - 1) {
            while (!stack1.isEmpty()) {
                n += stack1.pop();
                n += ' ';
            }
        }
    }
    n.pop_back();
    return n;
}

int eval(std::string cr) {
  TStack<int, 100> stack2;
    for (char a : cr) {
        if (isdigit(a)) {
            stack2.push(a - '0');
        } else if (a == ' ') {
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

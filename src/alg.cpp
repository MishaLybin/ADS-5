// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int getPrior(char op) {
    switch (op) {
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
    }
    return -1;
}

std::string infx2pstfx(std::string inf) {
    TStack<char, 100> stack1;
    std::string str = "";
    int result = 0;
    for (char a : inf) {
        bool truefalse = true;
        if (getPrior(a) == 0) {
            stack1.push(a);
            truefalse = false;
        }
        if (getPrior(a) == -1) {
            str = str + a;
            str = str + ' ';
            truefalse = false;
        }
        if (getPrior(a) > getPrior(stack1.get())) {
            stack1.push(a);
            truefalse = false;
        }
        if (stack1.isEmpty() && getPrior(a) != -1) {
            stack1.push(a);
            truefalse = false;
        }
        if (a != ')' && truefalse) {
            while (getPrior(stack1.get()) >= getPrior(a)) {
                str = str + stack1.pop();
                str = str + ' ';
            }
            stack1.push(a);
        }
        if (a == ')') {
            while (stack1.get() != '(') {
                str = str + stack1.pop();
                str = str + ' ';
            }
            stack1.pop();
        }
        if (result == inf.size() - 1) {
            while (!stack1.isEmpty()) {
                str = str + stack1.pop();
                if (stack1.pri() != -1) {
                    str = str + ' ';
                }
            }
        }
        ++result;
    }
    return str;
}

int eval(std::string post) {
    TStack<int, 100> stack2;
    for (char i : post) {
        if (i == '+') {
            int j = stack2.pop();
            j = j + stack2.pop();
            stack2.push(j);
        }
        if (i == '-') {
            int j = stack2.pop();
            j = stack2.pop() - j;
            stack2.push(j);
        }
        if (i == '*') {
            int j = stack2.pop();
            j = j * stack2.pop();
            stack2.push(j);
        }
        if (i == '/') {
            int j = stack2.pop();
            j = stack2.pop() / j;
            stack2.push(j);
        }
        if (i == ' ') {
            continue;
        }
        if ((i - '0') > 0) {
            int j = i - '0';
            stack2.push(j);
        }
    }
    return stack2.get();
}

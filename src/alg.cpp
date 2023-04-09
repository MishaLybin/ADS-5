// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int Prior(char c) {
    switch (c) {
    case '+':
        return 2;
    case '-':
        return 2;
    case '(':
        return 0;
    case ')':
        return 1;
    case '*':
        return 3;
    case '/':
        return 3;
    }
    return -1;
}

std::string infx2pstfx(std::string inf) {
    std::string p;
    TStack<char, 100> st;
    for (int i = 0; i < inf.size(); i++) {
        if ((inf[i] <= '9') && (inf[i] >= '0')) {
            p += inf[i];
            p += " ";
        } else {
            int k1 = Prior(inf[i]);
            int k2 = Prior(st.get());
            if (inf[i] == '(' || (k1 > k2) || st.isEmpty()) {
                st.push(inf[i]);
            } else if (inf[i] == ')') {
                char a = st.pop();
                while (a != '(') {
                    p += a;
                    p += " ";
                    a = st.pop();
                }
            } else if (Prior(inf[i] <= st.get())) {
                    while (Prior(inf[i] <= st.get()) && !st.isEmpty()) {
                        char a = st.pop();
                        p += a;
                        p += " ";
                    }
                    st.push(inf[i]);
                }
            }
        }
    while (!st.isEmpty()) {
        char a = st.pop();
            p += a;
            p += " ";
    }
    p.pop_back();
    return p;
}

int eval(std::string pref) {
    TStack <int, 100> temp;
    for (char a : pref) {
        if (a == ' ')
                continue;
        if ((a <= '9') && (a >= '0')) {
            int b = static_cast<int>(a - '0');
                temp.push(b);
        } else {
            int znac;
            int f = temp.get();
            temp.pop();
            int sec = temp.get();
            temp.pop();
            switch (a) {
            case '+':
                znac = sec + f;
                break;
            case '-':
                znac = sec - f;
                break;
            case '*':
                znac = sec * f;
                break;
            case '/':
                znac = sec / f;
                break;
            }
            temp.push(znac);
        }
    }
    return temp.pop();
}

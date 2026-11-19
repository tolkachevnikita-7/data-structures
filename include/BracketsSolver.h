#pragma once

#include <string>
#include "Stack.h"

namespace Brackets {

    inline bool isMatch(char open, char close) 
    {
        return (open == '(' && close == ')') ||
            (open == '[' && close == ']') ||
            (open == '{' && close == '}');
    }

    inline int Solve(const std::string& str) 
    {
        TStack<char> st(static_cast<int>(str.length()) + 1);
        int errors = 0;

        for (char c : str) {
            if (c == '(' || c == '[' || c == '{') {
                st.push(c);
            }
            else if (c == ')' || c == ']' || c == '}') 
            {
                if (st.IsEmpty()) 
                {
                    errors++; // Лишняя закрывающая
                }
                else if (isMatch(st.top(), c)) 
                {
                    st.pop(); // Нашли правильную пару
                }
                else 
                {
                    errors++; // Несовпадение типов
                    st.pop();
                }
            }
        }

        errors += static_cast<int>(st.GetSize());
        return errors;
    }
}
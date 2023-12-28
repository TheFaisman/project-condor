#include <iostream>

#include "std_lib_facilities.h"

class Token {
public:
    char    kind_{'u'}; // 'u' for uninitialized
    double  value_{0.0};
};

class TokenStream {
private:
    Token   buffer_{};
    bool    is_full_{false};

public:
    Token   GetToken();
    void    PutBack(Token t);
};

TokenStream t_stream{};

Token TokenStream::GetToken() {
    if (this->is_full_) {
        this->is_full_ = false;
        return this->buffer_;
    }
    
    Token token{};

    char ch = 'u';
    std::cin >> ch;
    switch (ch) {
        case '.':
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9': {
            double val = 0;
            std::cin.putback(ch);
            std::cin >> val;

            token.kind_     = '#';
            token.value_    = val;
            break;
        }
        case '{': case '}': case '!':
        case '+': case '-': case '/': case '*': 
        case '=': case '(': case ')': case 'q':
            token.kind_ = ch;
            break;
        default:
            error("Unknown token.");
            break;
    }
    return token;
}

void TokenStream::PutBack(Token token) {
    if (this->is_full_) {
        error("Token buffer already full.");
        return;
    }
    this->buffer_ = token;
    this->is_full_ = true;
    return;
}

double Primary();
double Term();
double Expression();

uint32_t Factorial(uint32_t x) {
    uint32_t i = 1;
    while (x > 0) {
        i *= x--;
    }
    return i;
}

double Primary() {
    double val = 0;
    Token token = t_stream.GetToken();
    switch (token.kind_) {
        case '#':
            val = token.value_;
            break;
        case '(': {
            val = Expression();
            token = t_stream.GetToken();
            if (token.kind_ != ')') {
                error("Invalid primary, ')' expected.");
            }
            break;
        }
        case '{': {
            val = Expression();
            token = t_stream.GetToken();
            if (token.kind_ != '}') {
                error("Invalid primary, '}' expected.");
            }         
            break;
        }
        default:
            t_stream.PutBack(token);
            break;
    }
    // Check for factorial after the primary
    token = t_stream.GetToken();
    if (token.kind_ == '!') {
        val = Factorial(static_cast<uint32_t>(val));
    } else {
        t_stream.PutBack(token);
    }
    return val;
}

double Term() {
    double term = Primary();
    Token token = t_stream.GetToken();
    while (true) {
        switch (token.kind_) {
            case '*':
                term *= Primary();
                token = t_stream.GetToken();
                break;
            case '/': {
                double p = Primary();
                if (p == 0) {
                    error("Cannot divide by zero.");
                }
                term /= p;
                token = t_stream.GetToken();
                break;
            }
            default:
                t_stream.PutBack(token);
                return term;
                break;
        }
    }
}

double Expression() {
    double expression = Term();
    Token token = t_stream.GetToken();
    while (true) {
        switch (token.kind_) {
            case '+':
                expression += Term();
                token = t_stream.GetToken();
                break;
            case '-':
                expression -= Term();
                token = t_stream.GetToken();
                break;
            default:
                t_stream.PutBack(token);
                return expression;
                break;
        }
    }
}

int main() {
    std::cout << "Project Condor: Arithmetic Calculator v1." << std::endl;
    double val{0};
    while (std::cin) {
        Token token = t_stream.GetToken();
        if (token.kind_ == 'q') break;
        if (token.kind_ == '=') {
            std::cout << "=" << val << std::endl;
        } else {
            t_stream.PutBack(token);
        }
        val = Expression();
    }
    return 0;
}
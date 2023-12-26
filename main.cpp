#include <iostream>

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

Token TokenStream::GetToken() {
    if (this->is_full_) {
        return this->buffer_;
    }
    Token t{};

    char c = 'u';
    std::cin >> c;
    switch (c) {
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9': {
            double val = 0;
            std::cin.putback(c);
            std::cin >> val;

            t.kind_     = '#';
            t.value_    = val;
            break;
        }
        case '+': case '-': case '/': case '*': 
        case '=': case '(': case ')': case 'q':
            t.kind_ = c;
            break;
        default:
            std::cerr << "Throw an unknown token error." << std::endl;
            break;
    }
    return t;
}

void TokenStream::PutBack(Token t) {
    if (this->is_full_) {
        std::cerr << "Throw an error: putting back into full buffer." << std::endl;
        return;
    }
    this->buffer_ = t;
    return;
}

TokenStream t_stream{};

double Primary();
double Term();
double Expression();

double Primary() {
    double val = 0;
    Token t = t_stream.GetToken();
    switch (t.kind_) {
    case '#':
        return t.value_;
        break;
    case '(':
        val = Expression();
        t = t_stream.GetToken();
        if (t.kind_ != ')') {
            std::cerr << "Throw an error, we didn't get a close bracket" << std::endl;
            return 0;
        }
        return val;
        break;
    }
}

double Term() {
    double val = Primary();
    double p = 0;
    Token t = t_stream.GetToken();
    switch (t.kind_) {
    case '*':
        val *= Primary();
        break;
    case '/':
        p = Primary();
        if (p == 0) {
            std::cerr << "Divide by 0 error" << std::endl;
            return 0;
        }
        val /= p;
    }
}

double Expression() {
    double val = Term();
    Token t = t_stream.GetToken();
    switch (t.kind_) {
        case '+':
            val += Term();
            break;
        case '-':
            val -= Term();
            break;
        default:
            break;
    }
    return val;
}

int main() {
    std::cout << "Project Condor: Arithmetic Calculator v1." << std::endl;
    std::cout << "Enter an expression below and end with = to evaluate." << std::endl;
    while (std::cin) {
        
    }
    return 0;
}
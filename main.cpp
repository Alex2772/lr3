#include <iostream>
#include <sstream>
#include <stack>
#include <cassert>

int main() {
    try {
        std::cout << "Expr: ";
        std::string wholeExpr;
        std::getline(std::cin, wholeExpr);
        std::stringstream ss(wholeExpr);

        std::stack<int> numbers;
        std::stack<char> ops;

        std::cout << "PLSK: ";

        std::string token;
        while (!ss.eof()) {
            ss >> token;
            if (token.empty()) {
                continue;
            }
            try {
                auto v = std::stod(token);
                numbers.push(v);
                std::cout << v << ' ';
            } catch (...) {
                if (token.length() != 1) {
                    throw std::runtime_error{"invalid operation: " + token};
                }
                switch (token[0]) {
                    case '+':
                    case '-':
                    case '*':
                    case '/':
                    case '(':
                    case '^':
                        ops.push(token[0]);
                        break;
                    case ')':
                        while (ops.top() != '(') {
                            std::cout << ops.top() << ' ';
                            ops.pop();
                            if (ops.empty()) {
                                throw std::runtime_error{"brackets are not consistent"};
                            }
                        }
                        ops.pop();
                        break;

                    default:
                        throw std::runtime_error{std::string("invalid operation: ") + token[0]};
                }
            }
        }
        if (ops.empty()) {
            throw std::runtime_error{"not enough numbers"};
        }

        int finalValue = numbers.top();
        numbers.pop();
        while (!ops.empty()) {
            if (ops.top() == '(') {
                throw std::runtime_error{"brackets are not consistent"};
            }

            if (ops.empty()) {
                throw std::runtime_error{"not enough numbers"};
            }
            int num = numbers.top();
            numbers.pop();
            switch (ops.top()) {
                case '+':
                    finalValue = num + finalValue;
                    break;
                case '-':
                    finalValue = num - finalValue;
                    break;
                case '*':
                    finalValue = num * finalValue;
                    break;
                case '/':
                    if (finalValue == 0) {
                        throw std::runtime_error{"zero division"};
                    }
                    finalValue = num / finalValue;
                    break;
            }

            std::cout << ops.top() << ' ';
            ops.pop();
        }
        std::cout << std::endl << "= " << finalValue;
    } catch (const std::exception& e) {
        std::cout << "error: " << e.what();
        return -1;
    }


    return 0;
}

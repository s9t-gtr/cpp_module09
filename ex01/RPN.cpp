#include "RPN.hpp"
#include <climits>

RPN::RPN(){}
RPN::~RPN(){}
RPN::RPN(const RPN &other){
    if(this == &other)
        return;
    *this = other;
}
RPN& RPN::operator=(const RPN &other){
    if(this != &other)
        stack = other.stack; //deep copy?
    return *this;
}


void RPN::exec(char **argv){
    std::string arg = std::string(argv[1]);
    for(std::string::size_type i=0;i<arg.length();i++){
        switch(int category = checkArgCategory(static_cast<char>(arg[i]))){
            case NUM:
                stack.push(static_cast<int>(arg[i])-CONVERT_ASCII_TO_DIGIT);
                break;
            case OPERATOR:
                operation(static_cast<char>(arg[i]));
                break;
            case SPACE:
                break;
            case INVALID:
                throw InvalidArgValue();
        }
    }
    if(stack.size() == 1)
        std::cout << stack.top() << std::endl;
    else
        throw InvalidArgGrammer();
}

int RPN::checkArgCategory(char c){
    if('0' <= c && c <= '9'){
        return NUM;
    }    
    if(c == '+' || c == '-' || c == '*' || c == '/')
        return OPERATOR;
    if(c == ' ')
        return SPACE;
    return INVALID;
}

void RPN::operation(char operatorType){
    if(stack.size() >= OPERABLE_STACK_SIZE){
        int b = stack.top();
        stack.pop();
        int a = stack.top();
        stack.pop();
        execOperation(a, b, operatorType);
    }else
        throw InvalidArgGrammer();
}


void RPN::execOperation(int a, int b, char operatorType){
    if(operatorType == '+') {
        if((b > 0 && a > INT_MAX - b) || (b < 0 && a < INT_MIN - b)) {
            throw Overflow();
        }
        stack.push(a + b);
    }
    else if(operatorType == '-') {
        if((b < 0 && a > INT_MAX + b) || (b > 0 && a < INT_MIN + b)) {
            throw Overflow();
        }
        stack.push(a - b);
    }
    else if(operatorType == '*') {
        if(a != 0 && b != 0 && (a > INT_MAX / b || a < INT_MIN / b)) {
            throw Overflow();
        }
        stack.push(a * b);
    }
    else if(operatorType == '/') {
        if(b == 0) {
            throw DivisionByZero();
        }
        if(a == INT_MIN && b == -1) { // Special case for division overflow
            throw Overflow();
        }
        stack.push(a / b);
    }
}

const char *RPN::InvalidArgValue::what() const throw(){
    return "Error";
}

const char *RPN::InvalidArgGrammer::what() const throw(){
    return "Error";
}
const char *RPN::DivisionByZero::what() const throw(){
    return "Error";
}
const char *RPN::InvalidSpaceUsage::what() const throw(){
    return "Error";
}
const char *RPN::Overflow::what() const throw(){
    return "Error";
}

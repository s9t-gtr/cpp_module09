#include "RPN.hpp"

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
    static int argNum = 0;
    if('0' <= c && c <= '9'){
        if(++argNum > RPN_NUM_MAX)
            throw InvalidArgNum();
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
    if(operatorType == '+')
        stack.push(a+b);
    else if(operatorType == '-')
        stack.push(a-b);
    else if(operatorType == '*')
        stack.push(a*b);
    else if(operatorType == '/'){
        if(b == 0)
            throw DivisionByZero();
        stack.push(a/b);
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
const char *RPN::InvalidArgNum::what() const throw(){
    return "Error";
}

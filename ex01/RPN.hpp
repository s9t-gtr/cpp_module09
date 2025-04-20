#ifndef __RPN_HPP_
# define __RPN_HPP_

#include <iostream>
#include <stack>

//argcの値なので./RPNの分*1する
#define RPN_ARG_CNT 2

#define OPERABLE_STACK_SIZE 2

#define NUM 0
#define OPERATOR 1
#define SPACE 2
#define INVALID -1

#define CONVERT_ASCII_TO_DIGIT 48

class RPN{
    private:
        std::stack<int> stack;
    public:
        RPN();
        ~RPN();
        RPN(const RPN &other);
        RPN& operator=(const RPN &other);
    private:
        int checkArgCategory(char arg);
        void operation(char operatorType);
        void execOperation(int a, int b, char operatorType);
        int toInt(char *arg);
        void checkSpace(std::string arg);
    public:
        void exec(char **argv);

        class InvalidArgValue: public std::exception{
            public:
                const char *what() const throw();
        };
        class InvalidArgGrammer: public std::exception{
            public:
                const char *what() const throw();
        };
        class InvalidSpaceUsage: public std::exception{
            public:
                const char *what() const throw();
        };
        class DivisionByZero: public std::exception{
            public:
                const char *what() const throw();
        };
        class Overflow: public std::exception{
            public:
                const char *what() const throw();
        };
};

#endif
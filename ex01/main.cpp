#include "RPN.hpp"

int main(int argc, char** argv){
    if(RPN_ARG_CNT == argc){
        RPN rpn = RPN();
        try{
            rpn.exec(argv);
        }catch(RPN::InvalidArgGrammer &e){
            std::cout << e.what() << std::endl;
        }catch(RPN::InvalidArgValue &e){
            std::cout << e.what() << std::endl;
        }catch(RPN::DivisionByZero &e){
            std::cout << e.what() << std::endl;
        }catch(RPN::InvalidSpaceUsage &e){
            std::cout << e.what() << std::endl;
        }catch(RPN::InvalidArgNum &e){
            std::cout << e.what() << std::endl;
        }
    }else{
        std::cout << "Usage: Arguments must be at least 1 and less than 10" << std::endl;
    }
}
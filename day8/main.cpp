#include<iostream>
#include"logger.h"
#include"let.h"

int main(){

    Let a = 45.3;
    Let b = 56.7;

    Let c = a + b;
    Let d = b - a;

    ConsoleLogger logger;

    LoggingDecorator loggingLet1(a, logger);
    LoggingDecorator loggingLet2(b, logger);

    LoggingDecorator result = loggingLet1 + loggingLet2;
    std::cout<< result << std::endl; 
    std::cout<< c << std::endl; 
    std::cout<< d << std::endl; 

    return 0;
}
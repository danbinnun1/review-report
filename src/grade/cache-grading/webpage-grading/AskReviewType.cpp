#include "AskReviewType.hpp"
#include <string>
#include <iostream>

grading::ReviewType grading::askUser()
{
    std::string input;
    std::cout<< "enter bad, not bad, or not interesting"<<std::endl;
    while (true) {
        getline(std::cin, input);
        if (input=="bad"){
            return grading::ReviewType::BAD;
        }
        if (input=="not bad"){
            return grading::ReviewType::NOT_BAD;
        }
        if (input=="not interesting"){
            return grading::ReviewType::UNINTERESTING;
        }
        std::cout<<"invalid input"<<std::endl;
    }
}
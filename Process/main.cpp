/*
Imagine this as a console application which takes input, process it and generates output to output console.
*/

#include <iostream>
#include <string>

void count_characters(std::string &str) {
    int len = str.length();
    len++;
    std::cout<<"The number of characters in { "<<str<<" } are: "<<len<<std::endl;
}

int main() {
    while (1) {
        std::cout<<"shell> ";
        std::string input;
        std::getline(std::cin, input);
        count_characters(input);
    }
    return 0;
}
#include "input.h"
#include <iostream>
#include <sstream>
#include <cctype>

std::string toLower(std::string value) {
    for (int i = 0; i < static_cast<int>(value.length()); i++)
        value[i] = static_cast<char>(std::tolower(static_cast<unsigned char>(value[i])));
    return value;
}

std::string readRequired(const std::string& prompt) {
    while (true) {
        std::cout << prompt;
        std::string value;
        std::getline(std::cin, value);
        if (value.find_first_not_of(" \t\r\n") != std::string::npos)
            return value;
        std::cout << "Input cannot be empty.\n";
    }
}

int readInt(const std::string& prompt, int minimum, int maximum) {
    while (true) {
        std::string line = readRequired(prompt);
        std::stringstream parser(line);
        int value;
        char extra;
        if ((parser >> value) && !(parser >> extra) && value >= minimum && value <= maximum)
            return value;
        std::cout << "Enter a whole number from " << minimum << " to " << maximum << ".\n";
    }
}

double readDouble(const std::string& prompt, double minimum, double maximum) {
    while (true) {
        std::string line = readRequired(prompt);
        std::stringstream parser(line);
        double value;
        char extra;
        if ((parser >> value) && !(parser >> extra) && value >= minimum && value <= maximum)
            return value;
        std::cout << "Enter a number from " << minimum << " to " << maximum << ".\n";
    }
}

std::string readChoice(const std::string& prompt, const std::string choices[], int size) {
    while (true) {
        std::string value = toLower(readRequired(prompt));
        for (int i = 0; i < size; i++)
            if (value == toLower(choices[i]))
                return choices[i];
        std::cout << "Valid values: ";
        for (int i = 0; i < size; i++)
            std::cout << choices[i] << (i == size - 1 ? ".\n" : ", ");
    }
}

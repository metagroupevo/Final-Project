#ifndef INPUT_H
#define INPUT_H
#include <string>
int readInt(const std::string& prompt, int minimum, int maximum);
double readDouble(const std::string& prompt, double minimum, double maximum);
std::string readRequired(const std::string& prompt);
std::string readChoice(const std::string& prompt, const std::string choices[], int size);
std::string toLower(std::string value);
#endif

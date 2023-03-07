//
//  main.cpp
//  DPB_01
//
//  Created by Furkan Karagöz on 7.03.2023.
//  Topic:      The Chain of Responsibility Pattern
//  Example:    Check user credentials

#include <iostream>
#include <regex>

class StringValidator
{
public:
    virtual ~StringValidator() {};
    virtual StringValidator *setNext(StringValidator *nextValidator) = 0;
    virtual std::string validate (std::string) = 0;
};

class BaseValidator: public StringValidator
{
protected:
    StringValidator *next = nullptr;
public:
    virtual ~BaseValidator() {delete next;};
    StringValidator *setNext(StringValidator *nextValidator) override
    {
        next = nextValidator;
        return nextValidator;
    }
    virtual std::string validate(std::string testString) override
    {
        if (this->next)
            return this->next->validate(testString);
        return "Success!";
    }
};

class NotEmptyValidator: public BaseValidator
{
public:
    NotEmptyValidator() {};
    std::string validate(std::string testString)
    {
        puts("Checking if empty...");
        if (testString.empty())
            return "Please enter a value.\n";
        return BaseValidator::validate(testString);
    }
};

class LengthValidator: public BaseValidator
{
    int minLength;
public:
    LengthValidator(int minLength) : minLength(minLength) {};
    std::string validate(std::string testString) override
    {
        puts("Checking string length...");
        if (testString.length() < minLength)
            return "Please enter a value longer than " + std::to_string(minLength) + "\n";
        return BaseValidator::validate(testString);
    }
};

class RegexValidator : public BaseValidator
{
    std::string patternName;
    std::string regexString;
public:
    RegexValidator(std::string patternName, std::string regexString) : patternName(patternName), regexString(regexString) {};
    std::string validate(std::string testString) override
    {
        puts("Checking regex match...");
        if(!std::regex_match(testString, std::regex(regexString)))
            return "The value entered does not match the proper format for a " + patternName + "\n";
        return BaseValidator::validate(testString);
    }
};

bool in_array(const std::string &value, const std::vector<std::string> &array)
{
    return std::find(array.begin(), array.end(), value) != array.end();
}

class HistoryValidator : public BaseValidator
{
    std::vector<std::string> historyItems;
public:
    HistoryValidator(std::vector<std::string> historyItems) : historyItems(historyItems) {};
    std::string validate(std::string testString) override
    {
        puts("Checking if string has been used before...");
        if(in_array(testString, historyItems))
            return "Please enter a value here that your haven't entered before.\n";
        return BaseValidator::validate(testString);
    }
};

int main(void)
{
    // Chain the chain of responsibilities
    StringValidator *emailValidator = new BaseValidator;
    
    emailValidator
    ->setNext(new NotEmptyValidator)
    ->setNext(new RegexValidator("email address", "^\\w+([-+.']\\w+)*@\\w+([-.]\\w+)*\\.\\w+([-.]\\w+)*$"));
    
    // Test cases:
    std::cout << "Checking Emails -----------\n";
    std::cout << "Input: \n" << emailValidator->validate("") << "\n";
    std::cout << "Input: shaun\n" << emailValidator->validate("shaun") << "\n";
    std::cout << "Input: shaun@test.com\n" << emailValidator->validate("shaun@test.com") << "\n";
    
    delete emailValidator;
    
    return 0;
}

/* Result:
 Checking Emails -----------
 Input:
 Checking if empty...
 Please enter a value.

 Input: shaun
 Checking if empty...
 Checking regex match...
 The value entered does not match the proper format for a email address

 Input: shaun@test.com
 Checking if empty...
 Checking regex match...
 Success!

 Program ended with exit code: 0
 */

// TODO:
// Create passwoed validator
// also utilizing length and history validators.

/*
 * Console.h
 *
 *  Created on: 22.12.2019
 *      Author: Marcin
 */

#ifndef CONSOLE_H_
#define CONSOLE_H_

#include <string>

enum class KeyCode : int
{
    LF = 10,
    CR = 13,
    Escape = 27,
    Tilde = 126,
    Backspace = 127
};

class Console
{
public:
    Console();
    void handler(void);
private:
    std::string inputLine;
};

#endif /* CONSOLE_H_ */

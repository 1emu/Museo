/*
 * Colors.cpp
 *
 *  Created on: May 3, 2014
 *      Author: jp
 */

#include "Colors.h"

void Colors::writeout(string message, const char* color){
	string coloredMessage = colorMessage(message, color);
	Utils::writeout(coloredMessage);
}


void Colors::writeerr(string message, const char* color){
	string coloredMessage = colorMessage(message, color);
	Utils::writeerr(coloredMessage);
}

string Colors::colorMessage(string message, const char* color) {
	string header = "\033[";
	string ending = "\033[0m";
	string coloredMessage = header + color + "m" + message + ending;
	return coloredMessage;
}

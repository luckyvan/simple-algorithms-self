/*
 * =====================================================================================
 *
 *       Filename:  Int2ExcelHeader.cpp
 *
 *    Description:  Excel Header: A-Z, AA, AB, ...
 *
 *        Version:  1.0
 *        Created:  05/11/2013 08:00:52 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */


#include <string>
#include <iostream>

using std::string;

string convertNum2ExcelHeader(size_t num, bool isBits = true){
	size_t divisor = (isBits)?26:27;
	size_t reminder = num % divisor;
	char temp = 'A'
   		+ reminder;
	
	size_t quot = num / divisor;
	if(quot == 0 && !isBits) temp--;
	
	return (quot != 0) ? convertNum2ExcelHeader(quot, false) + string(1,temp): string(1,temp);
}

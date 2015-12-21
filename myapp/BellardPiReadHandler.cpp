/*
 * BellardPiReadHandler.cpp
 *
 *  Created on: 20 дек. 2015 г.
 *      Author: imizus
 */

#include "BellardPiReadHandler.h"

void BellardPiReadHandler::checkResult() {
	  if (resultByteReadHandler == NULL) {
		  int piDigit = getPiDigit(n);

		  char digitStr[20];
		  digitStr[0] = 0;

		  sprintf(digitStr, "%09d", piDigit);

		  CefString str(digitStr);
		  int length = str.size() * sizeof(CefString::char_type);
		  resultByteReadHandler = new CefByteReadHandler((unsigned char*)str.c_str(), length, CefRefPtr<CefBase>(this));
	  }
}

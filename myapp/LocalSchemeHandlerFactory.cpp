/*
* LocalSchemeHandlerFactory.cpp
*
*  Created on: 18 ‰ÂÍ. 2015 „.
*      Author: imizus
*/

#include <stdlib.h>

#include "LocalSchemeHandlerFactory.h"
#include "BellardPiReadHandler.h"

#include "target/index.html.h"

CefRefPtr<CefResourceHandler> LocalSchemeHandlerFactory::Create(CefRefPtr<CefBrowser> browser,
										   CefRefPtr<CefFrame> frame,
										   const CefString& scheme_name,
										   CefRefPtr<CefRequest> request) {
// Return a new resource handler instance to handle the request.
//return new MyResourceHandler();

  CefURLParts parts;
  CefParseURL(request->GetURL(), parts);
  CefString requestHost(&parts.host);
  CefString requestPath(&parts.path);
  CefString requestQuery(&parts.query);

  if (requestPath == "/") {
	  //CefRefPtr<CefStreamReader> stream = CefStreamReader::CreateForFile("index.html");
	  // Create a stream reader for |html_content|.
	  CefRefPtr<CefStreamReader> stream =
		  CefStreamReader::CreateForData(
			  static_cast<void*>(__index_html),
			  __index_html_len);

	  // Constructor for HTTP status code 200 and no custom response headers.
	  // Thereís also a version of the constructor for custom status code and response headers.
	  return new CefStreamResourceHandler("text/html", stream);
  } else if (requestPath == "/api/pi_digit") {

	  int n = stoi(requestQuery.ToString());

	  /*int piDigit = getPiDigit(n);

	  char digitStr[11]; itoa(piDigit, digitStr, 10);
	  std::string str = std::string(digitStr);

	  const std::string& html_content = ((std::string)digitStr);

	  // Create a stream reader for |html_content|.
	  CefRefPtr<CefStreamReader> stream =
		  CefStreamReader::CreateForData(
			  static_cast<void*>(const_cast<char*>(html_content.c_str())),
			  html_content.size());

	  return new CefStreamResourceHandler("text/html", stream);*/

	  CefRefPtr<CefStreamReader> stream =
		  CefStreamReader::CreateForHandler(new BellardPiReadHandler(n));
	  return new CefStreamResourceHandler("text/html", stream);
  } else {
	  return NULL;
  }
}


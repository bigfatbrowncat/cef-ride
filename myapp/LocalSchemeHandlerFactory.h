/*
 * LocalSchemeHandlerFactory.h
 *
 *  Created on: 18 дек. 2015 г.
 *      Author: imizus
 */

#ifndef LOCALSCHEMEHANDLERFACTORY_H_
#define LOCALSCHEMEHANDLERFACTORY_H_

#include <unistd.h>

#include "include/cef_scheme.h"
#include "include/cef_parser.h"
#include "include/wrapper/cef_stream_resource_handler.h"

// Implementation of the factory for creating client request handlers.
class LocalSchemeHandlerFactory : public CefSchemeHandlerFactory {
 public:
  virtual CefRefPtr<CefResourceHandler> Create(CefRefPtr<CefBrowser> browser,
                                               CefRefPtr<CefFrame> frame,
                                               const CefString& scheme_name,
                                               CefRefPtr<CefRequest> request)
                                               OVERRIDE;

  IMPLEMENT_REFCOUNTING(LocalSchemeHandlerFactory);
};

#endif /* LOCALSCHEMEHANDLERFACTORY_H_ */

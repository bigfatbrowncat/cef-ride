// Copyright (c) 2013 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#ifndef CEF_TESTS_CEFSIMPLE_SIMPLE_APP_H_
#define CEF_TESTS_CEFSIMPLE_SIMPLE_APP_H_

#include "simple_handler.h"

#include "include/cef_app.h"

// Implement application-level callbacks for the browser process.
class SimpleApp : public CefApp,
                  public CefBrowserProcessHandler,
				  public CefRenderProcessHandler {
	CefRefPtr<SimpleHandler> handler;
	CefBrowserSettings browser_settings;
	CefWindowInfo window_info;

public:
  SimpleApp();

  // CefApp methods:
  virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler()
      OVERRIDE { return this; }

  virtual CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler()
	  OVERRIDE { return this; }


  // CefBrowserProcessHandler methods:
  virtual void OnContextInitialized() OVERRIDE;

  virtual void OnRegisterCustomSchemes(CefRefPtr<CefSchemeRegistrar> registrar) OVERRIDE;

  virtual void OnContextCreated(CefRefPtr<CefBrowser> browser,
                                CefRefPtr<CefFrame> frame,
                                CefRefPtr<CefV8Context> context);

  const CefBrowserSettings& GetBrowserSettings() {
	  return browser_settings;
  }

 private:
  // Include the default reference counting implementation.
  IMPLEMENT_REFCOUNTING(SimpleApp);
};

#endif  // CEF_TESTS_CEFSIMPLE_SIMPLE_APP_H_

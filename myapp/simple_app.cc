// Copyright (c) 2013 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#include "simple_app.h"

#include <string>

#include "simple_handler.h"
#include "include/cef_browser.h"
#include "include/cef_command_line.h"
#include "include/wrapper/cef_helpers.h"

#include "LocalSchemeHandlerFactory.h"

SimpleApp::SimpleApp() {
}

void SimpleApp::OnContextInitialized() {
  CEF_REQUIRE_UI_THREAD();

  // Information used when creating the native window.

#if defined(OS_WIN)
  // On Windows we need to specify certain flags that will be passed to
  // CreateWindowEx().
  window_info.SetAsPopup(NULL, "cefsimple");
#endif

  CefRegisterSchemeHandlerFactory("local", "myapp", new LocalSchemeHandlerFactory());

  // SimpleHandler implements browser-level callbacks.
  handler = new SimpleHandler();

  // Specify CEF browser settings here.

  std::string url;

  // Check if a "--url=" value was provided via the command-line. If so, use
  // that instead of the default URL.
  CefRefPtr<CefCommandLine> command_line =
      CefCommandLine::GetGlobalCommandLine();
  url = command_line->GetSwitchValue("url");
  if (url.empty()) {
    //url = "http://www.google.com";
    url = "local://myapp/";
  }

  // Create the first browser window.
  CefBrowserHost::CreateBrowser(window_info, handler.get(), url,
                                browser_settings, NULL);
}


bool DevToolsCefV8Handler::Execute(const CefString& name,
                     CefRefPtr<CefV8Value> object,
                     const CefV8ValueList& arguments,
                     CefRefPtr<CefV8Value>& retval,
                     CefString& exception) {
	  if (name == "showDevTools") {
		  printf("showDevTols function called\n");fflush(stdout);

		  //app->GetHandler()->ShowDevTools(browser);
		  return true;
	  }
	  return false;
}


void SimpleApp::OnContextCreated(CefRefPtr<CefBrowser> browser,
                              CefRefPtr<CefFrame> frame,
                              CefRefPtr<CefV8Context> context) {

	//devToolsHandler = new DevToolsCefV8Handler(browser, this);
	//CefRefPtr<CefV8Value> showDevTools_jsfunc = context->GetGlobal()->CreateFunction("showDevTools", devToolsHandler);
	//context->GetGlobal()->SetValue("showDevTools", showDevTools_jsfunc, V8_PROPERTY_ATTRIBUTE_READONLY);

	printf("showDevTols function created\n");fflush(stdout);

/*
	  CefRefPtr<CefV8Value> object = context->GetGlobal();

	  // Create a new V8 string value. See the "Basic JS Types" section below.
	  CefRefPtr<CefV8Value> str = CefV8Value::CreateString("My Value!");

	  // Add the string to the window object as "window.myval". See the "JS Objects" section below.
	  object->SetValue("myval", str, V8_PROPERTY_ATTRIBUTE_NONE);*/

	//browser->GetHost()->ShowDevTools(window_info, handler, GetBrowserSettings(), *(new CefPoint()));
}


void SimpleApp::OnRegisterCustomSchemes(CefRefPtr<CefSchemeRegistrar> registrar) {
	registrar->AddCustomScheme("local", true, false, false);
}


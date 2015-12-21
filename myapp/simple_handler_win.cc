// Copyright (c) 2013 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#include "simple_handler.h"

#include <string>
#include <windows.h>

#include "include/cef_browser.h"
#include "include/cef_v8.h"
#include "include/wrapper/cef_helpers.h"

void SimpleHandler::OnTitleChange(CefRefPtr<CefBrowser> browser,
                                  const CefString& title) {
  CEF_REQUIRE_UI_THREAD();
  CefWindowHandle hwnd = browser->GetHost()->GetWindowHandle();

  SetWindowTextW(hwnd, std::wstring(title).c_str());
}


#define ID_FILE_EXIT 9001
#define ID_STUFF_GO 9002


/*void SimpleHandler::OnAfterCreated(CefRefPtr<CefBrowser> browser) {
  CEF_REQUIRE_UI_THREAD();

  CefWindowHandle hwnd = browser->GetHost()->GetWindowHandle();

  CefV8Context* context = browser->GetMainFrame()->GetV8Context();

  HMENU hMenu, hSubMenu;
  HICON hIcon, hIconSm;

  hMenu = CreateMenu();

  hSubMenu = CreatePopupMenu();
  AppendMenu(hSubMenu, MF_STRING, ID_FILE_EXIT, "E&xit");
  AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&File");

  hSubMenu = CreatePopupMenu();
  AppendMenu(hSubMenu, MF_STRING, ID_STUFF_GO, "&Go");
  AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&Stuff");

  SetMenu(hwnd, hMenu);

  // Add to the list of existing browsers.
  browser_list_.push_back(browser);

}*/

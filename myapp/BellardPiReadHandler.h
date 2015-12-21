/*
 * BellardPiReadHandler.h
 *
 *  Created on: 20 дек. 2015 г.
 *      Author: imizus
 */

#ifndef BELLARDPIREADHANDLER_H_
#define BELLARDPIREADHANDLER_H_

#include <stddef.h>

#include <include/cef_base.h>
#include <include/cef_stream.h>

#include "include/wrapper/cef_byte_read_handler.h"

#include "bellard_pi.h"

// Class used to represent a custom scheme handler interface.
/*--cef(source=client)--*/
class BellardPiReadHandler : public CefReadHandler
{
private:
	int n;

	CefRefPtr<CefByteReadHandler> resultByteReadHandler = NULL;
	void checkResult();

public:
	BellardPiReadHandler(int n): n(n) { }

	  ///
	  // Read raw binary data.
	  ///
	  /*--cef()--*/
	  virtual size_t Read(void* ptr, size_t size, size_t n) {
		  checkResult();
		  return resultByteReadHandler->Read(ptr, size, n);
	  }

	  ///
	  // Seek to the specified offset position. |whence| may be any one of
	  // SEEK_CUR, SEEK_END or SEEK_SET. Return zero on success and non-zero on
	  // failure.
	  ///
	  /*--cef()--*/
	  virtual int Seek(int64 offset, int whence) {
		  checkResult();
		  return resultByteReadHandler->Seek(offset, whence);
	  }

	  ///
	  // Return the current offset position.
	  ///
	  /*--cef()--*/
	  virtual int64 Tell() {
		  checkResult();
		  return resultByteReadHandler->Tell();
	  }

	  ///
	  // Return non-zero if at end of file.
	  ///
	  /*--cef()--*/
	  virtual int Eof() {
		  checkResult();
		  return resultByteReadHandler->Eof();
	  }

	  ///
	  // Return true if this handler performs work like accessing the file system
	  // which may block. Used as a hint for determining the thread to access the
	  // handler from.
	  ///
	  /*--cef()--*/
	  virtual bool MayBlock() {
		  return true;
	  }
  IMPLEMENT_REFCOUNTING(BellardPiReadHandler);
};


#endif /* BELLARDPIREADHANDLER_H_ */

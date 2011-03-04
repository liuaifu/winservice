// Copyright 2010 The Go Authors.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package winservice

// #include "winservice.h"
import "C"

//import "unsafe"

func Start(name string) {
	p := C.CString(name)
	C.start(p)
	//C.free(unsafe.Pointer(p))
}

func Stop() {
	C.stop()
}


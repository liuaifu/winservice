// author: liuaifu
// laf163@gmail.com
// 2011-3-4

package winservice

// #include "winservice.h"
// #include <stdlib.h>
// #include <memory.h>
import "C"
import "unsafe"

type CallBack func()

var OnServiceStopped CallBack

func Start(name string) {
	p := C.CString(name)
	C.start(p)
	C.free(unsafe.Pointer(p))
}

func Stop() {
	C.stop()
}

//export NoticeServiceStopped
func NoticeServiceStopped() {
	if OnServiceStopped != nil {
		OnServiceStopped()
		OnServiceStopped = nil
	}
}

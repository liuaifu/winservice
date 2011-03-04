// Copyright 2009 The Go Authors.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package main

import (
	"time"
	"winservice"
)

func main() {
	winservice.Start("go")
	for{
		time.Sleep(20*1e9)
	}
	winservice.Stop()
	return
}

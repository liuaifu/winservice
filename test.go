// author: saturnfive
// laf163@gmail.com
// 2011-3-4

package main

import (
	"time"
	"winservice"
)

func main() {
	/**
	* ���GoService1�滻Ϊ�㴴���ķ�����������������������£�
	* ע�⣺�Ⱥź�Ŀո�ز�����
	* sc.exe create GoService1 binPath= x:\...\test.exe
	* sc start GoService1
	*/
	winservice.Start("GoService1")
	for{
		//��������һЩ����
		//do something here
		//...
		time.Sleep(20*1e9)
	}
	winservice.Stop()
	return
}

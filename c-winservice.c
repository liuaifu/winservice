// Copyright 2010 The Go Authors.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "winservice.h"
#include "_cgo_export.h"
#include "windows.h"

static char g_szServiceName[64] = "GoService1";

void ControlHandler(DWORD ); 
static SERVICE_STATUS ServiceStatus;
static SERVICE_STATUS_HANDLE hStatus;

void WINAPI ServiceMain(int argc, char** argv) 
{
	ServiceStatus.dwServiceType = SERVICE_WIN32; 
	ServiceStatus.dwCurrentState = SERVICE_START_PENDING; 
	ServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN;
	ServiceStatus.dwWin32ExitCode = 0;
	ServiceStatus.dwServiceSpecificExitCode = 0;
	ServiceStatus.dwCheckPoint = 0;
	ServiceStatus.dwWaitHint = 0;
	hStatus = RegisterServiceCtrlHandler(g_szServiceName, (LPHANDLER_FUNCTION)ControlHandler); 
	if (hStatus == (SERVICE_STATUS_HANDLE)0) 
	{ 
		// Registering Control Handler failed
		OutputDebugString("Registering Control Handler failed");
		return; 
	} 
	//Report the running status to SCM. 
	ServiceStatus.dwCurrentState = SERVICE_RUNNING; 
	SetServiceStatus (hStatus, &ServiceStatus);

	return; 
}

void ControlHandler(DWORD request) 
{ 
	switch(request) 
	{ 
		case SERVICE_CONTROL_STOP: 
			ServiceStatus.dwWin32ExitCode = 0; 
			ServiceStatus.dwCurrentState = SERVICE_STOPPED; 
			SetServiceStatus (hStatus, &ServiceStatus);
			return; 

		case SERVICE_CONTROL_SHUTDOWN: 
			ServiceStatus.dwWin32ExitCode = 0; 
			ServiceStatus.dwCurrentState = SERVICE_STOPPED; 
			SetServiceStatus (hStatus, &ServiceStatus);
			return; 

		default:
			break;
	}
	// Report current status
	SetServiceStatus (hStatus, &ServiceStatus);
	return; 
}

void ThreadFunc(void *parg)
{
	SERVICE_TABLE_ENTRY ServiceTable[2];
	ServiceTable[0].lpServiceName = g_szServiceName;
	ServiceTable[0].lpServiceProc = (LPSERVICE_MAIN_FUNCTION)ServiceMain;

	ServiceTable[1].lpServiceName = NULL;
	ServiceTable[1].lpServiceProc = NULL;
	StartServiceCtrlDispatcher(ServiceTable);
}

void start(char *name)
{
	strcpy(g_szServiceName, name);

	_beginthread(ThreadFunc,0,NULL);
}

void stop()
{
	ControlHandler(SERVICE_CONTROL_STOP);
}


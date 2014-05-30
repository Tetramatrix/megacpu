#include "IOAccess.h"
#include <stdio.h>
#include <winioctl.h>
#include "IOCTL.h"
 
IOAccess::IOAccess()
{
    hDevice =   NULL;
    hEvent  =   NULL;
    openDriver();
}
 
IOAccess::~IOAccess()
{
    closeDriver();
}
 
bool IOAccess::openDriver()
{
    hDevice = CreateFile(L"\\\\.\\kamel",
                                GENERIC_READ | GENERIC_WRITE,
                                FILE_SHARE_READ,
                                NULL,
                                OPEN_EXISTING,
                                FILE_ATTRIBUTE_NORMAL,
                                NULL);
 
    if (INVALID_HANDLE_VALUE == hDevice) 
	{
        //printf("Device Handle konnte nicht erstellt werden\n");
        return FALSE;
    }
    //printf("Device Handle erstellt\n");
    
    hEvent = CreateEvent(NULL, false, false, NULL);
    
    //download event object to device driver
    DeviceIoControl(hDevice, 
                    IO_REFERENCE_EVENT, 
                    (LPVOID) hEvent,
                    0, 
                    NULL, 
                    0, 
                    &dwBytesReturned, 
                    NULL);
    return TRUE;
 
}
 
void IOAccess::closeDriver()
{
    if(hDevice) {
        if(hEvent) {
            DeviceIoControl(hDevice, 
                            IO_DEREFERENCE_EVENT, 
                            NULL,0, 
                            NULL,0, 
                            &dwBytesReturned, 
                            NULL);
            CloseHandle(hEvent);
        }
 
        CloseHandle(hDevice);
    }
    //printf("Device Handle geschlossen\n");
}
 
void IOAccess::queryEvent()
{
    ULONG dwState;
 
    if(hEvent)
    {
        DeviceIoControl(hDevice, 
                IO_QUERY_EVENT_STATE, 
                NULL,
                0, 
                (LPVOID) &dwState, 
                sizeof(dwState), 
                &dwBytesReturned, 
                NULL);
                
       /* if(dwState) {
            printf("Event signaled state\n");
        }
        else {
            printf("Event not signaled state\n");
        }*/
    }   
}
 
void IOAccess::clearEvent()
{
    if(hEvent)
    {
        DeviceIoControl(hDevice, 
                IO_CLEAR_EVENT, 
                NULL,
                0, 
                NULL, 
                0, 
                &dwBytesReturned, 
                NULL);
    }
}
 
void IOAccess::setEvent()
{
    if(hEvent)
    {
        DeviceIoControl(hDevice, 
                IO_SET_EVENT, 
                NULL,
                0, 
                NULL, 
                0, 
                &dwBytesReturned, 
                NULL);
    }
}

void IOAccess::setFanMan()
{
    if(hEvent)
    {
        DeviceIoControl(hDevice, 
                IO_SET_FAN_MAN, 
                NULL,
                0, 
                NULL, 
                0, 
                &dwBytesReturned, 
                NULL);
    }
}

void IOAccess::setFanMin()
{
    if(hEvent)
    {
        DeviceIoControl(hDevice, 
                IO_SET_FAN_MIN, 
                NULL,
                0, 
                NULL, 
                0, 
                &dwBytesReturned, 
                NULL);
    }
}

void IOAccess::setFanMax()
{
    if(hEvent)
    {
        DeviceIoControl(hDevice, 
                IO_SET_FAN_MAX, 
                NULL,
                0, 
                NULL, 
                0, 
                &dwBytesReturned, 
                NULL);
    }
}

void IOAccess::setFanAuto()
{
    if(hEvent)
    {
        DeviceIoControl(hDevice, 
                IO_SET_FAN_AUTO, 
                NULL,
                0, 
                NULL, 
                0, 
                &dwBytesReturned, 
                NULL);
    }
}
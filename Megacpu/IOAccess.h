#ifndef __IO_ACCESS_H__
#define __IO_ACCESS_H__
 
#include <windows.h>
 
class IOAccess {
private:
    HANDLE  hDevice;
    HANDLE  hEvent;
    DWORD   dwBytesReturned;
public:
    IOAccess();
    ~IOAccess();
 
    bool openDriver();  
    void closeDriver(); 
 
    void queryEvent();
    void clearEvent();
    void setEvent();
    
    void setFanMan();
    void setFanMin();
    void setFanMax();
    void setFanAuto();
};
 
#endif // #ifndef __IO_ACCESS_H__
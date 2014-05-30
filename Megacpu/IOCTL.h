#ifndef __IO_CONTROL_H__
#define __IO_CONTROL_H__
 
const WCHAR deviceNameBuffer[] = L"\\Device\\kamel";
const WCHAR symbolicLinkNameBuffer[] = L"\\DosDevices\\kamel";
 
/* _____________________________________________________________________________ ______________________________________________________________________________________________
 .   IOCTL's are defined by the following bit layout.
 .   [ Common | Device Type | Required Access | Custom | Function Code | Transfer Type ]
 .      31     30         16 15             14    13    12           2  1            0
 .
 .   #define IOCTL_Device_Function CTL_CODE(DeviceType, Function, Method, Access)
 . 
 .   Common          - 1 bit.  This is set for user-defined device types.
 .   Device Type     - This is the type of device the IOCTL belongs to.  This can be user defined (Common bit set).  This must match the device type of the device object.
 .                   - Values of less than 0x8000 are reserved for Microsoft.
 .   Required Access - FILE_READ_DATA, FILE_WRITE_DATA, etc.  This is the required access for the device.
 .   Custom          - 1 bit.  This is set for user-defined IOCTL's.  This is used in the same manner as "WM_USER".
 .   Function Code   - This is the function code that the system or the user defined (custom bit set)
 .                   - Values of less than 0x800 are reserved for Microsoft
 .   Transfer Type   - Indicates how the system will pass data between the caller of DeviceIoControl (or IoBuildDeviceIoControlRequest) and the driver that handles the IRP.
 .                   - METHOD_IN_DIRECT, METHOD_OUT_DIRECT, METHOD_NEITHER, METHOD_BUFFERED.
 . _____________________________________________________________________________ ______________________________________________________________________________________________*/
 
#define FILE_DEVICE_TESTDEVICE 0x00008001
 
#define     IO_REFERENCE_EVENT          (ULONG) CTL_CODE(FILE_DEVICE_TESTDEVICE, 0x801, METHOD_NEITHER, FILE_ANY_ACCESS)
#define     IO_DEREFERENCE_EVENT        (ULONG) CTL_CODE(FILE_DEVICE_TESTDEVICE, 0x802, METHOD_NEITHER, FILE_ANY_ACCESS)
 
#define     IO_SET_EVENT                (ULONG) CTL_CODE(FILE_DEVICE_TESTDEVICE, 0x803, METHOD_NEITHER, FILE_ANY_ACCESS)
#define     IO_CLEAR_EVENT              (ULONG) CTL_CODE(FILE_DEVICE_TESTDEVICE, 0x804, METHOD_NEITHER, FILE_ANY_ACCESS)
#define     IO_QUERY_EVENT_STATE        (ULONG) CTL_CODE(FILE_DEVICE_TESTDEVICE, 0x805, METHOD_NEITHER, FILE_ANY_ACCESS)
#define     IO_SET_FAN_MAN			    (ULONG) CTL_CODE(FILE_DEVICE_TESTDEVICE, 0x806, METHOD_NEITHER, FILE_ANY_ACCESS)
#define     IO_SET_FAN_AUTO			    (ULONG) CTL_CODE(FILE_DEVICE_TESTDEVICE, 0x807, METHOD_NEITHER, FILE_ANY_ACCESS)
#define     IO_SET_FAN_MIN			    (ULONG) CTL_CODE(FILE_DEVICE_TESTDEVICE, 0x808, METHOD_NEITHER, FILE_ANY_ACCESS)
#define     IO_SET_FAN_MAX			    (ULONG) CTL_CODE(FILE_DEVICE_TESTDEVICE, 0x809, METHOD_NEITHER, FILE_ANY_ACCESS) 
 
#endif // #ifndef __IO_CONTROL_H__
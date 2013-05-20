#include "stdafx.h"
#include "changeRes.h"

void CChangeRes::setResolution (int newWidth, int newHeight)
{
    DISPLAY_DEVICE    device        = {0};
    struct DDList*    ddList        = NULL;
    DEVMODE           deviceMode    = {0};
    int               actualWidth   = 0;
    int               actualHeight  = 0;

    //    build display devices list
    DDList_Build(&ddList);

    //    get the first display device, if any (...); 
    //    decision is with user, or relying on other considerations
    device.cb = sizeof(device);
    if(DDList_Pop(&ddList, &device)) 
    {
        //    now change the display settings
        //    enumerate current (we can user NULL instead of device.DeviceName, 
        //    but this is more generic)
        deviceMode.dmSize            = sizeof(deviceMode);
        deviceMode.dmDriverExtra    = 0;
        if(EnumDisplaySettingsEx(device.DeviceName, ENUM_CURRENT_SETTINGS, &deviceMode, 0)) 
        {
            actualWidth = deviceMode.dmPelsWidth;
            actualHeight = deviceMode.dmPelsHeight;
            if((actualWidth != newWidth) || (actualHeight != newHeight)) 
            {
                //    change requested
                deviceMode.dmPelsWidth    = newWidth;
                deviceMode.dmPelsHeight    = newHeight;
                if(ChangeDisplaySettingsEx(device.DeviceName, &deviceMode, NULL, 0, NULL) == DISP_CHANGE_SUCCESSFUL) 
                {
                    //    broadcast change to system
                    SendMessage(HWND_BROADCAST, WM_DISPLAYCHANGE,  (WPARAM)(deviceMode.dmBitsPerPel),  MAKELPARAM(newWidth, newHeight));
                }
            }
        }
    }

    //    clear list
    DDList_Clean(&ddList);
}

void CChangeRes::DDList_Build(struct DDList **ppDD) 
{
    DWORD            deviceNum    = 0;
    DISPLAY_DEVICE    device        = {0};
    struct DDList    *ddList        = NULL;
    struct DDList    *dd            = NULL;
    struct DDList    *ddLastNode    = NULL;

    if(ppDD == NULL) 
    {
        return;
    }
    *ppDD = NULL;

    //    build display devices list
    device.cb = sizeof(device);
    do 
    {
        if(!EnumDisplayDevices(NULL, deviceNum, &device, 0)) 
        {
            break;
        }
        if(device.StateFlags & DISPLAY_DEVICE_ATTACHED_TO_DESKTOP) 
        {
            dd = (struct DDList *)malloc(sizeof(struct DDList));
            if(!dd) 
            {
                break;
            }
            dd->Device    = device;
            dd->Next    = NULL;

            if(ddList) 
            {
                ddLastNode->Next = dd;
                ddLastNode = dd;
            }
            else 
            {
                ddList = dd;
                ddLastNode = ddList;
            }
        }
        deviceNum++;
    } while(1);

    *ppDD = ddList;
}

void CChangeRes::DDList_Clean(struct DDList **ppDD) 
{
    struct DDList    *ddList        = NULL;
    struct DDList    *dd            = NULL;

    if(ppDD == NULL) 
    {
        return;
    }
    ddList = *ppDD;
    //    clear list
    while(ddList) 
    {
        dd = ddList;
        ddList = ddList->Next;
        free(dd);
    }
}

BOOL CChangeRes::DDList_Pop(struct DDList **ppDD, DISPLAY_DEVICE    *device) 
{
    struct DDList *ddList = NULL;
    struct DDList *ddHead = NULL;
    size_t cbDD = sizeof(DISPLAY_DEVICE);

    if(ppDD == NULL) 
    {
        return FALSE;
    }
    if(device == NULL) 
    {
        return FALSE;
    }
    if(device->cb < cbDD) 
    {
        return FALSE;
    }
    ddList = *ppDD;
    CopyMemory(device, &ddList->Device, cbDD);

    ddHead = ddList;
    ddList = ddList->Next;
    free(ddHead);

    *ppDD = ddList;
    return TRUE;
}
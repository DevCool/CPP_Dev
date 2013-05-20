#pragma once

struct DDList 
{
    DISPLAY_DEVICE    Device;
    struct DDList    *Next;
};

class CChangeRes
{
public:
    CChangeRes () {}
    ~CChangeRes () {}

private:
    static void DDList_Build    (struct DDList **ppDD);
    static void DDList_Clean    (struct DDList **ppDD);
    static BOOL DDList_Pop      (struct DDList **ppDD, DISPLAY_DEVICE    *device);

public:
    static void setResolution (int width, int height);
};


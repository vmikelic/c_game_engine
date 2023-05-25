#pragma pack(push, 1)
struct loaded_bitmap
{
    uint16   FileType;
    uint32  FileSize;
    uint16   Reserved1;
    uint16   Reserved2;
    uint32  BitmapOffset;
    uint32 Size;
    int32 Width;
    int32 Height;
    uint16  Planes;
    uint16  BitsPerPixel;
};
#pragma pack(pop)

global_variable uint8 GameIsRunning;
uint16 CurrentWindowWidth;
uint16 CurrentWindowHeight;

//------------------------------------------------------------------------------

#define CO_CREATE_INSTANCE(name) HRESULT name(REFCLSID  rclsid, LPUNKNOWN pUnkOuter, DWORD     dwClsContext, REFIID    riid, LPVOID    *ppv)
typedef CO_CREATE_INSTANCE(co_create_instance);
#define CoCreateInstance CoCreateInstance_
#define CO_INITIALIZE(name) HRESULT name(LPVOID pvReserved)
typedef CO_INITIALIZE(co_initialize);
#define CoInitialize CoInitialize_

//------------------------------------------------------------------------------

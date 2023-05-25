#include <audiopolicy.h>
#include <mmdeviceapi.h>
#include <audioclient.h>
#include <windows.h>
#include <emmintrin.h>
#include <gl/gl.h>
#include <iostream>
#include <math.h>
#include <stdint.h>
#include "Game_main.h"
#include "win32_Game.h"
#include "Game_opengl.h"

//------------------------------load file
PLATFORM_LOAD_FILE(Win32PlatformLoadFile)
{
    DWORD BytesRead = 0;
    if(FileName != 0)
    {
        HANDLE FileHandle = CreateFile(FileName,GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,0,0);
        LARGE_INTEGER FileSize;
        GetFileSizeEx(FileHandle,&FileSize);
        ReadFile(FileHandle,FileContents,FileSize.LowPart,&BytesRead,0);
        CloseHandle(FileHandle);
    }
    return(BytesRead);
}

//------------------------------write file
PLATFORM_WRITE_FILE(Win32PlatformWriteFile)
{
    DWORD BytesWritten = 0;
    HANDLE FileHandle = CreateFile(Filename, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, 0);
    if(FileHandle != INVALID_HANDLE_VALUE)
    {
        WriteFile(FileHandle, FileContents, FileBytesToWrite, &BytesWritten, 0);
        CloseHandle(FileHandle);
    }
    return(BytesWritten);
}

//------------------------------texture loading
PLATFORM_LOAD_TEXTURE(Win32PlatformLoadTexture)
{
    DWORD BytesRead = 0;
    if(TextureName != 0)
    {
        HANDLE TextureHandle = CreateFile(TextureName,GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,0,0);
        LARGE_INTEGER TextureSize;
        GetFileSizeEx(TextureHandle,&TextureSize);
        ReadFile(TextureHandle,TextureContents,TextureSize.LowPart,&BytesRead,0);
        CloseHandle(TextureHandle);
    }
    return(BytesRead);
}

//------------------------------keyboard handling
internal void
HandleStandardKeyboardInput(uint16 VKey,game_player_input* PlayerInput,RAWINPUT* RawInputData)
{
    uint64 KeyPressed = 0;
    switch(VKey)
    {	    
        case 'W'://----------
        {KeyPressed = WKEY_INPUT;} break;
        case 'A'://----------
        {KeyPressed = AKEY_INPUT;} break;
        case 'S'://----------
        {KeyPressed = SKEY_INPUT;} break;
        case 'D'://----------
        {KeyPressed = DKEY_INPUT;} break;
        case VK_SPACE://----------
        {KeyPressed = SPACEKEY_INPUT;} break;
        case VK_SHIFT://----------
        {KeyPressed = SHIFTKEY_INPUT;} break;
        case VK_CONTROL://----------
        {KeyPressed = CONTROLKEY_INPUT;} break;
        case VK_END://----------
        {KeyPressed = ENDKEY_INPUT;} break;
        case 'N'://----------
        {KeyPressed = NKEY_INPUT;} break;
        case 'L'://----------
        {KeyPressed = LKEY_INPUT;} break;
        case 'P'://----------
        {KeyPressed = PKEY_INPUT;} break;
        case 'E'://----------
        {KeyPressed = EKEY_INPUT;} break;
        case 'R'://----------
        {KeyPressed = RKEY_INPUT;} break;
        case 'T'://----------
        {KeyPressed = TKEY_INPUT;} break;
        case 'Y'://----------
        {KeyPressed = YKEY_INPUT;} break;
        case 'U'://----------
        {KeyPressed = UKEY_INPUT;} break;
        case 'Z'://----------
        {KeyPressed = ZKEY_INPUT;} break;
        case 'C'://----------
        {KeyPressed = CKEY_INPUT;} break;
        case 'V'://----------
        {KeyPressed = VKEY_INPUT;} break;
        case VK_UP://----------
        {KeyPressed = UPKEY_INPUT;} break;
        case VK_DOWN://----------
        {KeyPressed = DOWNKEY_INPUT;} break;
        case VK_LEFT://----------
        {KeyPressed = LEFTKEY_INPUT;} break;
        case VK_RIGHT://----------
        {KeyPressed = RIGHTKEY_INPUT;} break;
        case VK_F11://----------
        {KeyPressed = F11KEY_INPUT;} break;
        case VK_F1://----------
        {KeyPressed = F1KEY_INPUT;} break;
        case VK_F2://----------
        {KeyPressed = F2KEY_INPUT;} break;
        case VK_F3://----------
        {KeyPressed = F3KEY_INPUT;} break;
        case VK_F4://----------
        {KeyPressed = F4KEY_INPUT;} break;
        case VK_F5://----------
        {KeyPressed = F5KEY_INPUT;} break;
        case VK_ESCAPE://----------
        {KeyPressed = ESCAPEKEY_INPUT;} break;
    }
    //----------
    if ( (RawInputData->data.keyboard.Flags & 1) == 0)//key is down
    {
        if(!(PlayerInput->InputInstant & KeyPressed))
        {
            PlayerInput->InputInit |= KeyPressed;
        }
        PlayerInput->InputInstant |= KeyPressed;
        PlayerInput->InputToggle ^= KeyPressed;
    }
    else if( RawInputData->data.keyboard.Flags & 1 )//key is up
    {
        PlayerInput->InputInstant &= ~KeyPressed;
    }
}

//------------------------------message handling
internal void
HandleWindowsMessages(game_player_input* PlayerInput,WINDOWPLACEMENT* WindowPlacement,RAWINPUT* RawInputData,debug_struct* DebugStruct,HWND WindowHandle)
{
    MSG Message = {};
    Message.hwnd = WindowHandle;
    while(PeekMessage(&Message, WindowHandle, 0, 0, PM_REMOVE))
    {
        switch(Message.message)
        {
            case WM_MOUSEMOVE://----------
            {
                int32 ScreenMouseX = (WORD)(Message.lParam);
                int32 ScreenMouseY = (CurrentWindowHeight - (WORD)(Message.lParam >> 16))-1;
                PlayerInput->ScreenMouseX = (real64)ScreenMouseX / (real64)CurrentWindowWidth;
                PlayerInput->ScreenMouseY = (real64)ScreenMouseY / (real64)CurrentWindowHeight;
                DispatchMessage(&Message);
            } break;
            case WM_INPUT://----------
            {
                UINT RawInputDataSize = 48;
                GetRawInputData((HRAWINPUT)Message.lParam,RID_INPUT,RawInputData,&RawInputDataSize,sizeof(RAWINPUTHEADER));
                if(RawInputData->data.keyboard.VKey)
                {
                    HandleStandardKeyboardInput(RawInputData->data.keyboard.VKey,PlayerInput,RawInputData);
                    switch(RawInputData->data.keyboard.VKey)
                    {	
                        case VK_F11://----------
                        {
                            if ( (RawInputData->data.keyboard.Flags & 1) == 0 && PlayerInput->InputInit & F11KEY_INPUT)
                            {
                                DWORD Style = GetWindowLong(WindowHandle, GWL_STYLE);
                                if(Style & WS_OVERLAPPEDWINDOW)
                                {
                                    MONITORINFO MonitorInfo = { sizeof(MonitorInfo) };
                                    GetMonitorInfo(MonitorFromWindow(WindowHandle,MONITOR_DEFAULTTOPRIMARY), &MonitorInfo);
                                    GetWindowPlacement(WindowHandle,WindowPlacement);
                                    SetWindowLong(WindowHandle, GWL_STYLE,Style & ~WS_OVERLAPPEDWINDOW);
                                    SetWindowPos(WindowHandle, HWND_TOP,
                                                 MonitorInfo.rcMonitor.left, MonitorInfo.rcMonitor.top,
                                                 MonitorInfo.rcMonitor.right - MonitorInfo.rcMonitor.left,
                                                 MonitorInfo.rcMonitor.bottom - MonitorInfo.rcMonitor.top,
                                                 SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
                                }
                                else
                                {
                                    SetWindowLong(WindowHandle, GWL_STYLE,Style | WS_OVERLAPPEDWINDOW);
                                    SetWindowPlacement(WindowHandle,WindowPlacement);
                                    SetWindowPos(WindowHandle, 0, 0, 0, 0, 0,
                                                 SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER |
                                                 SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
                                }
                            }
                        } break;
                    }
                }
                //----------mouse
                if (RawInputData->data.mouse.usButtonFlags & RI_MOUSE_LEFT_BUTTON_DOWN)//left mouse down
                {
                    if(!(PlayerInput->InputInstant & LEFTCLICKMOUSE_INPUT))
                    {
                        PlayerInput->InputInit |= LEFTCLICKMOUSE_INPUT;
                    }
                    PlayerInput->InputInstant |= LEFTCLICKMOUSE_INPUT;
                    PlayerInput->InputToggle ^= LEFTCLICKMOUSE_INPUT;
                }
                else if(RawInputData->data.mouse.usButtonFlags & RI_MOUSE_LEFT_BUTTON_UP)//left mouse up
                {
                    PlayerInput->InputInstant &= ~LEFTCLICKMOUSE_INPUT;
                }
                //----------
                if (RawInputData->data.mouse.usButtonFlags & RI_MOUSE_RIGHT_BUTTON_DOWN)//right mouse down
                {
                    if(!(PlayerInput->InputInstant & RIGHTCLICKMOUSE_INPUT))
                    {
                        PlayerInput->InputInit |= RIGHTCLICKMOUSE_INPUT;
                    }
                    PlayerInput->InputInstant |= RIGHTCLICKMOUSE_INPUT;
                    PlayerInput->InputToggle ^= RIGHTCLICKMOUSE_INPUT;
                }
                else if(RawInputData->data.mouse.usButtonFlags & RI_MOUSE_RIGHT_BUTTON_UP)//right mouse up
                {
                    PlayerInput->InputInstant &= ~RIGHTCLICKMOUSE_INPUT;
                }
                //----------
                if (RawInputData->data.mouse.usButtonFlags & RI_MOUSE_MIDDLE_BUTTON_DOWN)//middle mouse down
                {
                    if(!(PlayerInput->InputInstant & MIDDLECLICKMOUSE_INPUT))
                    {
                        PlayerInput->InputInit |= MIDDLECLICKMOUSE_INPUT;
                    }
                    PlayerInput->InputInstant |= MIDDLECLICKMOUSE_INPUT;
                    PlayerInput->InputToggle ^= MIDDLECLICKMOUSE_INPUT;
                }
                else if(RawInputData->data.mouse.usButtonFlags & RI_MOUSE_MIDDLE_BUTTON_UP)//middle mouse up
                {
                    PlayerInput->InputInstant &= ~MIDDLECLICKMOUSE_INPUT;
                }
                //----------
                if (((short)(unsigned short)RawInputData->data.mouse.usButtonData) < 0) // MWHEELDOWN
                {
                    if(RawInputData->header.dwType == 0)
                    {
                        PlayerInput->InputInit |= WHEELDOWNMOUSE_INPUT;
                    }
                }
                else if (((short)(unsigned short)RawInputData->data.mouse.usButtonData) > 0) // MWHEELUP
                {
                    if(RawInputData->header.dwType == 0)
                    {
                        PlayerInput->InputInit |= WHEELUPMOUSE_INPUT;
                    }
                }
                //----------
                PlayerInput->MouseDeltaX += RawInputData->data.mouse.lLastX;
                PlayerInput->MouseDeltaY += -RawInputData->data.mouse.lLastY;
                if(PlayerInput->InputInstant & LEFTCLICKMOUSE_INPUT)
                {
                    DebugStruct->ClickAcumulationX += RawInputData->data.mouse.lLastX;
                    DebugStruct->ClickAcumulationY += -RawInputData->data.mouse.lLastY;
                }
                RawInputData->data.mouse.lLastX = 0;
                RawInputData->data.mouse.lLastY = 0;
            } break;
            default:
            {
                DispatchMessage(&Message);
            } break;
        }
    }
}

//------------------------------message callback
internal LRESULT CALLBACK
Win32WindowProcedure(HWND WindowHandle,UINT Message,WPARAM WParam,LPARAM LParam)
{
    LRESULT Result = 0;
    switch(Message)
    {
        case WM_CLOSE://----------
        {
            GameIsRunning = 0;
        } break;
        case WM_DESTROY://----------
        {
            GameIsRunning = 0;
        } break;
        case WM_SIZE://----------have to handle window size here because this message is not picked up by peekmessage.
        {
            CurrentWindowWidth = (WORD)(LParam);
            CurrentWindowHeight = (WORD)(LParam >> 16);
            GLint CurrentFrameBuffer = 0;
            glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &CurrentFrameBuffer);
            glBindFramebuffer(GL_FRAMEBUFFER,0);
            glViewport(0,0,CurrentWindowWidth,CurrentWindowHeight);
            glBindFramebuffer(GL_FRAMEBUFFER,FrameBuffer);
            glViewport(0,0,CurrentWindowWidth,CurrentWindowHeight);
            glBindTexture(GL_TEXTURE_2D, FrameTexture);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,CurrentWindowWidth,CurrentWindowHeight,0,GL_BGRA,GL_UNSIGNED_BYTE,0);
            glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT,CurrentWindowWidth,CurrentWindowHeight);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);
            glBindFramebuffer(GL_FRAMEBUFFER,CurrentFrameBuffer);
            GLint CurrentProgram = 0;
            glGetIntegerv(GL_CURRENT_PROGRAM,&CurrentProgram);
            real32 PixelSize[2] = 
            {
                1.0f/(real32)CurrentWindowWidth,
                1.0f/(real32)CurrentWindowHeight
            };
            glUseProgram(FXAAProgramID);
            GLint PixelSizeLoc = glGetUniformLocation(FXAAProgramID, "PixelSize");
            glUniform2f(PixelSizeLoc,PixelSize[0],PixelSize[1]);
            glUseProgram(CurrentProgram);
            Result = DefWindowProc(WindowHandle,Message,WParam,LParam);
        } break;
        default:
        {
            Result = DefWindowProc(WindowHandle,Message,WParam,LParam);
        } break;
    }
    return(Result);
}

//------------------------------
internal HWND
Win32CreateWindow(HINSTANCE Instance,WINDOWPLACEMENT* WindowPlacement)
{
    WNDCLASS WindowClass = {};
    WindowClass.lpfnWndProc = Win32WindowProcedure;
    WindowClass.hInstance = Instance;
    WindowClass.hCursor = LoadCursor(0, IDC_CROSS);
    WindowClass.lpszClassName = "GameWindowClass";
    RegisterClass(&WindowClass);
    HWND WindowHandle = 
        CreateWindowExA(0,WindowClass.lpszClassName,"Game",WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,0,0,Instance,0);
    GetWindowPlacement(WindowHandle,WindowPlacement);
    return(WindowHandle);
}

//------------------------------
internal HDC
Win32InitializeOpenGL(HWND WindowHandle)
{
    HDC DeviceContext = GetDC(WindowHandle);
    PIXELFORMATDESCRIPTOR DesiredPixelFormat =
    {
        sizeof(PIXELFORMATDESCRIPTOR),1,PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,PFD_TYPE_RGBA,32,0,0,0,0,0,0,0,0,0,0,0,0,0,24,8,0,PFD_MAIN_PLANE,0,0,0,0
    };
    int SuggestedPixelFormatIndex = ChoosePixelFormat(DeviceContext,&DesiredPixelFormat);
    SetPixelFormat(DeviceContext,SuggestedPixelFormatIndex,&DesiredPixelFormat);	
    HGLRC OpenGLRC = wglCreateContext(DeviceContext);
    wglMakeCurrent(DeviceContext, OpenGLRC);
    GetOpenGLFunction(wglCreateContextAttribsARB);
    int Attribs[] = 
    {
        WGL_CONTEXT_MAJOR_VERSION_ARB,3,WGL_CONTEXT_MINOR_VERSION_ARB,1,WGL_CONTEXT_FLAGS_ARB,WGL_CONTEXT_DEBUG_BIT_ARB,0
    };
    HGLRC ShareContext = 0;
    HGLRC ModernOpenGLRC = wglCreateContextAttribsARB( DeviceContext,  ShareContext,  Attribs);
    wglMakeCurrent(DeviceContext, ModernOpenGLRC);
    wglDeleteContext(OpenGLRC);
    return(DeviceContext);
}

//------------------------------
internal RAWINPUT*
Win32InitializeRawInput()
{
    RAWINPUTDEVICE InputDeviceList[2] = {};
    InputDeviceList[0].usUsagePage = 0x01; 
    InputDeviceList[0].usUsage = 0x02; 
    InputDeviceList[0].dwFlags = 0;
    InputDeviceList[0].hwndTarget = 0;
    InputDeviceList[1].usUsagePage = 0x01; 
    InputDeviceList[1].usUsage = 0x06; 
    InputDeviceList[1].dwFlags = 0;
    InputDeviceList[1].hwndTarget = 0;
    RegisterRawInputDevices(InputDeviceList,2,sizeof(RAWINPUTDEVICE));
    UINT RawInputDataSize = 48;
    return((RAWINPUT*)VirtualAlloc(0,RawInputDataSize,MEM_RESERVE|MEM_COMMIT,PAGE_READWRITE));
}

//------------------------------
internal void
Win32InitializeSound(IAudioClient** AudioClient,IAudioRenderClient** AudioRenderClient,uint32* BufferSize)
{
    HMODULE InstanceLibrary = LoadLibrary("ole32.dll");
    co_initialize* CoInitialize_;
    co_create_instance* CoCreateInstance_;
    CoInitialize = (co_initialize*) GetProcAddress(InstanceLibrary,"CoInitialize");
    CoCreateInstance = (co_create_instance*) GetProcAddress(InstanceLibrary,"CoCreateInstance");
    CLSID AudioDeviceEnumeratorCLSID = __uuidof(MMDeviceEnumerator);
    IID AudioDeviceEnumeratorIID = __uuidof(IMMDeviceEnumerator);
    IMMDeviceEnumerator* AudioDeviceEnumerator = 0;
    CoInitialize(0);
    CoCreateInstance(AudioDeviceEnumeratorCLSID,0,CLSCTX_ALL,AudioDeviceEnumeratorIID,(LPVOID*)&AudioDeviceEnumerator);
    IMMDevice* AudioDevice = 0;
    AudioDeviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &AudioDevice);
    FreeLibrary(InstanceLibrary);
    IID AudioClientIID = __uuidof(IAudioClient);
    AudioDevice->Activate(AudioClientIID,CLSCTX_ALL,0,(LPVOID*)AudioClient);
    WAVEFORMATEX AudioFormat = {};
    AudioFormat.wFormatTag = WAVE_FORMAT_PCM;
    AudioFormat.nChannels = 2;
    AudioFormat.nSamplesPerSec = 48000;
    AudioFormat.wBitsPerSample = 16;
    AudioFormat.nBlockAlign = (AudioFormat.nChannels * AudioFormat.wBitsPerSample) / 8U;
    AudioFormat.nAvgBytesPerSec = (AudioFormat.nSamplesPerSec * AudioFormat.nBlockAlign);
    WAVEFORMATEX* CorrectFormat = &AudioFormat;
    (*AudioClient)->IsFormatSupported(AUDCLNT_SHAREMODE_SHARED,&AudioFormat,&CorrectFormat);
    REFERENCE_TIME DevicePeriod = 0;
    (*AudioClient)->GetDevicePeriod(&DevicePeriod,0);
    if (CorrectFormat != 0 )
    {
        (*AudioClient)->Initialize(AUDCLNT_SHAREMODE_SHARED,0,DevicePeriod,0,CorrectFormat,0);
    }
    else
    {  
        (*AudioClient)->Initialize(AUDCLNT_SHAREMODE_SHARED,0,DevicePeriod,0,&AudioFormat,0);
    }
    IID AudioRenderClientIID = __uuidof(IAudioRenderClient);
    (*AudioClient)->GetService(AudioRenderClientIID,(LPVOID*)AudioRenderClient);
    IID AudioClockIID = __uuidof(IAudioClock);  
    IAudioClock* AudioClock = 0;
    (*AudioClient)->GetService(AudioClockIID,(LPVOID*)&AudioClock);
    (*AudioClient)->GetBufferSize(BufferSize);
}

//------------------------------
internal void
Win32InitializeMemory(game_memory* GameMemory)
{
    uint64 TotalSize = 0;
    uint32 GameStateSize = (uint32)sizeof(game_state);TotalSize += GameStateSize;
    uint32 DebugStateSize = (uint32)sizeof(debug_struct);TotalSize += DebugStateSize;
    uint32 ScratchMemorySize = (uint32)MegaBytes(50);TotalSize += ScratchMemorySize;// might need to be bigger?
    uint32 SpatialGridMemorySize = (uint32)sizeof(spatial_partition_grid)*((PARTITION_DEPTH)*(PARTITION_HEIGHT)*(PARTITION_STRIDE)+NUM_OF_BUFFER_HOLES);TotalSize += SpatialGridMemorySize;
    uint32 SpatialIndexMemorySize = (uint32)MegaBytes(100);TotalSize += SpatialIndexMemorySize;
    uint32 PartitionIndicesInfoSize = (uint32)sizeof(partition_indices_info)*(MAX_ENTITIES+NUM_OF_BUFFER_HOLES);TotalSize += PartitionIndicesInfoSize;
    uint32 PartitionIndicesDataSize = (uint32)MegaBytes(100);TotalSize += PartitionIndicesDataSize;
    uint32 StretchyBuffersSize = (uint32)sizeof(stretchy_buffer_list);TotalSize += StretchyBuffersSize;
    uint32 StretchyBufferInfoSize = (uint32)sizeof(stretchy_buffer)*(NUMBER_OF_STRETCHY_BUFFERS+NUM_OF_BUFFER_HOLES);TotalSize += StretchyBufferInfoSize;
    uint32 StretchyBufferDataSize = (uint32)MegaBytes(100);TotalSize += StretchyBufferDataSize;
    //----------
    GameMemory->GameStateMemory = VirtualAlloc(0,TotalSize,MEM_RESERVE|MEM_COMMIT,PAGE_READWRITE);
    GameMemory->DebugStateMemory = (uint8*)GameMemory->GameStateMemory + (GameStateSize);
    ScratchMemoryBuffer = (uint8*)GameMemory->DebugStateMemory + (DebugStateSize);
    GameMemory->SpatialGridMemory = (uint8*)ScratchMemoryBuffer + (ScratchMemorySize);
    GameMemory->SpatialIndexMemory = (uint8*)GameMemory->SpatialGridMemory + (SpatialGridMemorySize);
    GameMemory->PartitionIndicesInfo = (uint8*)GameMemory->SpatialIndexMemory + (SpatialIndexMemorySize);
    GameMemory->PartitionIndicesData = (uint8*)GameMemory->PartitionIndicesInfo + (PartitionIndicesInfoSize);
    GameMemory->StretchyBuffers = (uint8*)GameMemory->PartitionIndicesData + (PartitionIndicesDataSize);
    GameMemory->StretchyBufferInfo = (uint8*)GameMemory->StretchyBuffers + (StretchyBuffersSize);
    GameMemory->StretchyBufferData = (uint8*)GameMemory->StretchyBufferInfo + (StretchyBufferInfoSize);
}

//------------------------------
internal int64
Win32QueryPerformanceFrequency()
{
    LARGE_INTEGER QueryPerformanceFrequencyResult = {};
    QueryPerformanceFrequency(&QueryPerformanceFrequencyResult);
    return(QueryPerformanceFrequencyResult.QuadPart);
}

//------------------------------
int CALLBACK 
WinMain(HINSTANCE Instance,HINSTANCE PrevInstance,LPSTR CommandLine,int ShowCommand)
{
    ShowCursor(0);
    
    //----------window
    WINDOWPLACEMENT WindowPlacement = { sizeof(WindowPlacement) };
    HWND WindowHandle = Win32CreateWindow(Instance,&WindowPlacement);
    HDC DeviceContext = Win32InitializeOpenGL(WindowHandle); //need render context for procaddress to work
    
    //----------getting opengl functions
#if GPUDEBUG
    GetOpenGLFunction(glDebugMessageCallbackARB); //gl debug messages dont work on integrated 
#endif
    GetOpenGLFunction(glGenBuffers);
    GetOpenGLFunction(glBindBuffer);
    GetOpenGLFunction(glBufferData);
    GetOpenGLFunction(glCreateShader);
    GetOpenGLFunction(glShaderSource);
    GetOpenGLFunction(glCompileShader);
    GetOpenGLFunction(glCreateProgram);
    GetOpenGLFunction(glAttachShader);
    GetOpenGLFunction(glLinkProgram);
    GetOpenGLFunction(glDeleteShader);
    GetOpenGLFunction(glValidateProgram);
    GetOpenGLFunction(glGetProgramiv);
    GetOpenGLFunction(glGetShaderInfoLog);
    GetOpenGLFunction(glGetProgramInfoLog);
    GetOpenGLFunction(glUseProgram);
    GetOpenGLFunction(glVertexAttribPointer);
    GetOpenGLFunction(glEnableVertexAttribArray);
    GetOpenGLFunction(glGenVertexArrays);
    GetOpenGLFunction(glBindVertexArray);
    GetOpenGLFunction(glGenerateMipmap);
    GetOpenGLFunction(glGetUniformLocation);
    GetOpenGLFunction(glUniformMatrix4fv);
    GetOpenGLFunction(glBufferSubData);
    GetOpenGLFunction(glTexImage3D);
    GetOpenGLFunction(glTexSubImage3D);
    GetOpenGLFunction(glMapBufferRange);
    GetOpenGLFunction(glUnmapBuffer);
    GetOpenGLFunction(glTexImage2DMultisample);
    GetOpenGLFunction(glGenFramebuffers);
    GetOpenGLFunction(glBindFramebuffer);
    GetOpenGLFunction(glFramebufferTexture2D);
    GetOpenGLFunction(glCheckFramebufferStatus);
    GetOpenGLFunction(glBlitFramebuffer);
    GetOpenGLFunction(glGetShaderiv);
    GetOpenGLFunction(glUniform1i);
    GetOpenGLFunction(glActiveTexture);
    GetOpenGLFunction(glGenRenderbuffers);
    GetOpenGLFunction(glBindRenderbuffer);
    GetOpenGLFunction(glRenderbufferStorage);
    GetOpenGLFunction(glFramebufferRenderbuffer);
    GetOpenGLFunction(glUniform2f);
    
    //----------input
    RAWINPUT* RawInputData = Win32InitializeRawInput();
    game_player_input PlayerInput = {};
    
    //----------sound
    game_audio_buffer AudioBuffer = {};
    IAudioClient* AudioClient = {};
    IAudioRenderClient* AudioRenderClient = {};
    uint32 Padding = {};
    uint16 AudioBufferRemaining = {};
    uint32 BufferSize = {};
    Win32InitializeSound(&AudioClient,&AudioRenderClient,&BufferSize);
    
    //----------memory
    game_memory GameMemory = {};
    Win32InitializeMemory(&GameMemory);
    PlatformLoadFile = Win32PlatformLoadFile;
    PlatformWriteFile = Win32PlatformWriteFile;
    PlatformLoadTexture = Win32PlatformLoadTexture;
    game_state* GameState = (game_state*)GameMemory.GameStateMemory;
    debug_struct* DebugStruct = (debug_struct*)GameMemory.DebugStateMemory;
    stretchy_buffer_list* StretchyBuffers = (stretchy_buffer_list*)GameMemory.StretchyBuffers;
    InitializeStretchyBuffers(&GameMemory,StretchyBuffers);
    
    //----------setting default state
    SetDebugHUD(GameState,DebugStruct);
    GameState->RandomState = 91798;
    DebugStruct->ActiveGroupYBasis = {0,1};
    
    //----------timing
    int64 PerformanceFrequency = Win32QueryPerformanceFrequency();
    game_timers GameTimers = {};
    
    //----------loop is imminent
    OpenGLStartup(&GameMemory,GameState);
    AudioClient->Start();
    int64 CounterElasped = 0;
    LARGE_INTEGER LastCounter = {};
    LARGE_INTEGER EndCounter = {};  
    QueryPerformanceCounter(&LastCounter);
    GameIsRunning = 1;
    ShowWindow(WindowHandle,SW_SHOW);
    ShowCursor(1);
    LoadLevel(&GameMemory,GameState,StretchyBuffers);
    
    //----------
    while(GameIsRunning)
    {
        HandleWindowsMessages(&PlayerInput,&WindowPlacement,RawInputData,DebugStruct,WindowHandle);
        
        //----------render sound
        /*------------------------------//------------------------------ need to actually get audio memory set up
        AudioClient->GetCurrentPadding(&Padding);
        AudioBufferRemaining = (uint16)(BufferSize - Padding);
        if ( (AudioBufferRemaining) < (AudioBuffer.AudioFramesToRender) )
        {
            AudioBuffer.AudioFramesToRender = AudioBufferRemaining;
        }
        AudioRenderClient->GetBuffer(AudioBuffer.AudioFramesToRender,(uint8**)&AudioBuffer.AudioMemory);
        GameRenderSound(AudioBuffer,PlayerInput,GameState);
        AudioRenderClient->ReleaseBuffer(AudioBuffer.AudioFramesToRender,0);
        ------------------------------*/
        
        //----------game update and render
        if(PlayerInput.InputToggle & LKEY_INPUT)
        {
            if(PlayerInput.InputInit & PKEY_INPUT)
            {
                GameUpdateAndRender(&GameTimers,&GameMemory,&AudioBuffer,GameState,DebugStruct,&PlayerInput,StretchyBuffers);
                OpenGLRender(GameState);
                SwapBuffers(DeviceContext);
            }
        }
        else
        {
            GameUpdateAndRender(&GameTimers,&GameMemory,&AudioBuffer,GameState,DebugStruct,&PlayerInput,StretchyBuffers);
            OpenGLRender(GameState);
            SwapBuffers(DeviceContext);
        }
        
        //--------------------------------------timing and reset for next frame
        PlayerInput.MouseDeltaX = 0; //----------reset input
        PlayerInput.MouseDeltaY = 0;
        PlayerInput.InputInit = 0;
        GameState->VerticeCount = 0; //----------reset vertice numbers
        GameState->HUDVerticeCount = 0;
        QueryPerformanceCounter(&EndCounter);//----------timing
        CounterElasped = (EndCounter.QuadPart) - (LastCounter.QuadPart);
        LastCounter = EndCounter;
        GameTimers.MilliSecondsElapsed = ( ((real64)CounterElasped / (real64)PerformanceFrequency) * 1000.0 );
        GameTimers.SecondsElapsed = ((real64)CounterElasped / (real64)PerformanceFrequency);
        if(GameTimers.MilliSecondsElapsed > 50)
        {
            GameTimers.MilliSecondsElapsed = 50;
            GameTimers.SecondsElapsed = .05;
        }
        if(PlayerInput.InputToggle & LKEY_INPUT)
        {
            GameTimers.SecondsElapsed = 0.01515151515151515151515151515152;
            GameTimers.MilliSecondsElapsed = 0.01515151515151515151515151515152*1000;
        }
        //AudioBuffer.AudioFramesToRender =  (uint16)( (48000.0f * (GameTimers.MilliSecondsElapsed / 800.0f) ) );
    }
    return(0);
}

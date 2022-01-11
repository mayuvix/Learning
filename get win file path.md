Win 获取文件路径

```cpp
#include <windows.h>
#include <stdio.h>
BOOL CreateSampleService()
{
    TCHAR szPath[MAX_PATH];
    if( !GetModuleFileName( NULL, szPath, MAX_PATH ) )
    {
        printf("GetModuleFileName failed (%d)\n", GetLastError());
        return FALSE;
    }
return TRUE;
}
/*
如果想获得某个正在运行的EXE或者DLL的全路径可以这样写代码
GetModuleFileNameEx(hProcess,hInst,lpFile,MAX_PATH);//注意下缓冲区就行了。
*/

#define MAX_PATH 260
wchar_t pPath[MAX_PATH];
GetModuleFileName(NULL, pPath, MAX_PATH);
std::wstring wsPath = pPath;



```

        FORCE_INLINE std::wstring GetExeDirPath()
        {


    #ifdef _WINDOWS
    wchar_t pPath[MAX_PATH];
    GetModuleFileName(NULL, pPath, MAX_PATH);
           std::wstring wsPath = pPath;
            return wsPath.substr(0, wsPath.find_last_of(FileSystem::SeparatorChar()) + 1);
            #else
                return L"./";
    #endif
            }



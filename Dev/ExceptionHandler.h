#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>

#pragma warning(push)
#pragma warning(disable: 4091)  // 'typedef ': ignored on left of '' when no variable is declared
#include <DbgHelp.h>
#pragma warning(pop)

#pragma comment(lib, "Dbghelp.lib")

class ExceptionHandler
{
public:
    static ExceptionHandler& GetInstance();

    DWORD Initialize(
        __in const MINIDUMP_TYPE dump_type = MINIDUMP_TYPE::MiniDumpNormal
    );

    DWORD Start();

    static LONG WINAPI ExceptionCallback(
        __in struct _EXCEPTION_POINTERS* exceptioninfo
    );

private:
    //std::wstring dump_file_name;
    MINIDUMP_TYPE dump_type_;
    LPTOP_LEVEL_EXCEPTION_FILTER prev_filter_;
};

#endif
#include "pch.h"
#include "ExceptionHandler.h"

#include <chrono>
#include <iomanip>

ExceptionHandler& ExceptionHandler::GetInstance() {
    static ExceptionHandler handler;
    return handler;
}

DWORD ExceptionHandler::Initialize(
    __in const MINIDUMP_TYPE dump_type
) {
    DWORD error = ERROR_SUCCESS;
    dump_type_ = dump_type;
    return error;
}

DWORD ExceptionHandler::Start() {
    prev_filter_ = SetUnhandledExceptionFilter(ExceptionCallback);
    return ERROR_SUCCESS;
}

LONG ExceptionHandler::ExceptionCallback(
    __in struct _EXCEPTION_POINTERS* exceptioninfo
) {

    do {

        if (nullptr == exceptioninfo) {
            break;
        }

        SYSTEMTIME st = { 0 };
        ::GetLocalTime(&st);

      
        const std::wstring dump_file_name = L"Dev.dmp";
        
        //
        // create dump file.
        //
        HANDLE dump_file_handle = ::CreateFile(
            dump_file_name.c_str(),
            GENERIC_WRITE,
            0,
            nullptr,
            CREATE_ALWAYS,
            FILE_ATTRIBUTE_NORMAL,
            nullptr
        );

        if (INVALID_HANDLE_VALUE == dump_file_handle) {
            break;
        }

        MINIDUMP_EXCEPTION_INFORMATION ex_info = { 0 };

        ex_info.ThreadId = ::GetCurrentThreadId(); // Threae ID 설정
        ex_info.ExceptionPointers = exceptioninfo; // Exception 정보 설정
        ex_info.ClientPointers = FALSE;

        //
        // write dump file.
        //

        if (FALSE == ::MiniDumpWriteDump(
            ::GetCurrentProcess(),
            ::GetCurrentProcessId(),
            dump_file_handle,
            ExceptionHandler::GetInstance().dump_type_,
            &ex_info,
            nullptr, nullptr
        )) {

            break;
        }

    } while (false);

    return (ExceptionHandler::GetInstance().prev_filter_) ? ExceptionHandler::GetInstance().prev_filter_(exceptioninfo) : EXCEPTION_EXECUTE_HANDLER;
}
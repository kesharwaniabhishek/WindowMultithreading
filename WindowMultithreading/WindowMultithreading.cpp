// WindowMultithreading.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>

static HANDLE eventHandle{};

DWORD WINAPI ThreadFunc(LPVOID params)
{
    printf("waiting thread %ld\n" , GetCurrentThreadId());
    WaitForSingleObject(eventHandle, INFINITE);
    ThreadFunc(nullptr);
    printf("Running thread %ld\n", GetCurrentThreadId());
    ReleaseMutex(eventHandle);
    //SetEvent(eventHandle);
    return 0;
}

int main()
{
   // eventHandle = CreateEvent(nullptr, 0, 1, nullptr);

    eventHandle = CreateMutex(nullptr, false, nullptr);

    auto handle1 = CreateThread(nullptr, 0, ThreadFunc, nullptr, 0, nullptr);
    if(handle1==nullptr)
    {
        std::cout << "Failed to create thread";
        return 0;
    }

    auto handle2 = CreateThread(nullptr, 0, ThreadFunc, nullptr, 0, nullptr);
    if(handle2==nullptr)
    {
        std::cout << "Failed to create thread";
        return 0;
    }
    
    //SetEvent(eventHandle);

    HANDLE handles[] ={handle1, handle2};

    if(WAIT_OBJECT_0 == WaitForMultipleObjects(2, handles, TRUE, INFINITE))
    {
    }
}

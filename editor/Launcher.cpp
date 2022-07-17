#include "Launcher.h"

#include "Core.h"
#include <thread>
#include <future>

Launcher::Launcher()
{
    //pi = PROCESS_INFORMATION();
    ZeroMemory(&pi, sizeof(pi));
}

Launcher::~Launcher()
{
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}

void WaitForTermination(HANDLE handle)
{
    
}

void Launcher::Update()
{
    if (ImGui::Button("Start Engine"))
    {
        STARTUPINFO si;

        ZeroMemory(&si, sizeof(si));
        si.cb = sizeof(si);
        ZeroMemory(&pi, sizeof(pi));

        if (!engineActive)
        {
            engineActive = true;
            CreateProcess(L"Application.exe", NULL, NULL, NULL, false, 0, NULL, NULL, &si, &pi);
            std::thread( [](HANDLE h, bool* isActive) {
                WaitForSingleObject(h, -1);
                *isActive = false;
                }, pi.hProcess, &engineActive)
                .detach();
        }
    }
    auto readonlyEngineActive = engineActive;
    ImGui::Checkbox("Is Active", &readonlyEngineActive);
}

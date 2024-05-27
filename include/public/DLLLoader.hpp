#pragma once
#include <iostream>
#include "utils.hpp"

#ifdef _WIN32
    #ifndef WIN32_INCLUDE
    #define WIN32_INCLUDE
    #include <windows.h>
    #endif
#else
#include <dlfcn.h>
#endif

class DLLExport DLLLoader
{
private:
#ifdef _WIN32
    HINSTANCE hGetProcIDDLL;
#else
    void* handle;
#endif

    void loadDLL(std::string filepath)
    {
#ifdef _WIN32
        size_t separatorIndex = filepath.find_last_of("\\/");
        std::string filename, filefolder;
        if (separatorIndex == std::string::npos)
        {
            filename = filepath;
            filefolder = "";
        }
        else
        {
            filename = filepath.substr(separatorIndex + 1);
            filefolder = filepath.substr(0, separatorIndex);
            SetDllDirectoryA(filefolder.c_str());
        }

        this->hGetProcIDDLL = LoadLibraryA(filename.c_str());
        if (!hGetProcIDDLL)
        {
            std::cerr << std::endl << "Error: Could not load library!" << std::endl;
            std::cerr << "Error code: " << GetLastError() << std::endl;
            return;
        }
#else
        this->handle = dlopen(filepath.c_str(), RTLD_LAZY);
        if (!this->handle)
        {
            std::cerr << std::endl << "Error: Could not load library!" << std::endl;
            std::cerr << "Error: " << dlerror() << std::endl;
            return;
        }
#endif
    }

    void unloadDLL()
    {
#ifdef _WIN32
        FreeLibrary(this->hGetProcIDDLL);
#else
        dlclose(this->handle);
#endif
    }

public:
    DLLLoader(std::string path)
    {
        loadDLL(path);
    }

    ~DLLLoader()
    {
        unloadDLL();
    }

    void* resolve(std::string name)
    {
        void* fn;
#ifdef _WIN32
        fn = GetProcAddress(this->hGetProcIDDLL, name.c_str());
#else
        fn = dlsym(this->handle, name.c_str());
#endif
        if (!fn) std::cerr << std::endl << "Error: " << name << " not resolved!" << std::endl;
        return fn;
    }
};
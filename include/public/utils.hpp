#if (defined WIN32 || defined _WIN32 || defined WINCE)
    #ifdef BUILDING_DLL
        # define DLLExport __declspec(dllexport)
    #else
        # define DLLExport __declspec(dllimport)
    #endif
#else
# define DLLExport
#endif

#if (defined WIN32 || defined _WIN32 || defined WINCE)
# define DLLExport __declspec(dllexport)
#else
# define DLLExport
#endif

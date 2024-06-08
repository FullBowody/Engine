#include <filesystem>

namespace Path
{
    std::string GetDirectory(std::string fileorfolder)
    {
        if (std::filesystem::is_directory(fileorfolder))
        {
            if (fileorfolder.back() == '/' || fileorfolder.back() == '\\')
                fileorfolder.pop_back();
            return fileorfolder;
        }
        else
        {
            return std::filesystem::path(fileorfolder).parent_path().string();
        }
    }

    std::string Combine(std::string path1, std::string path2)
    {
        return std::filesystem::path(path1).append(path2).string();
    }
}

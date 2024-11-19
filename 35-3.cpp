#include <iostream>
#include <vector>
#include <string>
#include <filesystem>

int main () {
    std::filesystem::path path ("PATH");
    std::string extension = ".cpp";
    auto get_filenames_by_extension =
       [](std::filesystem::path path,
          const std::string extension) {
        std::vector <std::string> files;
        for(auto& p: std::filesystem::recursive_directory_iterator(path)) {
            if(std::filesystem::is_regular_file(p.path()) && 
                    p.path().extension() == extension)
                files.push_back(p.path().filename());
        }
        return std::make_unique <std::vector<std::string>> (files);
    };
    std::vector <std::string> founded_files = *get_filenames_by_extension (path, extension);
    for (auto next : founded_files) {
        std::cout << next << std::endl;
    }
    return 0;
}

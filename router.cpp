#include "router.h"
#include "fileReader.h"
#include <iostream>
#include <cstdio>
#include <string>
#include <filesystem>
#include <algorithm>

using namespace std;
namespace fs = std::filesystem;

string routeRequest(const string& request)
{
    size_t start = request.find(' ') + 1;
    size_t end = request.find(' ', start);

    if(start == 0 || end == string::npos)
    {
        return "";
    }


    string path = request.substr(start, end - start);
    if(path == "/")
        return "./web/index.html";
    path.erase(0,1);
    fs::path web = fs::weakly_canonical("./web");
    fs::path file = fs::weakly_canonical(web / path);
    fs::path relative = file.lexically_relative(web);

    if(relative.empty() || *relative.begin() == "..")
    {
        return "";
    }
    if (!fs::exists(file) || !fs::is_regular_file(file))
    {
        return "";
    }

    // cout << file.string() << endl;
    return file.string();
}

// string getContentType(const string& path)
// {

// }

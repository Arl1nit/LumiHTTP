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

string getContentType(const string& filePath)
{
    string extension = fs::path(filePath).extension().string();
    transform(extension.begin(), extension.end(), extension.begin(), ::tolower);

    if (extension == ".html") return "text/html";
    if (extension == ".css")  return "text/css";
    if (extension == ".js")   return "application/javascript";
    if (extension == ".json") return "application/json";
    if (extension == ".png")  return "image/png";
    if (extension == ".jpg" || extension == ".jpeg") return "image/jpeg";
    if (extension == ".svg")  return "image/svg+xml";
    if (extension == ".ico")  return "image/x-icon";
    if (extension == ".txt")  return "text/plain";
    if (extension == ".pdf")  return "application/pdf";

    return "application/octet-stream";
}

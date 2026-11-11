#include "router.h"
#include "fileReader.h"
#include <iostream>
#include <cstdio>
#include <string>
#include <filesystem>
#include <algorithm>

using namespace std;


string routeRequest(const string& request)
{
    size_t start = request.find(' ') + 1;
    size_t end = request.find(' ', start);

    if(start == 0 || end == string::npos)
    {
        return "";
    }

    string path = request.substr(start, end - start);
    string webContentPath = "./web";
    // string mainPagePath = "/index.html";
    // if(path=="/")
    // {
    //     path = webContentPath + mainPagePath;
    //     return path;
    // }

    path = webContentPath + path;
    cout << path << endl;
    return path;
}

// string getContentType(const string& path)
// {

// }

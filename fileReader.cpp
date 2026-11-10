#include "fileReader.h"
#include <fstream>
#include <sstream>
#include <string>


using namespace std;

string readFile(string filename)
{
    ifstream file(filename);
    if(!file.is_open())
    {
        return "";
    }
    stringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}

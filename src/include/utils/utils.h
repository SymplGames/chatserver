#pragma once

#include <string>

using namespace std;

class Logger
{

private:

    string filename;
    string prefix;

public:

    Logger(string filename, string prefix);

    ~Logger();

    string Prefix(){return prefix;}
    string Filename(){return filename;}

    void Log(string message);

};
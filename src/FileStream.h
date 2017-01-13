#pragma once

#include <fstream>
#include <string>

class FileStream : public std::fstream
{
public:
    FileStream(std::string filename);
    ~FileStream(void);
};

#include "FileStream.h"

FileStream::FileStream(std::string filename)
    : std::fstream(filename)
{
}

FileStream::~FileStream(void)
{
    this->close();
}

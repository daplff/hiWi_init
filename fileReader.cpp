#include "fileReader.h"
#include <fstream>

namespace test_space
{

fileReader::fileReader(std::string fileToOpen)
: fileName(fileToOpen),
	reader(static_cast<std::fstream*>(NULL))
{
	reader = new std::fstream(fileName.c_str());
}

fileReader::~fileReader()
{
	delete reader;
}


}


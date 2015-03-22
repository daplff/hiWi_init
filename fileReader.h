#ifndef FILEREADER_H
#define FILEREADER_H

#include <string>
#include <iosfwd>

namespace test_space
{

class fileReader
{
public:
	fileReader(std::string fileToOpen);
	~fileReader();
	
	
	
	private:
	
	std::string fileName;
	std::fstream* reader;
};

}

#endif // FILEREADER_H

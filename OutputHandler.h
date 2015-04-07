


// class for loading output files of SWE_SPHYSICS
#ifndef OUTPUTHANDLER_H
#define OUTPUTHANDLER_H

#include <string>
#include <boost/property_tree/ptree_fwd.hpp>


class OutputHandler
{
public:
	OutputHandler();
	~OutputHandler();

	static boost::property_tree::ptree loadDtFile(std::string fileName);
//	static boost::property_tree::ptree loadGridFiles(std::string fileNameXVel, std::string fileNameYVel, std::string fileNameDepths);
	static boost::property_tree::ptree loadParticleFile(std::string fileName);
	
	
	static boost::property_tree::ptree loadGrid(std::string fileName);
//	boost::property_tree::ptree loadDepthGrid(std::string fileName);
	
	
	
	

};

#endif // OUTPUTHANDLER_H

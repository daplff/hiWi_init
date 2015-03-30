/*
 * TreeInitialiser.cpp
 *
 *  Created on: Mar 25, 2015
 *      Author: wannerbe
 */

#include "TreeInitialiser.h"
#include <boost/property_tree/ptree.hpp>
#include <fstream>

namespace
{

	//gets first word ended by space ' ' and moves reader ahead one line
	inline std::string getFirstWordOfLine(std::istream& reader)
	{

		std::string temp;
		std::getline(reader,temp); 				//extract line
		return temp.substr(0,temp.find(' '));	//return first word before space
	}

	template<class OuterContainer>
	void recursivePrint(std::ostream& writer, const OuterContainer& container)
	{
		for (auto it = container.begin(); it != container.end(); ++it)
		{
			if(it->second.empty())
			{
				writer << it->second.data() << "\n";
			}
			else
			{
				recursivePrint(writer, container.begin()->second);
			}
		}
	}

}



TreeInitialiser::TreeInitialiser()
{
	treePtr = std::shared_ptr<boost::property_tree::ptree>(new boost::property_tree::ptree);
}

std::shared_ptr<boost::property_tree::ptree> TreeInitialiser::getTreePtr() {
	return treePtr;
}

TreeInitialiser::~TreeInitialiser() {
}

void TreeInitialiser::loadSettingsFile(std::string filePath)
{
	std::fstream reader(filePath);
	boost::property_tree::ptree& treeRef = *treePtr;


	treeRef.put("i_restartRun",	getFirstWordOfLine(reader));
	treeRef.put("idebug",		getFirstWordOfLine(reader));
	treeRef.put("rho0",			getFirstWordOfLine(reader));
	treeRef.put("ivisc",		getFirstWordOfLine(reader));
	treeRef.put("viscos_val",	getFirstWordOfLine(reader));
	treeRef.put("dw_min_fric",	getFirstWordOfLine(reader));
	treeRef.put("iMUSCL",		getFirstWordOfLine(reader));
	treeRef.put("tol",			getFirstWordOfLine(reader));
	treeRef.put("i_dw_iter",	getFirstWordOfLine(reader));
	treeRef.put("i_max_iter",	getFirstWordOfLine(reader));
	treeRef.put("ivar_dt",		getFirstWordOfLine(reader));
	treeRef.put("dt",			getFirstWordOfLine(reader));
	treeRef.put("CFL",			getFirstWordOfLine(reader));
	treeRef.put("out",			getFirstWordOfLine(reader));
	treeRef.put("tmax",			getFirstWordOfLine(reader));
	treeRef.put("trec_ini",		getFirstWordOfLine(reader));
	treeRef.put("coef",			getFirstWordOfLine(reader));
	treeRef.put("vlx",			getFirstWordOfLine(reader));
	treeRef.put("vly",			getFirstWordOfLine(reader));
	treeRef.put("dx_grd",		getFirstWordOfLine(reader));
	treeRef.put("i_openbc",		getFirstWordOfLine(reader));
	if (treeRef.get<int>("i_openbc") == 1)
	{
		treeRef.put("distmin",	getFirstWordOfLine(reader));
		//TODO: open boundary call
	}
	treeRef.put("i_closebc",	getFirstWordOfLine(reader));
	if (treeRef.get<int>("i_closebc") == 1)
	{
		//TODO: read variables if there are closed boundaries.
	}
	treeRef.put("i_bedType",	getFirstWordOfLine(reader));
	switch (treeRef.get<int>("i_bedType"))
	{
		case 1:

			break;
		case 2:

			break;

		case 3:

			break;
		default: //code broken
			break;
	}
	treeRef.put("i_fluid",		getFirstWordOfLine(reader));
	switch (treeRef.get<int>("i_fluid"))
	{
		case 1:

			break;
		case 2:

			break;

		default: //code broken
			break;
	}
	treeRef.put("iref",			getFirstWordOfLine(reader));
	if (treeRef.get<int>("iref") == 1)
	{
		treeRef.put("ref_p",	getFirstWordOfLine(reader));
		treeRef.put("ref_h",	getFirstWordOfLine(reader));
	}
	treeRef.put("dxx_ref",		getFirstWordOfLine(reader));
	treeRef.put("dyy_ref",		getFirstWordOfLine(reader));
	treeRef.put("dw_min", 		getFirstWordOfLine(reader));
	if (treeRef.get<int>("iref") == 1)
	{
		//TODO: read those six variables repeatedly until 6th == 0
	}
	treeRef.put("i_compile_opt",getFirstWordOfLine(reader));
	treeRef.put("idouble",		getFirstWordOfLine(reader));
}

void TreeInitialiser::printSettingsFile(std::string filePath) {
	std::fstream writer(filePath);
	const boost::property_tree::ptree& tree = *treePtr;
	recursivePrint(static_cast<std::ostream&>(writer), tree);



}



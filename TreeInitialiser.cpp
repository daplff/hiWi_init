/*
 * TreeInitialiser.cpp
 *
 *  Created on: Mar 25, 2015
 *      Author: wannerbe
 */

#include "TreeInitialiser.h"
#include <boost/property_tree/ptree.hpp>
#include <fstream>
#include <boost/property_tree/json_parser.hpp>

namespace
{

	//gets first word ended by space ' ' and moves reader ahead one line
//TODO: clean up and make whitespace-elimination cleaner
	inline std::string getFirstWordOfNonemptyLine(std::istream& reader)
	{

		std::string temp("");
		while ((temp.empty() || (temp.length() == 1 && std::isspace(temp[0]))) && reader.rdstate() != reader.eofbit)
		{
			std::getline(reader,temp); 				//extract line
		}
//		std::cout << temp.substr(0,temp.find(' ')).size() << std::endl;
		return temp.substr(0,temp.find(' '));	//return first word before space
	}

	template<class OuterContainer>
	void recursivePrint(std::ostream& writer, const OuterContainer& container)
	{
		for (auto it = container.begin(); it != container.end(); ++it)
		{
			if(it->second.empty())
			{
				writer << it->second.data() << "\t" << it->first << "\n";
			}
			else
			{
				recursivePrint(writer, it->second);
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
	std::ifstream reader(filePath);
	boost::property_tree::ptree& treeRef = *treePtr;
	int temp;


	treeRef.put("i_restartRun",	getFirstWordOfNonemptyLine(reader));
	treeRef.put("idebug",		getFirstWordOfNonemptyLine(reader));
	treeRef.put("rho0",			getFirstWordOfNonemptyLine(reader));
	treeRef.put("ivisc",		getFirstWordOfNonemptyLine(reader));
	treeRef.put("viscos_val",	getFirstWordOfNonemptyLine(reader));
	treeRef.put("dw_min_fric",	getFirstWordOfNonemptyLine(reader));
	treeRef.put("iMUSCL",		getFirstWordOfNonemptyLine(reader));
	treeRef.put("tol",			getFirstWordOfNonemptyLine(reader));
	treeRef.put("i_dw_iter",	getFirstWordOfNonemptyLine(reader));
	treeRef.put("i_max_iter",	getFirstWordOfNonemptyLine(reader));
	treeRef.put("ivar_dt",		getFirstWordOfNonemptyLine(reader));
	treeRef.put("dt",			getFirstWordOfNonemptyLine(reader));
	treeRef.put("CFL",			getFirstWordOfNonemptyLine(reader));
	treeRef.put("out",			getFirstWordOfNonemptyLine(reader));
	treeRef.put("tmax",			getFirstWordOfNonemptyLine(reader));
	treeRef.put("trec_ini",		getFirstWordOfNonemptyLine(reader));
	treeRef.put("coef",			getFirstWordOfNonemptyLine(reader));
	treeRef.put("vlx",			getFirstWordOfNonemptyLine(reader));
	treeRef.put("vly",			getFirstWordOfNonemptyLine(reader));
	treeRef.put("dx_grd",		getFirstWordOfNonemptyLine(reader));
	treeRef.put("dy_grd",		getFirstWordOfNonemptyLine(reader));
	temp = 	std::stoi(			getFirstWordOfNonemptyLine(reader));
	treeRef.put("i_openbc",		temp);
	if (temp == 1)
	{
		treeRef.put("i_openbc_dep.distmin",	getFirstWordOfNonemptyLine(reader));
		temp = 	std::stoi(					getFirstWordOfNonemptyLine(reader));
		treeRef.put("i_openbc_dep.number_obc",temp);
		for (int i = 1; i <= temp; i++)
		{
			std::string currentTreePath = std::string("i_openbc_dep.openbc")+std::to_string(i)+"."; //store in different nodes by openbc number

			treeRef.put(currentTreePath+"iflagbc",		getFirstWordOfNonemptyLine(reader));
			treeRef.put(currentTreePath+"xp_obc",		getFirstWordOfNonemptyLine(reader));
			treeRef.put(currentTreePath+"yp_obc",		getFirstWordOfNonemptyLine(reader));
			treeRef.put(currentTreePath+"l_obc",		getFirstWordOfNonemptyLine(reader));
			treeRef.put(currentTreePath+"ver_obc(1)",	getFirstWordOfNonemptyLine(reader));
			treeRef.put(currentTreePath+"ver_obc(2)",	getFirstWordOfNonemptyLine(reader));
			treeRef.put(currentTreePath+"verz_obc",		getFirstWordOfNonemptyLine(reader));
			treeRef.put(currentTreePath+"dx_obc",		getFirstWordOfNonemptyLine(reader));
			int temp_steady_obc = std::stoi(			getFirstWordOfNonemptyLine(reader));
			treeRef.put(currentTreePath+"i_steady_obc",	temp_steady_obc);
			if (temp_steady_obc==0)
			{
				treeRef.put(currentTreePath+"i_steady_obc_dep.dw_obc",	getFirstWordOfNonemptyLine(reader));
				treeRef.put(currentTreePath+"i_steady_obc_dep.up_obc",	getFirstWordOfNonemptyLine(reader));
			}
			else if (temp_steady_obc==1)
			{
				treeRef.put(currentTreePath+"i_steady_obc_dep.namefile",getFirstWordOfNonemptyLine(reader));
				//this will read in a lot from namefile
			}

		}


	}
	temp = 	std::stoi(			getFirstWordOfNonemptyLine(reader));
	treeRef.put("i_closebc",	temp);
	if (temp == 1)
	{
		// closed boundaries. also writes a lot to file "ipartv"
		int temp_closebc = std::stoi(				getFirstWordOfNonemptyLine(reader));
		treeRef.put("i_closebc_dep.iblock!BLOCK",	temp_closebc); //do you want to add a closed boundary block?

		int closebc_counter = 1;
		while (temp_closebc == 1)
		{
			std::string currentTreePath = std::string("i_closebc_dep.iblock_block")+std::to_string(closebc_counter)+"."; //store in different nodes by closebc number
			treeRef.put(currentTreePath+"xv_ini",		getFirstWordOfNonemptyLine(reader));
			treeRef.put(currentTreePath+"yv_ini",		getFirstWordOfNonemptyLine(reader));
			treeRef.put(currentTreePath+"i_start1",		getFirstWordOfNonemptyLine(reader));
			treeRef.put(currentTreePath+"xv_fin",		getFirstWordOfNonemptyLine(reader));
			treeRef.put(currentTreePath+"yv_fin",		getFirstWordOfNonemptyLine(reader));
			treeRef.put(currentTreePath+"i_start2",		getFirstWordOfNonemptyLine(reader));
			treeRef.put(currentTreePath+"dxvv",			getFirstWordOfNonemptyLine(reader));
			treeRef.put(currentTreePath+"vnx",			getFirstWordOfNonemptyLine(reader));
			treeRef.put(currentTreePath+"vny",			getFirstWordOfNonemptyLine(reader));
			temp_closebc = std::stoi(					getFirstWordOfNonemptyLine(reader));
			treeRef.put(currentTreePath+"iblock",		temp_closebc);

			closebc_counter++;
		}
		temp_closebc = std::stoi(					getFirstWordOfNonemptyLine(reader));
		treeRef.put("i_closebc_dep.iblock!CIRC",	temp_closebc); //do you want to add a circular closed boundary?

		closebc_counter = 1;
		while (temp_closebc == 1)
		{
			std::string currentTreePath = std::string("i_closebc_dep.iblock_circ")+std::to_string(closebc_counter)+"."; //store in different nodes by closebc number
			treeRef.put(currentTreePath+"xc",		getFirstWordOfNonemptyLine(reader));
			treeRef.put(currentTreePath+"yc",		getFirstWordOfNonemptyLine(reader));
			treeRef.put(currentTreePath+"rad",		getFirstWordOfNonemptyLine(reader));
			treeRef.put(currentTreePath+"dxvv",		getFirstWordOfNonemptyLine(reader));
			temp_closebc = std::stoi(				getFirstWordOfNonemptyLine(reader));
			treeRef.put(currentTreePath+"iblock",	temp_closebc);

			closebc_counter++;
		}
	}
	treeRef.put("i_bedType",	getFirstWordOfNonemptyLine(reader));
	switch (treeRef.get<int>("i_bedType"))
	{
		//TODO: case 1&2 + broken
		case 1:

			break;
		case 2:

			break;

		case 3:
			treeRef.put("i_bedType_dep.file_bedProfile",	getFirstWordOfNonemptyLine(reader));
			break;
		default: //code broken
			break;
	}
	temp = 	std::stoi(			getFirstWordOfNonemptyLine(reader));
	treeRef.put("i_fluid",		temp);
	//TODO: case 2 and possibly broken case
	if(temp == 1)
	{
			//calls surface_define
			int sqblock_counter = 1;
			while (temp == 1)
			{
				std::string currentTreePath = std::string("i_fluid_dep.sqblock")+std::to_string(sqblock_counter)+"."; //store in different nodes by fluid block number
				treeRef.put(currentTreePath+"xbini",		getFirstWordOfNonemptyLine(reader));
				treeRef.put(currentTreePath+"ybini",		getFirstWordOfNonemptyLine(reader));
				treeRef.put(currentTreePath+"lx",			getFirstWordOfNonemptyLine(reader));
				treeRef.put(currentTreePath+"ly",			getFirstWordOfNonemptyLine(reader));
				treeRef.put(currentTreePath+"dw_block(1)",	getFirstWordOfNonemptyLine(reader));
				treeRef.put(currentTreePath+"dw_block(2)",	getFirstWordOfNonemptyLine(reader));
				treeRef.put(currentTreePath+"dw_block(3)",	getFirstWordOfNonemptyLine(reader));
				treeRef.put(currentTreePath+"dw_block(4)",	getFirstWordOfNonemptyLine(reader));
				treeRef.put(currentTreePath+"up_block(1)",	getFirstWordOfNonemptyLine(reader));
				treeRef.put(currentTreePath+"up_block(2)",	getFirstWordOfNonemptyLine(reader));
				treeRef.put(currentTreePath+"up_block(3)",	getFirstWordOfNonemptyLine(reader));
				treeRef.put(currentTreePath+"up_block(4)",	getFirstWordOfNonemptyLine(reader));
				treeRef.put(currentTreePath+"vp_block(1)",	getFirstWordOfNonemptyLine(reader));
				treeRef.put(currentTreePath+"vp_block(2)",	getFirstWordOfNonemptyLine(reader));
				treeRef.put(currentTreePath+"vp_block(3)",	getFirstWordOfNonemptyLine(reader));
				treeRef.put(currentTreePath+"vp_block(4)",	getFirstWordOfNonemptyLine(reader));
				treeRef.put(currentTreePath+"dx_block",		getFirstWordOfNonemptyLine(reader));
				temp = std::stoi(							getFirstWordOfNonemptyLine(reader));
				treeRef.put(currentTreePath+"iblock",		temp);

				sqblock_counter++;
			}
	}
	treeRef.put("iref",			getFirstWordOfNonemptyLine(reader));
	if (treeRef.get<int>("iref") == 1)
	{
		treeRef.put("ref_p",	getFirstWordOfNonemptyLine(reader));
		treeRef.put("ref_h",	getFirstWordOfNonemptyLine(reader));
	}
	treeRef.put("dxx_ref",		getFirstWordOfNonemptyLine(reader));
	treeRef.put("dyy_ref",		getFirstWordOfNonemptyLine(reader));
	treeRef.put("dw_min", 		getFirstWordOfNonemptyLine(reader));
	if (treeRef.get<int>("iref") == 1)
	{
		//TODO: read those six variables repeatedly until 6th == 0
	}
	treeRef.put("i_compile_opt",getFirstWordOfNonemptyLine(reader));
	treeRef.put("idouble",		getFirstWordOfNonemptyLine(reader));
}

void TreeInitialiser::printSettingsFile(std::string filePath) {
	std::ofstream writer(filePath);
	const boost::property_tree::ptree& tree = *treePtr;
	recursivePrint(writer, tree);



}


//TODO: export to another class/source file because compiling takes forever..
void TreeInitialiser::printJSONTree(std::string filePath) {

	boost::property_tree::json_parser::write_json(filePath,*treePtr);

}

void TreeInitialiser::loadJSONTree(std::string filePath) {

	boost::property_tree::json_parser::read_json(filePath, *treePtr);

}




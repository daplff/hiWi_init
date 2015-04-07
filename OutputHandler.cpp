#include "OutputHandler.h"
#include <boost/property_tree/ptree.hpp>
#include <fstream>
#include <iostream>
#include <boost/property_tree/json_parser.hpp>

OutputHandler::OutputHandler()
{
}

OutputHandler::~OutputHandler()
{
}

//boost::property_tree::ptree OutputHandler::loadDepthGrid(std::string fileName)
//{
//
//}

boost::property_tree::ptree OutputHandler::loadDtFile(std::string fileName)
{
//	std::cout << "start of fn" <<std::endl;
	std::ifstream reader(fileName);
//	std::cout << "reader done " << std::endl;
	boost::property_tree::ptree tree;
//		std::cout << "ptree done"<< std::endl;
	std::string tempTime;
	
	std::getline(reader, tempTime);
	
	

	double tempDt;
	
//	int i=0;
//		std::cout << "temps&counter done"<< std::endl;
	while (reader>> tempTime >> tempDt)
	{
//		std::cout<< tempTime << "\t" << tempDt << "\t" << i++ << std::endl;
		tree.put(boost::property_tree::ptree::path_type(tempTime,'/'),tempDt); //enable dots in path name to have time as name
	}
//		std::cout << "while done"<< std::endl;
	return tree;
	
}

//boost::property_tree::ptree OutputHandler::loadGridFiles(std::string fileNameXVel, std::string fileNameYVel, std::string fileNameDepths)
//{
//	
//}

boost::property_tree::ptree OutputHandler::loadParticleFile(std::string fileName)
{
	std::ifstream reader(fileName);
	boost::property_tree::ptree tree;
	
	std::string dataTemp[8];
	
	boost::property_tree::ptree tempTrees[8],dataTrees[8];
	
	
	while (reader >> dataTemp[0]>> dataTemp[1]>> dataTemp[2]>> dataTemp[3]>> dataTemp[4]>> dataTemp[5]>> dataTemp[6]>> dataTemp[7])
	{
		for (int i = 0; i<8 ; i++)
		{
//				reader >> dataTemp[i];
				tempTrees[i].put_value(dataTemp[i]);
				dataTrees[i].push_back(std::make_pair("",tempTrees[i]));
		}
		
	}
	tree.add_child("xposArray",dataTrees[0]);
	tree.add_child("yposArray",dataTrees[1]);
	tree.add_child("xvelArray",dataTrees[2]);
	tree.add_child("yvelArray",dataTrees[3]);
	tree.add_child("depthArray",dataTrees[4]);
	tree.add_child("areaArray",dataTrees[5]);
	tree.add_child("smoothlenArray",dataTrees[6]);
	tree.add_child("flagsArray",dataTrees[7]);
	
	return tree;
}



boost::property_tree::ptree OutputHandler::loadGrid(std::string fileName)
{
	std::ifstream reader(fileName);
	boost::property_tree::ptree tree;
	
	std::string temp;
	reader>>temp; //first word is DSAA
	int nplot_x,nplot_y; //number of plot points in X and Y directions
	reader >> nplot_x >> nplot_y;
	double vlx, vly, m_dw_grd; //medium extent in X,Y and Z/depth directions	
	reader >> temp >> vlx >> temp >> vly >> temp >> m_dw_grd;
	
	tree.put("nplot_x",nplot_x);
	tree.put("nplot_y",nplot_y);
	tree.put("vlx",vlx);
	tree.put("vly",vly);
	tree.put("m_dw_grd",m_dw_grd);
	
	boost::property_tree::write_json(std::cout,tree);
	boost::property_tree::ptree dataMatrixTree, dataArrayTree, tempTree;
	
	double data_temp;
		
	for (int i_y = 0; i_y < nplot_y ; i_y++)
	{
		dataArrayTree.clear();
		
		for (int i_x = 0; i_x < nplot_x; i_x++)
		{
			reader>>data_temp;
			tempTree.put_value(data_temp);
			dataArrayTree.push_back(std::make_pair("",tempTree));
		}
		dataMatrixTree.push_back(std::make_pair("",dataArrayTree));
	}
	tree.add_child("data",dataMatrixTree);
	return tree;
}

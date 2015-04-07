/*
 * main.cpp
 *
 *  Created on: 26 Mar 2015
 *      Author: erik
 */
#include <string>
#include <fstream>
#include <iostream>
#include <boost/property_tree/ptree.hpp>
//#include <boost/property_tree/json_parser.hpp>
#include "OutputHandler.h"

int main(int argc, char * argv[]){

//	boost::property_tree::ptree tree;
	
//	tree.add_child("grid",OutputHandler::loadGrid("GRD_u0113"));
//	tree.add_child("parts",OutputHandler::loadParticleFile("PART_0113"));
//	
//	boost::property_tree::write_json(std::cout,tree);
	
	
//	if (argc>2){
//		TreeInitialiser treeInitialiser;
//
//		treeInitialiser.loadSettingsFile(argv[1]);
//		treeInitialiser.printJSONTree(argv[2]+std::string(".json"));
//		treeInitialiser.printSettingsFile(argv[2]+std::string(".txt"));
//
//		std::cout << "done" << std::endl;
//	}
//	std::string test;
//	std::getline(std::cin,test);
//	std::cout << test.length();
//	boost::property_tree::ptree tree;
//	tree.put("somewhere","10");
//	if (tree.get<double>("somewhere")==10.0)
//	std::cout<< tree.get<std::string>("somewhere")  << 10.0 << std::endl;


//	if (argc>2){
//		std::fstream myFileReader(argv[2]);
//
//		for (int i=0; i<std::atoi(argv[1]); i++){
//			std::string temp;
//			std::getline(myFileReader,temp);
//			std::cout<<i<<" "<<temp<<"\n";
//			temp = temp.substr(0,temp.find(' '));
//			std::cout<<i<<" "<<temp<<"\n";
//		}
//	}

	return 0;

}



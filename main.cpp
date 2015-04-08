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
#include "TreeInitialiser.h"
#include <cstdlib>

int main(int argc, char * argv[]){


	
	
	if (argc>3){
		TreeInitialiser treeInitialiser;

		treeInitialiser.loadSettingsFile(argv[1]);
		treeInitialiser.printJSONTree(argv[2]+std::string(".json"));
		treeInitialiser.printSettingsFile(argv[2]));
		
		std::cout << "done, calling script" << std::endl;
		
		std::system(argv[3]+std::string(" <" ) + argv[2] + ".txt>lineoutput.txt");
		
		std::cout << "program done" <<std::endl;
		boost::property_tree::ptree& tree = *(treeInitialiser.getTreePtr());
		tree.add_child("time-dt", OutputHandler::loadDtFile("DT"));
		std::cout<<"loaded DT" << std::endl;
		tree.add_child("particles", OutputHandler::loadParticleFile("PART_0113");
		std::cout<<"loaded particles" << std::endl;
		tree.add_child("GRD_d", OutputHandler::loadGrid("GRD_d0113"));
		std::cout<<"loaded GRD_d" << std::endl;
		tree.add_child("GRD_u", OutputHandler::loadGrid("GRD_u0113"));
		std::cout<<"loaded GRD_u" << std::endl;
		tree.add_child("GRD_v", OutputHandler::loadGrid("GRD_v0113"));
		std::cout<<"loaded GRD_v" << std::endl;
		treeInitialiser.printJSONTree(argv[2]+std::string("_full.json"));
		std::cout<<"printed tree, finished" << std::endl;
		}
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



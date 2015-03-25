/*
 * TreeInitialiser.cpp
 *
 *  Created on: Mar 25, 2015
 *      Author: wannerbe
 */

#include "TreeInitialiser.h"
#include <boost/property_tree/ptree.hpp>

TreeInitialiser::TreeInitialiser()
{
	treePtr = std::shared_ptr(new boost::property_tree::ptree);
}

std::shared_ptr<boost::property_tree::ptree> TreeInitialiser::getTreePtr() {
	return treePtr;
}

TreeInitialiser::~TreeInitialiser() {
}

void TreeInitialiser::loadSettingsFile(std::string filePath) {
}

void TreeInitialiser::printSettingsFile(std::string filePath) {
}



/*
 * TreeInitialiser.h
 *
 *  Created on: Mar 25, 2015
 *      Author: wannerbe
 */

#ifndef TREEINITIALISER_H_
#define TREEINITIALISER_H_

#include <string>
#include <boost/property_tree/ptree_fwd.hpp>
#include <memory>

class TreeInitialiser {
public:
	std::shared_ptr<boost::property_tree::ptree> getTreePtr();
	TreeInitialiser();
	virtual ~TreeInitialiser();
	void loadSettingsFile(std::string filePath);
	void printSettingsFile(std::string filePath);
	void printJSONTree(std::string filePath);
	void loadJSONTree(std::string filePath);

// 	TODO:
//	void printJSONTree(std::string filePath, std::string pathInTree = "");
//	void loadJSONTree(std::string filePath, std::string pathInTree = "");

private:
	std::shared_ptr<boost::property_tree::ptree> treePtr;
};

#endif /* TREEINITIALISER_H_ */

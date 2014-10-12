/*
 * Reference.cpp
 *
 * Copyright (c) 2014, Alessandro Pezzato
 */

#include "Reference.h"
#include "Tree.h"
#include "swiftree.h"

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>
#include <vector>

using namespace std;
using namespace boost;

namespace swiftree {

bool Reference::isReference(const std::string& refPath) {
	return refPath.substr(0, 4) == "ref:";
}

Reference::Reference(const std::string& refPath) {
	std::vector<std::string> list;
	split(list, refPath, is_any_of(":"));
	std::string fileType = list[1];
	std::string fileName = list[2];
	if (fileType == "xml") {
		tree_ = fromXml(fileName);
	} else if (fileType == "json") {
		tree_ = fromJson(fileName);
	} else {
		throw std::runtime_error(list[1] + " is not a valid filetype");
	}
	if (list.size() > 3) {
		std::string treePath = list[3];
		tree_ = tree_.child(treePath);
	}
}

Reference::operator Tree() const {
	return tree_;
}

} /* namespace swiftree */

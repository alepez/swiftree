/*
 * Reference.cpp
 *
 * Copyright (c) 2014, Alessandro Pezzato
 */

#include "Reference.h"
#include "Node.h"
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
	if (list[1] == "xml") {
		fileType_ = FILETYPE_XML;
	}
	if (list[1] == "json") {
		fileType_ = FILETYPE_JSON;
	}
	fileName_ = list[2];
	if (list.size() > 3) {
		treePath_ = list[3];
	}
}

Reference::operator Node() const {
	Node node;
	switch (fileType_) {
	case FILETYPE_XML:
		node = fromXml(fileName_);
		break;
	case FILETYPE_JSON:
		node = fromJson(fileName_);
		break;
	}
	if (treePath_.empty()) {
		return node;
	}
	return node.child(treePath_);
}

} /* namespace swiftree */

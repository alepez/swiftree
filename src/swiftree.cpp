/*
 * swiftree.cpp
 *
 * Copyright (c) 2014, Alessandro Pezzato
 */

#include "swiftree.h"
#include "Tree.h"
#include "internal/TreeImpl.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/json_parser.hpp>

using namespace boost::property_tree;

namespace swiftree {

Tree fromXml(const std::string& filename) {
	ptree pt;
	xml_parser::read_xml(filename, pt);
	return Tree(TreeImpl(pt));
}

Tree fromJson(const std::string& filename) {
	ptree pt;
	json_parser::read_json(filename, pt);
	return Tree(TreeImpl(pt));
}

} /* namespace swiftree */

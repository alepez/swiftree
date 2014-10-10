/*
 * swiftree.cpp
 *
 * Copyright (c) 2014, Alessandro Pezzato
 */

#include "swiftree.h"
#include "Node.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

using namespace boost::property_tree;

namespace swiftree {

NodePtr loadXml(const std::string& filename) {
	ptree pt;
	xml_parser::read_xml(filename, pt);
	return NodePtr(new Node(pt));
}

} /* namespace swiftree */

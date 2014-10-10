/*
 * Node.cpp
 *
 * Copyright (c) 2014, Alessandro Pezzato
 */

#include "Node.h"

namespace swiftree {

Node::Node() {

}

Node::Node(const boost::property_tree::ptree& pt) :
				pt_(pt) {

}

Node::~Node() {

}

NodePtr Node::getChild(const std::string& path) const {
	return NodePtr(new Node(pt_.get_child(path)));
}

} /* namespace swiftree */

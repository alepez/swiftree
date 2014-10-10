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

} /* namespace swiftree */

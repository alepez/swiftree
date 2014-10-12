/*
 * Node.cpp
 *
 * Copyright (c) 2014, Alessandro Pezzato
 */

#include "Node.h"
#include "Reference.h"

namespace swiftree {

Node::Node() {

}

Node::Node(const boost::property_tree::ptree& pt) :
				pt_(pt) {

}

Node::~Node() {

}

Node::Node(const Node& node) :
				pt_(node.pt_) {

}

Node& Node::operator =(const Node& node) {
	pt_ = boost::property_tree::ptree(node.pt_);
	return *this;
}

Node Node::child(const std::string& path) const {
	std::string refPath = pt_.get_value<std::string>(path);
	if (Reference::isReference(refPath)) {
		return Reference(refPath);
	}
	return Node(pt_.get_child(path));
}

Node Node::operator[](const std::string& path) const {
	return this->child(path);
}

Node Node::operator[](const char* path) const {
	return this->child(path);
}

} /* namespace swiftree */

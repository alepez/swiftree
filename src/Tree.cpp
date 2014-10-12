/*
 * Tree.cpp
 *
 * Copyright (c) 2014, Alessandro Pezzato
 */

#include "Tree.h"
#include "Reference.h"

namespace swiftree {

Tree::Tree() {

}

Tree::Tree(const boost::property_tree::ptree& pt) :
				pt_(pt) {

}

Tree::~Tree() {

}

Tree::Tree(const Tree& tree) :
				pt_(tree.pt_) {
}

Tree& Tree::operator =(const Tree& tree) {
	pt_ = tree.pt_;
	return *this;
}

Tree Tree::child(const std::string& path) const {
	std::string strValue = pt_.get<std::string>(path);
	if (Reference::isReference(strValue)) {
		return Reference(strValue);
	}
	return Tree(pt_.get_child(path));
}

Tree Tree::operator[](const std::string& path) const {
	return this->child(path);
}

Tree Tree::operator[](const char* path) const {
	return this->child(path);
}

} /* namespace swiftree */

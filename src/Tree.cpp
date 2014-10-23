/*
 * Tree.cpp
 *
 * Copyright (c) 2014, Alessandro Pezzato
 */

#include "Tree.h"
#include "internal/TreeImpl.h"
#include "internal/Reference.h"

#include <boost/property_tree/ptree.hpp>

namespace swiftree {

Tree::Tree() :
				impl_(nullptr) {

}

Tree::~Tree() {
	delete impl_;
}

Tree::Tree(const Tree& tree) :
				impl_(new TreeImpl(*tree.impl_)) {
}

Tree::Tree(const TreeImpl& impl) :
				impl_(new TreeImpl(impl)) {

}

std::string Tree::toString() const {
	return impl_->toString();
}

Tree& Tree::operator =(const Tree& tree) {
	delete impl_;
	impl_ = new TreeImpl(*tree.impl_);
	return *this;
}

Tree Tree::child(const std::string& path) const {
	std::string strValue = impl_->child(path).toString();
	if (Reference::isReference(strValue)) {
		return Reference(strValue);
	}
	return Tree(impl_->child(path));
}

Tree Tree::operator[](const std::string& path) const {
	return this->child(path);
}

Tree Tree::operator[](const char* path) const {
	return this->child(path);
}

bool Tree::has(const std::string& path) const {
	return impl_->has(path);
}

} /* namespace swiftree */

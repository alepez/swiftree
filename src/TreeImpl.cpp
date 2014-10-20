/*
 * TreeImpl.cpp
 *
 * Copyright (c) 2014, Alessandro Pezzato
 */

#include "TreeImpl.h"

namespace swiftree {

TreeImpl::TreeImpl(const boost::property_tree::ptree& pt) :
				pt_(pt) {

}

TreeImpl::TreeImpl(const TreeImpl& tree) :
				pt_(tree.pt_) {

}

TreeImpl::~TreeImpl() {

}

std::string TreeImpl::toString() const {
	return pt_.get_value<std::string>();
}

bool TreeImpl::has(const std::string& path) const {
	return pt_.count(path) > 0;
}

TreeImpl TreeImpl::child(const std::string& path) {
	return TreeImpl(pt_.get_child(path));
}

} /* namespace swiftree */

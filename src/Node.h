/*
 * Node.h
 *
 * Copyright (c) 2014, Alessandro Pezzato
 */

#ifndef swiftree_NODE_H_
#define swiftree_NODE_H_

#include "swiftree_fwd.h"

#include <boost/property_tree/ptree.hpp>

namespace swiftree {

class Node {
public:
	Node();
	Node(const boost::property_tree::ptree& pt);
	virtual ~Node();
	template<class Type>
	Type get(const std::string& path) const {
		return pt_.get<Type>(path);
	}
	NodePtr getChild(const std::string& path) const;

private:
	const boost::property_tree::ptree pt_;
};

} /* namespace swiftree */

#endif /* swiftree_NODE_H_ */

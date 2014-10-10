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
	/**
	 * Default constructor
	 */
	Node();
	/**
	 * Copy constructor
	 */
	Node(const Node& node);
	/**
	 * Construct from boost property tree
	 */
	Node(const boost::property_tree::ptree& pt);
	/**
	 * Destructor
	 */
	virtual ~Node();
	/**
	 * Copy operator
	 */
	Node& operator=(const Node& node);
	/**
	 * Explicit value getter
	 */
	template<class Type>
	Type value(const std::string& path) const {
		return pt_.get<Type>(path);
	}
	/**
	 * Explicit value getter with default value
	 */
	template<class Type>
	Type value(const std::string& path, Type defaultValue) const {
		try {
			return pt_.get<Type>(path);
		} catch (...) {
			return defaultValue;
		}
	}
	/**
	 * Value getter
	 */
	template<class Type>
	operator Type() const {
		return pt_.get_value<Type>();
	}
	/**
	 * Explicit child getter
	 */
	Node child(const std::string& path) const;
	/**
	 * Child getter
	 */
	Node operator[](const std::string& path) const;
private:
	boost::property_tree::ptree pt_;
};

} /* namespace swiftree */

#endif /* swiftree_NODE_H_ */

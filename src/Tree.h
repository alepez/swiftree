/*
 * Tree.h
 *
 * Copyright (c) 2014, Alessandro Pezzato
 */

#ifndef swiftree_TREE_H_
#define swiftree_TREE_H_

#include "swiftree_fwd.h"

#include <boost/property_tree/ptree.hpp>

namespace swiftree {

class Tree {
public:
	/**
	 * Default constructor
	 */
	Tree();
	/**
	 * Copy constructor
	 */
	Tree(const Tree& tree);
	/**
	 * Construct from boost property tree
	 */
	Tree(const boost::property_tree::ptree& pt);
	/**
	 * Destructor
	 */
	~Tree();
	/**
	 * Copy operator
	 */
	Tree& operator=(const Tree& tree);
	/**
	 * Explicit direct value getter
	 */
	template<class Type>
	Type to() const {
		return pt_.get_value<Type>();
	}
	/**
	 * Explicit direct value getter with default value
	 */
	template<class Type>
	Type to(Type defaultValue) const {
		try {
			return pt_.get_value<Type>();
		} catch (...) {
			return defaultValue;
		}
	}
	/**
	 * Explicit child value getter
	 */
	template<class Type>
	Type value(const std::string& path) const {
		return pt_.get<Type>(path);
	}
	/**
	 * Explicit child value getter with default value
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
	 *
	 * \param path a dot separated path
	 * \return a Tree from the specified path
	 */
	Tree child(const std::string& path) const;
	/**
	 * Child getter
	 *
	 * \param path a dot separated path
	 * \return a Tree from the specified path
	 */
	Tree operator[](const std::string& path) const;
	/**
	 * Child getter
	 *
	 * \param path a dot separated path
	 * \return a Tree from the specified path
	 */
	Tree operator[](const char* path) const;
private:
	boost::property_tree::ptree pt_;
};

} /* namespace swiftree */

#endif /* swiftree_TREE_H_ */

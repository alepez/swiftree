/*
 * Tree.h
 *
 * Copyright (c) 2014, Alessandro Pezzato
 */

#ifndef swiftree_TREE_H_
#define swiftree_TREE_H_

#include "swiftree_fwd.h"

#include <string>
#include <memory>

#include <boost/lexical_cast.hpp>

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
	 * From implementation
	 *
	 * \attention internal use only
	 */
	Tree(const TreeImpl& impl);
	/**
	 * Destructor
	 */
	~Tree();
	/**
	 * Copy operator
	 */
	Tree& operator=(const Tree& tree);
	/**
	 * Get the string value, a shortcut to Tree::to<std::string>()
	 */
	std::string toString() const;
	/**
	 * Explicit direct value getter
	 */
	template<class Type>
	Type to() const {
		return boost::lexical_cast<Type>(this->toString());
	}
	/**
	 * Explicit direct value getter with default value
	 */
	template<class Type>
	Type to(Type defaultValue) const {
		try {
			return boost::lexical_cast<Type>(this->toString());
		} catch (...) {
			return defaultValue;
		}
	}
	/**
	 * Explicit child value getter
	 */
	template<class Type>
	Type value(const std::string& path) const {
		return boost::lexical_cast<Type>(this->child(path).toString());
	}
	/**
	 * Explicit child value getter with default value
	 */
	template<class Type>
	Type value(const std::string& path, Type defaultValue) const {
		try {
			return boost::lexical_cast<Type>(this->child(path).toString());
		} catch (...) {
			return defaultValue;
		}
	}
	/**
	 * Implicit casting (direct value getter)
	 *
	 * Usage:
	 *
	 * \code
	 * float speed = tree["speed"];
	 * int count = tree["count"];
	 * std::string name = tree["name];
	 * \endcode
	 */
	template<class Type>
	operator Type() const {
		return boost::lexical_cast<Type>(this->toString());
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
	 * \copydoc child(const std::string& path) const
	 */
	Tree operator[](const char* path) const;
	/**
	 * Test if tree has a property
	 *
	 * \param path the path
	 * \return true if is defined
	 */
	bool has(const std::string& path) const;
	/**
	 * Test if tree has a property
	 *
	 * \param path the path
	 * \return true if is defined
	 */
	template<class Type>
	bool has(const std::string& path) const {
		return this->has(path) && this->child(path).is<Type>();
	}

	/**
	 * Test if can be cast to a specific type
	 */
	template<class Type>
	bool is() const {
		try {
			boost::lexical_cast<Type>(this->toString());
			return true;
		} catch (...) {
			return false;
		}
	}
private:
	TreeImpl* impl_;
};

} /* namespace swiftree */

#endif /* swiftree_TREE_H_ */

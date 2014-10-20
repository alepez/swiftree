/*
 * TreeImpl.h
 *
 * Copyright (c) 2014, Alessandro Pezzato
 */

#ifndef swiftree_TREEIMPL_H_
#define swiftree_TREEIMPL_H_

#include <boost/property_tree/ptree.hpp>

namespace swiftree {

class TreeImpl {
public:
	/**
	 * Construct from boost property tree
	 */
	TreeImpl(const boost::property_tree::ptree& pt);
	/**
	 * Copy constructor
	 */
	TreeImpl(const TreeImpl& pt);
	/**
	 *
	 */
	virtual ~TreeImpl();
	/**
	 *
	 */
	std::string toString() const;
	/**
	 *
	 */
	bool has(const std::string& path) const;
	/**
	 *
	 */
	TreeImpl child(const std::string& path);

private:
	boost::property_tree::ptree pt_;
};

} /* namespace swiftree */

#endif /* swiftree_TREEIMPL_H_ */

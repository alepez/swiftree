/*
 * swiftree.h
 *
 * Copyright (c) 2014, Alessandro Pezzato
 */

#ifndef swiftree_SWIFTREE_H_
#define swiftree_SWIFTREE_H_

#include "Tree.h"
#include <string>

namespace swiftree {

Tree fromXml(const std::string& filename);
Tree fromJson(const std::string& filename);

} /* namespace swiftree */

#endif /* swiftree_SWIFTREE_H_ */

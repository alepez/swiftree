/*
 * swiftree.h
 *
 * Copyright (c) 2014, Alessandro Pezzato
 */

#ifndef swiftree_SWIFTREE_H_
#define swiftree_SWIFTREE_H_

#include "Node.h"

namespace swiftree {

Node fromXml(const std::string& filename);
Node fromJson(const std::string& filename);

} /* namespace swiftree */

#endif /* swiftree_SWIFTREE_H_ */

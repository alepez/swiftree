/*
 * swiftree.h
 *
 * Copyright (c) 2014, Alessandro Pezzato
 */

#ifndef swiftree_SWIFTREE_FWD_H_
#define swiftree_SWIFTREE_FWD_H_

#include <memory>

namespace swiftree {

class Node;

using NodePtr = std::shared_ptr<Node>;

} /* namespace swiftree */

#endif /* swiftree_SWIFTREE_FWD_H_ */

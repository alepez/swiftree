/*
 * Reference.h
 *
 * Copyright (c) 2014, Alessandro Pezzato
 */

#ifndef swiftree_REFERENCE_H_
#define swiftree_REFERENCE_H_

#include "swiftree_fwd.h"
#include "Node.h"

#include <string>

namespace swiftree {

class Reference {
public:
	static bool isReference(const std::string& refPath);
	Reference(const std::string& refPath);
	operator Node() const;
private:
	Node node_;
};

} /* namespace swiftree */

#endif /* swiftree_REFERENCE_H_ */

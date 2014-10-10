/*
 * Node_test.cpp
 *
 * Copyright (c) 2014, Alessandro Pezzato
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Node.h"

using namespace ::swiftree;
using namespace ::testing;

class ANode: public Test {
public:
	Node node_();
};

//TEST_F(ANode, CanGetFloat) {
//	ASSERT_NO_THROW(engine->setInput(input));
//}

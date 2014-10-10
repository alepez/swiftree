/*
 * Node_test.cpp
 *
 * Copyright (c) 2014, Alessandro Pezzato
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Node.h"
#include "swiftree.h"

using namespace ::swiftree;
using namespace ::testing;

class ANode: public Test {
public:
	NodePtr node_ { fromXml("test.xml")->getChild("root") };
};


TEST_F(ANode, CanGetChild) {
	ASSERT_FLOAT_EQ(3.14, node_->get<float>("float"));
}

TEST_F(ANode, CanGetFloat) {
	ASSERT_FLOAT_EQ(3.14, node_->get<float>("float"));
}


TEST_F(ANode, CanGetInt) {
	ASSERT_FLOAT_EQ(42, node_->get<int>("int"));
}

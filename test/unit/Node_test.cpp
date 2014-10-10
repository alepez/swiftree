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
	Node node_ { fromXml("test.xml").child("root") };
};

TEST_F(ANode, CanGetChildByExplicitGetter) {
	ASSERT_NO_THROW(node_.child("child"));
}

TEST_F(ANode, CanGetStringByExplicitGetter) {
	Node child = node_.child("child");
	auto value = child.value<std::string>("string");
	ASSERT_EQ("test", value);
}

TEST_F(ANode, CanGetFloatByExplicitGetter) {
	auto value = node_.value<float>("float");
	ASSERT_FLOAT_EQ(3.14, value);
}

TEST_F(ANode, CanGetIntByExplicitGetter) {
	auto value = node_.value<int>("int");
	ASSERT_EQ(42, value);
}

TEST_F(ANode, CanGetDefaultInt) {
	auto value = node_.value<int>("undefined", 42);
	ASSERT_EQ(42, value);
}

TEST_F(ANode, ThrowsIfNotDefinedAndWithoutDefault) {
	ASSERT_ANY_THROW(node_.value<int>("undefined"));
}

TEST_F(ANode, CanGetChildWithBrackets) {
	ASSERT_NO_THROW(node_["child"]);
}

TEST_F(ANode, CanGetFloatWithBrackets) {
	float value = node_["float"];
	ASSERT_FLOAT_EQ(3.14, value);
}

TEST_F(ANode, CanGetNestedChildWithBrackets) {
	std::string value = node_["child"]["string"];
	ASSERT_EQ("test", value);
}

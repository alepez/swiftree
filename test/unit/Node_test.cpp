/*
 * Node_test.cpp
 *
 * Copyright (c) 2014, Alessandro Pezzato
 */

#include <gtest/gtest.h>

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

TEST_F(ANode, CanBeCopied) {
	Node a;
	ASSERT_NO_THROW(a = node_);
	ASSERT_NO_THROW(Node b(a));
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
	ASSERT_EQ(42, node_.value("undefined", 42));
}

TEST_F(ANode, ThrowsIfNotDefinedAndWithoutDefault) {
	ASSERT_ANY_THROW(node_.value<int>("undefined"));
	ASSERT_ANY_THROW(node_["undefined"].to<int>());
	ASSERT_ANY_THROW(node_["undefined"]);
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


TEST_F(ANode, CanBeCastedToAFloat) {
	Node n = node_["float"];
	float value = n;
	ASSERT_FLOAT_EQ(3.14, value);
}

TEST_F(ANode, CanBeUsedInInitializationList) {
	class A {
	public:
		A(const Node& node) :
						number_(node["int"]) {
		}
		int number_;
	};
	A a(node_);
	ASSERT_EQ(42, a.number_);
}

TEST_F(ANode, CanBeExplicitlyCastedToAString) {
	class A {
	public:
		A(const Node& node) :
						str_(node["child"]["string"].to<std::string>()) {
		}
		std::string str_;
	};
	A a(node_);
	ASSERT_EQ("test", a.str_);
}

TEST_F(ANode, CanBeExplicitlyCastedToATypeDeterminedByDefaultValue) {
	class A {
	public:
		A(const Node& node) :
						value_(node["int"].to(5)) {
		}
		float value_;
	};
	A a(node_);
	ASSERT_EQ(42, a.value_);
}

TEST_F(ANode, CanBePassedToOtherObjects) {
	class A {
	public:
		A(const Node& node) :
						str_(node["number43"]) {
		}
		int str_;
	};
	class B {
	public:
		B(const Node& node) :
						a_(node["child"]) {
		}
		A a_;
	};
	B b(node_);
	ASSERT_EQ(43, b.a_.str_);
}

TEST_F(ANode, CanDynamicallyInstantiated) {
	Node* a = new Node(node_);
	Node* b = new Node(node_);
	*a = *b;
	delete a;
	delete b;
}

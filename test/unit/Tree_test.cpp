/*
 * Tree_test.cpp
 *
 * Copyright (c) 2014, Alessandro Pezzato
 */

#include <gtest/gtest.h>

#include "Tree.h"
#include "swiftree.h"

using namespace ::swiftree;
using namespace ::testing;

class ATree: public Test {
public:
	ATree() :
					tree_(fromXml("test.xml").child("root")) {

	}
	Tree tree_;
};

TEST_F(ATree, CanGetChildByExplicitGetter) {
	ASSERT_NO_THROW(tree_.child("child"));
}

TEST_F(ATree, CanBeCopied) {
	Tree a;
	ASSERT_NO_THROW(a = tree_);
	ASSERT_NO_THROW(Tree b(a));
}

TEST_F(ATree, CanGetStringByExplicitGetter) {
	Tree child = tree_.child("child");
	auto value = child.value<std::string>("string");
	ASSERT_EQ("test", value);
}

TEST_F(ATree, CanGetFloatByExplicitGetter) {
	auto value = tree_.value<float>("float");
	ASSERT_FLOAT_EQ(3.14, value);
}

TEST_F(ATree, CanGetIntByExplicitGetter) {
	auto value = tree_.value<int>("int");
	ASSERT_EQ(42, value);
}

TEST_F(ATree, CanGetDefaultInt) {
	ASSERT_EQ(42, tree_.value("undefined", 42));
}

TEST_F(ATree, ThrowsIfNotDefinedAndWithoutDefault) {
	ASSERT_ANY_THROW(tree_.value<int>("undefined"));
	ASSERT_ANY_THROW(tree_["undefined"].to<int>());
	ASSERT_ANY_THROW(tree_["undefined"]);
}

TEST_F(ATree, CanGetChildWithBrackets) {
	ASSERT_NO_THROW(tree_["child"]);
}

TEST_F(ATree, CanGetFloatWithBrackets) {
	float value = tree_["float"];
	ASSERT_FLOAT_EQ(3.14, value);
}

TEST_F(ATree, CanGetNestedChildWithBrackets) {
	std::string value = tree_["child"]["string"];
	ASSERT_EQ("test", value);
}

TEST_F(ATree, CanBeCastedToAFloat) {
	Tree n = tree_["float"];
	float value = n;
	ASSERT_FLOAT_EQ(3.14, value);
}

TEST_F(ATree, CanBeUsedInInitializationList) {
	class A {
	public:
		A(const Tree& tree) :
						number_(tree["int"]) {
		}
		int number_;
	};
	A a(tree_);
	ASSERT_EQ(42, a.number_);
}

TEST_F(ATree, CanBeExplicitlyCastedToAString) {
	class A {
	public:
		A(const Tree& tree) :
						str_(tree["child"]["string"].to<std::string>()) {
		}
		std::string str_;
	};
	A a(tree_);
	ASSERT_EQ("test", a.str_);
}

TEST_F(ATree, CanBeExplicitlyCastedToATypeDeterminedByDefaultValue) {
	class A {
	public:
		A(const Tree& tree) :
						value_(tree["int"].to(5)) {
		}
		float value_;
	};
	A a(tree_);
	ASSERT_EQ(42, a.value_);
}

TEST_F(ATree, CanBePassedToOtherObjects) {
	class A {
	public:
		A(const Tree& tree) :
						str_(tree["number43"]) {
		}
		int str_;
	};
	class B {
	public:
		B(const Tree& tree) :
						a_(tree["child"]) {
		}
		A a_;
	};
	B b(tree_);
	ASSERT_EQ(43, b.a_.str_);
}

TEST_F(ATree, CanDynamicallyInstantiated) {
	Tree* a = new Tree(tree_);
	Tree* b = new Tree(tree_);
	*a = *b;
	delete a;
	delete b;
}

TEST_F(ATree, CanGetATreeFromReference) {
	Tree refTree = tree_["child"]["reference"];
	ASSERT_EQ("foo", refTree["two"].to<std::string>());
}

TEST_F(ATree, CanGetAnXmlTreeFromReference) {
	Tree refTree = tree_["child"]["referenceXml"];
	ASSERT_EQ(42, refTree["int"].to<int>());
}

TEST_F(ATree, CanGetAnXmlTreeFromReferenceWithoutPath) {
	Tree refTree = tree_["child"]["referenceWithoutPath"];
	ASSERT_EQ(42, refTree["root"]["int"].to<int>());
}

TEST_F(ATree, ThrowsIfInvalidReference) {
	ASSERT_ANY_THROW(Tree refTree = tree_["child"]["invalidReference"]);
}

TEST_F(ATree, CanBeTestedForDefinedProperty) {
	ASSERT_TRUE(tree_.has("int"));
	ASSERT_FALSE(tree_.has("undefined"));
}

TEST_F(ATree, CanBeTestedForGoodCasting) {
	ASSERT_TRUE(tree_.is<int>("int"));
	ASSERT_TRUE(tree_.is<float>("int"));
	ASSERT_TRUE(tree_.is<std::string>("int"));
	ASSERT_FALSE(tree_.is<int>("name"));
	ASSERT_FALSE(tree_.is<float>("name"));
}


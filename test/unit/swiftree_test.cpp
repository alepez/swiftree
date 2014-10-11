/*
 * swiftree_test.cpp
 *
 * Copyright (c) 2014, Alessandro Pezzato
 */

#include <gtest/gtest.h>

#include "swiftree.h"

using namespace ::swiftree;
using namespace ::testing;

TEST(SwiftreeLibrary, CanLoadFromXml) {
	ASSERT_NO_THROW(fromXml("test.xml"));
}

PROJECT := swiftree

## DIRECTORIES
SRC_DIR := src
BUILD_DIR := build
DIST_DIR := dist

## SOURCES
CXX_SRC := $(shell find $(SRC_DIR) -name "*.cpp")
HXX_SRC := $(shell find $(SRC_DIR) -name "*.h")

## OBJECTS
CXX_OBJS := $(addprefix $(BUILD_DIR)/, $(patsubst $(SRC_DIR)/%,%,$(patsubst %.cpp,%.o,$(CXX_SRC))))
CXX_DEPS := $(CXX_OBJS:.o=.d)

###############################################################################
## DIST

## LIBRARIES OUTPUT
LIB_DIST_DIR := $(DIST_DIR)/lib
LIB_SHARED := $(LIB_DIST_DIR)/lib$(PROJECT).so
LIB_STATIC := $(LIB_DIST_DIR)/lib$(PROJECT).a

## HEADERS OUTPUT
HEADERS_DIST_DIR := $(DIST_DIR)/include
HEADERS_DIST := $(addprefix $(HEADERS_DIST_DIR)/, $(patsubst $(SRC_DIR)/%,%,$(HXX_SRC)))

###############################################################################
## COMPILER

DEFINES +=

## INCLUDES
INCLUDE_DIRS +=

## LIBRARIES
LIBRARIES += 
LIBRARY_DIRS += 

## COMPILER WARNINGS
WARNINGS := -pedantic -Wall -Wextra -c -fmessage-length=0

## COMPILER FLAGS (DEBUG/RELEASE)
ifeq ($(DEBUG), 1)
	DEFINES += DEBUG
	COMMON_FLAGS += -g3 -O0
	COMMON_FLAGS += -p -pg --coverage
	LDFLAGS += --coverage
else
	DEFINES += NDEBUG
	COMMON_FLAGS +=-O2
endif

COMMON_FLAGS += $(foreach includedir,$(INCLUDE_DIRS),-I$(includedir))
COMMON_FLAGS += $(foreach define,$(DEFINES),-D$(define))
EXTRA_FLAGS += -fPIC -std=c++0x

CXXFLAGS = $(EXTRA_FLAGS) $(COMMON_FLAGS) $(WARNINGS)

LDFLAGS += $(foreach librarydir,$(LIBRARY_DIRS),-L$(librarydir))
LDFLAGS += $(foreach library,$(LIBRARIES),-l$(library))

###############################################################################
## TARGETS

.PHONY: all test clean distclean includes libraries executables default unit_test doc

#default: test
default: libraries

## autogenerated dependencies
-include $(CXX_DEPS)

## build single object
## compile and generate dependencies tree http://stackoverflow.com/a/2045668/786186 
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c -o $@ $<
	$(CXX) $(CXXFLAGS) -MF$(@:%.o=%.d) -MG -MM -MP -MT$(@:%.o=%.d) -MT$@ $<

## build shared library
$(LIB_SHARED): $(CXX_OBJS)
	mkdir -p $(LIB_DIST_DIR)
	$(CXX) -shared -o $@ $(CXX_OBJS) $(LDFLAGS)

## build static library
$(LIB_STATIC): $(CXX_OBJS)
	mkdir -p $(LIB_DIST_DIR)
	ar rcs $@ $(CXX_OBJS)

## copy headers to dist/include
$(HEADERS_DIST_DIR)/%.h: $(SRC_DIR)/%.h
	mkdir -p $(dir $@)
	cp $< $@

libraries: $(LIB_STATIC) $(LIB_SHARED)

## build libraries executables and miscellaneus
dist: libraries $(HEADERS_DIST)
	@echo $(HEADERS_DIST)

## doc
doc:
	doxygen

## clean libraries and executables
clean:
	rm -f $(CXX_OBJS) $(CXX_DEPS) $(UNIT_TESTS_OBJ)
	rm -f $(LIB_SHARED) $(LIB_STATIC)

## clean everything
distclean: clean
	rm -rf $(DIST_DIR)/* $(BUILD_DIR)/*

###############################################################################
## TESTS

UNIT_TESTS_DIR := test/unit
UNIT_TESTS_BUILD_DIR := $(BUILD_DIR)/test/unit
UNIT_TESTS_SRC := $(shell find $(UNIT_TESTS_DIR) -name "*.cpp")
UNIT_TESTS_OBJ := $(addprefix $(UNIT_TESTS_BUILD_DIR)/, $(patsubst $(UNIT_TESTS_DIR)/%,%,$(patsubst %.cpp,%.o,$(UNIT_TESTS_SRC))))
UNIT_TESTS_EXE := $(UNIT_TESTS_BUILD_DIR)/test

## autogenerated dependencies
-include $(wildcard $(UNIT_TESTS_BUILD_DIR)/**/*.d)

$(UNIT_TESTS_BUILD_DIR)/%.o: $(UNIT_TESTS_DIR)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -I$(SRC_DIR) -c -o $@ $<
	$(CXX) $(CXXFLAGS) -I$(SRC_DIR) -MF$(@:%.o=%.d) -MG -MM -MP -MT$(@:%.o=%.d) -MT$@ $<

$(UNIT_TESTS_EXE): $(UNIT_TESTS_OBJ) $(CXX_OBJS)
	$(CXX) -o $@ -lgtest $(LDFLAGS) $(UNIT_TESTS_OBJ) $(CXX_OBJS)

unit_test: $(UNIT_TESTS_EXE)
	@echo $(wildcard $(UNIT_TESTS_BUILD_DIR)/**/*.d)
	cd test/env && ../../$(UNIT_TESTS_EXE)

test: unit_test

coverage: test
	lcov -b . --capture --directory . --output-file build/coverage.info
	genhtml build/coverage.info --output-directory build/coverage

###############################################################################
## build libraries, tests and documentaion
all: libraries $(UNIT_TESTS_EXE)

# swiftree [![travis build](http://img.shields.io/travis/alessandro-pezzato/swiftree.svg?style=flat)](https://travis-ci.org/alessandro-pezzato/swiftree)

Provides a concise way to access data inside xml and json from C++.

## Example:

    Node cfg = fromXml("configuration.xml");

Can access data directly with a dot-separated path:

    float speed = cfg["car.speed"];

Or accessing nested elements using the brackets operator:

    float speed = cfg["car"]["speed"];

Casting to the right type is done automatically, the type is
determined by the variable to which the value is assigned.

For examples of what you can do, see `test/unit/Node_test.cpp`

You can get the child node of a node by its name:

	Node child = node.child("childName");

The same can be achieved with the more concise operator[]:

	Node child = node["childName"];

You can explicitly get a value from a child 
	
	auto speed = node.value<float>("speed");
	auto direction = node.value<int>("direction");

You can set a default value that is returned if the child node is undefined.
The type is inferred by the default value.

	auto theAnswer = node.value("theAnswer", 42));

Node is automatically casted to any type:

	Node a = node["speed"];
	float value = a;

Node can be explicitly casted to any type: 

	auto b = a.to<float>();

Even with default value:

	auto b = a.to(3.14);

A special "reference" node can load data from another file (or part of it):

File bla.xml:

	<foo>
		<bar>
			<dee>ref:xml:guu.xml</dee>
			<hii>ref:xml:guu.xml:meh</hii>
		</bar>
	</foo>

File guu.xml:

	<meh>
		<ooo>ciao!</ooo>
	</meh>

the node loaded from guu.xml is attached to "foo.bar.dee" in the node loaded by bla.xml:

	std::string greeting = fromXml("bla.xml")["foo"]["bar"]["dee"]["meh"]["ooo"];
	std::string greeting2 = fromXml("bla.xml")["foo"]["bar"]["hii"]["ooo"];

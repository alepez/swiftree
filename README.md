# swiftree [![travis build](http://img.shields.io/travis/alessandro-pezzato/swiftree.svg?style=flat)](https://travis-ci.org/alessandro-pezzato/swiftree)

Provides a concise way to access data inside xml and json from C++.

## Example:

```cpp
    Tree cfg = fromXml("configuration.xml");
```

Can access data directly with a dot-separated path:

```cpp
    float speed = cfg["car.speed"];
```

Or accessing nested elements using the brackets operator:

```cpp
    float speed = cfg["car"]["speed"];
```

Casting to the right type is done automatically, the type is
determined by the variable to which the value is assigned.

See `test/unit/Tree_test.cpp` for examples.

You can get the child tree of a tree by its name:

```cpp
	Tree child = tree.child("childName");
```

The same can be achieved with the more concise operator[]:

```cpp
	Tree child = tree["childName"];
```

You can explicitly get a value from a child 

```cpp	
	auto speed = tree.value<float>("speed");
	auto direction = tree.value<int>("direction");
```

You can set a default value that is returned if the child tree is undefined.
The type is inferred by the default value.

```cpp
	auto theAnswer = tree.value("theAnswer", 42));
```

Tree is automatically casted to any type:

```cpp
	Tree a = tree["speed"];
	float value = a;
```

Tree can be explicitly casted to any type: 

```cpp
	auto b = a.to<float>();
```

Even with default value:

```cpp
	auto b = a.to(3.14);
```

A special "reference" tree can load data from another file (or part of it):

File bla.xml:

```xml
	<foo>
		<bar>
			<dee>ref:xml:guu.xml</dee>
			<hii>ref:xml:guu.xml:meh</hii>
		</bar>
	</foo>
```

File guu.xml:

```xml
	<meh>
		<ooo>ciao!</ooo>
	</meh>
```

the tree loaded from guu.xml is attached to "foo.bar.dee" in the tree loaded by bla.xml:

```cpp
	std::string greeting = fromXml("bla.xml")["foo"]["bar"]["dee"]["meh"]["ooo"];
	std::string greeting2 = fromXml("bla.xml")["foo"]["bar"]["hii"]["ooo"];
```

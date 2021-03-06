# swiftree [![travis build](http://img.shields.io/travis/alessandro-pezzato/swiftree.svg?style=flat)](https://travis-ci.org/alessandro-pezzato/swiftree)

Provides a concise way to access data inside xml and json from C++.

[Why I've started this project](http://pezzato.net/2014/10/swiftree-reading-values-concisely-from-tree-data-structures.html)

## Usage

### Load from file

~~~cpp
using swiftree::Tree;
Tree cfg = swiftree::fromXml("configuration.xml");
Tree cfg2 = swiftree::fromJson("configuration.json");
~~~

### Access data

You can access data directly with a dot-separated path

~~~cpp
float speed = cfg["car.speed"];
~~~

...or using the square brackets operator:

~~~cpp
float speed = cfg["car"]["speed"];
~~~

Casting to the right type is done automatically, the type is
deduced by the variable to which the value is assigned.

See `test/unit/Tree_test.cpp` for examples.

You can get the child tree of a tree by its name:

~~~cpp
	Tree child = tree.child("childName");
~~~

The same can be achieved with the more concise operator[]:

~~~cpp
	Tree child = tree["childName"];
~~~

You can explicitly get a value from a child 

~~~cpp	
	auto speed = tree.value<float>("speed");
	auto direction = tree.value<int>("direction");
~~~

### Default value

You can set a default value that is returned if the child tree is undefined.
The type is inferred by the default value.

~~~cpp
	auto theAnswer = tree.value("theAnswer", 42));
~~~

### Excplicit and implicit casting

Tree is automatically cast to any type:

~~~cpp
	Tree a = tree["speed"];
	float value = a;
~~~

Tree can be explicitly cast to any type: 

~~~cpp
	auto b = a.to<float>();
~~~

Even with default value:

~~~cpp
	auto b = a.to(3.14);
~~~

### Reference another tree

A special "reference" tree can load data from another file (or part of it):

File bla.xml:

~~~xml
	<foo>
		<bar>
			<dee>ref:xml:guu.xml</dee>
			<hii>ref:xml:guu.xml:meh</hii>
		</bar>
	</foo>
~~~

File guu.xml:

~~~xml
	<meh>
		<ooo>ciao!</ooo>
	</meh>
~~~

the tree loaded from guu.xml is attached to "foo.bar.dee" in the tree loaded by bla.xml:

~~~cpp
	std::string greeting = fromXml("bla.xml")["foo"]["bar"]["dee"]["meh"]["ooo"];
	std::string greeting2 = fromXml("bla.xml")["foo"]["bar"]["hii"]["ooo"];
~~~

### Checking for existence and casting

You can check if a child is defined

~~~cpp
tree.has("speed");
~~~

And if it can be cast to a type:

~~~cpp
Tree speed = tree["speed"]
if (speed.is<float>()) {
  /* speed can be cast to float */
}
~~~

You can also test if a child can be cast to a specific type:

~~~cpp
if (tree.has<float>("speed")) {
  /* speed exists and can be cast to float */
}
~~~ 

### Custom types

You can define custom translation from a Tree to any class:

~~~cpp
struct Vector3 {
	float x;
	float y;
	float z;
};

namespace swiftree {
template<>
Tree::operator Vector3() const {
	Vector3 obj;
	obj.x = value<float>("x");
	obj.y = value<float>("y");
	obj.z = value<float>("z");
	return obj;
}
}
~~~

Now you can cast a Tree to your custom class:

~~~cpp
Vector3 position = tree["position"];
~~~
## Build and install

Just build with `make dist` so libraries and headers will be generated in `dist` directory inside the
project. Add the `dist/include/swiftree` directory to your own project and link to the library in `dist/lib/`.

## Testing

For unit testing, swiftree needs [Google Test](https://code.google.com/p/googletest/).

    make test

For coverage testing, swiftree needs [lcov](http://ltp.sourceforge.net/coverage/lcov.php) and has to be compiled in DEBUG mode. Remember to `make clean` if it has already been compiled without DEBUG flag.

    make DEBUG=1 coverage

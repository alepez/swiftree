# swiftree

Provide a concise way to access data inside xml and json from C++.

## Example:

    Node cfg = fromXml("configuration.xml");

Can access data directly with a dot-separated path:

    float speed = cfg["car.speed"];

Or accessing nested elements using the brackets operator:

    float speed = cfg["car"]["speed"];

Casting to the right type is done automatically, the type is
determined by the variable to which the value is assigned.

For examples of what you can do, see `test/unit/Node_test.cpp`

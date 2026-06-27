# Area Calculator

This repository contains code for calculating the area and bounding box of arbitrarily-defined 2D grid shapes.

To use this code, you must
- add `#include "areacalculator.h"`,
- define a testing class implementing `Tester::test(x, z)`; and
- call `AreaCalculator::calculate(tester, starting X, starting Z)`.
The `x` and `z` coordinates support arbitrary units, so long as their types support assignment, comparison, addition, subtraction, increments/decrements, and hashing. The returned struct will be an `AreaCalculator::Result` class containing the area and bounding box.

This code is adapted from pseudocode on Wikipedia (although heavily modified), and thus is licensed under Creative Commons BY-SA 4.0. Issues or pull requests are welcome.
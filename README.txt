Laplace inverse transform helper for electronics.
file format: number_of_numerators max_power coef(max_power) ... coef(0) number_of_denominators max_power coef(max_power) ... coef(0)
use the first executable Laplace.x with test.txt or test2 for an example

TODO:
- better error/functionality limits checking, fails miserably right now - not yet started
- Automaticaly apply the inverse laplace transform on the partial fractions - not yet started
- remove obvious memory leaks, profile and optimize the whole thing - not yet started
- Support for normal text input, for example: (s+2)/(s+3)(s^2-1) - not yet started

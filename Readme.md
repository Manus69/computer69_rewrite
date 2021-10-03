### Computer69 is an interpreter of mathematical expressions.
### It is capable of evaluating arithmetical expressions, polynomials, trigonometric functions, matrix operations and so on.
---
## Installation and controls
### Clone the repository in the directory of your choice and type "make".
### Type in "./computer69" to run the program.
### To interpret a statement, type it in and press Enter.
### Type "--q" to quit the program.
### Type "--list" to list all current variables.
### Type "--purge" to purge all variables.
### Lines starting with "//" are treated as "comments".

---
## Supported features
---
## Basic arithmetic
### Computer69 is capable of evaluating arithmetical expressions like this:
    1 + 1
### or like this
    661 * (1 + 3!)
### or this
    -((1+2+3*4^5) + 3.14*(2.71 - (1 - 1))) / 10
### or any other expression, you might come up with
---

## Built-in constants
### Some useful numbers, like pi and e, are predefined, with precision of at least 10 decimal digits.
    pi
    e
---

## Complex numbers
### Complex arithmetic is fully supported
    i*i
    pi + e*i / (e*i)
---

## Variables (I)
### It is possible to define variables. The syntax is straightforward:
    <variable name> = <value>
### Variable name must begin with a letter and may contain underscores and numbers.
### For instance:
    x = (pi * pi) / e
    x = x + 1
    y = -x*i
    variable69 = x^69
    this_is_also_a_variable = 0
### Variable names are not case sensitive. So "var69" and "VAR69" stand for the same entity.
---

## Built-in functions
### Many commonly used functions are supported out of the box:
    abs(x), sqrt(x), sin(x), cos(x), tan(x), exp(x), log(x), ln(x)
### They are defined on **R**.
### For instance:
    cos(pi)^2 + sin(pi)^2
    sqrt(abs(-pi))
    zero = log(e) - 1 / ln(2)
---

## Some words on syntax
### In general, the syntax rules are conventional. Symbols are connected by special characters,
### that represent mathematical operations:
    (i * pi * e)^0
### "+" stands for numeric or matrix addition;
### "-" numeric or matrix subtraction or unary negation;
### "*" numeric multiplication;
### "**" matrix multiplication;
### "/" numeric division;
### "%" remainder after integer division;
### "^" exponentiation (rhs must be in **N**);
### "!" factorial (operand must be in **N**);
### When a number precedes a symbolic constant, variable name or function name,
### multiplication symbol can be omitted:
    x = 2e
    x = 1
    1cos(2pi)^3x
---

## Error management
### In case of an error, the program stops the computation and tries to display a helpful message.
    x = 1 / 0
    pi = e
    rubbish input ?
---

## User-defined functions / Variables(II)
### Users can define functions of a single variable:
    f(x) = x^2
    g(x) = exp(x) + 1 / sqrt(x)
    s(t) = (1/2) * g(t) * t^2 + sin(t)
---

## Function evaluation
### Any function can be evaluated by providing it with an argument:
    inverse_sqrt(x) = 1 / sqrt(x)
    inverse_sqrt(pi^2)
### Note that if you try to evaluate a function with a value, that is not in its domain, you will get an error. Try this:
    f(x) = sin(x) + x!
    f(i)
### Also note that function evaluation might be **lazy**, meaning that if you create a function,
### it will not be evaluated until you provide it with an argument.
---

## Function algebra
### Functions can be added, subtracted, multiplied and so on:
    f(x) = 2x
    g(x) = x^2
    w(x) = f(x) + g(x)
    f(x) = f(x) + g(x) + w(x)
### or
    f(x) = f + g + w
### (the argument is implicit)
---

## Function composition
### Functions can be composed to produce other functions:
    f(x) = 2x
    g(x) = x^2
    h(x) = f(g(x))
    w(x) = g(f(x))
### or, for example:
    f(x) = exp(x)
    g(x) = ln(x)
    id(x) = f(g(x))
---

## Roots of polynomials
### Computer69 can find roots of a polynomial with real coefficients, provided the degree of a polynomial is no greater than 3. To do that, just put a question mark after a polynomial:
    x^2 = 2 ?
### or:
    p(x) = x^2 - x - 1
    p(x) = 0 ?
    y^2 + 1 = 0 ?
    x^3 - 3x^2 - 144x + 432 = 0 ?
---

## Matrices
### Matrices with real or complex coefficients are also supported. The syntax is as follows:
    [<row0>; <row1>; ... <rowN>]
### where each row has the form:
    [_, _, ... , _]
### for example:
    [[1, 0];[0, 1]]
    A = [[pi, e];[0, 1]]
### note that matrix size is limited to 4 right now.
---

## Matrix operations
### Matrices can be added, multiplied by a scalar or multiplied by a matrix:
    A = [[1, 0];[0, 1]] + [[0, 1];[1, 0]]
    B = pi * [[1, 0]]
    C = [[pi, e]] ** A ** [[1];[1]]
### raising to an integer power is also defined:
    A = [[1, 1];[0, 1]]^69
---

## Matrix entries
### Matrices can have other objects as entries:
    A = [[sin(pi/2)];[1 + sqrt(e)]]
---

## Matrix functions
### You can define matrix-valued functions of a single variable:
    <name>(<parameter>) = [[f0(<parameter>), f1(<parameter>), ...]]
### For example:
    a(x) = [[1, x];[0, 1]]
    b(x) = [[1, 0];[x, 1]]
    c(x) = a(x) ** b(x)
    c(0)

---

## Fun
### Let's play around with the program and compute some stuff.
### Let's compute e with reasonable precision:
    my_e(x) = 1 + x + x^2 / 2! + x^3 / 3! + x^4 / 4! + x^5 / 5!
    my_e(1)
### Compute the 69th Fibonacci number using matrices:
    F69 = [[0, 1]]**[[1, 1];[1, 0]]^68**[[1];[0]]
### Another way to have fun is to rotate some vectors in the plane:
    r(x) = [[cos(x), -sin(x)];[sin(x), cos(x)]]
    r_pi = r(pi)
    v = [[1];[1]]
    w = r_pi^2 ** v
---

## Upcoming features
* Derivatives and integrals of real functions
* Functions of multiple variables
* gcd, lcm, C(n, k)
* Systems of linear equations
* Matrix transposition
* Determinants, inverses, eigenvalues
* Non-integer exponents
* Functions from C to C
* Better controls
* Roots of higher degree polynomials (?)

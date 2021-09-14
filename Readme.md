# Computer69
---
### Computer69 is an interpreter of mathematical expressions.
### It is capable of evaluating arithmetical expressions, polynomials, trigonometric functions, matrix operations and so on.
### Some of its more advanced features are still in development, they will become available in the future versions.
---
## Installation and controls
#### Clone the repository in the directory of your choice and type "make".
#### Type in "./computer69" to run the program.
#### To interpret a statement, type it in and press Enter.
#### Type "q" and Enter to quit the program.
#### Type "--list" to list all current variables.
#### Lines starting with "//" are treated as "comments"

---
## Supported features
---
### Basic arithmetic
#### Computer69 is capable of evaluating arithmetical expressions like this:
    1 + 1
#### or like this
    661 * (1 + 3!)
#### or this
    -((1+2+3*4^5) + 3.14*(2.71 - (1 - 1))) / 10
#### or any other expression, you might come up with
---

### Built-in constants
#### Some useful numbers, like pi and e, are predefined, with precision of at least 10 decimal digits.
---

### Complex numbers
#### Complex arithmetic is fully supported
    i*i
    pi + e*i / e*i
---

### Variables (I)
#### It is possible to define variables. The syntax is straightforward:
    <variable name> = <value>
#### For instance:
    x = (pi * pi) / e
    x = x + 1
    y = -x*i
    variable69 = x^69
#### Variable names are not case sensitive. So "var69" and "VAR69" stand for the same entity.
---

### Built-in functions
#### Many commonly used functions are supported out of the box:
    abs(x), sqrt(x), sin(x), cos(x), tan(x), exp(x), log(x), ln(x)
#### They are defined on **R**.
#### For instance:
    cos(pi)^2 + sin(pi)^2
---

### Some words on syntax
#### In general, the syntax rules are conventional. Symbols are connected by special characters,
#### that represent mathematical operations:
    (i * pi * e)^0
#### "+" stands for numeric or matrix addition;
#### "-" numeric or matrix subtraction or unary negation;
#### "*" numeric or matrix multiplication;
#### "/" numeric division;
#### "%" remainder after integer division;
#### "^" exponentiation (rhs must be in **N**);
#### "!" factorial (operand must be in **N**);
#### When a numeric symbol precedes a symbolic constant, variable name or function name,
#### multiplication symbol can be omitted:
    x = 2e
    x = 1
    1cos(2pi)^3x
---

### User-defined functions / Variables(II)
#### Users can define functions of a single variable:
    f(x) = x^2
    g(x) = exp(x) + 1 / sqrt(x)
    s(t) = a + v * t + (1/2) * g * t^2
---

### Function evaluation
#### Any function can be evaluated by providing it with an argument:
    inverse_sqrt(x) = 1 / sqrt(x)
    inverse_sqrt(pi^2)
#### Note that if you try to evaluate a function with a value, that is not in its domain, you will get an error. Try this:
    f(x) = sin(x) + x!
    f(i)
#### Also note that function evaluation is **lazy**, meaning that if you create a function,
#### it will not be evaluated until you provide it with an argument.
---

### Function algebra
#### Functions can be added, subtracted, multiplied and so on:
    f(x) = 2x
    g(x) = x^2
    w(x) = f(x) + g(x)
---

### Function composition
#### Functions can be composed to produce other functions:
    f(x) = 2x
    g(x) = x^2
    h(x) = f(g(x))
    w(x) = g(f(x))
#### or, for example:
    f(x) = exp(x)
    g(x) = ln(x)
    id(x) = f(g(x))
---

### Roots of polynomials
#### Computer69 can find roots of a polynomial with real coefficients, provided the degree of a polynomial is no greater than 3. To do that, just put a question mark after a polynomial:
    x + x^2 = 0 ?
#### or:
    p(x) = x^2 - x - 1
    p(x) = 0 ?
---

### Matrices
#### Matrices with real or complex coefficients are also supported. The syntax is as follows:
    [<row0>; <row1>; ... <rowN>]
#### where each row has the form:
    [_, _, ... , _]
#### for example:
    [[1, 0];[0, 1]]
    A = [[pi, e];[0, 1]]
---

### Matrix operations
#### Matrices can be added, multiplied by a scalar or multiplied by a matrix:
    A = [[1, 0];[0, 1]] + [[0, 1];[1, 0]]
    B = [[1, 0]] * pi
    C = [[pi, e]]*[[e];[pi]]*A
#### raising to an integer power is also defined:
    A = [[1, 1];[0, 1]]^69
---

### Matrix entries
#### Matrices can have other objects as entries:
    A = [[sin(pi/2)];[1 + sqrt(e)]]
---

### Matrix functions
#### You can define matrix-valued functions of a single variable:
    <name>(<parameter>) = [[f0(<parameter>), f1(<parameter>), ...]]
#### For example:
    a(x) = [[1, x];[0, 1]]
    b(x) = [[1, 0];[x, 1]]
    a(x) * b(x)
---

### Fun
#### Let's play around with the program and compute the 69th Fibonacci number using matrices.
    F69 = [[0, 1]]*[[1, 1];[1, 0]]^69*[[1];[0]]
#### Another way to have fun is to rotate some vectors in the plane:
    r(x) = [[cos(x), -sin(x)];[sin(x), cos(x)]]
    v = [[1];[1]]
    w = r(pi/2) * v
---

## Upcoming features
* Derivatives and integrals of real functions
* Functions of multiple variables
* Systems of linear equations
* Determinants, inverses, eigenvalues
* Non-integer exponents
* Functions from C to C
* Better controls

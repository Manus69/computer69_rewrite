#include "frontend_declarations.h"
#include "print.h"
#include "test.h"

#include <stdio.h>

const char *valid_basic_strings[] = {"1", "-1", "0", "0+0", "0-1",
"1+1", "-1-1", "1-1", "-1-1-1", "-1-1+1", "1-1-1+1",
"5*5", "1-(2*2)", "1+(2*2)",
"1+1*2", "1+2^2", "1-2*2", "1-(2*2)",
"(1-1)^2", "(1+1)*2", "(1+1)^2", "1-(1-(1))", "(1-1)^(1-1)",
"(1+1)^(1*2-1)", "-1*2-1*2-1*2-1*2-1*2",
"(1+1)!", "1+2*3^2!", "3!+(2+2)", "1+(1+1)^2", "(1+1)^(1+1)", 
"3!^2+1*(1+1)", "1-(1+1)", "1-(1-(1+1*(2)))", "1-(1+2*3^(1+1))", 
"1-(1+(2*3-1))+1", "2-2*2-2^3+1", "3!-1", "1-3!", "(3-1)!-1", "2!!!",
"(3!)!", 0};

const char *valid_id_strings[] = {"sin(0)", "sin(pi)",
"cos(2*pi-pi)", "cos(pi)^2+sin(pi)^2",
"cos(2*pi*sin(-pi+2*pi))", "-pi", "-pi*sin(pi/2)", "pi*i", "i*pi", 
"-i*pi", "-pi*i", "-sin(pi/2)", "sin(-pi/2)", "-sin(2*cos(0))/sin(pi/2)", 0};

const char *invalid_strings[] = {
". * -",
"*",
"-",
"- = -",
"- 1 * = 0",
"a = b = 0",
"0 = 0 = 0",
"x y = 0",
"-",
"-1 *",
"y -",
"1 + x =",
"012345678901234567890123456789",
"3 - 3 = ",
"1 =",
"= x",
"+",
" + ",
"- ",
"=",
" =",
" = ",
"x == -1",
"x = -x = x",
"===",
"x^-11 = -9",
"x = 01",
"x = -01",
"x-1^x = 0",
"-x++x = -1",
"-2 --1 = 0",
"x^-1 = -1",
"+x = -1",
"_",
"	~",
"1 * X^^1 = -X",
"* x = -1",
"-1 * * c = 0",
"-x + = -1",
"ч = 0",
"3.1ч = 0",
"0 = 3.1ч",
"0 = +-1",
"0 = +- x",
"01 = 0x",
"+7 = 0",
"1. = x",
"x = .001",
"x = ..",
"1..0 = x",
"-00..1 = x",
"0.0.1 = x",
".09 = -1",
"0131.99 = -1",
"0 - 1 = 9.",
"#1 = -@0",
"#=",
"   - $ = -#",
0};

const char *context_dependent_strings[] = {
"x",
"X",
"x - X",
"x = YYYY",
"012345678901234567890123456789 = x",
"012345678901234567890123456789x = -1",
"x = y",
"-x = 0x * x",
"0 = x * x",
"0 = 0x + 0x^10",
"1x^9999999999999999999 = -1",
"0x = -1",
"-x = 0x^9",
"-1 * X = - 1 * Y",
"-x^11 -x^2 = x^3",
"3.14 *x = -1",
"-x = 3.24* x^10",
"0 = -3.1x^3.1",
"0 = a1",
"a^x = 0",
"3.1A + 8.1111b = 0",
"3.11A = -4.1B",
"10*x = -1",
"1-x = 0",
"-xX = 0",
"x*a^1 = -1",
"1^1 = x",
"a-1 = 0",
"a-1 = b",
"a-1=v",
0};

const char *valid_strings[] = {
"11",
"0 = 0 * 0",
"-X^10 = 0",
// "-999999999999999999999999999999999999999999999999999999x = x^20",
"x^99999999999999999999999999 = -1",
"x^3 - x^4 = 0",
"0 = 5 * 5",
"1 = 1",
"1 = 3",
"x = x",
"-1x = 0",
"x = 0",
"a = -a",
"K^1 = -99",
"x + -x = -1",
"x + x^3 + x^2 = -1",
"7 = 0",
"-7 = 0",
"0 = -3.9999999999999999999999999999999999999999x^1",
"a^0 = -1",
"5 * X^0 = 5 * X^0",
"4 * X^0 = 8 * X^0",
"5 * X^0 = 4 * X^0 + 7 * X^1",
"1x - x = -1x",
"5 * X^0 + 13 * X^1 + 3 * X^2 = 1 * X^0 + 1 * X^1",
"5 + 13 * x + 3x^2 = 1 + x ",
"  -x = 3.1  ",
"5 * X^0 + 13 * X^1 + 3 * X^2 = 1 * X^0 + 1 * X^1",
"-1 - 5 = 0",
"6 * X^0 + 11 * X^1 + 5 * X^2 = 1 * X^0 + 1 * X^1",
"5 * X^0 + 3 * X^1 + 3 * X^2 = 1 * X^0 + 0 * X^1",
"0.000001 = x",
"x = 0.0000000000000000000000000000000000001",
"-0.1 = x",
"0 = 0.99999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999x^1",
"-x = 99999999999999999999999999999999999999.99999999999999999999999999",
"0 + 0 = 0 * x + 0 * x^10",
"-13.5203 + 6.533X^2 - 3.64131X^3 = 0",
"-0.0000220921 + 11.4785X^2 = 0",
"-9.1 - 8.77x + 4x^3 = 0",
"c^2 - c^2 + c^2 + c^2 + 1.14124c^2 = -1",
"5x^3 + 4x^2 + 2x + 2 = 0",
"x^3 = 27",
"x^3 = 99999999999999999999999999999",
"x^3 - 6x^2 + 11x - 6 = 0",
"x^3 - 3 * x^2 + 3 * x - 1 = 0",
"a^3 - 5a^2 - 2a + 24 = 0",
"0 = X^3 + 4 * X^2 + X - 5",
"x^3 - 3x^2 - x + 1 = 0",
"-13.2593 + 6.48091X - 8.58475X^2 + 0.0000267855X^3 = 0",
"9999999 + 9999999999x + 99999999x^2 = 0",
"999 + 999x + 999x^2 = 0",
"9999999 + 9999999999x + 99999999x^2 + 9999999 * x^3 = 0",
"-13.5203 + 6.533X^2 - 3.64131X^3 = 0",
"-1 + x^3 = x^2 + x^3 + x^3",
"A^17 = -1",
"-x = 0.0001x^10",
"-1 - -1 = C^31",
"0 = x^11",
"x^10 = 0",
"2 * X^4 = 0",
"-0x^0 = 0",
"-0 = x",
"0 = 0 * x + -0",
"x + -0 * x = -0",
"-13.2593 + 6.48091X - 8.58475X^2 + 0.0000267855X^3 = 0",
"37.7801 + 58.1269X - 50.5115X^2 - 141.452X^3 = 0",
"-121.34 - 76.7428X + 35.6213X^2 + 37.283X^3 = 0",
"76.7264 + 83.6769X^2 - 21.1039X^3 = 0",
"-13.5203 + 6.533X^2 - 3.64131X^3 = 0",
"-150281 - 308387X - 962354X^2 = 0",
"-0.00000220921 + 11.4785X^2 = 0",
"99999999999999999999999999999x^3 - 1 = 0",
"0 = X^3 - 3 * X^2 + 4 * X - 2",
"x^3 - 3x^2 + 4x - 2 = 0",
"x^3 - 15x - 4 = 0",
"x^3 - 3x + 1.412 = 0",
"-1 + x^3 = x^2 + x^3 + x^3",
"A^3 + A^3 = 125",
"126 = 1X^3",
"-125 = c^3",
"2x^3 - 5x^2 - 23x - 10 = 0",
"x^2 = 2",
0};

const char *valid_cubics[] = {
"-981.227X^3 = 0",
"935.483X^2 - 981.227X^3 = 0",
"305.887X^2 - 981.227X^3 = 0",
"-26.6508 + 305.887X^2 - 981.227X^3 = 0",
"-26.6508 + 177.748X^2 - 981.227X^3 = 0",
0};

const char *valid_sequence_basic[] = {"A = [[1]]", "B = 2*A", 0};

const char *valid_sequence[] = {"r(x) =[[x]]", "r + [[1]]", 0};

const char *valid_sequences[][SEQUENCE_LENGTH] = {
{"0", 0},
{"-1", "--1", "---pi", "----e", "-i", "--i", 0},
{"2 + 3 * 4 / 4", 0},
{"cos(2*pi*sin(-pi+2*pi))", 0},
{"-sin(2*cos(0))/sin(pi/2)", 0},
{"2-2*2-2^3+1", 0},
{"x = 1", "y = x + x", 0},
{"x = 1", "x = x + 1", 0},
{"var = pi", "var2 = var*var + 1", 0},
{"f(x) = x", "y = f(1)", 0},
{"f(x) = x", "g(x) = f(x + 1)", 0},
{"f(x) = x", "g(x) = f(x)", "f(x) = g(x)", 0},
{"f(x) = x", "g(x) = f(x)", "f(x) = g(x)", "f(1)", 0},
{"ass(cock) = cock + cock", "y = ass(ass(1))", 0},
{"f(x) = x + x + x", "g(x) = x^2", "y = f(g(1))", "z = g(f(1))", 0},
{"f(x) = sin(x)", "ass2(x) = -f(x)", "var = ass2(pi/2)", 0},
{"x1 = -pi/e", "x2 = x1^2 - 1", 0},
{"x = 0", "x = x + 1", 0},
{"ass1 = pi", "ass1 = ass1 + 1", 0},
{"ass10 = pi/2", "f(x) = sin(x) + ass10", "ass1 = f(ass10)", 0},
{"x = pi*e", "x = x^2", "x = x*3!", "f(w) = w + w", "z = f(1)", 0},
{"x = pi/4", "f(y) = sin(y)^(3!) - e", "w = f(x)", 0},
{"x = -sin(2*cos(0))/sin(pi/2)", "y(k) = x^k", "w = y(2)", 0},
{"thisIsaVariable = -1-1-1", "f(vvv) = vvv^3!", "w = f(thisIsaVariable)", 0},
{"1-(1+(2*3-1))+1", "sin(pi/2)", 0},
{"p(x) = pi + x + x^2", "p(1)", 0},
{"cos(2*pi*sin(-pi+2*pi))*cos(pi)^2+sin(pi)^2-sin(-pi/2)", 0},
{"f(x) = x + x", "g(x) = 2*x", "w(x) = f(x) + g(x)", "k = w(1)", 0},
{"f(x) = 2!*sin(x^2)^2", 0},
{"ffff(x) = x^2 + sin(x)*cos(x)", 0},
{"f(x) = 2!*sin(x^2)^2", "g(x) = x^2 + sin(x)*cos(x)", 0},
{"f(x) = 2!*sin(x^2)^2", "g(x) = x^2 + sin(x)*cos(x)", "w(x) = f(g(x))", "w(1)", 0},
{"f(x) = x^2", "g(x) = x + 1", "h(x) = f(g(x))", "h(x) = g(f(x))", 0},
{"f(x) = x^2", "g(x) = sin(f(x))", 0},
{"f(x) = x^2", "g(x) = f(sin(x))", 0},
{"f(a) = a + a", "g(x) = f(sin(x))", "g(pi/2)", 0},
{"f = pi", "f = i", 0},
{"f(x) = x", "g(x) = x * x", "f(x) = g(x)", 0},
{"f(x) = sin(x)", "f(x) = f(x)", 0},
{"f(x) = x^2", "g(x) = sin(x)", "f(x) = g(x)", "g(x) = f(x)", 0},
{"f(x) = x^2", "g(x) = sin(x)", "f(x) = g(x)", "g(x) = x + f(x)", 0},
{"f(x) = sin(x)", "g(x) = f(x)", "f(pi/2)", 0},
{"f(x) = sin(x) + x", "g(x) = f(x)", "f(pi/2)", 0},
{"f(x) = x^2", "g(x) = f(x + 1)", 0},
{"f(x) = x + x", "g(x) = f(x)", "f(x) = g(x)", "f(1)", 0},
{"f(x) = (x + 1)^2", "f(1)", "g(X) = f(X - 1)", "g(0)", 0},
{"f(x) = x^2 + x + 1", "f(i)", 0},
{"f(x) = sin(x) + x^10", "f(pi)", 0},
{"P(z) = z^7 + 5*z^3 + 1", "P(i)", 0},
{"tan(0)", 0},
{"f(x) = sqrt(x)", "f(2)", 0},
{"f(x) = sin(sqrt(4)*pi)", "f(pi)", 0},
{"f(x) = sin(sqrt(x)*pi)", "f(4)", 0},
{"f(x) = abs(sin(x))", "f(pi/2)", "f(-pi/2)", 0},
{"f(x) = ln(e)", 0},
{"f(x) = ln(1)", 0},
{"ln(1)", "ln(e)", "ln(e^10)", 0},
{"log(2)", "log(512)", "log(2048)", 0},
{"f(x) = exp(x)", "g(x) = ln(x)", "w(x) = f(g(x))", "w(1)", "w(e)", 0},
{"ln(--1)", 0},
{0}};

const char *valid_matrix_strings[] = {"[[0]]", "[[0,1]]", "[[-1,10]]",
"[[99];[-99]]", "[[-1,-2];[-9.1,-1.99]]", "[[pi]]", "[[-pi];[-i];[0.0]]",
"[[cos(pi/2),-sin(pi/2)]]", 0};

const char *valid_matrix_sequences[][SEQUENCE_LENGTH] = {{"[[0]]", 0},
{"[[1,0];[0,1]]", 0},
{"x = [[0]]", 0},
{"a = 1", "[[a]]", 0},
{"a(x) = [[x]]", 0},
{"a(x) = [[sin(x)]]", 0},
{"A(x) = [[cos(x), -sin(x)];[sin(x), cos(x)]]", "A(pi/2)", 0},
{"A(x) = [[cos(x)]]", 0},
{"A(x) = [[cos(x), sin(x)]]", 0},
{"A(x) = [[cos(x)];[sin(x)]]", 0},
{"f(y) = y + 1", "g(w) = w^2", "A(x) = [[g(f(x))]]", 0},
{"[[1]] + [[1]]", 0},
{"[[1,0]] + [[0,1]]", 0},
{"[[1,0];[0,1]] + [[-1,0];[0,-1]]", 0},
{"A = [[0,0]]", 0},
{"A = [[1,0];[0,1]]", "B = A + [[1,0];[0,1]]", 0},
{"A = [[1,0];[0,1]]", "B = 2*A", 0},
{"A = [[pi, -i];[i, -pi]]", "B = [[1, 0];[0, 1]]", "A * B", 0},
{"a(x) = [[cos(x), -sin(x)];[sin(x), cos(x)]]", "a(pi/2)", "a(pi/4 + pi/4)", 0},
{"a(x) = [[cos(x), -sin(x)];[sin(x), cos(x)]]", "b(x) = a(x)", "b(pi/2)", 0},
{"a(x) = [[cos(x), -sin(x)];[sin(x), cos(x)]]", "b(x) = a(x)", "c(x) = a(x) * b(x)", "c(pi)", 0},
{"A(x) = [[x^2 + sin(x)*cos(x), 2!*sin(x^2)^2]]", 0},
{"A = [[1];[1]]", "B = [[pi, pi]]", "B * A", 0},
{"A = [[1,0];[0,1]]", "b = [[1];[1]]", "A * b", 0},
{"A = [[1,0];[0,1]]", "B = [[pi,pi];[pi,pi]]", "A*B", 0},
{"A = [[1,1];[1,0]]", "A^20", 0}, //22nd fib number
{"A = [[1,1];[1,0]]", "A^20*[[1];[0]]", 0},
{"A = [[1]]", "f(x) = x + x", "f(A)", 0},
{"A(x) = [[sin(x)]]", "B(x) = A(x) + A(x)", "B(pi/2)", 0},
{"A(x) = [[cos(x), -sin(x)];[sin(x), cos(x)]]", "B(x) = x^2", "A(pi/2)", "B(A(pi/2))", 0},
{"A(x) = [[cos(x)];[sin(x)]]", "B(x) = [[1];[0]] + A(x + pi/2)", 0},
{"[[0,-1];[1,0]]^2", 0},
{"[[5,2,6,1];[0,6,2,0];[3,8,1,4];[1,8,5,6]]*[[7,5,8,0];[1,8,2,6];[9,4,3,8];[5,3,7,9]]", 0},
//[[96,68,69,69];[24,56,18,52];[58,95,71,92];[90,107,81,142]]
{"a = 1", "a = [[sin(pi)];[cos(pi)]]", 0},
{"a = [[1,0];[0,1]]", "a = i", "a + a", 0},
{"a = [[1,0];[0,1]]", "a(x) = x^2", "a(2)", 0},
{"A(x) = [[cos(x), -sin(x)];[sin(x), cos(x)]]", "v = A(pi/2) * A(-pi/2) * [[1];[1]]", 0},
{0}};

const char *valid_polynomial_sequences[][SEQUENCE_LENGTH] = {
{"x = 1 ?", 0},
{"1 = 1 ?", 0},
{"x = x ?", 0},
{"x^2 = 0 ?", 0},
{"x^2 + 3*x - 4 = 0 ?", 0},
{"x^2 = -1 ?", 0},
{"x^2 + 2 = 0?", 0},
{"x^2 = 0?", 0},
{"x^2 + 1=1 ?", 0},
{"q = sin(pi/2)", "y = q^2", "x^2 + 1 = y?", 0},
{"x^2 - 2 = 0?", 0},
{"f(x) = x^2 - 1", "f(x) = 0?", 0},
{"x^2 - x - 1 = 0?", 0},
{"f(x) = -x - 1", "g(x) = x^2", "h(x) = f(x) + g(x)", "h(x) = 0?", 0},
{"x = x?", 0},
{"1 = 0?", 0},
{"2x + 3x^2 = 0?", 0},
{"2*x + 3*x^2 = 0?", 0},
{"-999999999999999999999999999999999999999999999999999999x = x^2?", 0},
{"x^99999999999999999999999999 = -1?", 0},
{"-X^2 = 0?", 0},
{"x^2 - x^1 = 0?", 0},
{"0 = 5 * 5?", 0},
{"1 = 1?", 0},
{"1 = 3?", 0},
{"x = x?", 0},
{"-1x = 0?", 0},
{"x = 0?", 0},
{"a = -a?", 0},
{"K^1 = -99?", 0},
{"x + -x = -1?", 0},
{"x + x^2 + x^2 = -1?", 0},
{"7 = 0?", 0},
{"pi*x^2 - pi*x = 0?", 0},
{"PI*x^2 - PI = 0?", 0},
{"x--x=0?", 0},
{"---5=5?", 0},
{"0 = 0.99999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999x^1?", 0},
{"x + -x = -1?", 0},
{"x + x^3 + x^2 = -1?", 0},
{"7 = 0?", 0},
{"-7 = 0?", 0},
{"0 = -3.9999999999999999999999999999999999999999x^1?", 0},
{"a^0 = -1?", 0},
{"5 * X^0 = 5 * X^0?", 0},
{"4 * X^0 = 8 * X^0?", 0},
{"5 * X^0 = 4 * X^0 + 7 * X^1?", 0},
{"1x - x = -1x?", 0},
{"5 * X^0 + 13 * X^1 + 3 * X^2 = 1 * X^0 + 1 * X^1?", 0},
{"5 + 13 * x + 3x^2 = 1 + x ?", 0},
{"  -x = 3.1  ?", 0},
{"5 * X^0 + 13 * X^1 + 3 * X^2 = 1 * X^0 + 1 * X^1?", 0},
{"-1 - 5 = 0?", 0},
{"6 * X^0 + 11 * X^1 + 5 * X^2 = 1 * X^0 + 1 * X^1?", 0},
{"5 * X^0 + 3 * X^1 + 3 * X^2 = 1 * X^0 + 0 * X^1?", 0},
{"0.000001 = x?", 0},
{"x = 0.0000000000000000000000000000000000001?", 0},
{"-0.1 = x?", 0},
{"-x = 9999999.99999999999999999999999999?", 0},
{"0 + 0 = 0 * x + 0 * x^10?", 0},
{"-13.5203 + 6.533X^2 - 3.64131X^3 = 0?", 0},
{"-0.0000220921 + 11.4785X^2 = 0?", 0},
{"-9.1 - 8.77x + 4x^3 = 0?", 0},
{"c^2 - c^2 + c^2 + c^2 + 1.14124c^2 = -1?", 0},
{"5x^3 + 4x^2 + 2x + 2 = 0?", 0},
{"x^3 = 27?", 0},
{"x^3 = 99999999999999999999999999999?", 0},
{"x^3 - 6x^2 + 11x - 6 = 0?", 0},
{"x^3 - 3 * x^2 + 3 * x - 1 = 0?", 0},
{"a^3 - 5a^2 - 2a + 24 = 0?", 0},
{"0 = X^3 + 4 * X^2 + X - 5?", 0},
{"x^3 - 3x^2 - x + 1 = 0?", 0},
// {"-13.2593 + 6.48091X - 8.58475X^2 + 0.0000267855X^3 = 0?", 0}, /////
{"9999999 + 9999999999x + 99999999x^2 = 0?", 0},
{"999 + 999x + 999x^2 = 0?", 0},
{"9999999 + 9999999999x + 99999999x^2 + 9999999 * x^3 = 0?", 0},
{"-13.5203 + 6.533X^2 - 3.64131X^3 = 0?", 0},
{"-1 + x^3 + x^2 = x^3 + x^3?", 0},
{"A^3 = -1?", 0},
{"-x = 0.0001x^3?", 0},
{"-1 - -1 = C^3?", 0},
{"0 = x^2?", 0},
{"x^3 = 0?", 0},
{"2 * X^3 = 0?", 0},
{"-0x^0 = 0?", 0},
{"-0 = x?", 0},
{"0 = 0 * x + -0?", 0},
{"x + -0 * x = -0?", 0},
// {"-13.2593 + 6.48091X - 8.58475X^2 + 0.0000267855X^3 = 0?", 0}, ////
{"37.7801 + 58.1269X - 50.5115X^2 - 141.452X^3 = 0?", 0},
{"-121.34 - 76.7428X + 35.6213X^2 + 37.283X^3 = 0?", 0},
{"76.7264 + 83.6769X^2 - 21.1039X^3 = 0?", 0},
{"-13.5203 + 6.533X^2 - 3.64131X^3 = 0?", 0},
{"-150281 - 308387X - 962354X^2 = 0?", 0},
{"-0.00000220921 + 11.4785X^2 = 0?", 0},
{"99999999999999999999999999999x^3 - 1 = 0?", 0},
{"0 = X^3 - 3 * X^2 + 4 * X - 2?", 0},
{"x^3 - 3x^2 + 4x - 2 = 0?", 0},
{"x^3 - 15x - 4 = 0?", 0},
{"x^3 - 3x + 1.412 = 0?", 0},
{"-1 + x^3 - x^2 + x^3 + x^3 = 0?", 0},
{"A^3 + A^3 = 125?", 0},
{"126 = 1X^3?", 0},
{"-125 = c^3?", 0},
{"2x^3 - 5x^2 - 23x - 10 = 0?", 0},
{"x^2 = 2?", 0},
{0}};

void test_statement(const char *characters)
{
    String *string;

    // string = string_new_no_space_to_lower(characters);
    string = string_new_trimmed(characters);
    print_string_n(string);

    process_input_line(string, NULL);
    string_delete(&string);
}

void test_all_statements(const char **strings)
{
    int_signed n;
    String *string;

    n = 0;
    while (strings[n])
    {
        // string = string_new_no_space_to_lower(strings[n]);
        string = string_new_trimmed(strings[n]);
        print_string_n(string);

        process_input_line(string, NULL);
        string_delete(&string);

        n ++;
    }
}

void test_sequence(const char **strings)
{
    String *string;
    VariableTable *v_table;
    int_signed n;

    n = 0;
    v_table = NULL;
    while (strings[n])
    {
        // string = string_new_no_space_to_lower(strings[n]);
        string = string_new_trimmed(strings[n]);
        print_string_n(string);

        v_table = process_input_line(string, v_table);

        string_delete(&string);
        n ++;
    }
}

void test_all_sequences(const char *array[][SEQUENCE_LENGTH])
{
    int_signed n;
    const char **sequence;

    n = 0;
    sequence = array[n];
    while (*sequence)
    {
        test_sequence(array[n]);
        printf("\n");

        n ++;
        sequence = array[n];
    }
}

void sqrt_test(real initial_value, real step, real terminal_value)
{
    real x, _x;

    while (initial_value < terminal_value)
    {
        printf("a = %Lf\n", initial_value);
        x = math_sqrt(initial_value);
        printf("my sqrt:    %.10Lf\n", x);

        _x = sqrt(initial_value);
        printf("stock sqrt: %.10Lf\n\n", _x);

        initial_value += step;
    }
}

void log_test(real initial_value, real step, real terminal_value)
{
    real x, _x;

    while (initial_value < terminal_value)
    {
        printf("a = %Lf\n", initial_value);
        x = math_ln(initial_value);
        printf("my log:    %.10Lf\n", x);

        _x = log(initial_value);
        printf("stock log: %.10Lf\n\n", _x);

        initial_value += step;
    }
}

void exp_test(real initial_value, real step, real terminal_value)
{
    real x, _x;

    while (initial_value < terminal_value)
    {
        x = math_exp(initial_value);
        _x = exp(initial_value);
        printf("a = %Lf\n", initial_value);
        printf("my exp:     %.10Lf\n", x);
        printf("stock exp:  %.10Lf\n\n", _x);

        initial_value += step;
    }
}

void math_test()
{
    real initial_value;
    real terminal_value;
    real step;

    initial_value = 0.1;
    terminal_value = __INT_MAX__;
    step = 10000;

    // sqrt_test(initial_value, step, terminal_value);
    log_test(initial_value, step, terminal_value);
}

void matrix_test()
{
    MatrixRepr *A;
    MatrixRepr *B;
    MatrixRepr *result;
    int_signed size;
    NUMBER_TYPE type;

    size = 100;
    type = NT_REAL;
    A = generate_random_matrix(size, size, type);
    B = generate_random_matrix(size, size, type);
    result = matrix_repr_mult(A, B);

    print_matrix_repr(result, NULL);

    matrix_repr_delete(&A);
    matrix_repr_delete(&B);
    matrix_repr_delete(&result);
}
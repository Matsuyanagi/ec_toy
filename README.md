# Elliptic Curve toy

## prerequire

[Botan: Crypto and TLS for Modern C++ — Botan](https://botan.randombit.net/) 3.0-alpha

Visual Studio 2022

[Boost C++ Libraries](https://www.boost.org/) 1.78.0

## command line option

./ec_toy.exe [ [ [ a ] b ] prime ]

y^2 = x^3 + a x + b (mod prime)

### output sample

`ec_toy.exe 1 1 7`

order(include inf), points, each P 2P 3P... , a/b order( [n] is prime number )

```
a = 1 , b = 1 , prime = 7
order : 5
( 0 : 1 )
( 0 : 6 )
( 2 : 2 )
( 2 : 5 )
( - : - )
5 : ( 0 : 1 )( 2 : 5 )( 2 : 2 )( 0 : 6 )( - : - )
5 : ( 0 : 6 )( 2 : 2 )( 2 : 5 )( 0 : 1 )( - : - )
5 : ( 2 : 2 )( 0 : 1 )( 0 : 6 )( 2 : 5 )( - : - )
5 : ( 2 : 5 )( 0 : 6 )( 0 : 1 )( 2 : 2 )( - : - )
1 : ( - : - )
a\b     0       1       2       3       4       5       6
0       -       12      9       [13]    [3]     [7]     4
1       8       [5]     -       6       10      -       [11]
2       8       [5]     -       6       10      -       [11]
3       8       12      9       6       10      [7]     4
4       8       [5]     -       6       10      -       [11]
5       8       12      9       6       10      [7]     4
6       8       12      9       6       10      [7]     4
```


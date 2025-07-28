# Practice Round 1 Editorial

#### *Author: AkiLotus + chocological*

## Problem A

**Statements**: Given $n$ distinct points, count the amount of non-degenerate triangles formed by any three distinct points out of $n$.

**Constraints**: $1 \le n \le 300$.

**Tags**: brute force, maths

**Solution/Idea**:

The small limit for $n$ implies an $\mathcal{O}(n^3)$ brute force solution is possible. We'll just iterate every triplet of points and see if the triangle formed by them is non-degenerate, i.e. the points are not on the same line.

One of the possible checking method is to check if the two vectors originating from one arbitrary point of the three are the same. In this context, a vector $(x, y)$ is a vector with $\gcd(x, y) = 1$ that illustrates a straight line in the Cartesian plane.

A few notes:
- Direction doesn't matter - $(-1, 1)$ and $(1, -1)$ are considered the same. To combat it, we declare that in case of non-zero $x$ and $y$, only $y$ is allowed to be negative.
- Should either $x$ or $y$ is zero, the other argument must be $1$.

## Problem B

**Statements**: Given a string $s$ and $k$ distinct strings, calculate the number of ways to use strings in those $k$ strings to form the string $s$ (each string must be used in whole, one string can be used multiple times) taken modulo $1000000007$.

**Constraints**: $|s| \le 5000$, $1 \le k \le 10^5$.

**Tags**: strings, dynamic programming, hashing

**Solution/Idea**:

If $k$ is a bit lower (maybe around $5000$ at most) then this problem could be solved not by hashing but some deterministic string matching algorithms (namely KMP and Z) as well.

This is a basic dynamic programming (DP) problem. The catch is: denote $f(i)$ as the number of ways to construct the prefix of length $i$ of $s$, our objective is to calculate $f(|s|)$ starting from $f(0) = 1$.

For each string $t$ of $k$ given strings, should the next $|t|$ letters match, we can add $f(i)$ to $f(i + |t|)$.

That's about it for the DP.

The string matching part can be solved with hashing: for each length from $1$ to $|s|$, keep a list of hash values that exist from the $k$ inputted strings. We can safely ignore any string longer than $s$, obviously.

The rolling hash function used to perform this can be freely decided. With $|s|$ being low enough, there are numerous ways to calculate all hash values for all possible substrings of $s$, since we'd need all of them for string matching during DP. Make sure to choose a proper base multiplier and modulo - rule of thumb is to choose both as prime numbers, and base multiplier should be strictly higher than the amount of possible characters in the string.

Reusing the modulo in the statements is fine, but it is recommended to use a different variable/constant for it for easier debugging.

Also, be extra careful with typecasting when doing multiplication in hashing.

Using `#define int long long` is a working way to ignore this issue, but it is very dangerous should the problem's limit grow tight. Try to avoid using unnecessary `int64`, but be sure that the multiplication actually yields `int64` when needed. For C++, the rule of thumb is that the first element would dictate the final type.

For example, `1 * BASE * hash_val` will yield an `int32`, but `1LL * BASE * hash_val` will yield an `int64`. The former can and will overflow if `BASE * hash_val` exceeds `int32` limit.

## Problem C

**Statements**: Given a string $s$, find the longest substring that starts with `A` and ends with `Z`.

**Constraints**: $|s| \le 10^5$.

**Tags**: ad-hoc, implementation

**Solution/Idea**:

A bit off-topic. ***Always*** ask the jury about things unclear in the problem. In this one, it is strongly advised to ask if the string is guaranteed to have both `A` and `Z` and there is at least one `A` standing before some `Z` (thankfully the problem covertly ensures that anyway).

The idea here is simple: the longest string will span from the first `A` to the last `Z`.

## Problem D

**Statements**: Given an array $a$ of $n$ elements. We perform coloring each and every element, so that for every two elements at indices $i$ and $j$ ($i < j$), they will have the same color if and only if $a_i < a_j$. Calculate the minimum number of colors required to color the whole array.

**Constraints**: $1 \le n \le 10^5$, $-10^9 \le a_i \le 10^9$.

**Tags**: greedy, binary search, implementation

**Solution/Idea**:

It is clear that each color has elements forming a strictly increasing sequence.

Let's iterate the array from left to right. For every new element, ignoring the trivial case of it being smaller than every previous elements (resulting in a new color), if it has many choices for its color, it's always preferable to pick the one with the latest element being the largest. Proof for this greedy observation is left as an exercise for the reader.

## Problem E

**Statements**: Alice and Bob has $n$ stones and they will play a game: Alice goes first, for each turn the player can take a number of stones between $[1, 2k]$, with $k$ being infinite for the first turn (i.e. Alice's turn $1$) or the number of stones taken in the last turn; whoever takes the last stone wins. Given $n$, find the minimum number of stones Alice must take in the first turn so that she will surely win the game (a.k.a. assuming both play optimally onwards).

**Constraints**: $1 \le n \le 10^{15}$.

**Tags**: maths, games

**Solution/Idea**:

It's not solved yet. One idea that's still certain to be correct, however, will be showed below.

First off, strongly recommend that you've read about Nim games and Grundy numbers beforehands. If not, please do so or skip this problem for now.

If we cannot ever take the entirety of the stones in a turn, then assuming the state of $n'$ stones remaining, it's always unwise to take at least $\frac{n'}{3}$, since it'll open the window for the opponent to take the rest and win. This is the basis to construct the Grundy numbers for every $n$, with it being $0$ for $0 \le n \le 3$, and $1$ for $n = 4$, the rest will be calculated.

We can see a few recurring patterns: the Grundy number for any $n = 3x + 1$ is $x$, and after every $0$ will be a repeat from the first non-zero Grundy number following its previous $0$ to it itself, taken lower priority than $n = 3x + 1$ (see `draft.txt`).

Then, it's easy to construct a list of valid $n$ with Grundy numbers being $0$. Then, it should be simply checking if the given $n$ is of a losing game (that Alice must take all $n$ in the first turn), or not (that Alice will take the amount to lower $n$ to the nearest $0$).

I have no idea why my solution gave WA though. At least I'm certain it's not fully incorrect (tested towards $n = 109$).

## Problem F

**Statements**: Calculate $\gcd(a, b)$.

**Constraints**: $1 \le a \le 10^{12}$, $1 \le b \le 10^{200}$.

**Tags**: maths, strings, implementation

**Solution/Idea**:

For Python users: free dinner. Do what you want.

For C++ users: slow down. You see that limit for $b$? Yes.

Though, since we all know how to calculate GCD using Euler's algorithm, we do know $\gcd(a, b) = \gcd(a, b \mod a)$. So we will calculate just that - it should be an easy iteration through the string that denotes $b$. Then, the rest is trivial.

## Problem G

**Statements**: Given an array $a$ of $n$ elements and a positive integer $m$. We are given that $0 \le a_i \le m-1$. We can do any number of operations, each consists of picking an arbitrary number of indices $i$, and set $a_i$ to $(a_i + 1) \mod m$. Calculate the minimum number of operations to make the array non-decreasing.

**Constraints**: $1 \le n \le 10^5$, $1 \le m \le 10^9$.

**Tags**: binary search

**Solution/Idea**:

The nature of this operation can rephrase the problem into this: create an array $b$ of $n$ elements and then for each $1 \le i \le n$, set $a_i$ to $(a_i + b_i) \mod m$, find the minimum $\max(b)$ that satisfies the non-decreasing criteria for final $a$.

Obviously, if a smaller value works, a larger value will also work. This means, we can binary search the answer in the range $[0, m-1]$.

For each value $x$ in question, we'll check if a non-decreasing final array is possible. Iterate through array $a$, and for each element $a_i$, inspect the possible value range (a.k.a. using at most $x$ additions on it), and pick the smallest element that ensures the non-decreasing properties as of the prefix up to $a_i$.

$x$ will be considered invalid if at anytime during the iteration, an element cannot be picked - this can only happen when the value range is a continuous one (not latching from $m-1$ to $0$) and the previous smallest element is beyond the upper bound.

## Problem H

**Statements**: There are two numbers $a$ and $b$. We can do any number of operations, the $i^{th}$ operation is adding $i$ to either number. Calculate the minimum number of operations required to make two numbers equal.

**Constraints**: $1 \le a, b \le 10^9$.

**Tags**: maths, number theory

**Solution/Idea**:

We have a key lemma to solve this problem: given a number $k$ and a number $s$ so that $1 \le s \le \frac{k(k+1)}{2} - 1$, it is always possible to partition the set of natural numbers from $1$ to $k$ into two disjoint sets such that one has the sum of elements being $s$. Proof is left as an exercise for the reader.

With that out of the way, we'd just need to find the smallest $k$ such that $\min(a, b) + \frac{k(k+1)}{2} \ge \max(a, b)$ (at least if tossing all numbers to the lower side, it should not be still lower) and $a + b + \frac{k(k+1)}{2}$ is an even number (so that the final numbers can actually be equal).

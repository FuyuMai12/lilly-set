# ICPC PTIT 2025 Qualifier Editorial

#### *Author: AkiLotus + chocological feat. kokokuro*

## Problem A

**Statements**: Given an array $a$ of $n$ elements. We define $a_p$ as an average element if there exists three pairwise-distinct indices $i$, $j$, and $k$ such as $a_p = \frac{1}{3} (a_i + a_j + a_k)$. Count the number of indices $p$ satisfying that $a_p$ being an average element.

**Constraints**: $1 \le n \le 1000$, $1 \le a_i \le 10^9$.

**Tags**: brute force, maths

**Solution/Idea**:

An $\mathcal{O}(n^3)$ brute force solution is not possible. However, an optimized one of $\mathcal{O}(n^2 \log n)$ is possible, with some maths taken into account.

We can brute force all $(i, j)$ index pair to get all $a_i + a_j$ sums. Store the sums and the indices that form them. The latter part should be done in a way to keep only the index that is ***strictly*** required for that sum to exist. Namely: we'll only store at most two indices of the first pair that forms the sum in question, and gradually remove them if they don't appear in subsequent index pairs (if having any).

Now, iterate all index $p$. For each, we iterate index $k$, and now we are seeking $a_i + a_j = 3 a_p - a_k$. If the sum exists and the required index doesn't include $k$, then $p$ is a valid index for an average element.

Both processes have $\mathcal{O}(n^2)$ complexity. The extra log is there due to the use of AVL/RBTree map to store the sum (could be reduce to high-coefficient $\mathcal{O}(1) if utilizing hash tables).

## Problem B

**Statements**: Given an array $a$ of $n$ elements and an integer $m$. List all integers $k$ ($1 \le k \le m$) such that $k$ is coprime with every element of array $a$.

**Constraints**: $1 \le n, m, a_i \le 10^5$.

**Tags**: number theory

**Solution/Idea**:

It is shown that we can easily list all prime divisors that appear in any element in array $a$. Store them in a list.

Now, perform a sieve in range $[1, m]$ using just the primes found above. The elements not being punched out will be the ones listed in the answer.

Time complexity: $\mathcal{O}(n \log \log a_i)$.

## Problem C

**Statements**: Given an array $a$ of $n$ elements. Calculate the sum of all $|a_i - a_j|$ among all $(i, j)$ index pair.

**Constraints**: $2 \le n \le 2 \cdot 10^5, -10^9 \le a_i \le 10^9$.

**Tags**: maths, sorting

**Solution/Idea**:

Sort array $a$ in increasing order. We'll see that for each element $a_i$, it will contribute, using elements before it in the array, the amount equals to $a_i \times (i - 1)$ minus sums of all elements before it. This is the key to accumulate the answer for this problem.

## Problem D

**Statements**: Given a string $s$ of length $n$. Count the number of index pair $(i, j)$ such that if removing either $s_i$ or $s_j$, the resulting string is the same.

**Constraints**: $2 \le n \le 3 \cdot 10^5$.

**Tags**: strings, maths

**Solution/Idea**:

Any valid index pair $(i, j)$ must have $s_i = s_j$ and all the characters between them being the same as them.

Thus, a two-pointer approach can be used to iterate each "cluster" of characters - group of the same characters spanning consecutively as long as possible. A "cluster" of size $k$ contributes $\frac{k(k-1)}{2}$ index pairs into the final answer.

## Problem E

**Statements**: Given a tree of $n$ vertices. We can add exactly one extra edge to the tree - find the minimum sum of shortest paths between all vertex pairs in the graph after that addition.

**Constraints**: $1 \le n \le 300$.

**Tags**: graphs, trees

**Solution/Idea**:

It's not solved yet. No idea either.

## Problem F

**Statements**: A number is called near-palindrome if you could make at most one change in one digit and its decimal notation would be a palindrome. Count the number of near-palindromes in range $[A, B]$.

**Constraints**: $1 \le A \le B \le 10^6$, multitest problem.

**Tags**: maths, strings, brute force, binary search

**Solution/Idea**:

The multitest requirements make us prefer to just outright list all near-palindromes in range $[1, 10^6]$, then calculate how many near-palindromes in range $[1, x]$ for all $x$ - we'll call this $f(x)$.

Then, for each test, calculate $f(B) - f(A-1)$.

## Problem G

**Statements**: Given a chessboard of size $n \times m$ and $k$ obstacles in $k$ distinct cells, with a rook at cell $(1, 1)$. This rook can move straight horizontally or vertically at any length, but cannot touch or surpass an obstacle if it's in the way. Count the number of distinct cells it could reach in no more than $2$ moves.

**Constraints**: $1 \le n, m \le 2 \cdot 10^5$, $0 \le k \le 2 cdot 10^5$.

**Tags**: ad-hoc, data structures, maths

**Solution/Idea**:

I really don't want to write editorial for this problem. It's an implementation hell with multiple pitfalls.

The core idea is that it's easy to count distinctively for if the first move is horizontal and if the first move is vertical. The hard part is to subtract the intersection of the two cases. This involves a lot of spanning observations.

A segment tree is required for the counting.

Be extra careful about multiple pitfalls. One of the most obnoxious ones being obstacles at row $1$ and/or column $1$.

## Problem H

**Statements**: Given a string $s$, partition it into the minimal amount of substrings $n$ ($s_1 + s_2 + \ldots + s_n = s$) such that each $s_i$ can be permuted to be a palindrome.

**Constraints**: $1 \le |s| \le 10^5$.

**Tags**: strings, dynamic programming, bitmasks

**Solution/Idea**:

This is a bitmask-DP, but also not. If we consider a character (we only have 26 in this problems as in 26 letters in the English alphabet) as a bit in a number, a string's permuted-palindrome status can be mapped into a bitmask with each bit being a XOR operation on that mask. It will be valid if the mask is a power of two.

Consider $dp_i$ as the minimal number of substrings to partition the prefix of $i$ characters of $s$. Surely, $dp_0 = 0$, and our target is $dp_n$.

Traverse through all prefixes of $s$ and consider their masks. With each mask, check if it could be XOR'd with any known prefix to become a power of two - iterate all possible power of two and check, then update the dynamic programming value accordingly if found any. For easy lookup, the prefix mask values can be stored in an AVL/RBTree map.

Time complexity: $\mathcal{O}(26 |s| \log |s|)$

## Problem I

**Statements**: An integer $n$ will have $f(n)$ positive divisors. Given an integer $X$, find the smallest $n$ such as $n^{f(n)} = X$.

**Constraints**: $1 \le X \le 10^{18}$.

**Tags**: maths, number theory, binary search

**Solution/Idea**:

If $f(n) = 1$, the only possible $X$ for a correct answer would be $1$.

Otherwise, the problem can be bruteforced with $f(n)$ from $60$ down to $2$. Be extra careful when taking roots of numbers to find corresponding $n$ - it is strongly advised to use binary search other than real number manipulation to maintain accuracy.

## Problem J

**Statements**: Given a tree of $n$ vertices and a string $s$ consisting of only bracket characters (open/close for normal/square/curly brackets) that its indices correspond to the tree's vertices, count the number of paths such that the bracket sequence made by that path is a proper bracket sequence.

**Constraints**: $1 \le n \le 5000$.

**Tags**: graphs, trees, strings, data structures

**Solution/Idea**:

No clear solution so far. Though, the small $n$ likely implies a brute force solution.

## Problem K

**Statements**: Given an empty array and $q$ queries, each query contains two integers $l$ and $r$ and will append the sequence $l, l+1, \ldots, r$ to the end of the array. Calculate the length of the longest increasing subsequence of the final array.

**Constraints**: $1 \le q \le 2 \cdot 10^5$, $1 \le l \le r \le 10^9$.

**Tags**: data structures?

**Solution/Idea**:

No clear solution so far.

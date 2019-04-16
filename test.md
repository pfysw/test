$$
  \begin{pmatrix}
  1 & a_1 & a_1^2 & \cdots & a_1^n\\
  1 & a_2 & a_2^2 & \cdots & a_2^n \\
  \vdots & \vdots & \ddots & \vdots \\  
  1 & a_n & a_n^2 & \cdots & a_n^n  \\
  \end{pmatrix}
$$


$$
f(n) =
\begin{cases}
n/2,  & \text{if $n$ is even} \\
3n+1, & \text{if $n$ is odd}
\end{cases}
$$

$$
f(n) =
\begin{cases}
\frac{n}{2},  & \text{if $n$ is even} \\[2ex]
3n+1, & \text{if $n$ is odd}
\end{cases}
$$

$$
\begin{aligned}
&
\begin{pmatrix}
1 & 2 &  3&4  &5 \\ 
 2&  3& 4 & 5 & 1
\end{pmatrix}\cdot 
\begin{pmatrix}
1 & 2 &  3&4  &5 \\ 
 3& 4& 1 & 2 &5
\end{pmatrix} \\
=& \begin{pmatrix}
1 & 2 &  3&4  &5 \\ 
 3& 4& 1 & 2 &5
\end{pmatrix}\circ\begin{pmatrix}
1 & 2 &  3&4  &5 \\ 
 2&  3& 4 & 5 & 1
\end{pmatrix}\\
=&\begin{pmatrix}
1 & 2 &  3&4  &5 \\ 
 4&  5& 2 & 3 & 1
\end{pmatrix} 
\end{aligned} \tag{1}
$$
# SurfacePolynomialFitting
N-order polynomial surface fitting with Eigen (Least squares). Usage: 

## Usage

```
git clone -b main --recursive https://github.com/nescirem/SurfacePolynomialFitting.git 
cd SurfacePolynomialFitting
mkdir build && cd build
cmake ..
make
```

Execute`./SPF ${N}`，N can be any natural number.

* N=2

$$
f(x,y) = C_{00}+C_{01}y+C_{02}y^2+C_{10}x+C_{11}xy+C_{20}x^2
$$

$$
\mathbf{C} = \begin{bmatrix} C_{00} & C_{10} & C_{20} \\\ C_{01} & C_{11} & C_{21} \\\ C_{02} & C_{12} & C_{22} \end{bmatrix}
$$

![image-20231209230316793](media/image-20231209230316793.png)

* N=3

$$
f(x,y) = C_{00}+C_{01}y+C_{02}y^2+C_{03}y^3+C_{10}x+C_{11}xy+C_{12}xy^2+C_{20}x^2+C_{21}x^2y+C_{30}x^3
$$

$$
\mathbf{C} = \begin{bmatrix} C_{00} & C_{10} & C_{20} & C_{30} \\\ C_{01} & C_{11} & C_{21} & C_{31} \\\ C_{02} & C_{12} & C_{22} & C_{32} \\\ C_{03} & C_{13} & C_{23} & C_{33} \end{bmatrix}
$$

![image-20231209231735500](media/image-20231209231735500.png)

* N=4

$$
f(x,y) = C_{00}+C_{01}y+C_{02}y^2+C_{03}y^3+C_{04}y^4+C_{10}x+C_{11}xy+C_{12}xy^2+C_{13}xy^3+C_{20}x^2+C_{21}x^2y+C_{22}x^2y^2+C_{30}x^3+C_{31}x^3y+C_{40}x^4
$$

$$
\mathbf{C} = \begin{bmatrix} C_{00} & C_{10} & C_{20} & C_{30} & C_{40} \\\ C_{01} & C_{11} & C_{21} & C_{31} & C_{41} \\\ C_{02} & C_{12} & C_{22} & C_{32} & C_{42} \\\ C_{03} & C_{13} & C_{23} & C_{33} & C_{43} \\\ C_{04} & C_{14} & C_{24} & C_{34} & C_{44} \end{bmatrix}
$$

![image-20231210003916311](media/image-20231210003916311.png)

---------------

![image-20231209232155304](media/image-20231209232155304.png)

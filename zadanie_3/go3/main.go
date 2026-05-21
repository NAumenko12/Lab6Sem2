package main

import (
	"fmt"
	"math"
)

const razmer = 4

func main() {
	var m, nPar, p, eps float64

	fmt.Print("Vvedite M: ")
	fmt.Scan(&m)
	fmt.Print("Vvedite N: ")
	fmt.Scan(&nPar)
	fmt.Print("Vvedite P: ")
	fmt.Scan(&p)
	fmt.Print("Vvedite epsilon: ")
	fmt.Scan(&eps)
	a := createMatrix(razmer)
	iterA := createMatrix(razmer)
	b := createMassive(razmer)
	iterB := createMassive(razmer)
	x := createMassive(razmer)
	zapolnitSistem(a, b, m, nPar, p)
	copySistem(a, b, iterA, iterB)
	fmt.Println("\nIshodnaya sistema:")
	printSistem(a, b)
	gauss(a, b, x)
	simpleIteration(iterA, iterB, eps)
}

func createMatrix(n int) [][]float64 {
	a := make([][]float64, n)
	for i := 0; i < n; i++ {
		a[i] = make([]float64, n)
	}
	return a
}

func createMassive(n int) []float64 {
	return make([]float64, n)
}

func zapolnitSistem(a [][]float64, b []float64, m, nPar, p float64) {
	koef := [razmer][razmer]float64{
		{m, -0.04, 0.21, -1.16},
		{0.25, -1.23, nPar, -0.09},
		{-0.21, nPar, 0.8, -0.13},
		{0.15, -1.31, 0.06, p},
	}
	svob := [razmer]float64{-1.24, p, 2.56, m}

	for i := 0; i < razmer; i++ {
		for j := 0; j < razmer; j++ {
			a[i][j] = koef[i][j]
		}
		b[i] = svob[i]
	}
}

func printSistem(a [][]float64, b []float64) {
	for i := 0; i < len(a); i++ {
		for j := 0; j < len(a[i]); j++ {
			fmt.Printf("%12.6f ", a[i][j])
		}
		fmt.Printf(" | %12.6f\n", b[i])
	}
}

func printKorni(x []float64) {
	for i := 0; i < len(x); i++ {
		fmt.Printf("x%d = %.6f\n", i+1, x[i])
	}
}

func copySistem(fromA [][]float64, fromB []float64, toA [][]float64, toB []float64) {
	for i := 0; i < len(fromA); i++ {
		copy(toA[i], fromA[i])
	}
	copy(toB, fromB)
}

func findGlavStroku(a [][]float64, k int) int {
	maxStr := k
	for i := k + 1; i < len(a); i++ {
		if math.Abs(a[i][k]) > math.Abs(a[maxStr][k]) {
			maxStr = i
		}
	}
	return maxStr
}

func swapStroki(a [][]float64, b []float64, str1, str2 int) {
	a[str1], a[str2] = a[str2], a[str1]
	b[str1], b[str2] = b[str2], b[str1]
}

func pryamoiHod(a [][]float64, b []float64) float64 {
	per := 0
	det := 1.0
	fmt.Println("\n Pryamoi hod")
	for k := 0; k < len(a)-1; k++ {
		maxStr := findGlavStroku(a, k)
		if maxStr != k {
			swapStroki(a, b, k, maxStr)
			per++
		}
		for i := k + 1; i < len(a); i++ {
			q := a[i][k] / a[k][k]
			for j := k; j < len(a); j++ {
				a[i][j] -= q * a[k][j]
			}
			b[i] -= q * b[k]
		}
		fmt.Printf("\n Posle shaga %d:\n", k+1)
		printSistem(a, b)
	}
	for i := 0; i < len(a); i++ {
		det *= a[i][i]
	}
	if per%2 != 0 {
		det = -det
	}
	return det
}

func obratniyHod(a [][]float64, b []float64, x []float64) {
	fmt.Println("\n Obratniy hod")
	for i := len(a) - 1; i >= 0; i-- {
		sum := 0.0
		for j := i + 1; j < len(a); j++ {
			sum += a[i][j] * x[j]
		}
		x[i] = (b[i] - sum) / a[i][i]
		fmt.Printf("x%d = %.6f\n", i+1, x[i])
	}
}

func gauss(a [][]float64, b []float64, x []float64) {
	det := pryamoiHod(a, b)
	obratniyHod(a, b, x)
	fmt.Println("\nReshenie sistemy")
	printKorni(x)
	fmt.Printf("\nOpredelitel %.6f\n", det)
}

func rowQ(a [][]float64, row int, diagCol int) float64 {
	if math.Abs(a[row][diagCol]) < 1e-12 {
		return 1e100
	}
	sum := 0.0
	for j := 0; j < len(a); j++ {
		if j != diagCol {
			sum += math.Abs(a[row][j] / a[row][diagCol])
		}
	}
	return sum
}

func findBestPermutationRec(a [][]float64, col int, perm []int, used []int, bestPerm []int, bestQ *float64) {
	n := len(a)
	if col == n {
		q := 0.0
		for i := 0; i < n; i++ {
			current := rowQ(a, perm[i], i)
			if current > q {
				q = current
			}
		}
		if q < *bestQ {
			*bestQ = q
			copy(bestPerm, perm)
		}
		return
	}
	for row := 0; row < n; row++ {
		if used[row] == 0 {
			used[row] = 1
			perm[col] = row
			findBestPermutationRec(a, col+1, perm, used, bestPerm, bestQ)
			used[row] = 0
		}
	}
}

func findBestPermutation(a [][]float64) ([]int, float64) {
	n := len(a)
	perm := make([]int, n)
	used := make([]int, n)
	bestPerm := make([]int, n)
	for i := 0; i < n; i++ {
		bestPerm[i] = i
	}
	bestQ := 1e100
	findBestPermutationRec(a, 0, perm, used, bestPerm, &bestQ)
	return bestPerm, bestQ
}

func makeCanonical(a [][]float64, b []float64, perm []int) ([][]float64, []float64) {
	n := len(a)
	c := createMatrix(n)
	f := createMassive(n)
	for i := 0; i < n; i++ {
		row := perm[i]
		f[i] = b[row] / a[row][i]
		for j := 0; j < n; j++ {
			if i == j {
				c[i][j] = 0.0
			} else {
				c[i][j] = -a[row][j] / a[row][i]
			}
		}
	}
	return c, f
}

func normMatrix(c [][]float64) float64 {
	q := 0.0
	for i := 0; i < len(c); i++ {
		sum := 0.0
		for j := 0; j < len(c[i]); j++ {
			sum += math.Abs(c[i][j])
		}
		if sum > q {
			q = sum
		}
	}
	return q
}

func maxRaznost(x1 []float64, x2 []float64) float64 {
	maxDiff := 0.0
	for i := 0; i < len(x1); i++ {
		diff := math.Abs(x1[i] - x2[i])
		if diff > maxDiff {
			maxDiff = diff
		}
	}
	return maxDiff
}

func printCanonical(c [][]float64, f []float64) {
	fmt.Println("\nKanonicheskiy vid x = Cx + f")
	fmt.Println("Matrica C:")
	printSistem(c, f)
}

func printIterationHeader(n int) {
	fmt.Println("\nTablica iteraciy:")
	fmt.Printf("%6s", "N")
	for i := 0; i < n; i++ {
		fmt.Printf("%14s", fmt.Sprintf("X%d", i+1))
	}
	fmt.Printf("%16s\n", "eps_n")
}

func simpleIteration(a [][]float64, b []float64, eps float64) {
	fmt.Println("\nMetod prostoy iteracii")
	perm, _ := findBestPermutation(a)
	c, f := makeCanonical(a, b, perm)
	q := normMatrix(c)
	printCanonical(c, f)
	fmt.Printf("\nNorma C = %.6f\n", q)
	if q < 1.0 {
		fmt.Println("Uslovie shodimosti vipolneno: ||C|| < 1")
	} else {
		fmt.Println("Uslovie shodimosti ne vipolneno: ||C|| >= 1")
		fmt.Println("Iteracii mogut ne shoditsya dlya vibrannih parametrov.")
	}
	xOld := createMassive(len(a))
	xNew := createMassive(len(a))
	copy(xOld, f)
	printIterationHeader(len(a))
	fmt.Printf("%6d", 0)
	for i := 0; i < len(xOld); i++ {
		fmt.Printf("%14.6f", xOld[i])
	}
	fmt.Printf("%16s\n", "-")
	k := 0
	pogreshnost := eps + 1.0
	const maxIterations = 1000
	for pogreshnost > eps && k < maxIterations {
		for i := 0; i < len(a); i++ {
			sum := f[i]
			for j := 0; j < len(a); j++ {
				sum += c[i][j] * xOld[j]
			}
			xNew[i] = sum
		}
		pogreshnost = maxRaznost(xNew, xOld)
		k++
		fmt.Printf("%6d", k)
		for i := 0; i < len(xNew); i++ {
			fmt.Printf("%14.6f", xNew[i])
		}
		fmt.Printf("%16.6f\n", pogreshnost)
		copy(xOld, xNew)
	}
	fmt.Println("\nReshenie metodom prostoy iteracii")
	printKorni(xOld)
	fmt.Println("Kolichestvo iteraciy:", k)
	if k == maxIterations && pogreshnost > eps {
		fmt.Println("Dostignut predel iteraciy, trebuemaya tochnost ne poluchena.")
	}
}

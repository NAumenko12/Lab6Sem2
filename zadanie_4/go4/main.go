package main

import (
	"fmt"
	"math"
)

func main() {
	var n, m int
	fmt.Print("Введите N: ")
	fmt.Scan(&n)
	fmt.Print("Введите M: ")
	fmt.Scan(&m)
	matrix := createMatrix(n, m)
	fmt.Println("Введите матрицу из 0 и 1:")
	inputMatrix(matrix, n, m)
	fmt.Println()
	fmt.Println("Исходная матрица:")
	printMatrix(matrix, n, m)
	result := minMovesToHalf(matrix, n, m)
	if result >= INF {
		fmt.Println("Получить нужный рисунок невозможно")
	} else {
		fmt.Println("Результат:", result)
	}
}

const INF = 1000000

func createMatrix(n, m int) [][]int {
	matrix := make([][]int, n)
	for i := 0; i < n; i++ {
		matrix[i] = make([]int, m)
	}
	return matrix
}

func inputMatrix(matrix [][]int, n, m int) {
	for i := 0; i < n; i++ {
		for j := 0; j < m; j++ {
			fmt.Scan(&matrix[i][j])
		}
	}
}

func printMatrix(matrix [][]int, n, m int) {
	for i := 0; i < n; i++ {
		for j := 0; j < m; j++ {
			fmt.Print(matrix[i][j], " ")
		}
		fmt.Println()
	}
}

func distanceCells(a, b []int) int {
	return int(math.Abs(float64(a[0]-b[0])) + math.Abs(float64(a[1]-b[1])))
}

func findMinPairing(cells [][]int, used []bool) int {
	first := -1
	for i := 0; i < len(cells); i++ {
		if !used[i] {
			first = i
			break
		}
	}
	if first == -1 {
		return 0
	}
	used[first] = true
	best := INF
	for i := 0; i < len(cells); i++ {
		if !used[i] {
			used[i] = true
			current := distanceCells(cells[first], cells[i]) +
				findMinPairing(cells, used)
			if current < best {
				best = current
			}
			used[i] = false
		}
	}
	used[first] = false
	return best
}

func minMovesForVariant(matrix [][]int, n, m, topValue int) int {
	cells := make([][]int, 0)
	bottomValue := 1 - topValue
	for i := 0; i < n; i++ {
		for j := 0; j < m; j++ {
			need := 0
			if i < n/2 {
				need = topValue
			} else {
				need = bottomValue
			}
			if matrix[i][j] != need {
				cells = append(cells, []int{i, j})
			}
		}
	}
	if len(cells)%2 != 0 {
		return INF
	}
	used := make([]bool, len(cells))
	return findMinPairing(cells, used)
}

func minMovesToHalf(matrix [][]int, n, m int) int {
	result1 := minMovesForVariant(matrix, n, m, 0)
	result2 := minMovesForVariant(matrix, n, m, 1)
	if result1 < result2 {
		return result1
	}
	return result2
}

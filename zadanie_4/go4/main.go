package main

import "fmt"

func main() {
	var n, m int

	fmt.Print("Введите N ")
	fmt.Scan(&n)
	fmt.Print("Введите M ")
	fmt.Scan(&m)

	a := createMatrix(n, m)

	fmt.Println("Введите матрицу из 0 и 1:")
	zapolnitMatrix(a)

	fmt.Println("\nИсходная матрица")
	printMatrix(a)

	verh := findBestVerh(a)
	fmt.Println("Результат:", minHodovDoPolovini(a))
	fmt.Println("Итоговая матрица:")
	printItogMatrix(n, m, verh)
}

func createMatrix(n, m int) [][]int {
	a := make([][]int, n)
	for i := 0; i < n; i++ {
		a[i] = make([]int, m)
	}
	return a
}

func zapolnitMatrix(a [][]int) {
	for i := 0; i < len(a); i++ {
		for j := 0; j < len(a[i]); j++ {
			fmt.Scan(&a[i][j])
		}
	}
}

func printMatrix(a [][]int) {
	for i := 0; i < len(a); i++ {
		for j := 0; j < len(a[i]); j++ {
			fmt.Print(a[i][j], " ")
		}
		fmt.Println()
	}
}

func rastMinHodov(stroka1, stolb1, stroka2, stolb2 int) int {
	raznostStrok := stroka1 - stroka2
	raznostStolb := stolb1 - stolb2

	if raznostStrok < 0 {
		raznostStrok = -raznostStrok
	}
	if raznostStolb < 0 {
		raznostStolb = -raznostStolb
	}

	return raznostStrok + raznostStolb
}

func findNepravilnieKletki(a [][]int, verh int) ([]int, []int) {
	n := len(a)
	m := len(a[0])
	niz := 1 - verh
	stroki := make([]int, 0, n*m)
	stolbci := make([]int, 0, n*m)

	for i := 0; i < n; i++ {
		for j := 0; j < m; j++ {
			nado := niz
			if i < n/2 {
				nado = verh
			}
			if a[i][j] != nado {
				stroki = append(stroki, i)
				stolbci = append(stolbci, j)
			}
		}
	}

	return stroki, stolbci
}

func findFirstFalseEl(used []int) int {
	indOfEl := -1
	for i := 0; i < len(used); i++ {
		if used[i] == 0 && indOfEl == -1 {
			indOfEl = i
		}
	}
	return indOfEl
}

func podborPar(stroki, stolbci, used []int) int {
	first := findFirstFalseEl(used)
	best := 0

	if first != -1 {
		used[first] = 1
		isVariant := false

		for i := 0; i < len(used); i++ {
			if used[i] == 0 {
				used[i] = 1
				cena := rastMinHodov(stroki[first], stolbci[first], stroki[i], stolbci[i])
				tek := cena + podborPar(stroki, stolbci, used)

				if !isVariant || tek < best {
					best = tek
					isVariant = true
				}

				used[i] = 0
			}
		}

		used[first] = 0
	}

	return best
}

func minHodovRisunka(a [][]int, verh int) int {
	stroki, stolbci := findNepravilnieKletki(a, verh)
	count := len(stroki)
	otvet := -1

	if count%2 == 0 {
		used := make([]int, count)
		otvet = podborPar(stroki, stolbci, used)
	}

	return otvet
}

func minHodovDoPolovini(a [][]int) int {
	otvet1 := minHodovRisunka(a, 0)
	otvet2 := minHodovRisunka(a, 1)
	otvet := -1

	if otvet1 != -1 && otvet2 != -1 {
		if otvet1 < otvet2 {
			otvet = otvet1
		} else {
			otvet = otvet2
		}
	} else if otvet1 != -1 {
		otvet = otvet1
	} else if otvet2 != -1 {
		otvet = otvet2
	}

	return otvet
}

func findBestVerh(a [][]int) int {
	otvet1 := minHodovRisunka(a, 0)
	otvet2 := minHodovRisunka(a, 1)
	verh := -1

	if otvet1 != -1 && otvet2 != -1 {
		if otvet1 <= otvet2 {
			verh = 0
		} else {
			verh = 1
		}
	} else if otvet1 != -1 {
		verh = 0
	} else if otvet2 != -1 {
		verh = 1
	}

	return verh
}

func printItogMatrix(n, m, verh int) {
	niz := 1 - verh

	for i := 0; i < n; i++ {
		for j := 0; j < m; j++ {
			if i < n/2 {
				fmt.Print(verh, " ")
			} else {
				fmt.Print(niz, " ")
			}
		}
		fmt.Println()
	}
}

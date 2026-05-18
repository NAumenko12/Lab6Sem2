package main

import (
	"fmt"
	"math"
)

func main() {
	var razmer int
	fmt.Print("Vvedite razmer sistemy: ")
	fmt.Scan(&razmer)
	matrica := SozdatMatricu(razmer)
	stolbecSvobodnihChlenov := SozdatMassiv(razmer)
	korni := SozdatMassiv(razmer)
	fmt.Println("\nVvedite matricu koefficientov:")
	VvestiMatricu(matrica, razmer)
	fmt.Println("\nVvedite stolbec svobodnih chlenov:")
	VvestiMassiv(stolbecSvobodnihChlenov, razmer)
	fmt.Println("\nIshodnaya sistema:")
	VivestiSistemu(matrica, stolbecSvobodnihChlenov, razmer)
	ReshitMetodomGaussa(matrica, stolbecSvobodnihChlenov, korni, razmer)
}

func SozdatMatricu(razmer int) [][]float64 {
	matrica := make([][]float64, razmer)

	for i := 0; i < razmer; i++ {
		matrica[i] = make([]float64, razmer)
	}

	return matrica
}

func SozdatMassiv(razmer int) []float64 {
	return make([]float64, razmer)
}

func VvestiMatricu(matrica [][]float64, razmer int) {
	for i := 0; i < razmer; i++ {
		for j := 0; j < razmer; j++ {
			fmt.Printf("matrica[%d][%d] = ", i+1, j+1)
			fmt.Scan(&matrica[i][j])
		}
	}
}

func VvestiMassiv(massiv []float64, razmer int) {
	for i := 0; i < razmer; i++ {
		fmt.Printf("b[%d] = ", i+1)
		fmt.Scan(&massiv[i])
	}
}

func VivestiSistemu(matrica [][]float64, stolbecSvobodnihChlenov []float64, razmer int) {
	for i := 0; i < razmer; i++ {
		for j := 0; j < razmer; j++ {
			fmt.Printf("%12.6f ", matrica[i][j])
		}
		fmt.Printf(" | %12.6f\n", stolbecSvobodnihChlenov[i])
	}
}

func VivestiMassiv(massiv []float64, razmer int) {
	for i := 0; i < razmer; i++ {
		fmt.Printf("x%d = %.6f\n", i+1, massiv[i])
	}
}

func ReshitMetodomGaussa(matrica [][]float64, stolbecSvobodnihChlenov []float64, korni []float64, razmer int) {
	const EPS = 1e-12
	kolichestvoPerestanovok := 0
	opredelitel := 1.0
	for shag := 0; shag < razmer-1; shag++ {
		maksimalnayaStroka := shag
		for i := shag + 1; i < razmer; i++ {
			if math.Abs(matrica[i][shag]) > math.Abs(matrica[maksimalnayaStroka][shag]) {
				maksimalnayaStroka = i
			}
		}
		if math.Abs(matrica[maksimalnayaStroka][shag]) < EPS {
			fmt.Println("Sistema ne imeet edinstvennogo resheniya.")
			return
		}
		if maksimalnayaStroka != shag {
			matrica[shag], matrica[maksimalnayaStroka] =
				matrica[maksimalnayaStroka], matrica[shag]
			stolbecSvobodnihChlenov[shag], stolbecSvobodnihChlenov[maksimalnayaStroka] =
				stolbecSvobodnihChlenov[maksimalnayaStroka], stolbecSvobodnihChlenov[shag]
			kolichestvoPerestanovok++
		}
		for i := shag + 1; i < razmer; i++ {
			koefficientIsklucheniya := matrica[i][shag] / matrica[shag][shag]
			for j := shag; j < razmer; j++ {
				matrica[i][j] =
					matrica[i][j] -
						koefficientIsklucheniya*matrica[shag][j]
			}
			stolbecSvobodnihChlenov[i] = stolbecSvobodnihChlenov[i] - koefficientIsklucheniya*stolbecSvobodnihChlenov[shag]
		}
		fmt.Printf("\nPosle shaga %d:\n", shag+1)
		VivestiSistemu(matrica, stolbecSvobodnihChlenov, razmer)
	}

	if math.Abs(matrica[razmer-1][razmer-1]) < EPS {
		fmt.Println("Sistema ne imeet edinstvennogo resheniya.")
		return
	}
	for i := 0; i < razmer; i++ {
		opredelitel *= matrica[i][i]
	}
	if kolichestvoPerestanovok%2 != 0 {
		opredelitel = -opredelitel
	}
	for i := razmer - 1; i >= 0; i-- {
		summa := 0.0
		for j := i + 1; j < razmer; j++ {
			summa += matrica[i][j] * korni[j]
		}
		korni[i] = (stolbecSvobodnihChlenov[i] - summa) / matrica[i][i]
	}
	fmt.Println("\nReshenie sistemy:")
	VivestiMassiv(korni, razmer)
	fmt.Printf("\nOpredelitel matrici = %.6f\n", opredelitel)
}

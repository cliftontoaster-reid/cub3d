package main

import (
	"fmt"
	"math/rand"
	"os"
	"path/filepath"
	"regexp"
	"runtime"
	"strconv"
	"strings"
	"sync"
	"time"
)

type Point struct {
	X, Y int
}

func main() {
	if len(os.Args) < 3 {
		fmt.Fprintf(os.Stderr, "Usage: %s <width> <height> [out_path]\n", os.Args[0])
		fmt.Fprintf(os.Stderr, "Example: %s 30 20 maps/map_[0..5].cub\n", os.Args[0])
		os.Exit(1)
	}

	width, err := strconv.Atoi(os.Args[1])
	if err != nil || width < 5 {
		fmt.Fprintf(os.Stderr, "Error: width must be >= 5\n")
		os.Exit(1)
	}

	height, err := strconv.Atoi(os.Args[2])
	if err != nil || height < 5 {
		fmt.Fprintf(os.Stderr, "Error: height must be >= 5\n")
		os.Exit(1)
	}

	outPath := "map.cub"
	if len(os.Args) > 3 {
		outPath = os.Args[3]
	}

	// Expand ranges in output path
	paths := expandRanges(outPath)

	// Use all available CPUs
	runtime.GOMAXPROCS(runtime.NumCPU())

	// Generate maps in parallel
	var wg sync.WaitGroup
	semaphore := make(chan struct{}, runtime.NumCPU())

	start := time.Now()
	for i, path := range paths {
		wg.Add(1)
		semaphore <- struct{}{}

		go func(index int, outFile string) {
			defer wg.Done()
			defer func() { <-semaphore }()

			// Use different seed for each goroutine
			rng := rand.New(rand.NewSource(time.Now().UnixNano() + int64(index)))
			
			mapData := generateRandomMap(width, height, rng)
			writeMapFile(outFile, mapData)
			
			fmt.Printf("Generated: %s\n", outFile)
		}(i, path)
	}

	wg.Wait()
	elapsed := time.Since(start)
	fmt.Printf("\nGenerated %d map(s) in %v\n", len(paths), elapsed)
}

func expandRanges(path string) []string {
	re := regexp.MustCompile(`\[(\d+)\.\.(\d+)\]`)
	matches := re.FindStringSubmatch(path)

	if matches == nil {
		return []string{path}
	}

	start, _ := strconv.Atoi(matches[1])
	end, _ := strconv.Atoi(matches[2])

	var paths []string
	for i := start; i <= end; i++ {
		expanded := re.ReplaceAllString(path, strconv.Itoa(i))
		paths = append(paths, expanded)
	}

	return paths
}

func generateRandomMap(width, height int, rng *rand.Rand) [][]byte {
	// Initialize map with walls
	grid := make([][]byte, height)
	for y := 0; y < height; y++ {
		grid[y] = make([]byte, width)
		for x := 0; x < width; x++ {
			grid[y][x] = '1'
		}
	}

	// Create a random cave-like structure using cellular automata
	// Start with random fill in the interior
	for y := 2; y < height-2; y++ {
		for x := 2; x < width-2; x++ {
			if rng.Float64() < 0.45 {
				grid[y][x] = '0'
			}
		}
	}

	// Apply cellular automata smoothing
	iterations := 4 + rng.Intn(3)
	for i := 0; i < iterations; i++ {
		grid = smoothMap(grid, width, height)
	}

	// Ensure borders are all walls
	for y := 0; y < height; y++ {
		grid[y][0] = '1'
		grid[y][width-1] = '1'
	}
	for x := 0; x < width; x++ {
		grid[0][x] = '1'
		grid[height-1][x] = '1'
	}

	// Find valid player position
	validPositions := findValidPositions(grid, width, height)
	if len(validPositions) == 0 {
		// Fallback: create a simple valid map
		return createFallbackMap(width, height, rng)
	}

	// Place player at random valid position
	playerPos := validPositions[rng.Intn(len(validPositions))]
	directions := []byte{'N', 'S', 'E', 'W'}
	grid[playerPos.Y][playerPos.X] = directions[rng.Intn(len(directions))]

	// Ensure map is valid (enclosed and reachable)
	if !isMapValid(grid, width, height, playerPos) {
		return createFallbackMap(width, height, rng)
	}

	return grid
}

func smoothMap(grid [][]byte, width, height int) [][]byte {
	newGrid := make([][]byte, height)
	for y := 0; y < height; y++ {
		newGrid[y] = make([]byte, width)
		copy(newGrid[y], grid[y])
	}

	for y := 1; y < height-1; y++ {
		for x := 1; x < width-1; x++ {
			wallCount := countAdjacentWalls(grid, x, y, width, height)

			if wallCount >= 5 {
				newGrid[y][x] = '1'
			} else if wallCount <= 3 {
				newGrid[y][x] = '0'
			}
		}
	}

	return newGrid
}

func countAdjacentWalls(grid [][]byte, x, y, width, height int) int {
	count := 0
	for dy := -1; dy <= 1; dy++ {
		for dx := -1; dx <= 1; dx++ {
			if dx == 0 && dy == 0 {
				continue
			}
			nx, ny := x+dx, y+dy
			if nx < 0 || nx >= width || ny < 0 || ny >= height {
				count++
			} else if grid[ny][nx] == '1' {
				count++
			}
		}
	}
	return count
}

func findValidPositions(grid [][]byte, width, height int) []Point {
	var positions []Point

	for y := 2; y < height-2; y++ {
		for x := 2; x < width-2; x++ {
			if grid[y][x] == '0' {
				// Check if surrounded by playable area
				hasSpace := true
				for dy := -1; dy <= 1; dy++ {
					for dx := -1; dx <= 1; dx++ {
						if grid[y+dy][x+dx] == '1' {
							hasSpace = false
							break
						}
					}
					if !hasSpace {
						break
					}
				}
				if hasSpace {
					positions = append(positions, Point{x, y})
				}
			}
		}
	}

	return positions
}

func isMapValid(grid [][]byte, width, height int, start Point) bool {
	visited := make([][]bool, height)
	for y := 0; y < height; y++ {
		visited[y] = make([]bool, width)
	}

	// Flood fill from start position
	floodFill(grid, visited, start.X, start.Y, width, height)

	// Check if we can reach all empty spaces
	for y := 1; y < height-1; y++ {
		for x := 1; x < width-1; x++ {
			if grid[y][x] == '0' && !visited[y][x] {
				return false
			}
		}
	}

	return true
}

func floodFill(grid [][]byte, visited [][]bool, x, y, width, height int) {
	if x < 0 || x >= width || y < 0 || y >= height {
		return
	}
	if visited[y][x] || grid[y][x] == '1' {
		return
	}

	visited[y][x] = true

	floodFill(grid, visited, x+1, y, width, height)
	floodFill(grid, visited, x-1, y, width, height)
	floodFill(grid, visited, x, y+1, width, height)
	floodFill(grid, visited, x, y-1, width, height)
}

func createFallbackMap(width, height int, rng *rand.Rand) [][]byte {
	grid := make([][]byte, height)
	for y := 0; y < height; y++ {
		grid[y] = make([]byte, width)
		for x := 0; x < width; x++ {
			if y == 0 || y == height-1 || x == 0 || x == width-1 {
				grid[y][x] = '1'
			} else {
				grid[y][x] = '0'
			}
		}
	}

	// Add some random internal walls
	numWalls := (width * height) / 20
	for i := 0; i < numWalls; i++ {
		x := 2 + rng.Intn(width-4)
		y := 2 + rng.Intn(height-4)
		grid[y][x] = '1'
	}

	// Place player
	px := width / 2
	py := height / 2
	directions := []byte{'N', 'S', 'E', 'W'}
	grid[py][px] = directions[rng.Intn(len(directions))]

	return grid
}

func writeMapFile(path string, grid [][]byte) {
	// Create directory if needed
	dir := filepath.Dir(path)
	if dir != "." && dir != "" {
		os.MkdirAll(dir, 0755)
	}

	var sb strings.Builder

	// Write texture and color configuration
	sb.WriteString("NO ./textures/north.xpm\n")
	sb.WriteString("SO ./textures/south.xpm\n")
	sb.WriteString("WE ./textures/west.xpm\n")
	sb.WriteString("EA ./textures/east.xpm\n")
	sb.WriteString("\n")
	sb.WriteString("F 64,64,64\n")
	sb.WriteString("C 135,206,235\n")
	sb.WriteString("\n")

	// Write map
	for _, row := range grid {
		sb.Write(row)
		sb.WriteByte('\n')
	}

	os.WriteFile(path, []byte(sb.String()), 0644)
}
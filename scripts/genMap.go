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

// Cell represents a character in the map grid.
type Cell rune

const (
	Wall    Cell = '1'
	Floor   Cell = '0'
	North   Cell = 'N'
	South   Cell = 'S'
	East    Cell = 'E'
	West    Cell = 'W'
	Space   Cell = ' '
)

// Random utility functions
func randInt(max int) int {
	return rand.Intn(max)
}

func choose[T any](arr []T) T {
	return arr[randInt(len(arr))]
}

func randomRGB() (r, g, b int) {
	return randInt(256), randInt(256), randInt(256)
}

// Grid operations
func makeEmptyGrid(w, h int) [][]Cell {
	grid := make([][]Cell, h)
	for y := 0; y < h; y++ {
		grid[y] = make([]Cell, w)
		for x := 0; x < w; x++ {
			grid[y][x] = Wall
		}
	}
	return grid
}

func gridToLines(grid [][]Cell) []string {
	lines := make([]string, len(grid))
	for i, row := range grid {
		var sb strings.Builder
		for _, cell := range row {
			sb.WriteRune(rune(cell))
		}
		lines[i] = sb.String()
	}
	return lines
}

func placeInteriorRandom(grid [][]Cell, floorProb float64) {
	h := len(grid)
	if h == 0 {
		return
	}
	w := len(grid[0])
	for y := 1; y < h-1; y++ {
		for x := 1; x < w-1; x++ {
			if rand.Float64() < floorProb {
				grid[y][x] = Floor
			} else {
				grid[y][x] = Wall
			}
		}
	}
}

func findAll(grid [][]Cell, chs map[Cell]bool) [][2]int {
	var out [][2]int
	for y := 0; y < len(grid); y++ {
		for x := 0; x < len(grid[0]); x++ {
			if chs[grid[y][x]] {
				out = append(out, [2]int{x, y})
			}
		}
	}
	return out
}

func countPlayer(grid [][]Cell) int {
	playerChars := map[Cell]bool{North: true, South: true, East: true, West: true}
	return len(findAll(grid, playerChars))
}

func placePlayer(grid [][]Cell) bool {
	floorChars := map[Cell]bool{Floor: true}
	floors := findAll(grid, floorChars)
	if len(floors) == 0 {
		return false
	}
	pos := choose(floors)
	x, y := pos[0], pos[1]
	dir := choose([]Cell{North, South, East, West})
	grid[y][x] = dir
	return true
}

func hasInvalidChars(grid [][]Cell) bool {
	allowed := map[Cell]bool{Floor: true, Wall: true, North: true, South: true, East: true, West: true, Space: true}
	for _, row := range grid {
		for _, c := range row {
			if !allowed[c] {
				return true
			}
		}
	}
	return false
}

// Core Validation Function (flood-fill)
func floodFillIsValid(grid [][]Cell) bool {
	h := len(grid)
	if h == 0 {
		return false
	}
	w := len(grid[0])
	if w == 0 {
		return false
	}

	// 1. Check for exactly one player & no spaces in map body
	px, py, pcnt := -1, -1, 0
	for y := 0; y < h; y++ {
		for x := 0; x < w; x++ {
			c := grid[y][x]
			if c == North || c == South || c == East || c == West {
				px, py = x, y
				pcnt++
			}
			if c == Space {
				// Spaces are invalid in the main map region for this validation style
				return false
			}
		}
	}
	if pcnt != 1 {
		return false
	}

	// 2. BFS/DFS flood-fill from player
	visited := make([][]bool, h)
	for i := range visited {
		visited[i] = make([]bool, w)
	}

	queue := [][2]int{{px, py}}
	visited[py][px] = true

	for len(queue) > 0 {
		curr := queue[0]
		queue = queue[1:]
		x, y := curr[0], curr[1]

		// If we are at border (0 or w-1 / h-1) => invalid (unclosed map)
		if x == 0 || y == 0 || x == w-1 || y == h-1 {
			return false
		}

		neighbors := [][2]int{
			{x + 1, y}, {x - 1, y}, {x, y + 1}, {x, y - 1},
		}

		for _, nei := range neighbors {
			nx, ny := nei[0], nei[1]

			if nx < 0 || ny < 0 || nx >= w || ny >= h {
				continue // Should not happen with border check above, but safe to include
			}
			if visited[ny][nx] {
				continue
			}

			c := grid[ny][nx]

			if c == Wall {
				continue // Wall, stop here
			}
			if c == Space {
				return false // Invalid space encountered
			}

			visited[ny][nx] = true
			queue = append(queue, nei)
		}
	}
	return true
}

// File handling and Map Generation Orchestration
func writeMapFile(path string, headers []string, lines []string) error {
	content := strings.Join(headers, "\n") + "\n\n" + strings.Join(lines, "\n") + "\n"
	return os.WriteFile(path, []byte(content), 0644)
}

func parseOutputPaths(outPath string) ([]string, error) {
	rangeRe := regexp.MustCompile(`\[(\d+)\.\.(\d+)\]`)
	m := rangeRe.FindStringSubmatch(outPath)
	if m == nil {
		return []string{outPath}, nil
	}

	startStr, endStr := m[1], m[2]
	start, errStart := strconv.Atoi(startStr)
	end, errEnd := strconv.Atoi(endStr)
	if errStart != nil || errEnd != nil {
		return nil, fmt.Errorf("invalid range numbers in out_path: %v, %v", errStart, errEnd)
	}

	if start > end {
		start, end = end, start // Normalize direction
	}

	var outputs []string
	pad := 0
	if len(startStr) > 1 {
		pad = len(startStr)
	}

	for i := start; i <= end; i++ {
		idx := strconv.Itoa(i)
		if pad > 0 {
			idx = fmt.Sprintf("%0*d", pad, i)
		}
		outputs = append(outputs, rangeRe.ReplaceAllString(outPath, idx))
	}
	return outputs, nil
}

func generateMap(targetPath string, w, h, maxAttempts int, wg *sync.WaitGroup) {
	defer wg.Done()

	var (
		attempt = 0
		success = false
		grid    [][]Cell
	)

	for attempt < maxAttempts && !success {
		attempt++
		grid = makeEmptyGrid(w, h)
		// Carve interior randomly (0.63 prob for floor)
		placeInteriorRandom(grid, 0.63)

		// Ensure at least one floor if none was carved
		floorChars := map[Cell]bool{Floor: true}
		if len(findAll(grid, floorChars)) == 0 {
			cx, cy := w/2, h/2
			grid[cy][cx] = Floor
		}

		// Clear existing player characters if any (shouldn't happen here, but robust)
		for y := 0; y < h; y++ {
			for x := 0; x < w; x++ {
				c := grid[y][x]
				if c == North || c == South || c == East || c == West {
					grid[y][x] = Floor
				}
			}
		}

		if !placePlayer(grid) {
			continue
		}

		// Quick checks (checking again after placePlayer to be safe, though placePlayer uses "0")
		if hasInvalidChars(grid) {
			continue
		}
		if countPlayer(grid) != 1 {
			continue
		}

		// Flood-fill validation (the critical check)
		if !floodFillIsValid(grid) {
			continue
		}
		success = true
	}

	if !success {
		fmt.Fprintf(os.Stderr, "Failed to generate a valid map after %d attempts for %s\n", maxAttempts, targetPath)
		return
	}

	// Generate map headers
	fr, fg, fb := randomRGB()
	cr, cg, cb := randomRGB()
	headers := []string{
		"NO ./north.xpm",
		"SO ./south.xpm",
		"WE ./west.xpm",
		"EA ./east.xpm",
		fmt.Sprintf("F %d,%d,%d", fr, fg, fb),
		fmt.Sprintf("C %d,%d,%d", cr, cg, cb),
	}

	lines := gridToLines(grid)

	// Ensure directory exists
	dir := filepath.Dir(targetPath)
	if dir != "" && dir != "." {
		if err := os.MkdirAll(dir, 0755); err != nil {
			fmt.Fprintf(os.Stderr, "Error creating directory for %s: %v\n", targetPath, err)
			return
		}
	}

	// Write file
	if err := writeMapFile(targetPath, headers, lines); err != nil {
		fmt.Fprintf(os.Stderr, "Error writing map file to %s: %v\n", targetPath, err)
		return
	}

	fmt.Printf("Wrote generated map to %s (attempt %d)\n", targetPath, attempt)
}

func main() {
	// Seed the random number generator
	rand.Seed(time.Now().UnixNano())

	// Use command-line arguments directly from os.Args for simplicity, similar to the Deno script
	if len(os.Args) < 3 {
		fmt.Fprintln(os.Stderr, "Usage: go run genMap.go <width> <height> [out_path]")
		os.Exit(1)
	}

	w, errW := strconv.Atoi(os.Args[1])
	h, errH := strconv.Atoi(os.Args[2])
	if errW != nil || errH != nil || w < 3 || h < 3 {
		fmt.Fprintln(os.Stderr, "Width and height must be integers >= 3")
		os.Exit(1)
	}

	outPath := fmt.Sprintf("assets/maps/generated_%dx%d.cub", w, h)
	if len(os.Args) >= 4 {
		outPath = os.Args[3]
	}

	outputs, err := parseOutputPaths(outPath)
	if err != nil {
		fmt.Fprintf(os.Stderr, "Error parsing output path: %v\n", err)
		os.Exit(1)
	}

	maxAttempts := 200

	// Use standard concurrency model (goroutines and WaitGroup)
	// We'll limit concurrency to the number of CPUs available.
	cpuCount := runtime.GOMAXPROCS(0)
	if cpuCount == 0 {
		cpuCount = 1
	}

	var wg sync.WaitGroup
	sem := make(chan struct{}, cpuCount) // Semaphore to limit concurrency

	for _, targetPath := range outputs {
		wg.Add(1)
		sem <- struct{}{} // Acquire a slot

		go func(path string) {
			defer func() { <-sem }() // Release the slot
			generateMap(path, w, h, maxAttempts, &wg)
		}(targetPath)
	}

	wg.Wait()
}
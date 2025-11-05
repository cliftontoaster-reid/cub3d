#!/usr/bin/env -S deno run --allow-read --allow-write
// Generate a random but valid .cub map for the cub3d project.
// Usage: deno run --allow-read --allow-write scripts/genMap.ts <width> <height> [out_path]

function randInt(max: number) {
  return Math.floor(Math.random() * max);
}

function choose<T>(arr: T[]) {
  return arr[randInt(arr.length)];
}

function randomRGB(): [number, number, number] {
  return [randInt(256), randInt(256), randInt(256)];
}

type Cell = "0" | "1" | "N" | "S" | "E" | "W" | " ";

function makeEmptyGrid(w: number, h: number): Cell[][] {
  const grid: Cell[][] = new Array(h);
  for (let y = 0; y < h; y++) {
    grid[y] = new Array(w);
    for (let x = 0; x < w; x++) grid[y][x] = "1";
  }
  return grid;
}

function gridToLines(grid: Cell[][]): string[] {
  return grid.map((row) => row.join(""));
}

function placeInteriorRandom(grid: Cell[][], floorProb = 0.6) {
  const h = grid.length,
    w = grid[0].length;
  for (let y = 1; y < h - 1; y++) {
    for (let x = 1; x < w - 1; x++) {
      grid[y][x] = Math.random() < floorProb ? "0" : "1";
    }
  }
}

function findAll(grid: Cell[][], chs: Set<Cell>) {
  const out: [number, number][] = [];
  for (let y = 0; y < grid.length; y++) {
    for (let x = 0; x < grid[0].length; x++) {
      if (chs.has(grid[y][x])) out.push([x, y]);
    }
  }
  return out;
}

function countPlayer(grid: Cell[][]) {
  const set = new Set(["N", "S", "E", "W"]);
  return findAll(grid, set as Set<Cell>).length;
}

function placePlayer(grid: Cell[][]) {
  const floors = findAll(grid, new Set(["0"]));
  if (floors.length === 0) return false;
  const [x, y] = choose(floors);
  const dir = choose(["N", "S", "E", "W"]) as Cell;
  grid[y][x] = dir;
  return true;
}

function hasInvalidChars(grid: Cell[][]) {
  const allowed = new Set(["0", "1", "N", "S", "E", "W", " "]);
  for (const row of grid) for (const c of row) if (!allowed.has(c)) return true;
  return false;
}

function floodFillIsValid(grid: Cell[][]): boolean {
  const h = grid.length,
    w = grid[0].length;
  // Check for exactly one player
  let px = -1,
    py = -1,
    pcnt = 0;
  for (let y = 0; y < h; y++) {
    for (let x = 0; x < w; x++) {
      const c = grid[y][x];
      if (c === "N" || c === "S" || c === "E" || c === "W") {
        px = x;
        py = y;
        pcnt++;
      }
      if (c === " ") return false; // spaces are treated as invalid region per validator
    }
  }
  if (pcnt !== 1) return false;

  // BFS/DFS flood-fill from player; cannot reach boundary or space
  const visited = Array.from({ length: h }, () =>
    new Array<boolean>(w).fill(false),
  );
  const q: [number, number][] = [];
  q.push([px, py]);
  visited[py][px] = true;
  while (q.length > 0) {
    const [x, y] = q.shift()!;
    // If we are at border => invalid
    if (x === 0 || y === 0 || x === w - 1 || y === h - 1) return false;
    const nei = [
      [x + 1, y],
      [x - 1, y],
      [x, y + 1],
      [x, y - 1],
    ];
    for (const [nx, ny] of nei) {
      if (nx < 0 || ny < 0 || nx >= w || ny >= h) continue;
      if (visited[ny][nx]) continue;
      const c = grid[ny][nx];
      if (c === "1") continue; // wall
      if (c === " ") return false; // invalid
      visited[ny][nx] = true;
      q.push([nx, ny]);
    }
  }
  return true;
}

async function writeMapFile(path: string, headers: string[], lines: string[]) {
  const content = headers.join("\n") + "\n\n" + lines.join("\n") + "\n";
  await Deno.writeTextFile(path, content);
}

async function main() {
  const args = Deno.args;
  if (args.length < 2) {
    console.error("Usage: genMap.ts <width> <height> [out_path]");
    Deno.exit(1);
  }
  const w = Number(args[0]);
  const h = Number(args[1]);
  if (!Number.isInteger(w) || !Number.isInteger(h) || w < 3 || h < 3) {
    console.error("Width and height must be integers >= 3");
    Deno.exit(1);
  }
  let outPath = args[2] ?? `assets/maps/generated_${w}x${h}.cub`;

  // Support smart range syntax in outPath, e.g. "maps/map[0..2].cub" -> 3 maps
  const rangeRe = /\[(\d+)\.\.(\d+)\]/;
  const outputs: string[] = [];
  const m = outPath.match(rangeRe);
  if (m) {
    const startStr = m[1];
    const endStr = m[2];
    let start = Number(startStr);
    let end = Number(endStr);
    if (Number.isNaN(start) || Number.isNaN(end)) {
      console.error("Invalid range in out_path");
      Deno.exit(1);
    }
    // allow either direction by normalizing
    if (start > end) {
      const tmp = start;
      start = end;
      end = tmp;
    }
    const pad = startStr.length > 1 ? startStr.length : 0;
    for (let i = start; i <= end; i++) {
      const idx = pad ? String(i).padStart(pad, "0") : String(i);
      outputs.push(outPath.replace(rangeRe, idx));
    }
  } else {
    outputs.push(outPath);
  }

  const maxAttempts = 200;

  // Generate function for a single map
  async function generateMap(targetPath: string): Promise<void> {
    let attempt = 0;
    let success = false;
    let grid: Cell[][] = [];

    while (attempt < maxAttempts && !success) {
      attempt++;
      grid = makeEmptyGrid(w, h);
      // Carve interior randomly
      placeInteriorRandom(grid, 0.63);
      // Ensure at least one floor
      const floors = findAll(grid, new Set(["0"]));
      if (floors.length === 0) {
        const cx = Math.floor(w / 2),
          cy = Math.floor(h / 2);
        grid[cy][cx] = "0";
      }
      // Place player
      // clear any existing players just in case
      for (let y = 0; y < h; y++) {
        for (let x = 0; x < w; x++) {
          if (["N", "S", "E", "W"].includes(grid[y][x])) grid[y][x] = "0";
        }
      }
      if (!placePlayer(grid)) continue;
      // quick checks
      if (hasInvalidChars(grid)) continue;
      if (countPlayer(grid) !== 1) continue;
      // flood-fill validation
      if (!floodFillIsValid(grid)) continue;
      success = true;
    }

    if (!success) {
      console.error(
        "Failed to generate a valid map after",
        maxAttempts,
        "attempts for",
        targetPath,
      );
      return;
    }

    const [fr, fg, fb] = randomRGB();
    const [cr, cg, cb] = randomRGB();
    const headers = [
      "NO ./north.xpm",
      "SO ./south.xpm",
      "WE ./west.xpm",
      "EA ./east.xpm",
      `F ${fr},${fg},${fb}`,
      `C ${cr},${cg},${cb}`,
    ];

    const lines = gridToLines(grid);
    // Ensure directory exists for targetPath
    try {
      const dir = targetPath.substring(0, targetPath.lastIndexOf("/")) || ".";
      await Deno.mkdir(dir, { recursive: true });
    } catch (_e) {}
    await writeMapFile(targetPath, headers, lines);
    console.log(`Wrote generated map to ${targetPath} (attempt ${attempt})`);
  }

  // Generate maps with concurrency limited to CPU count
  const cpuCount = navigator.hardwareConcurrency || 1;
  const results: Promise<void>[] = [];

  for (let i = 0; i < outputs.length; i += cpuCount) {
    const batch = outputs.slice(i, i + cpuCount);
    await Promise.all(batch.map(generateMap));
  }
}

if (import.meta.main) {
  main();
}

let cols;
let rows;
const w = 20;
const grid = [];
let current;
const stack = [];

function setup() {
  createCanvas(400, 400);

  cols = floor(width / w);
  rows = floor(height / w);

  for (let j = 0; j < rows; j++) {
    for (let i = 0; i < cols; i++) {
      const cell = new Cell(i, j);
      grid.push(cell);
    }
  }

  current = grid[0];

  // frameRate(5);
}

function draw() {
  background(51);

  for (let i = 0; i < grid.length; i++) {
    grid[i].show();
  }

  current.visited = true;
  current.highlight();
  let next = current.checkNeighbors();
  if (next) {
    next.visited = true;
    stack.push(current);
    removeWalls(current, next);
    current = next;
  } else if (stack.length > 0) {
    // pop() removes last elment from an array
    current = stack.pop();
    // console.log("stack", stack);
  }
}

// i -> Column Number (up/down)
// j -> Row Number (left/right)
function Cell(i, j) {
  this.i = i;
  this.j = j;
  this.visited = false;

  // Top Right Bottom Left
  this.walls = [true, true, true, true];

  this.checkNeighbors = function () {
    let neighbors = [];

    let top = grid[index(this.i, this.j - 1)];
    let right = grid[index(this.i + 1, this.j)];
    let bottom = grid[index(this.i, this.j + 1)];
    let left = grid[index(this.i - 1, this.j)];

    if (top && !top.visited) {
      neighbors.push(top);
    }

    if (right && !right.visited) {
      neighbors.push(right);
    }

    if (bottom && !bottom.visited) {
      neighbors.push(bottom);
    }

    if (left && !left.visited) {
      neighbors.push(left);
    }

    if (neighbors.length > 0) {
      let r = floor(random(0, neighbors.length));
      return neighbors[r];
    } else {
      return undefined;
    }
  };

  function index(i, j) {
    if (i < 0 || j < 0 || i > cols - 1 || j > rows - 1) {
      return -1;
    }
    return i + j * cols;
  }

  this.highlight = function () {
    let x = this.i * w;
    let y = this.j * w;
    noStroke();
    fill(0, 0, 255, 100);
    rect(x, y, w, w);
  };

  this.show = function () {
    let x = this.i * w;
    let y = this.j * w;
    stroke(255);

    // Top
    if (this.walls[0]) {
      line(x, y, x + w, y);
    }

    // Right
    if (this.walls[1]) {
      line(x + w, y, x + w, y + w);
    }

    // Bottom
    if (this.walls[2]) {
      line(x + w, y + w, x, y + w);
    }

    // Left
    if (this.walls[3]) {
      line(x, y + w, x, y);
    }

    if (this.visited) {
      fill(255, 0, 255, 100);
      noStroke();
      rect(x, y, w, w);
    }
  };
}

function removeWalls(a, b) {
  let x = a.i - b.i;
  if (x === 1) {
    a.walls[3] = false;
    b.walls[1] = false;
  } else if (x === -1) {
    a.walls[1] = false;
    b.walls[3] = false;
  }

  let y = a.j - b.j;
  if (y === 1) {
    a.walls[0] = false;
    b.walls[2] = false;
  } else if (y === -1) {
    a.walls[2] = false;
    b.walls[0] = false;
  }
}

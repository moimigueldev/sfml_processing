let cols;
let rows;
const w = 40;
const grid = [];

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
}

function draw() {
  background(51);

  for (let i = 0; i < grid.length; i++) {
    grid[i].show();
  }
}

// i -> Column Number (up/down)
// j -> Row Number (left/right)
function Cell(i, j) {
  this.i = i;
  this.j = j;

  // Top Right Bottom Left
  this.walls = [true, true, true, true];

  console.log("i", i, j);

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
  };
}

const cols = 50;
const rows = 50;
const grid = new Array(cols);

const openSet = [];
const closedSet = [];
let start;
let end;
let path = [];
let current;
let noSolution = false;

let w, h;

function heuristic(a, b) {
  const d = dist(a.i, a.j, b.i, b.j);
  return d;
}

// function heuristic(a, b) {
//   var d = abs(a.i - b.i) + abs(a.j, b.j);
//   return d;
// }

function Spot(i, j) {
  this.i = i;
  this.j = j;

  this.previous = undefined;

  this.wall = false;

  if (random(1) < 0.34) {
    this.wall = true;
  }

  // cost of g + h
  this.f = 0;

  // cost of this spot to starting node
  this.g = 0;

  // cost of this spot to end node
  this.h = 0;
  this.neighbors = [];

  this.show = function (color) {
    // fill(color);
    if (this.wall) {
      fill(0);
      noStroke();
      // rect(this.i * w, this.j * h, w - 1, h - 1);
      ellipse(this.i * w + w / 2, this.j * h + h / 2, w / 2, h / 2);
    }
  };

  this.addNeighbors = function (grid) {
    let i = this.i;
    let j = this.j;

    if (i < cols - 1) {
      this.neighbors.push(grid[i + 1][j]);
    }
    if (i > 0) {
      this.neighbors.push(grid[i - 1][j]);
    }
    if (j < rows - 1) {
      this.neighbors.push(grid[i][j + 1]);
    }
    if (j > 0) {
      this.neighbors.push(grid[i][j - 1]);
    }

    if (i > 0 && j > 0) {
      this.neighbors.push(grid[i - 1][j - 1]);
    }
    if (i < cols - 1 && j > 0) {
      this.neighbors.push(grid[i + 1][j - 1]);
    }
    if (i > 0 && j < rows - 1) {
      this.neighbors.push(grid[i - 1][j + 1]);
    }
    if (i < cols - 1 && j < rows - 1) {
      this.neighbors.push(grid[i + 1][j + 1]);
    }
  };
}

function removeFromArray(arr, element) {
  for (let i = arr.length - 1; i >= 0; i--) {
    if (arr[i] == element) {
      arr.splice(i, 1);
    }
  }
}

function setup() {
  createCanvas(400, 400);
  w = width / cols;
  h = height / rows;

  for (let index = 0; index < cols; index++) {
    grid[index] = new Array(rows);
  }

  for (let i = 0; i < cols; i++) {
    for (let j = 0; j < rows; j++) {
      grid[i][j] = new Spot(i, j);
    }
  }
  for (let i = 0; i < cols; i++) {
    for (let j = 0; j < rows; j++) {
      grid[i][j].addNeighbors(grid);
    }
  }

  start = grid[0][0];
  end = grid[cols - 1][rows - 1];
  start.wall = false;
  end.wall = false;

  openSet.push(start);
}

function draw() {
  background(255);

  if (openSet.length > 0) {
    // we can keep going
    let winner = 0;
    for (let i = 0; i < openSet.length; i++) {
      if (openSet[i].f < openSet[winner].f) {
        winner = i;
      }
    }

    current = openSet[winner];

    removeFromArray(openSet, current);
    closedSet.push(current);

    const neighbors = current.neighbors;

    for (let i = 0; i < neighbors.length; i++) {
      const neighbor = neighbors[i];

      if (!closedSet.includes(neighbor) && !neighbor.wall) {
        const tempG = current.g + 1;
        let newPath = false;
        if (openSet.includes(neighbor)) {
          if (tempG < neighbor.g) {
            neighbor.g = tempG;
            newPath = true;
          }
        } else {
          neighbor.g = tempG;
          openSet.push(neighbor);
          newPath = true;
        }
        if (newPath) {
          neighbor.h = heuristic(neighbor, end);
          neighbor.f = neighbor.g + neighbor.h;
          // previous === camefrom
          neighbor.previous = current;
        }
      }
    }

    if (current == end) {
      console.log("DONE");
      noLoop();

      // find the path
    }
  } else {
    // no solution
    noLoop();
    console.log("no solution");
    return;
  }

  for (let i = 0; i < cols; i++) {
    for (let j = 0; j < rows; j++) {
      grid[i][j].show(255);
    }
  }

  for (let i = 0; i < closedSet.length; i++) {
    // closedSet red
    closedSet[i].show(color(255, 0, 0));
  }
  for (let i = 0; i < openSet.length; i++) {
    // openSet green
    openSet[i].show(color(0, 255, 0));
  }

  path = [];
  let temp = current;
  path.push(temp);
  while (temp.previous) {
    path.push(temp.previous);
    temp = temp.previous;
  }

  beginShape();

  noFill();
  stroke(0, 255, 255);
  strokeWeight(w / 2);
  for (let i = 0; i < path.length; i++) {
    vertex(path[i].i * w + w / 2, path[i].j * h + h / 2);
  }

  endShape();

  // noLoop();
}

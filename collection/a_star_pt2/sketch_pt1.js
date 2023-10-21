const cols = 25;
const rows = 25;
const grid = [];
let w, h;

// list of nodes that still have NOT been evaluated
// the algo is finished when openSet is empty
const openSet = [];

// stores a list of all the nodes that have finished being evaluated
// these nodes don't need to be visited again

const closedSet = [];

let start;
let end;
let current;

let path = [];

function removeFromArray(arr, el) {
  for (let i = arr.length - 1; i >= 0; i--) {
    if (arr[i] == el) arr.splice(i, 1);
  }
}

// function heuristic(a, b) {
//   const d = dist(a.i, a.j, b.i, b.j);
//
//   return d;
// }

function heuristic(a, b) {
  var d = abs(a.i - b.i) + abs(a.j - b.j);
  return d;
}

function Spot(i, j) {
  this.i = i;
  this.j = j;

  // cost of spot to goal cell
  this.h = 0;

  // cost of spot to starting cell
  this.g = 0;

  // cost of h & g summed
  this.f = 0;

  this.neighbors = [];

  this.previous;

  this.addNeighbors = function (grid) {
    const { i } = this;
    const { j } = this;

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

    // if (i > 0 && j > 0) {
    //   this.neighbors.push(grid[i - 1][j - 1]);
    // }
    // if (i < cols - 1 && j > 0) {
    //   this.neighbors.push(grid[i + 1][j - 1]);
    // }
    // if (i > 0 && j < rows - 1) {
    //   this.neighbors.push(grid[i - 1][j + 1]);
    // }
    // if (i < cols - 1 && j < rows - 1) {
    //   this.neighbors.push(grid[i + 1][j + 1]);
    // }
  };

  this.show = function (color) {
    fill(color);
    noStroke();
    rect(this.i * w, this.j * h, w - 1, h - 1);
  };
}

function setup() {
  createCanvas(400, 400);

  w = width / cols;
  h = height / rows;

  // Making a 2D array
  for (let i = 0; i < cols; i++) {
    grid[i] = new Array(rows);
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

  openSet.push(start);
}

function draw() {
  background(0);

  if (openSet.length > 0) {
    // lowesetIndex
    let winner = 0;
    for (let i = 0; i < openSet; i++) {
      if (openSet[i].f < openSet[winner].f) {
        winner = i;
      }
    }

    current = openSet[winner];

    if (current == end) {
      console.log("done");
      noLoop();
    }

    // openSet.remove(current);
    removeFromArray(openSet, current);
    closedSet.push(current);

    const neighbors = current.neighbors;

    for (let i = 0; i < neighbors.length; i++) {
      const neighbor = neighbors[i];
      if (!closedSet.includes(neighbor)) {
        const tempG = (neighbor.g = current.g + 1);

        if (openSet.includes(neighbor)) {
          if (tempG < neighbor.g) {
            neighbor.g = tempG;
          }
        } else {
          neighbor.g = tempG;
          openSet.push(neighbor);
        }

        neighbor.h = heuristic(neighbor, end);
        neighbor.f = neighbor.g + neighbor.h;
        neighbor.previous = current;
      }
    }
  } else {
    // no solution
    console.log("no solution");
    noLoop();
  }

  for (let i = 0; i < cols; i++) {
    for (let j = 0; j < rows; j++) {
      grid[i][j].show(color(255));
    }
  }

  for (let i = 0; i < closedSet.length; i++) {
    closedSet[i].show(color(255, 0, 0));
  }

  for (let i = 0; i < openSet.length; i++) {
    openSet[i].show(color(0, 255, 0));
  }

  path = [];
  let temp = current;
  path.push(temp);
  while (temp.previous) {
    path.push(temp.previous);
    temp = temp.previous;
  }
  for (let i = 0; i < path.length; i++) {
    path[i].show(color(0, 0, 255));
  }

  // noLoop();
}

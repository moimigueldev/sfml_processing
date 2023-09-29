const points = [];

let left;

const hull = [];

let buffer = 20;
let leftMost;
let currentVertex;
let index = 0;
let nextIndex = -1;
let nextVertex;

function setup() {
  createCanvas(500, 500);
  for (let index = 0; index < 10; index++) {
    points.push(
      createVector(
        random(buffer, width - buffer),
        random(buffer, height - buffer)
      )
    );
  }

  // a will be sorted before b
  points.sort((a, b) => a.x - b.x);
  leftMost = points[0];
  currentVertex = leftMost;
  hull.push(currentVertex);
  nextVertex = points[1];
  index = 2;
  frameRate(10);
}

function draw() {
  // put drawing code here
  background(0);
  stroke(255);
  strokeWeight(8);
  for (let p of points) {
    point(p.x, p.y);
  }

  stroke(0, 0, 255);
  fill(0, 0, 255, 50);
  beginShape();
  for (let p of hull) {
    vertex(p.x, p.y);
  }
  endShape(CLOSE);

  stroke(0, 255, 0);
  strokeWeight(32);
  point(leftMost.x, leftMost.y);

  stroke(200, 0, 255);
  strokeWeight(32);
  point(currentVertex.x, currentVertex.y);

  stroke(0, 255, 0);
  strokeWeight(2);
  line(currentVertex.x, currentVertex.y, nextVertex.x, nextVertex.y);

  let checking = points[index];
  stroke(255);
  line(currentVertex.x, currentVertex.y, checking.x, checking.y);

  const a = p5.Vector.sub(nextVertex, currentVertex);
  const b = p5.Vector.sub(checking, currentVertex);
  const cross = a.cross(b);

  console.log("cross", cross.z);

  if (cross.z < 0) {
    nextVertex = checking;
    nextIndex = index;
  }
  index = index + 1;
  if (index == points.length) {
    if (nextVertex == leftMost) {
      console.log("done;");
      noLoop();
    }
    hull.push(nextVertex);
    currentVertex = nextVertex;
    index = 0;
    // points.splice(nextIndex, 1);
    nextVertex = leftMost;
    // noLoop();
  }
}

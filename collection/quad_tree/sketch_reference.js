let qtree;
let count = 100;

function setup() {
  createCanvas(400, 400);

  let boundary = new Rectangle(200, 200, 200, 200);
  qtree = new QuadTree(boundary, 4);

  for (let index = 0; index < 200; index++) {
    let p = new Point(random(width), random(height));
    qtree.insert(p);
  }
  console.log("qtree", qtree);
}

function draw() {
  // put drawing code here

  if (mouseIsPressed) {
    console.log("click");
    for (let index = 0; index < 5; index++) {
      let m = new Point(mouseX + random(-5, 5), mouseY + random(-5, 5));
      qtree.insert(m);
    }
  }

  background(0);
  qtree.show();

  stroke(0, 255, 0);
  rectMode(CENTER);
  let range = new Rectangle(mouseX, mouseY, 25, 25);
  rect(range.x, range.y, range.w * 2, range.h * 2);

  let points = qtree.query(range, count);

  for (let p of points) {
    strokeWeight(4);
    point(p.x, p.y);
  }

  // console.log(count);

  // noLoop();
}

function setup() {
  createCanvas(400, 400);

  let boundary = new Rectangle(200, 200, 200, 200);
  let qt = new QuadTree(boundary, 4);

  for (let index = 0; index < 50; index++) {
    let p = new Point(random(width), random(height));
    qt.insert(p);
  }
  console.log("qt", qt);
}

function draw() {
  // put drawing code here

  noLoop();
}

let qtree;

function setup() {
  createCanvas(400, 400);

  let boundary = new Rectangle(200, 200, 200, 200);
  qtree = new QuadTree(boundary, 4);

  // for (let index = 0; index < 500; index++) {
  //   let p = new Point(random(width), random(height));
  //   qtree.insert(p);
  // }
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

  // noLoop();
}

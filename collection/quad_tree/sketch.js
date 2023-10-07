let particles = [];

function setup() {
  createCanvas(600, 400);

  for (let index = 0; index < 1000; index++) {
    particles[index] = new Particle(random(width), random(height));
  }
}

function draw() {
  background(0);

  let boundary = new Rectangle(300, 200, 600, 400);
  qtree = new QuadTree(boundary, 4);

  // draw Boundary
  // stroke(255, 0, 0);
  // noFill();
  // strokeWeight(4);
  // rectMode(CENTER);
  // rect(300, 200, 600, 400);

  for (let index = 0; index < particles.length; index++) {
    let point = new Point(
      particles[index].x,
      particles[index].y,
      particles[index]
    );
    qtree.insert(point);
    particles[index].move();
    particles[index].render();
    particles[index].setHighlight(false);
  }

  for (let p of particles) {
    // circle is the range
    let range = new Circle(p.x, p.y, p.r * 2);

    // draw range
    // stroke(0, 255, 0);
    // strokeWeight(1);
    // ellipse(p.x, p.y, p.r * 2); // Draw a circle at (200, 200) with a diameter of 50 pixels
    //
    let points = qtree.query(range);
    for (let point of points) {
      let other = point.userData;
      if (p !== other && p.intersects(other)) {
        p.setHighlight(true);
      }
    }
  }

  qtree.show();
}

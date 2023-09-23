let circles = [];
let numOfCircles = 2000;
let canvasWidth = 1600;
let canvasHeight = 1000;

function setup() {
  createCanvas(canvasWidth, canvasHeight);
  for (let i = 0; i < numOfCircles; i++) {
    circles.push(new Circle());
  }
}

function draw() {
  background(68, 70, 83);
  for (let circle of circles) {
    circle.update();
    circle.display();
  }
}

class Circle {
  constructor() {
    this.radius = random(10, 50);
    this.x = random(this.radius, canvasWidth - this.radius);
    this.y = random(this.radius, canvasHeight - this.radius);
    this.speed = 6.0;
    this.vx = this.speed + random(0, 9) / 10.0;
    this.vy = this.speed + random(0, 9) / 10.0;
    if (random() > 0.5) this.vx = -this.vx;
    if (random() > 0.5) this.vy = -this.vy;
    this.color = color(random(255), random(255), random(255));
  }

  update() {
    this.x += this.vx;
    this.y += this.vy;

    if (this.x > canvasWidth) {
      this.x = this.radius;
    }
    if (this.x < 0) {
      this.x = canvasWidth - this.radius;
    }
    if (this.y > canvasHeight) {
      this.y = this.radius;
    }
    if (this.y < 0) {
      this.y = canvasHeight - this.radius;
    }
  }

  display() {
    stroke(this.color);
    strokeWeight(5);
    noFill();
    ellipse(this.x, this.y, this.radius * 2);
  }
}

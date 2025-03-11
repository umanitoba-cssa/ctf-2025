PImage p;
PFont f;
String s = " cssactf{m0710n_15_l0710n}";
int i = 0;

void setup() {
  size(1024, 768);
  p = loadImage("in.jpg");
  f = createFont("Cambria Math", min(width, height)*7/8, true);
  fill(255);
  textAlign(CENTER, CENTER);
  textFont(f);
}

void draw() {
  background(0);
  image(p, 0, 0);
  text(s.charAt(i), width/2, (height-textDescent())/2);
  saveFrame("frame##.jpg");
  i++;
  if(i == s.length()) {
    exit();
  }
}

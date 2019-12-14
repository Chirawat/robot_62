const int outputEnabled = 2; // write LOW to turn on Note, may not be hooked up.
const int s0 = 7; // sensor pins
const int s1 = 8;
const int s2 = 9;
const int s3 = 10;
const int nLED = 11; // illuminating LED
const int out = 12; // TCS230 output

// variables to store color values
int red = 0;
int green = 0;
int blue = 0;

void setup() {
  pinMode(outputEnabled, OUTPUT);
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(nLED, OUTPUT);
  pinMode(out, INPUT);
  Serial.begin(9600);
  //This pin may be set to ground and not available on the breakout
  //If not available don't worry about it.
  digitalWrite(outputEnabled, LOW);
  //Set Frequency scaling to largest value
  digitalWrite(s0, HIGH);
  digitalWrite(s1, HIGH);
  digitalWrite(nLED, LOW);
}

void loop() {
  color();
  Serial.print("R");
  Serial.print(red, DEC);
  Serial.print(" G");
  Serial.print(green, DEC);
  Serial.print(" B");
  Serial.print(blue, DEC);
  Serial.println();
  //Simple logic to test for color
  if (blue > red && blue > green)
    Serial.println("Yellow");
  else if (red < blue && red < green) 
    Serial.println("Red");
  else if (blue < red && blue < green) 
    Serial.println("blue");
  else 
    Serial.println("green");
  delay(1000);
}
  
void color() {
  digitalWrite(nLED,1);
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  // count OUT, pRed, RED
  red = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  digitalWrite(s3, HIGH);
  //count OUT, pBLUE, BLUE
  blue = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  digitalWrite(s2, HIGH);
  // count OUT, pGreen, GREEN
  green = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  digitalWrite(nLED,0);
}

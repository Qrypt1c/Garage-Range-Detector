int red = 12;
int green = 11;
int blue = 10;

int trigger = 14;
int echo = 15;

float duration = 0;
float distance = 0;

void setup() {
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(blue, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);

  duration = pulseIn(echo, HIGH);

  long distance_cm = ((duration * 0.034) / 2);

  if (distance_cm < 10){
    colorfn(green);
  }

  else{
    colorfn(red);
  }

  Serial.print("Distance = ");
  Serial.print(distance_cm);
  Serial.println(" cm");
}

long Distance(long time){
  return ((time * 0.034) / 2);
}

void colorfn(int color){
  digitalWrite(color, HIGH);
  delay(2000);
  digitalWrite(color, LOW);
  delay(1000);
}
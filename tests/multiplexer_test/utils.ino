//Utilities
//Pins: pinModePower
//Math: absi,clampi,clampf,mapi_clamp,mapf
//Print: pr, prln - shortening for Serial.print,Serial.println

//---------------------------------------------------------------
//Set pin to output and write initial power there
void pinModePower(byte pin, byte value) {
  pr("pin "); pr(pin); pr(" set to "); prln((value) ? "HIGH" : "LOW");
  pinMode(pin, OUTPUT);
  digitalWrite(pin, (value) ? HIGH : LOW);
}

//---------------------------------------------------------------
//abs function, Arduino's abs works not correct for me in some cases
int absi(int i) {
  return  (i >= 0) ? i : -i;
}

int clampi(int i, int a, int b) {
  if (a > b) {
    int t = a;
    a = b;
    b = t;
  }
  if (i < a) return a;
  if (i > b) return b;
  return i;
}

inline float clampf(float i, float a, float b) {
  if (a > b) {
    float t = a;
    a = b;
    b = t;
  }
  if (i < a) return a;
  if (i > b) return b;
  return i;
}

int mapi_clamp(int i, int a, int b, int A, int B) {
  return clampi(map(i, a, b, A, B), A, B);
}

float mapf(float x, float a, float b, float A, float B) {
  return (x - a) / (b - a) * (B - A) + A;
}
//---------------------------------------------------------------
//print routines - use their for shortening code
void pr(const char *str) {
  Serial.print(str);
}
void prln(const char *str) {
  Serial.println(str);
}
void pr(int i) {
  Serial.print(i);
}
void prln(int i) {
  Serial.println(i);
}
void pr(uint32 i) {
  Serial.print(i);
}
void prln(uint32 i) {
  Serial.println(i);
}
void pr(long i) {
  Serial.print(i);
}
void prln(long i) {
  Serial.println(i);
}

void pr(long long i) {
  Serial.print(long(i));
}
void prln(long long i) {
  Serial.println(long(i));
}
void pr(unsigned long long i) {
  Serial.print((unsigned long)(i));
}
void prln(unsigned long int i) {
  Serial.println((unsigned long)(i));
}
void prln() {
  Serial.println();
}
void pr(float x) {
  Serial.print(x);
}
void prln(float x) {
  Serial.println(x);
}

//---------------------------------------------------------------

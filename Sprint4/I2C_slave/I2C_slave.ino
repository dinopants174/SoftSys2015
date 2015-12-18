#include <Wire.h>
#include <MatrixMath.h>

#define N  (2)

float A[N][N];
float B[N][N];
float C[N][N];

int x = 0;
int count = 0;
String data = "";

void setup() {
  // Initialize matrices
  A[0][0] = 3;
  A[0][1] = 0;
  A[1][0] = 0;
  A[1][1] = 1;
  
  Serial.begin(9600); 
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB
  }
  // Start the I2C Bus as Slave on address 9
  Wire.begin(9); 
  // Attach a function to trigger when something is received.
  Wire.onReceive(receiveEvent);
}

void receiveEvent(int bytes) {
  while(Wire.available()){
    char c = Wire.read();
    data += c;
    count++;
    if (count >= 8){
      break;
    }
    }
  data += ']';
  
}

void loop() {
 
 if (data.length() == 9){
 stringToMatrix(B, data);
 printMatrixResult(*A, *B, N, N, N, *C);
 delay(5000); 
 }

}

int printMatrixResult(float* A, float* B, int m, int p, int n, float* C) {
  
  Matrix.Print(A,m,n,"A");
  Matrix.Print(B,m,n,"B");
  Matrix.Multiply(A,B,m,p,n,C);
  Serial.println("\nC = A*B");
  Matrix.Print(C,m,n,"C");
  return 0;
}

void stringToMatrix(float matrix[N][N], String input) {
  int i, j, k, q;
  i = 0;
  j = 0;
  for (k=0;k<input.length();k+=2){
    switch(input[k]) {
      case '[':
        q = input[k+1];
        matrix[i][j] = q - 48;
        j++;
        break;
      case ',':
        q = input[k+1];
        matrix[i][j] = q - 48;
        j++;
        break;
      case ';':
        q = input[k+1];
        matrix[i][j] = q - 48;
        j++;
        break;
      case ']':
        break; 
    } 
  }
}

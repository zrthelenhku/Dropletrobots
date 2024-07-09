const int RST = 10;
const int SI = 11;
const int SCLK = 12;
const int CS1 = 8;
const int CS2 = 9;

int interval = 1000;
int incomingByte = 0;
int x, y;
//temporary coordinate example
int x1_array []={5,6,6,7,8};

int y1_array []={1,1,2,2,2};

int x2_array []={26,26,26,26,27};

int y2_array []={1,2,3,4,4};

int x3_array []={2,3,3,3,4};

int y3_array []={30,29,28,27,27};


int list1=0;
int list2=0;
int list3=0;

int flag=1;


//All switches are off
void clearSwitch() {                                                                           
  digitalWrite(CS1, HIGH);
  digitalWrite(CS2, HIGH);
  digitalWrite(RST, LOW);
  delayMicroseconds(2);
  digitalWrite(RST, HIGH);
  delayMicroseconds(2);
}

void setup() {
  pinMode(RST, OUTPUT);
  pinMode(SI, OUTPUT);
  pinMode(SCLK, OUTPUT);
  pinMode(CS1, OUTPUT);
  pinMode(CS2, OUTPUT);

  clearSwitch();

  //Set initial coordination
  x = 5;
  y = 1;
  
  Serial.begin(9600); 
  //Output coordinate in serial monitor
  Serial.print("Start Coordinate: ( ");
  Serial.print(x);
  Serial.print(" , ");
  Serial.print(y);
  Serial.println(" )");
}

//Set specific Pin to High or Low
void setPin(int pin, int val) {
  digitalWrite(pin, val);
  delayMicroseconds(2);
}

//Driver for MC33996
void commandMC33996(int output) {
  setPin(SCLK, LOW);
  setPin(CS2, LOW); //NEED TO DEFINE CS2 PIN
  
  for(int i = 0; i < 8; i++){
    setPin(SCLK,HIGH);
    setPin(SI,LOW);
    setPin(SCLK,LOW);
  }
  for(int i = 32; i > 16; i--){
    setPin(SCLK,HIGH);
    if(i == output) setPin(SI,HIGH);
    else setPin(SI,LOW);
    setPin(SCLK,LOW);
  }
  for(int i = 0; i < 8; i++){
    setPin(SCLK,HIGH);
    setPin(SI,LOW);
    setPin(SCLK,LOW);
  }
  for(int i = 16; i > 0; i--){
    setPin(SCLK,HIGH);
    if(i == output) setPin(SI,HIGH);
    else setPin(SI,LOW);
    setPin(SCLK,LOW);
  }
  setPin(CS2, HIGH);
}

//Driver for MAX14662
void commandMAX14662(int output) {
  setPin(SCLK, HIGH);
  setPin(CS1, LOW); //NEED TO DEFINE CS1 PIN 
  
  //Shift in the data
  for(int i = 32; i > 0; i--){
    setPin(SCLK,LOW);
    if(i == output) setPin(SI,HIGH);
    else setPin(SI,LOW);
    setPin(SCLK,HIGH);
  }
  
  setPin(CS1, HIGH);
}

//Actuate one coil in the matrix according to coordinate, other coils are off;
//x is row, y is column
void selectMatrixCoil(int x, int y) {
  commandMC33996(0);
  commandMC33996(x);
  commandMAX14662(0);
  commandMAX14662(y);
}

//Control the direction of motion by typing "W":Up, "S":Down, "A":Left, "D":Right, "X":Down*2, "C":Down*3
//Start point is based on setup()
//Coordinate is shown in Serial Monitor
void serialControl() {
  if (Serial.available() > 0) {
    incomingByte = Serial.read();

    if ((incomingByte == 'w') || (incomingByte == 'W')) {
      y++;
      Serial.print("Moving Up...  ");
    }
    else if ((incomingByte == 's') || (incomingByte == 'S')) {
      y--;
      Serial.print("Moving Down...  ");
    }
    else if ((incomingByte == 'a') || (incomingByte == 'A')) {
      x++;
      Serial.print("Moving Left...  ");
    }
    else if ((incomingByte == 'd') || (incomingByte == 'D')) {
      x--;
      Serial.print("Moving Right...  ");
    }
    else if ((incomingByte == 'x') || (incomingByte == 'X')) {
      y++;
      selectMatrixCoil(x, y); delay(100);
      y++;
      selectMatrixCoil(x, y); delay(100);
      y++;
      Serial.print("Moving up * 3 ...  ");
    }
    else if ((incomingByte == 'c') || (incomingByte == 'C')) {
      y--;
      selectMatrixCoil(x, y); delay(100);
      y--;
      selectMatrixCoil(x, y); delay(100);
      y--;
      Serial.print("Moving Down * 3 ...  ");
    }
    //switch control among different grippers
    else if ((incomingByte == 'i') || (incomingByte == 'I')) {
      if(flag==2)
      {
      list2++;
      x2_array [list2]=x;
      y2_array [list2]=y;
      }
      else if(flag==3)
      {
      list3++;
      x3_array [list3]=x;
      y3_array [list3]=y;
      }
      flag=1;
      x=x1_array [list1];
      y=y1_array [list1];
      Serial.print("Reading list +1...  ");
      Serial.print("list_robot1= ");
      Serial.print(list1);
    }
    //switch control among different grippers
    else if ((incomingByte == 'o') || (incomingByte == 'O')) {
      if(flag==1)
      {
      list1++;
      x1_array [list1]=x;
      y1_array [list1]=y;
      }
      else if(flag==3)
      {
      list3++;
      x3_array [list3]=x;
      y3_array [list3]=y;
      }
      flag=2;
      x=x2_array [list2];
      y=y2_array [list2];
      Serial.print("Reading list +1...  ");
      Serial.print("list_robot2= ");
      Serial.print(list2);
    }
    //switch control among different grippers
    else if ((incomingByte == 'p') || (incomingByte == 'P')) {
      if(flag==1)
      {
      list1++;
      x1_array [list1]=x;
      y1_array [list1]=y;
      }
      else if(flag==2)
      {
      list2++;
      x2_array [list2]=x;
      y2_array [list2]=y;
      }
      flag=3;
      x=x3_array [list3];
      y=y3_array [list3];
      Serial.print("Reading list +1...  ");
      Serial.print("list_robot3= ");
      Serial.print(list3);
    }
    else if ((incomingByte == 'y') || (incomingByte == 'Y')) {
      for(int i=7;i<18;i++){
        selectMatrixCoil(i,16);
        delay(20);
      }
    }
    if (incomingByte != '\n') {
      Serial.print("Coordinate: ( ");
      Serial.print(x);
      Serial.print(" , ");
      Serial.print(y);
      Serial.println(" )");
    }
    //selectMatrixCoil(x, y);

  }
}

void loop(){
  serialControl();
  selectMatrixCoil(x,y);
}

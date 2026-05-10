#define IR1 22
#define IR2 23
#define IR3 24

#define ENRight 7
#define ENLeft 9
#define IN_right 6
#define IN_left 8
#define RIGHTSPEED  180
#define LEFTSPEED  180

int ADDD=10;
int sensor1,sensor2,sensor3;
int TO_RP=10;
char val;
int xp=A0,yp=A1,X,Y;
int buzzer=11;

void setup() {
  pinMode(TO_RP, OUTPUT);

  pinMode(ENRight, OUTPUT);
  pinMode(ENLeft, OUTPUT);
  pinMode(IN_right, OUTPUT);
  pinMode(IN_left, OUTPUT);
    pinMode(buzzer, OUTPUT);
  pinMode(IR1, INPUT_PULLUP);
  pinMode(IR2, INPUT_PULLUP);
  pinMode(IR3, INPUT_PULLUP);
  pinMode(xp, INPUT);
  pinMode(yp, INPUT);
  
  Serial.begin(9600); 
}

void loop() {
  // put your main code here, to run repeatedly:
  sensor_readind();
    if(sensor1==0 || sensor2==0 || sensor3==0)digitalWrite(buzzer,HIGH);
    else digitalWrite(buzzer,LOW);
    
     if(sensor1==1 && sensor2==1 && sensor3==1){controlJOYSTICK();}
else if(sensor1==1 && sensor2==0 && sensor3==1){controlJOYSTICK_WITHOUT_FWD();}
else if(sensor1==0 && sensor2==0 && sensor3==1){ LEFT();}
else if(sensor1==0 && sensor2==1 && sensor3==1){ LEFT();}
else if(sensor1==1 && sensor2==0 && sensor3==0){ RIGHT();}
else if(sensor1==1 && sensor2==1 && sensor3==0){RIGHT();}
else if(sensor1==0 && sensor2==0 && sensor3==0){controlJOYSTICK_only_back();digitalWrite(buzzer,HIGH);}



 // serial_display();
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void sensor_readind() {
   sensor1 = digitalRead(IR1);    
   sensor2 = digitalRead(IR2);    
   sensor3 = digitalRead(IR3);   
}

//------------------------------------------------------------------------------------
void serial_display() {
  Serial.print("sensor1= ");   Serial.print(sensor1);
  Serial.print(" | sensor2= ");Serial.print(sensor2);
  Serial.print(" | sensor3= ");Serial.print(sensor3);
  Serial.print(" | X= ");Serial.print(X);
  Serial.print(" | Y= ");Serial.print(Y);
  Serial.print(" | TORP= ");Serial.print(1);  
  Serial.println();
}

void controlJOYSTICK() {
    Serial.println("normal");
  if(Serial.available()) {
     val=Serial.read();
  }
  X=analogRead(xp);
  Y=analogRead(yp);
  
  if(val=='f' || X>900) fwd();
  if(val=='b' || X<200) bck();
  if(val=='r' || Y<200 ) RIGHT();
  if(val=='l' || Y>900) LEFT();
  if(val=='s' || (X>=200 && X<=900 && Y>=200 && Y<=900 )) STOP();
}
void controlJOYSTICK_WITHOUT_FWD() {
Serial.println("obstcle in middle");
  X=analogRead(xp);
  Y=analogRead(yp);
  if(X<300) bck();
  if(Y<300) RIGHT();
  if(Y>800) LEFT();
  if(X>=300 && X<=800 && Y>=300 && Y<=800 ) STOP();

}
void controlJOYSTICK_only_back() {
Serial.println("must back ");
  X=analogRead(xp);
  Y=analogRead(yp);
  if( X<300) bck();
  if(X>=300 && X<=800 && Y>=300 && Y<=800 ) STOP();
}
//==============================================
void fwd() {
    Serial.print(" fwd ");
    analogWrite(ENRight,LEFTSPEED);//f_left
    analogWrite(ENLeft,LEFTSPEED);//b_left
    digitalWrite(IN_right, HIGH);
    digitalWrite(IN_left, HIGH);
    val='0';
 }

void RIGHT() {
    Serial.print(" right ");
    analogWrite(ENRight,LEFTSPEED+50);
    analogWrite(ENLeft,LEFTSPEED+50);
    
    digitalWrite(IN_right, HIGH);
    digitalWrite(IN_left, LOW);
    val='0';
  }

void LEFT() {
    Serial.print(" left ");

    analogWrite(ENRight,LEFTSPEED+50);
    analogWrite(ENLeft,LEFTSPEED+50);//

    digitalWrite(IN_right, LOW);
    digitalWrite(IN_left, HIGH);
    val='0';
 }

void STOP() {
   Serial.print(" STOP ");

   analogWrite(ENRight,0);
   analogWrite(ENLeft,0);
 } 

void bck() {
   Serial.print(" Back ");

   analogWrite(ENRight,LEFTSPEED);
   analogWrite(ENLeft,LEFTSPEED);
   
   digitalWrite(IN_right, LOW);
   digitalWrite(IN_left, LOW);
   val='0';
}

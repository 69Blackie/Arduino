#define  PI_DIN 12
#define  PI_CLK 11
#define  PI_CS 10

#define OP_NOOP   0
#define OP_DIGIT0 1
#define OP_DIGIT1 2
#define OP_DIGIT2 3
#define OP_DIGIT3 4
#define OP_DIGIT4 5
#define OP_DIGIT5 6
#define OP_DIGIT6 7
#define OP_DIGIT7 8
#define OP_DECODEMODE  9
#define OP_INTENSITY   10
#define OP_SCANLIMIT   11
#define OP_SHUTDOWN    12
#define OP_DISPLAYTEST 15
byte Data_Trans[4][2]={{B00000000,B00000000},
                       {B00000000,B00000000},
                       {B00000000,B00000000},
                       {B00000000,B00000000}}; 
byte LedStatu[8][4]={{B00000000,B00000000,B00000000,B00000000},
                     {B00000000,B00000000,B00000000,B00000000},
                     {B00000000,B00000000,B00000000,B00000000},
                     {B00000000,B00110000,B00000000,B00000000},
                     {B00000000,B00000000,B00000000,B00000000},
                     {B00000000,B00000000,B00000000,B00000000},
                     {B00000000,B00000000,B00000000,B00000000},
                     {B00000000,B00000000,B00000000,B00000000}};


void Transfer(){  //the max number of transfer byte is 4x2 (4 devices x 2 bytes)
                 //between PI_CS Low and High
 digitalWrite(PI_CS,LOW);   
  for(int i=0;i<4;i++)
      for(int j=0;j<2;j++){
      shiftOut(PI_DIN,PI_CLK,MSBFIRST,Data_Trans[i][1-j]);
      Data_Trans[i][1-j]=B00000000;
      }
  digitalWrite(PI_CS,HIGH);
}  

void Transfer2(){  //the max number of transfer byte is 4x2 (4 devices x 2 bytes)
                 //between PI_CS Low and High
   

  for(int k=0;k<8;k++){
digitalWrite(PI_CS,LOW);
    for(int i=0;i<4;i++)
      {
                            //to triger series sequence transfer through PIN_DOUT
                           //PI_CLK DOWN and UP 16 times more
                          //PIN_DOUT change at rise of PI_CLK to fullfil the bit by bit transfer
      shiftOut(PI_DIN,PI_CLK,MSBFIRST,(byte)(k+1));
      shiftOut(PI_DIN,PI_CLK,MSBFIRST,0x1<<i);
      }
delay(500);
digitalWrite(PI_CS,HIGH);
  }
}

void Transfer3(){  //the max number of transfer byte is 4x2 (4 devices x 2 bytes)
                 //between PI_CS Low and High
 digitalWrite(PI_CS,LOW);    
     shiftOut(PI_DIN,PI_CLK,MSBFIRST,(byte)(1));
     shiftOut(PI_DIN,PI_CLK,MSBFIRST,0);  
 digitalWrite(PI_CS,HIGH);//PI_CS High is to change the statu according to command in the reservoir waterfall
 delay(1000);
 digitalWrite(PI_CS,LOW);   
     shiftOut(PI_DIN,PI_CLK,MSBFIRST,(byte)(2));
     shiftOut(PI_DIN,PI_CLK,MSBFIRST,0);  
digitalWrite(PI_CS,HIGH);
 delay(1000);
 // for(int k=0;k<8;k++){
 //   for(int i=0;i<4;i++)
  //    {
//digitalWrite(PI_CS,LOW);
                           
     // shiftOut(PI_DIN,PI_CLK,MSBFIRST,(byte)(k+1));
     // shiftOut(PI_DIN,PI_CLK,MSBFIRST,0x1<<i);
 //delay(500);
//digitalWrite(PI_CS,HIGH);
 //     }

//  }
}


void setup() {
  // put your setup code here, to run once:

  pinMode(PI_DIN, OUTPUT);
  pinMode(PI_CLK, OUTPUT);
  pinMode(PI_CS, OUTPUT);
  digitalWrite(PI_CS,HIGH);
  
     for(int i=0;i<4;i++){
        Data_Trans[i][1]=OP_DISPLAYTEST;
        Data_Trans[i][0]=0;
     }
     Transfer();
     for(int i=0;i<4;i++){
        Data_Trans[i][1]=OP_SCANLIMIT;
        Data_Trans[i][0]=7;
     }
     Transfer();
     
     for(int i=0;i<4;i++){
        Data_Trans[i][1]=OP_DECODEMODE;
        Data_Trans[i][0]=0;
     }
     Transfer();
     
     for(int i=0;i<4;i++){
        Data_Trans[i][1]=OP_SHUTDOWN;
        Data_Trans[i][0]=1;
     }
     Transfer();
     
     for(int i=0;i<4;i++){
        Data_Trans[i][1]=OP_INTENSITY;
        Data_Trans[i][0]=1;
     }
     Transfer();
     

}

void loop() {
 
  for(int j=0;j<8;j++){ 
     for(int i=0;i<4;i++){
        Data_Trans[i][1]=j+1;
        Data_Trans[i][0]=LedStatu[j][i];
       }
     Transfer();
    }  


  // put your main code here, to run repeatedly:
//Transfer2();    
//Transfer3();
}

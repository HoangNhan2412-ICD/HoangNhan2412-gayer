
#include <SPI.h>
#include <SD.h>

File myFile;

// chân điều khiển 74HC595
byte DS = A1;
byte STCP = A2;
byte SHCP = A3;

// chân chọn tầng Z
int Tangz[8] = {2,3,4,5,6,7,8,9};

void setup() {
  Serial.begin(9600);

  pinMode(DS, OUTPUT);
  pinMode(STCP, OUTPUT);
  pinMode(SHCP, OUTPUT);

  for(int i=0;i<8;i++){
    pinMode(Tangz[i], OUTPUT);
  }

  randomSeed(analogRead(0));
}

void loop() {

  mua(60,10);

  plane('X',8);
  plane('Y',8);
  plane('Z',8);

  plane2('X',6);
  plane2('Y',6);
  plane2('Z',6);
}

/* =========================
   DRIVER 74HC595
=========================*/

void dich74hc595(byte a){
  if(a==0){
    digitalWrite(DS,LOW);
  }else{
    digitalWrite(DS,HIGH);
  }

  digitalWrite(SHCP,HIGH);
  digitalWrite(SHCP,LOW);
}

void mo74hc595(){
  digitalWrite(STCP,HIGH);
  digitalWrite(STCP,LOW);
}

void resetCube(){
  for(byte i=0;i<64;i++){
    dich74hc595(0);
  }
  mo74hc595();
}

/* =========================
   HIỂN THỊ CUBE
=========================*/

void hienthi(byte mangba[8][8][8], byte Solan){

  for(byte t=0;t<Solan;t++){

    for(byte z=0;z<8;z++){

      for(byte x=0;x<8;x++){
        for(byte y=0;y<8;y++){
          dich74hc595(mangba[x][y][z]);
        }
      }

      mo74hc595();

      digitalWrite(Tangz[z],HIGH);

      resetCube();

      digitalWrite(Tangz[z],LOW);
    }

  }
}

/* =========================
   HIỆU ỨNG MƯA
=========================*/

void mua(int solanmua, byte Solan){

  byte mangba[8][8][8]={0};

  for(byte s=0;s<solanmua;s++){

    byte n=random(1,5);

    for(byte h=0;h<n;h++){
      byte x=random(8);
      byte y=random(8);

      mangba[x][y][7]=1;
    }

    hienthi(mangba,Solan);

    for(byte z=0;z<7;z++){
      for(byte x=0;x<8;x++){
        for(byte y=0;y<8;y++){
          mangba[x][y][z]=mangba[x][y][z+1];
        }
      }
    }

    for(byte x=0;x<8;x++){
      for(byte y=0;y<8;y++){
        mangba[x][y][7]=0;
      }
    }
  }
}

/* =========================
   HIỆU ỨNG PLANE
=========================*/

void plane(char truc, byte Solan){

  byte mangba[8][8][8]={0};

  for(byte i=0;i<8;i++){

    for(byte z=0;z<8;z++){
      for(byte x=0;x<8;x++){
        for(byte y=0;y<8;y++){

          mangba[x][y][z]=0;

          if(truc=='X') mangba[i][y][z]=1;
          if(truc=='Y') mangba[x][i][z]=1;
          if(truc=='Z') mangba[x][y][i]=1;

        }
      }
    }

    hienthi(mangba,Solan);
  }

  for(int i=7;i>=0;i--){

    for(byte z=0;z<8;z++){
      for(byte x=0;x<8;x++){
        for(byte y=0;y<8;y++){

          mangba[7-x][7-y][7-z]=0;

          if(truc=='X') mangba[i][7-y][7-z]=1;
          if(truc=='Y') mangba[7-x][i][7-z]=1;
          if(truc=='Z') mangba[7-x][7-y][i]=1;

        }
      }
    }

    hienthi(mangba,Solan);
  }
}

/* =========================
   HIỆU ỨNG PLANE2
=========================*/

void plane2(char truc, byte Solan){

  byte mangba[8][8][8]={0};
  byte manghai[8][8]={0};

  for(byte x=0;x<8;x++){
    for(byte y=0;y<8;y++){

      if(truc=='X') mangba[0][x][y]=1;
      else if(truc=='Y') mangba[x][0][y]=1;
      else mangba[x][y][0]=1;

    }
  }

  hienthi(mangba,Solan*2);

  for(byte i=1;i<8;i++){

    byte u=0;

    while(u<8){

      byte x=random(8);
      byte y=random(8);

      if(manghai[x][y]==0){

        manghai[x][y]=1;
        u++;

        hienthi(mangba,1);
      }
    }

    for(byte x=0;x<8;x++){
      for(byte y=0;y<8;y++){

        if(manghai[x][y]==0){

          if(truc=='X'){
            mangba[i][x][y]=1;
            mangba[i-1][x][y]=0;
          }

          else if(truc=='Y'){
            mangba[x][i][y]=1;
            mangba[x][i-1][y]=0;
          }

          else{
            mangba[x][y][i]=1;
            mangba[x][y][i-1]=0;
          }

        }
      }
    }

  }

  hienthi(mangba,Solan);
}

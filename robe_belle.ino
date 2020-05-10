#include <LEDMatrixDriver.hpp>
 
const uint8_t LEDMATRIX_CS_PIN = 9;
const int LEDMATRIX_SEGMENTS = 4;
const int LEDMATRIX_WIDTH    = LEDMATRIX_SEGMENTS * 8;

LEDMatrixDriver lmd(LEDMATRIX_SEGMENTS, LEDMATRIX_CS_PIN);
const int ANIM_DELAY = 50;
byte anim[2][8]={{0x00, 0x38, 0x28, 0x38, 0x10, 0x10, 0x28, 0x44},
                {0x00, 0x38, 0x28, 0x38, 0x10, 0x10, 0x10, 0x10},};
byte anim2[2][8]={{0x00, 0x38, 0x28, 0x3b, 0x1e, 0x10, 0x28, 0x44},
                {0x00, 0x38, 0x28, 0x3b, 0x1e, 0x10, 0x10, 0x10},};
byte mandying[3][8]{{0x00,0x00,0x70,0x50,0x70,0x20,0xe0,0xb0},
                    {0x00,0x00,0x04,0x0a,0x2c,0x10,0xe0,0xb0},
                    {0x00,0x00,0x00,0x00,0x00,0x00,0x0e,0xfe},
                    };
void setup() {
  lmd.setEnabled(true);
  lmd.setIntensity(4);
}
int x=0, y=0; 
  int i=0;
  int man1=3;
  int man2=20;
void loop() {

//first man walks
  for(int j=-7; j<man1; j++)
  {
    draw(x+j, y, anim[i]);
    lmd.display();
    if(j%2==0)
    {
        i=!i;
    }
    delay(ANIM_DELAY);
  }
  //second man walks
  for(int j=33; j>man2-4; j--)
  {
    draw(x+j, y, anim[i]);
    lmd.display();
    if(j%2==0)
    {
        i=!i;
    }
    delay(ANIM_DELAY);
  }
  //first man withdraws gun
  draw(man1-1,y,anim2[0]);
  //shot
  for(int j=man1+8;j<man2;j++)
  {
    if(j>man1+8)
    {
      lmd.setPixel(j-1, 3, 0);
    }
     lmd.setPixel(j, 3, 1);
     lmd.display();
     delay(ANIM_DELAY);
  }
  for(int j=0; j<3; j++)
  {
    draw(man2-1,y,mandying[j]);
    lmd.display();
    delay(ANIM_DELAY+40);
    if(j==1) delay(20);
  }
  //first man walks with gun
  for(int j=man1; j<32; j++)
  {
    draw(x+j, y, anim2[i]);
    lmd.display();
    if(j%2==0)
    {
        i=!i;
    }
    delay(ANIM_DELAY);
  }
}
void draw(int x, int y, byte* d)
{
  byte mask= B10000000;
  for(int y1=0; y1<8; y1++)
  {
    for(int x1=0; x1<8; x1++)
    {
      lmd.setPixel(x+x1, y+y1, (bool)(d[y1]&mask));
      mask=mask>>1;
    }
    mask=B10000000;
  }
}

// Strick chaotic map //

#include "SPI.h"
#include "GD.h"

  byte i;
  float x = 0.1f;
  float y = 0.1f;
  float a = 0.5f;
  float b = 1.1f;
       
void setpixel(byte x, byte y, byte color){
  
  unsigned int addr = RAM_SPRIMG|(x & 0xf)|(y << 4)|((x & 0x30)<<8);
  byte mask = 0xc0 >> ((x >> 5) & 6);
  GD.wr(addr, (GD.rd(addr) & ~mask) | (color & mask));

}

void setup(){
  
  int i;
  GD.begin();
  GD.ascii();
  
  for (i = 0; i < 256; i++) {
    int x = 72 + 16 * ((i >> 4) & 15);
    int y = 22 + 16 * (i & 15); 
    int image = i & 63;
    int pal = 3-(i >> 6);
    GD.sprite(i, x, y, image, 0x8 | (pal << 1), 0,0);
  }
  
  GD.fill(RAM_SPRIMG, 0, 16384);
  GD.wr16(PALETTE4A + 6, RGB(0,255,255));
  GD.putstr(16, 1, "Strick chaotic map");
  GD.putstr(16, 36, "Created by JLS 2021");
    
}

void loop(){
  
  float nx = x;
  if (fabs(nx)<0.5f){
    x = (2.0f-a)*nx-b*y;
    y = -b*nx+a*y;
  } else {
    x = a*nx-b*y+(1.0f-a)*(nx/fabs(nx));
    y = b*nx+a*y-b*(nx/fabs(nx));
  }
  
  setpixel(128+(66*x), 128+(108*y), 255);
       
}

// Horseshoe chaotic map //

#include "SPI.h"
#include "GD.h"

  byte i;
  float x;
  float y;
  float a = 0.9809966f;
  float b = 0.19657558f;
  float c = -1.3123202f;
  float d = 0.98187745f;
  float e = 0.71452355f;
  float f = 0.02965593f;
       
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
  GD.putstr(15, 1, "Horseshoe chaotic map");
  GD.putstr(16, 36, "Created by JLS 2021");
    
}

void loop(){
  
  float tx = a*x + b*y + c;
  float ty = d*x + e*y + f;
    
  float a1 = atan2f(tx, ty);
  float c1 = sinf(a1);
  float c2 = cosf(a1);
    
  x = c1*tx - c2*ty;
  y = c2*tx + c1*ty;
  
  setpixel(133+(24*x), 78+(24*y), 255);
       
}

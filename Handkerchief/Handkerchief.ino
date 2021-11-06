// Handkerchief chaotic map //

#include "SPI.h"
#include "GD.h"

  byte i;
  float x;
  float y;
  float a = 0.5484506f;
  float b = 0.06226462f;
  float c = 0.6522658f;
  float d = 0.79520136f;
  float e = 0.92721486f;
  float f = 1.8089988f;
       
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
  GD.putstr(13, 1, "Handkerchief chaotic map");
  GD.putstr(16, 36, "Created by JLS 2021");
    
}

void loop(){
  
  float tx = a*x + b*y + c;
  float ty = d*x + e*y + f;
    
  float a1 = atan2f(tx, ty);
  float r = sqrtf(tx*tx + ty*ty);
    
  x = r * sinf(a1 + r);
  y = r * cosf(a1 - r);

  int xx = 128+(9*x);
  int yy = 128+(9*y);
  
  if(xx>0 && xx<256 && yy>0 && yy<256) setpixel(xx, yy, 255);
       
}

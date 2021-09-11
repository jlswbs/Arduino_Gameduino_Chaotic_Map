// Fractal-Dream chaotic map //

#include "SPI.h"
#include "GD.h"

  byte i;
  float a = -0.966918f;
  float b = 2.879879f;
  float c = 0.765145f;
  float d = 0.744728f;
  float x = 0.1f;
  float y = 0.1f;
       
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
  GD.putstr(13, 1, "Fractal-Dream chaotic map");
  GD.putstr(16, 36, "Created by JLS 2021");
    
}

void loop(){
  
  float nx = x;
  x = sinf(y*b)+c*sinf(nx*b);
  y = sinf(nx*a)+d*sinf(y*a);
  
  setpixel(128+(71*x), 128+(88*y), 255);
       
}

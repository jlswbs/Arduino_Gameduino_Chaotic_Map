// Pickover chaotic map //

#include "SPI.h"
#include "GD.h"

  byte i;
  float a = -0.75f;
  float b = 2.44f;
  float c = 1.25f;
  float d = 1.5f;
  float x = 0.1f;
  float y = -0.4f;
  float z = 0.1f;
       
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
  GD.putstr(15, 1, "Pickover chaotic map");
  GD.putstr(16, 36, "Created by JLS 2021");
    
}

void loop(){

  float nx = x;
  x = sinf(a*y)-z*cosf(b*nx);
  y = z*sinf(c*nx)-cosf(d*y);
  z = sinf(nx);
 
  setpixel(78+(325*x), 228+(216*y), 255);
       
}

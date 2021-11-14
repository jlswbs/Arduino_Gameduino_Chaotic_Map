// Quadratic chaotic map //

#include "SPI.h"
#include "GD.h"

  byte i;
  float x = 0.1f;
  float y = 0.1f;
  float a1 = -1.0f;
  float a2 = 0.9f;
  float a3 = 0.4f;
  float a4 = -0.2f;
  float a5 = -0.6f;
  float a6 = -0.5f;
  float a7 = 0.4f;
  float a8 = 0.7f;
  float a9 = 0.3f;
  float a10 = -0.5f;
  float a11 = 0.7f;
  float a12 = -0.8f;
       
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
  GD.putstr(15, 1, "Quadratic chaotic map");
  GD.putstr(16, 36, "Created by JLS 2021");
    
}

void loop(){
  
  float nx = x;
    
  x = a1+a2*nx+a3*powf(nx,2.0f)+a4*nx*y+a5*y+a6*powf(y,2.0f);
  y = a7+a8*nx+a9*powf(nx,2.0f)+a10*nx*y+a11*y+a12*powf(y,2.0f);
  
  setpixel(205+(55*x), 77+(102*y), 255);
       
}

// Cubic chaotic map //

#include "SPI.h"
#include "GD.h"

  byte i;
  float x = 0.1f;
  float y = 0.1f;
  float a1 = -0.4f;
  float a2 = 0.6f;
  float a3 = 0.0f;
  float a4 = -0.5f;
  float a5 = 0.4f;
  float a6 = -1.0f;
  float a7 = -0.5f;
  float a8 = 0.3f;
  float a9 = -0.9f;
  float a10 = -0.7f;
  float a11 = -0.2f;
  float a12 = -0.7f;
  float a13 = -1.1f;
  float a14 = -0.2f;
  float a15 = -0.8f;
  float a16 = -1.2f;
  float a17 = -0.1f;
  float a18 = -0.4f;
  float a19 = -0.7f;
  float a20 = -0.9f;
       
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
  GD.putstr(17, 1, "Cubic chaotic map");
  GD.putstr(16, 36, "Created by JLS 2021");
    
}

void loop(){
  
  float nx = x;
    
  x = a1+a2*nx+a3*powf(nx,2.0f)+a4*powf(nx,3.0f)+a5*powf(nx,2.0f)*y+a6*nx*y+a7*nx*powf(y,2.0f)+a8*y+a9*powf(y,2.0f)+a10*powf(y,3.0f);
  y = a11+a12*nx+a13*powf(nx,2.0f)+a14*powf(nx,3.0f)+a15*powf(nx,2.0f)*y+a16*nx*y+a17*nx*powf(y,2.0f)+a18*y+a19*powf(y,2.0f)+a20*powf(y,3.0f);
  
  setpixel(208+(120*x), 160+(148*y), 255);
       
}

// Quartic chaotic map //

#include "SPI.h"
#include "GD.h"

  byte i;
  float x = 0.1f;
  float y = 0.1f;
  float a1 = -0.6f;
  float a2 = 0.1f;
  float a3 = 1.1f;
  float a4 = 0.9f;
  float a5 = 1.2f;
  float a6 = 0.9f;
  float a7 = -1.2f; 
  float a8 = 0.6f;
  float a9 = 1.0f;
  float a10 = 0.0f;
  float a11 = 0.0f;
  float a12 = 0.1f;
  float a13 = -0.7f;
  float a14 = -0.7f;
  float a15 = 0.4f;
  float a16 = 0.2f;
  float a17 = -0.7f;
  float a18 = -0.3f;
  float a19 = 0.7f;
  float a20 = 0.0f;
  float a21 = 0.5f;
  float a22 = -1.1f;
  float a23 = 0.1f;
  float a24 = 0.5f;
  float a25 = -0.7f;
  float a26 = 1.0f;
  float a27 = 0.5f;
  float a28 = -0.8f;
  float a29 = -0.3f;
  float a30 = -0.5f;
       
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
  GD.putstr(16, 1, "Quartic chaotic map");
  GD.putstr(16, 36, "Created by JLS 2021");
    
}

void loop(){
  
  float nx = x;
    
  x = a1+a2*nx+a3*powf(nx,2.0f)+a4*powf(nx,3.0f)+a5*powf(nx,4.0f)+a6*powf(nx,3.0f)*y+a7*powf(nx,2.0f)*y+a8*powf(nx,2.0f)*powf(y,2.0f)+a9*nx*y+a10*nx*powf(y,2.0f)+a11*nx*powf(y,3.0f)+a12*y+a13*powf(y,2.0f)+a14*powf(y,3.0f)+a15*powf(y,4.0f);
  y = a16+a17*nx+a18*powf(nx,2.0f)+a19*powf(nx,3.0f)+a20*powf(nx,4.0f)+a21*powf(nx,3.0f)*y+a22*powf(nx,2.0f)*y+a23*powf(nx,2.0f)*powf(y,2.0f)+a24*nx*y+a25*nx*powf(y,2.0f)+a26*nx*powf(y,3.0f)+a27*y+a28*powf(y,2.0f)+a29*powf(y,3.0f)+a30*powf(y,4.0f);
  
  setpixel(246+(287*x), 73+(446*y), 255);
       
}

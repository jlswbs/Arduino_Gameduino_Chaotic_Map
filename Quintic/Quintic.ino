// Quintic chaotic map //

#include "SPI.h"
#include "GD.h"

  byte i;
  float x = 0.1f;
  float y = 0.1f;
  float a1 = 0.4f;
  float a2 = -1.1f;
  float a3 = -0.2f;
  float a4 = 0.6f;
  float a5 = -0.2f;
  float a6 = -0.4f;
  float a7 = 1.1f;
  float a8 = 0.4f;
  float a9 = 0.0f;
  float a10 = -0.2f;
  float a11 = -0.8f;
  float a12 = 0.2f;
  float a13 = 0.9f;
  float a14 = 0.9f;
  float a15 = 0.0f;
  float a16 = -1.2f;
  float a17 = -0.5f;  
  float a18 = 1.1f;
  float a19 = -0.1f;
  float a20 = -1.1f;
  float a21 = 0.2f;
  float a22 = 0.4f;
  float a23 = 0.4f;
  float a24 = -0.3f;
  float a25 = 1.1f;
  float a26 = -0.8f;
  float a27 = 1.2f;
  float a28 = 0.0f;
  float a29 = -1.1f;
  float a30 = 0.8f;
  float a31 = 0.0f;
  float a32 = -1.1f;
  float a33 = 0.2f;
  float a34 = -0.8f;
  float a35 = -0.7f;
  float a36 = 0.9f;
  float a37 = -0.9f;
  float a38 = -1.1f;
  float a39 = -1.2f;
  float a40 = 0.3f;
  float a41 = 1.0f;
  float a42 = 0.8f; 
  
       
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
  GD.putstr(16, 1, "Quintic chaotic map");
  GD.putstr(16, 36, "Created by JLS 2021");
    
}

void loop(){
  
  float nx = x;
    
  x = a1+a2*nx+a3*powf(nx,2.0f)+a4*powf(nx,3.0f)+a5*powf(nx,4.0f)+a6*powf(nx,5.0f)+a7*powf(nx,4.0f)*y+a8*powf(nx,3.0f)*y+a9*powf(nx,3.0f)*powf(y,2.0f)+a10*powf(nx,2.0f)*y+a11*powf(nx,2.0f)*powf(y,2.0f)+a12*powf(nx,2.0f)*powf(y,3.0f)+a13*nx*y+a14*nx*powf(y,2.0f)+a15*nx*powf(y,3.0f)+a16*nx*powf(y,4.0f)+a17*y+a18*powf(y,2.0f)+a19*powf(y,3.0f)+a20*powf(y,4.0f)+a21*powf(y,5.0f);
  y = a22+a23*nx+a24*powf(nx,2.0f)+a25*powf(nx,3.0f)+a26*powf(nx,4.0f)+a27*powf(nx,5.0f)+a28*powf(nx,4.0f)*y+a29*powf(nx,3.0f)*y+a30*powf(nx,3.0f)*powf(y,2.0f)+a31*powf(nx,2.0f)*y+a32*powf(nx,2.0f)*powf(y,2.0f)+a33*powf(nx,2.0f)*powf(y,3.0f)+a34*nx*y+a35*nx*powf(y,2.0f)+a36*nx*powf(y,3.0f)+a37*nx*powf(y,4.0f)+a38*y+a39*powf(y,2.0f)+a40*powf(y,3.0f)+a41*powf(y,4.0f)+a42*powf(y,5.0f);
  
  setpixel(42+(248*x), 128+(140*y), 255);
       
}

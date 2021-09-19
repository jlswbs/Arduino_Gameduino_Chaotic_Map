// Sunflower chaotic map //

#include "SPI.h"
#include "GD.h"

  byte i;
  float x = 1.86f;
  float y = 1.85f;
  float a = -1.76f;
  float b = 2.0f;
  float c = 0.1f;
  float d = 0.75f;
       
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
  GD.putstr(15, 1, "Sunflower chaotic map");
  GD.putstr(16, 36, "Created by JLS 2021");
    
}

void loop(){
  
  float nx = x;
  x = ((a+b*nx)*(nx+y)) / (1.0f+c*powf(nx,2.0f)+d*powf(y,2.0f));
  y = nx;
  
  setpixel(45+(41*x), 45+(41*y), 255);
       
}

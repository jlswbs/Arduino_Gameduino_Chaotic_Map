// Metz chaotic map //

#include "SPI.h"
#include "GD.h"

  byte i;
  float x = 0.1f;
  float y = 0.1f;
  float a = 4.145f;
  float b = 10.0f;

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
  GD.putstr(17, 1, "Metz chaotic map");
  GD.putstr(16, 36, "Created by JLS 2021");
    
}

void loop(){

  x = random(100);
  y = random(1000)/1000.0f;
  
  for (int i=0;i<100;i++) {

    float nx = x;
    float ny = y;
        
    x = a * nx * expf((1.0f - sqrtf(1.0f + ny)) / b);
    y = a * nx - nx;
    
    setpixel(5+(0.6f*x), 5+(0.19f*y), 255);
    
  }

}

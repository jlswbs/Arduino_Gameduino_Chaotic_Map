// Mira chaotic map //

#include "SPI.h"
#include "GD.h"

  byte i;
  float x = 5.0f;
  float y = 0.0f;
  float f = 0.0f;
  float a = 0.3f;
  float b = 2.0f;
       
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
  GD.putstr(17, 1, "Mira chaotic map");
  GD.putstr(16, 36, "Created by JLS 2021");
    
}

void loop(){
  
  float nx = x;
  x = y + f;
  f = a * x + (b*powf(x,2.0f)*(1.0f-a))/(1.0f+powf(x,2.0f));
  y = -nx + f;    
  
  setpixel(126+(7*x), 128+(7*y), 255);
       
}

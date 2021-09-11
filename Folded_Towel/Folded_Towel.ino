// Folded-Towel chaotic map //

#include "SPI.h"
#include "GD.h"

  byte i;
  float a = 3.8f;
  float b = 0.05f;
  float c = 0.35f;
  float d = 2.0f;
  float e = 0.1f;
  float f = 0.25f;
  float g = 1.9f;
  float h = 3.78f;
  float j = 0.2f;
  float x = 0.1f;
  float y = 0.0f;
  float z = 0.2f;
       
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
  GD.putstr(14, 1, "Folded-Towel chaotic map");
  GD.putstr(16, 36, "Created by JLS 2021");
    
}

void loop(){
  
  float nx = x;
  x = a*nx*(1.0f-nx)-b*(y+c)*(1.0f-d*z);
  y = e*((y+f)*(1.0f+d*z)-1.0f)*(1.0f-g*nx);
  z = h*z*(1.0f-z)+j*y;
  
  setpixel(-30+(294*x), 106+(2650*y), 255);
       
}

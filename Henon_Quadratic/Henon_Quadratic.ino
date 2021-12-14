// Quadratic Henon map //

#include "SPI.h"
#include "GD.h"

  byte i;  
       
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
  GD.putstr(15, 1, "Quadratic Henon map");
  GD.putstr(16, 36, "Created by JLS 2021");
    
}

void loop(){

  int cnt = 0;
  float nx = 1.0f;
  float ny = 1.0f;
  float x = 0.0f;
  float y = 0.0f;
  float r = 0.0f;
  float a = 1.524f;
  
  for (int i=0; i<1000; i++){
    
    r = powf(x,2.0f) + powf(y,2.0f);
  
    if (r > 1){   
      nx = random(1000)/1000.0f;
      ny = random(1000)/1000.0f;  
      cnt = 0;
    }
    
    x = nx*cosf(a)-(ny-powf(nx,2.0f))*sinf(a);
    y = nx*sinf(a)+(ny-powf(nx,2.0f))*cosf(a);
      
    if (cnt > 100) setpixel(115+(140*x), 115+(140*y), 255);
   
    nx = x;
    ny = y;
    cnt ++;
   
   } 
     
}

// "If I have seen further it is by standing on ye sholders of Giants." Isaac Newton
// Simple tool to get a better understandig of MPU6050 on a GY-521 
// It use OUTPUT_READABLE_YAWPITCHROLL and OUTPUT_READABLE_WORLDACCEL 
// thr-# 15.12.2016 
// use Use myMPU6050Demo3Kalman_2 with local offsets
// version 0.1.1 
// correct yaw,pitch, roll angels (gimbal lock) 
import processing.serial.*;
import processing.opengl.*;
import toxi.geom.*;
import toxi.processing.*;

ToxiclibsSupport gfx;
    
    Kalman filter_X, filter_Y, filter_Z;
    
    Serial myPort;
    float[] value=new float[7];

    int i=0;
    int k=100;
    int interval;
    int linefeed = 10;   // Linefeed in ASCII
    String[] msg=new String[7];
    PImage img,img2;
    
    float timePrev, deltaTime;
    float[] pos=new float[3];
    float[] newpos=new float[3];
    float[] currAccel=new float[3];
    float[] velocity=new float[3];
    float[] preVelocity=new float[3];
    float[] a_off =new float[3];
    int count = 1; 
    float ax_off, ay_off, az_off; 
    int counter = 0;
    
    
  
    void setup()
    {
      size(800,800,P3D);
      noStroke();
      
      img = loadImage("GY-521_Front.JPG");
      img.resize(200, 100);
      img2 = loadImage("GY-521_Back.JPG");
      img2.resize(200, 100);
      imageMode(CENTER);
    
      filter_X=new Kalman(.1,.1,.001,.0000001);
      filter_Y=new Kalman(.1,.1,.001,.0000001);
      filter_Z=new Kalman(.1,.1,.001,.0000001);
    
      String portName = Serial.list()[1];
      myPort = new Serial(this, portName, 115200);
      myPort.bufferUntil(linefeed);
      myPort.write('r'); 
      frameRate(100);
      background(255);
      fill(246, 225, 65);
      lights();  
    }

    void draw()
    {
       if (millis() - interval > 1000) {
         // resend single character to trigger DMP init/start
         // in case the MPU is halted/reset while applet is running
         myPort.write('r');
         interval = millis();
        }
   
    // black background
    background(0);
    // translate everything to the middle of the viewport
    pushMatrix();
    // a tribute to world to processing transformation
    translate(0,0,pos[1]); // x
    translate(-pos[0],0,0); // y 
    translate(0,-pos[2],0); // z
    translate(width / 2, height / 2);
 //    rotateX(value[2]);   // MPU y  
 //    rotateY(-value[0]);  // MPU z
 //    rotateZ(value[1]);   // MPU x
     // 3-step rotation from yaw/pitch/roll angles (gimbal lock!)
    // ...and other weirdness I haven't figured out yet

    rotateY(value[0]);
    rotateZ(-value[1]);
    rotateX(-value[2]);
    position();     
    drawbox();  
    popMatrix();
}
// set position 0,0,0
    void keyPressed() {
      for (int i=0; i < 3; i++) {
        pos[i] = 0;
      }
    }
   
     

    
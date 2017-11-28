import processing.core.*; 
import processing.data.*; 
import processing.event.*; 
import processing.opengl.*; 

import java.util.HashMap; 
import java.util.ArrayList; 
import java.io.File; 
import java.io.BufferedReader; 
import java.io.PrintWriter; 
import java.io.InputStream; 
import java.io.OutputStream; 
import java.io.IOException; 

public class pikurosu2 extends PApplet {

int red=0,MASU=70,VERTEX=203,count=-11,size=0,cellNumber=10; //MASU\u521d\u671f\u502470\u300034\u306f10*10\u306e\u3068\u304d
int numberX=0,numberY=0,xx=0,yy=0;
int stage=1,stageFlag=1,stageCount=0,stagePage=0; //stageFlag=2\u306e\u3068\u304d\u30af\u30ea\u30a8\u30a4\u30c8\u30e2\u30fc\u30c9
int[][] Map = new int[cellNumber][cellNumber],a_Map = new int[cellNumber][cellNumber];
int[][] countX = new int[cellNumber][cellNumber],countY = new int[cellNumber][cellNumber];
int[][] draggMap = new int[cellNumber][cellNumber];
int[] neko2;
boolean color_b = true; //\u8d64\u8272\u3092\u70b9\u6ec5\u3055\u305b\u308b\u305f\u3081\u306e\u30d5\u30e9\u30b0
String lin,nek;     //\u30d5\u30a1\u30a4\u30eb\u8aad\u307f\u8fbc\u307f\u306b\u5fc5\u8981
String lines[],neko[]; //\u30d5\u30a1\u30a4\u30eb\u8aad\u307f\u8fbc\u307f\u306b\u5fc5\u8981
PrintWriter outfile,createMap;

public void setup() {
size(800,600);
colorMode(HSB,360,100,100);
background(360,10,100);
frameRate(15); // \u30d5\u30ec\u30fc\u30e0\u30ec\u30fc\u30c8\u3092\u8a2d\u5b9a
stageInit();
}

public void stageInit(){
  
  neko = loadStrings("map/neko.txt");
  nek=neko[0];
  String[] nyan=split(nek,',');
  stageCount=PApplet.parseInt(nyan[0]);
  
  
  
  count=-11;
  lines = loadStrings("map/pazzle" + stage + ".txt"); //\u56de\u7b54\u30de\u30c3\u30d7\u3092\u8aad\u307f\u8fbc\u3080
  
  if(lines.length==5||lines.length==6){
    MASU=70;
    cellNumber=5;
  }
  else{
    MASU=34;
    cellNumber=10;
  }

for(int i=0;i<cellNumber;i++){
  for(int j=0;j<cellNumber;j++){
    countX[i][j] = 0;
    countY[i][j] = 0;
    Map[i][j] = 0;
    a_Map[i][j] = -1;
    draggMap[i][j]=0;
  }
}
manage_file();
numberAnalysis();
fill(360,10,100);
rect(0,0,width,height);
}
  

// \u30e1\u30a4\u30f3\u30eb\u30fc\u30d7
public void draw() {
  if(stageFlag==1){
    stageInit();
    stageFlag=0;
  }
  
  
  fadeToRed();
  circleDraw();
  dotDraw();
  
  lineDraw();
  
   if(stageFlag!=2){
  numberDraw();
  }
   stageDraw();
    if(stageFlag!=2 && gameClearSecond()){
      clearFade();
    }
 
 
}

public void manage_file(){
  for(int i=0;i<cellNumber;i++){
    lin = lines[i];
    String[] co = split(lin,',');
    for(int j=0;j<cellNumber;j++){
      int y = PApplet.parseInt(co[j]);
      a_Map[i][j] = y;
    }
  }
}

public boolean gameClearSecond(){
  for(int i=0;i<cellNumber;i++){
    for(int j=0;j<cellNumber;j++){
      if(!(a_Map[i][j] == Map[i][j] || a_Map[i][j] == Map[i][j]-2)){
        return false;
      }
    }
  }
  return true;
}

public void numberAnalysis(){
  
  for(int i=0;i<cellNumber;i++){
    for(int j=0;j<cellNumber;j++){
      if(a_Map[i][j] == 1){
        numberY++;
        if(j==cellNumber-1)
          countY[i][yy]=numberY;
        
      }else if(a_Map[i][j] == 0 && numberY != 0){
          countY[i][yy]=numberY;
          numberY=0;
          yy++;
        }
      }
    numberY=0;
    yy=0;
    }
  
  for(int j=0;j<cellNumber;j++){
    for(int i=0;i<cellNumber;i++){
      if(a_Map[i][j] == 1){
        numberX++;
        if(i==cellNumber-1)
          countX[j][xx]=numberX;
      
      }else if(a_Map[i][j] == 0 && numberX != 0){
          countX[j][xx]=numberX;
          numberX=0;
          xx++;
      }
    }
    numberX=0;
    xx=0;
  }
}
    
    
public void createMap(){
  int cc=0;

  for(int i=0;i<cellNumber;i++){
    for(int j=0;j<cellNumber;j++){
      if(Map[i][j]==2){
        Map[i][j]=0;
        }
        if(Map[i][j]==0) cc++;
      
     }
   }
   if(cc!=cellNumber*cellNumber){
     
     outfile=createWriter("map/neko.txt");
  outfile.println((stageCount+1));
  createMap=createWriter("map/pazzle"+(stageCount+1)+".txt");
  
     for(int i=0;i<cellNumber;i++){
    for(int j=0;j<cellNumber;j++){
      if(j==cellNumber-1){
        createMap.println(Map[i][j]);
      }else{
      createMap.print(Map[i][j]+",");
      }
    }
  }
     outfile.flush();
     createMap.flush();
     outfile.close();
  createMap.close();
  
  stageFlag=1;
   }
}


public void mousePressed() {
  if(!gameClearSecond()){
  if(mouseButton == LEFT){ 
    
    for(int i=1;i<=stageCount;i++){
    if(mouseX>VERTEX*3+20 && mouseY>VERTEX+34*(i-1)+(i-2)*2)
      {
        stage=stagePage*10+i;
        stageFlag=1;
      }
  }
  
  if(mouseX>VERTEX*3 && mouseX<VERTEX*3+50 && mouseY>VERTEX-20 &&mouseY<VERTEX+20)
     if(stagePage!=0){
     stagePage--;
     }
  if(mouseX>VERTEX*3+70 && mouseX<VERTEX*3+150 && mouseY>VERTEX-20 &&mouseY<VERTEX+20)
     if(stageCount/10!=stagePage){
     stagePage++;
     }
     
     if(mouseX>VERTEX*3+25 && mouseX<VERTEX*3+100  && mouseY>VERTEX-80 &&mouseY<VERTEX-35){
       if(stageFlag!=2){
       
        fill(360,10,100);
        rect(0,0,width,height);
         stageFlag=2;
       }
         else{
         createMap();
         
         }
         
     }
  
  
    
    
    
    for(int i=0;i<cellNumber;i++){
      for(int j=0;j<cellNumber;j++){
        if(mouseX > VERTEX+(MASU+2)*j && mouseX < VERTEX+(MASU+2)*(j+1) && mouseY > VERTEX+(MASU+2)*i && mouseY < VERTEX+(MASU+2)*(i+1) )
           {
             if(Map[i][j] == 0 || Map[i][j] == 2){
               Map[i][j] = 1;
               draggMap[i][j] = 1;
               
             }else{
               Map[i][j] = 0;
            }
          }
        } 
      } 
    }
  
  if(mouseButton == RIGHT){
    
    for(int i=0;i<cellNumber;i++){
      for(int j=0;j<cellNumber;j++){
        if(mouseX > VERTEX+(MASU+2)*j && mouseX < VERTEX+(MASU+2)*(j+1) && mouseY > VERTEX+(MASU+2)*i && mouseY < VERTEX+(MASU+2)*(i+1) )
            {
             if(Map[i][j] == 0 || Map[i][j] == 1){
               Map[i][j] = 2;
               draggMap[i][j] = 2;
            }else{
               Map[i][j] = 0;
            }
          }
        } 
      }
    }    
  }else{
    if(count>50&&mouseButton == RIGHT){
      stageFlag=1;
      }
    }
  
}


public void mouseDragged() {
  
  if(!gameClearSecond()){
  if(mouseButton == LEFT){
    for(int i=0;i<cellNumber;i++){
      for(int j=0;j<cellNumber;j++){
        if(mouseX > VERTEX+(MASU+2)*j && mouseX < VERTEX+(MASU+2)*(j+1) && mouseY > VERTEX+(MASU+2)*i && mouseY < VERTEX+(MASU+2)*(i+1))
           {
             if(draggMap[i][j] != 1){
               if(Map[i][j] == 0 || Map[i][j] == 2){
                 Map[i][j] = 1;
               }else{
                 Map[i][j] = 0;
              }
              draggMap[i][j] = 1;
             }
          }else{
            draggMap[i][j] = 0;
          }
        }
      } 
    }
  
  if(mouseButton == RIGHT){
    for(int i=0;i<cellNumber;i++){
      for(int j=0;j<cellNumber;j++){
        if(mouseX > VERTEX+(MASU+2)*j && mouseX < VERTEX+(MASU+2)*(j+1) && mouseY > VERTEX+(MASU+2)*i && mouseY < VERTEX+(MASU+2)*(i+1) )
            {
              if(draggMap[i][j] != 2){
               if(Map[i][j] == 0 || Map[i][j] == 1){
                 Map[i][j] = 2;
              }else{
                 Map[i][j] = 0;
              }
              draggMap[i][j] = 2;
            }
          }else{
            draggMap[i][j] = 0;
          }
        } 
      }
    }    
  }
}






// \u8272\u3092\u30e9\u30f3\u30c0\u30e0\u306b\u8a2d\u5b9a\u3059\u308b\u95a2\u6570
public int randomColor() {
int c = color(random(10),random(100),100);
return c;
}


// \u753b\u9762\u3092\u8d64\u306b\u30d5\u30a7\u30fc\u30c9\u30a2\u30a6\u30c8\u3059\u308b\u95a2\u6570
public void fadeToRed() {
noStroke();
fill(350,50+red,100,30);
rect(200,200,364,364);
if(color_b == true){
  red++;
}if(red == 30){
  color_b = false;
  red=29;
}if(color_b == false){
  red--;
  
}if(red == -20){
  color_b = true;
  red=-19;
}

}

//\u5857\u3089\u308c\u3066\u3044\u308b\u30de\u30b9\u306b\u5186\u3092\u63cf\u304f\u95a2\u6570
public void circleDraw(){
  int x = PApplet.parseInt(random(width-250-VERTEX)+VERTEX);
  int y = PApplet.parseInt(random(height-VERTEX)+VERTEX);
  int sz = PApplet.parseInt(random(80));
  
  noStroke();
  fill( randomColor() ); // \u8272\u3092\u30e9\u30f3\u30c0\u30e0\u306b\u8a2d\u5b9a
  if(count<10)
    ellipse(x, y, sz, sz);
}

//\u30de\u30b9\u76ee\u306b\u8272\u3092\u5857\u3063\u305f\u308a\u659c\u7dda\u3092\u5165\u308c\u305f\u308a\u3059\u308b\u95a2\u6570
public void dotDraw(){
  for(int i=0;i<cellNumber;i++){
    for(int j=0;j<cellNumber;j++){
       if(Map[i][j] == 0){
         fill(360);
         rect(VERTEX+1+(MASU+2)*j,VERTEX+1+(MASU+2)*i,MASU+1,MASU+1);
       }else if(Map[i][j] == 1){
       }else if(Map[i][j] == 2){
          fill(360);
          rect(VERTEX+1+(MASU+2)*j,VERTEX+1+(MASU+2)*i,MASU+1,MASU+1);
          stroke(0);
          strokeWeight(3);
          line(VERTEX+1+(MASU+2)*(j+1),VERTEX+1+(MASU+2)*i,VERTEX+1+(MASU+2)*j,VERTEX+1+(MASU+2)*(i+1));
          noStroke();
      }
    }
  }
}

//\u30af\u30ea\u30a2\u5f8c\u306e\u30a8\u30d5\u30a7\u30af\u30c8\u3092\u63cf\u753b\u3059\u308b\u95a2\u6570
public void clearFade(){
  rectMode(CENTER);
  noStroke();
  fill(360,20,100,60);
  count++;
  for(int i=0;i<cellNumber+1;i++){
    if(count<0)
      break;
    else if(count<5*i){
      for(int j=0;j<cellNumber;j++){
        if(a_Map[i-1][j] == 1){
          rect(VERTEX+(MASU+2)*j+MASU/2,VERTEX+(MASU+2)*(i-1)+MASU/2,MASU+size,MASU+size);
          size+=3;
          if(size == 15) size = 0;
        }
        if(count>5*i+5){
          if(a_Map[i-2][j] == 1){
            rect(VERTEX+(MASU+2)*j+MASU/2,VERTEX+(MASU+2)*(i-2)+MASU/2,MASU-(size-15),MASU-(size-15));
          }
        }
      }
       break;
    }
  }
  if(count>30){
    textSize(60);
    textAlign(CENTER);
    fill(360,80,100,20);
    text("GAME",100,100);
    text("CLAER!",100,160);
    textSize(40);
    text("Reset",680,70);
    text("right click",680,120);
  }
  rectMode(CORNER);
}

//\u7dda\u3092\u5f15\u304f
public void lineDraw(){
  stroke(0);
  noFill();
  strokeWeight(5);
  
  if(cellNumber == 5){
    rect(VERTEX,VERTEX,MASU*cellNumber+8,MASU*cellNumber+8);
  }else{
    rect(VERTEX,VERTEX,MASU*cellNumber+19,MASU*cellNumber+19);
  }
  
  strokeWeight(3);
  for(int i=0;i<cellNumber;i++){
    line(VERTEX+1+(MASU+2)*i,VERTEX,VERTEX+1+(MASU+2)*i,VERTEX+MASU*cellNumber+20);
    line(VERTEX,VERTEX+1+(MASU+2)*i,VERTEX+MASU*cellNumber+20,VERTEX+1+(MASU+2)*i);
  }
  //\u767d\u3092\u3072\u304d\u5468\u308a\u306b\u5186\u304c\u898b\u3048\u306a\u3044\u3088\u3046\u306b\u3059\u308b
  stroke(360,10,100);
  noFill();
  strokeWeight(41);
  rect(VERTEX-23,VERTEX-23,VERTEX+201,VERTEX+201);
  fill(360,10,100);
  rect(VERTEX*3-20,VERTEX-50,width,height);
}
//stage\u3092\u63cf\u753b\u3059\u308b\u95a2\u6570
public void stageDraw(){
  textAlign(LEFT,BOTTOM);
  fill(350,80,50);
  textSize(25);
  
  for(int i=1;i<=10;i++){
    if(stageCount+1==stagePage*10+i){
      break;
    }
    
    text("stage"+(stagePage*10+i),VERTEX*3+20,VERTEX+34*i+(i-1)*2);
  }

  text("prev   next",VERTEX*3,VERTEX);
  textSize(35);
  fill(300,60,80);
  text("new",VERTEX*3+25,VERTEX-30);
}

  

//\u6570\u5b57\u3092\u63cf\u753b\u3059\u308b\u95a2\u6570
public void numberDraw(){

  textSize(50);
  textAlign(RIGHT,BOTTOM);
  fill(350,80,50);
  
  if(cellNumber == 10){
    textSize(25);
  }

  for(int i=0;i<cellNumber;i++){
    for(int j=0;j<cellNumber;j++){
      if(countX[i][0]==0){
        text("0 ",VERTEX+2*i+MASU*i,VERTEX-300,MASU,300);
        continue;
      }
      if(countX[i][0]==10){
        text("10",VERTEX+2*i+MASU*i,VERTEX-300,MASU,300);
        continue;
      }
      String joinedX = join(nf(countX[i],1), ' '); 
      String[] arrayJoinedX = splitTokens(joinedX, "0");
      text(arrayJoinedX[0],VERTEX+2*i+MASU*i,VERTEX-300,MASU,300);
    }
  }
  
  for(int i=0;i<cellNumber;i++){
    for(int j=0;j<cellNumber;j++){
      if(countY[i][0]==0){
         text("0 ",VERTEX-MASU/2,VERTEX+MASU*(i+1)+i*2);
        continue;
      }
       if(countY[i][0]==10){
         text("10",VERTEX-MASU/2,VERTEX+MASU*(i+1)+i*2);
        continue;
      }
      String joinedY = join(nf(countY[i],1), ' '); 
      String[] arrayJoinedY = splitTokens(joinedY, "0");
      text(arrayJoinedY[0],VERTEX-MASU/2,VERTEX+MASU*(i+1)+i*2);
    }
  }
}

public void stringDraw(){
  textSize(50);
  textAlign(RIGHT,BOTTOM);
  fill(350,80,50);
   if(cellNumber == 10){
    textSize(25);
  }
}
  static public void main(String[] passedArgs) {
    String[] appletArgs = new String[] { "pikurosu2" };
    if (passedArgs != null) {
      PApplet.main(concat(appletArgs, passedArgs));
    } else {
      PApplet.main(appletArgs);
    }
  }
}

int red=0,MASU=70,VERTEX=203,count=-11,size=0,cellNumber=10; //MASU初期値70　34は10*10のとき
int numberX=0,numberY=0,xx=0,yy=0;
int stage=1,stageFlag=1,stageCount=0,stagePage=0; //stageFlag=2のときクリエイトモード
int[][] Map = new int[cellNumber][cellNumber],a_Map = new int[cellNumber][cellNumber];
int[][] countX = new int[cellNumber][cellNumber],countY = new int[cellNumber][cellNumber];
int[][] draggMap = new int[cellNumber][cellNumber];
int[] neko2;
boolean color_b = true; //赤色を点滅させるためのフラグ
String lin,nek;     //ファイル読み込みに必要
String lines[],neko[]; //ファイル読み込みに必要
PrintWriter outfile,createMap;

void setup() {
size(800,600);
colorMode(HSB,360,100,100);
background(360,10,100);
frameRate(15); // フレームレートを設定
stageInit();
}

void stageInit(){
  
  neko = loadStrings("map/neko.txt");
  nek=neko[0];
  String[] nyan=split(nek,',');
  stageCount=int(nyan[0]);
  
  
  
  count=-11;
  lines = loadStrings("map/pazzle" + stage + ".txt"); //回答マップを読み込む
  
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
  

// メインループ
void draw() {
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

void manage_file(){
  for(int i=0;i<cellNumber;i++){
    lin = lines[i];
    String[] co = split(lin,',');
    for(int j=0;j<cellNumber;j++){
      int y = int(co[j]);
      a_Map[i][j] = y;
    }
  }
}

boolean gameClearSecond(){
  for(int i=0;i<cellNumber;i++){
    for(int j=0;j<cellNumber;j++){
      if(!(a_Map[i][j] == Map[i][j] || a_Map[i][j] == Map[i][j]-2)){
        return false;
      }
    }
  }
  return true;
}

void numberAnalysis(){
  
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
    
    
void createMap(){
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


void mousePressed() {
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


void mouseDragged() {
  
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






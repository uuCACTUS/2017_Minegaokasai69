
// 色をランダムに設定する関数
color randomColor() {
color c = color(random(10),random(100),100);
return c;
}


// 画面を赤にフェードアウトする関数
void fadeToRed() {
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

//塗られているマスに円を描く関数
void circleDraw(){
  int x = int(random(width-250-VERTEX)+VERTEX);
  int y = int(random(height-VERTEX)+VERTEX);
  int sz = int(random(80));
  
  noStroke();
  fill( randomColor() ); // 色をランダムに設定
  if(count<10)
    ellipse(x, y, sz, sz);
}

//マス目に色を塗ったり斜線を入れたりする関数
void dotDraw(){
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

//クリア後のエフェクトを描画する関数
void clearFade(){
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

//線を引く
void lineDraw(){
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
  //白をひき周りに円が見えないようにする
  stroke(360,10,100);
  noFill();
  strokeWeight(41);
  rect(VERTEX-23,VERTEX-23,VERTEX+201,VERTEX+201);
  fill(360,10,100);
  rect(VERTEX*3-20,VERTEX-50,width,height);
}
//stageを描画する関数
void stageDraw(){
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

  

//数字を描画する関数
void numberDraw(){

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

void stringDraw(){
  textSize(50);
  textAlign(RIGHT,BOTTOM);
  fill(350,80,50);
   if(cellNumber == 10){
    textSize(25);
  }
}

#include <simple2d.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#define size 800
#define v 20
struct score{
int p1;
int p2;
int turn;

}sc;
struct shoot{
int sh;
float t;
int temp;
float vy;
}sh;
struct input{
 char n1[10];
 char n2[20];
    int s;
    int end;

}in;
struct coordinates{
    int x;
    int y;
};
struct coordinates s1;
struct coordinates s2;
struct coordinates s4;
struct arrow{ int x;
 int y;
int theta;
double r;
}s3;
void init(){
    s1.x = rand()%size-50;
    s1.y = rand()%size-50;
    s2.x = rand()%size-50;
    s2.y = rand()%size-50;
    s4.x = s3.x;
    s4.y = s3.y;
}

void save(){
    FILE *f = fopen("savefile.txt", "w");
    fprintf(f, "%s\n", in.n1);
    fprintf(f, "%s\n", in.n2);
    fprintf(f, "%d\n", sc.p1);
    fprintf(f, "%d\n", sc.p2);
    fclose(f);
}
void load(){
    FILE *f = fopen("savefile.txt", "r");
    int s1, s2;
    fgets(in.n1, 10, f);
    fgets(in.n2, 10, f);
    fscanf(f, "%d", &sc.p1);
    fscanf(f, "%d", &sc.p2);
    fclose(f);

}





//////////////////////////////////////////////////////////////


void render() {
    S2D_DrawLine(0, size, s3.x, s3.y,
                 5,
                 0, 0, 0, 1,
                 0, 0, 0, 1,
                 0, 0, 0, 1,
                 0, 0, 0, 1);
    S2D_DrawCircle(s1.x, s1.y, 50, 360, 1, 0, 0.2, 0.5);
    S2D_DrawCircle(s2.x,s2.y, 50, 360, 0.3, 0, 1, 0.5);
    S2D_DrawCircle(s4.x,s4.y,20,360,0.6,0.1,0.6,1);

    }
//////////////////////////////////////////////////////////////////////
void on_key(S2D_Event e) {
  if (e.type == S2D_KEY_DOWN || e.type == S2D_KEY_HELD) {
    if(strcmp(e.key,"Up")==0 && s3.theta<90){

        s3.theta +=2;

    }

    else if(strcmp(e.key,"Down")==0 && s3.theta>0){
        s3.theta -=2;

    }
        s3.y =size-s3.r*sin(s3.theta*M_PI/180);
        s3.x =s3.r*cos(s3.theta*M_PI/180);
        s4.x = s3.x;
        s4.y = s3.y;
  }
       if(e.type == S2D_KEY_DOWN){
        if(strcmp(e.key,"Space")==0){
        sh.sh = 1;
        }
    }
    if(e.type == S2D_KEY_DOWN){
            if(strcmp(e.key,"S")==0){
                save();
            }

}

    if(e.type == S2D_KEY_DOWN){
            if(strcmp(e.key,"L")==0){
                load();
            }

}
}
////////////////////////////////////////////////////////////////////
void update(S2D_Window *window) {
// TEXTS:
S2D_Text *txt1 = S2D_CreateText("a.ttf",in.n1, 15);
S2D_Text *txt2 = S2D_CreateText("a.ttf", in.n2, 15);
txt1->color.r = 0;
txt1->color.g = 0.0;
txt1->color.b = 0.0;
txt1->color.a = 1;
txt1->x = s2.x-10;
txt1->y = s2.y-10;
txt2->color.r = 0;
txt2->color.g = 0.0;
txt2->color.b = 0.0;
txt2->color.a = 1;
txt2->x = s1.x-15;
txt2->y = s1.y-10;
S2D_DrawText(txt2);
S2D_DrawText(txt1);

S2D_Text *txt3 = S2D_CreateText("a.ttf"," ", 15);
if(sc.turn==1){
S2D_SetText(txt3, "turn :%s",in.n1);
txt3->x = 10;
txt3->y = 60;
}
else{
S2D_SetText(txt3, "turn :%s",in.n2);
txt3->x = 10;
txt3->y = 60;
}
S2D_DrawText(txt3);
S2D_Text *txt4 = S2D_CreateText("a.ttf"," ", 15);
S2D_Text *txt5 = S2D_CreateText("a.ttf"," ", 15);
S2D_SetText(txt4, "%s:%d",in.n1, sc.p1);
S2D_SetText(txt5, "%s:%d",in.n2, sc.p2);
txt4->x = 10;
txt4->y = 10;
txt5->x = 10;
txt5->y = 30;
S2D_DrawText(txt4);
S2D_DrawText(txt5);
S2D_Text *txt6 = S2D_CreateText("a.ttf", " " ,15);
S2D_SetText(txt6, "speed:%dx",in.s);
txt6->x = 10;
txt6->y = 90;
S2D_DrawText(txt6);
/////////////////////////////////////////

   // Random movement of the balls:
        srand(time(NULL));
        s1.x+=in.s*(rand()%3-1);
        s1.y+=in.s*(rand()%3-1);
        s2.x+=in.s*(rand()%3-1);
        s2.y+=in.s*(rand()%3-1);
  // if the balls hit the walls:
if(s1.x<50)
    s1.x+=in.s;
 else if(s1.x>size-50)
    s1.x-=in.s;
else if(s2.x<50)
    s2.x+=in.s;
else if(s2.x>size-50)
    s2.x-=in.s;
else if(s1.y >=size-50)
s1.y-=in.s;
else if(s1.y<50)
s1.y+=in.s;
else if(s2.y >=size-50)
s2.y-=in.s;
else if(s2.y<50)
s2.y+=in.s;
//shooting ball movement in x&y axis:
    if(sh.sh==1){
    s4.x+=v*cos(s3.theta*M_PI/180)*sh.t;
    s4.y-=v*sin(s3.theta*M_PI/180)*sh.t;
    }
// distance between the bullet and balls!
    double d1,d2;
    d1 = sqrt(pow(s2.x-s4.x, 2) + pow(s2.y -s4.y, 2));
    d2 = sqrt(pow(s1.x-s4.x, 2) + pow(s1.y -s4.y, 2));
  // Scoring conditions
  if (sh.sh == 1) {
    if (sc.turn == 1) {
      if (d2 < 70) {
        init();
        sc.p1 += 5;
        sc.turn = 2;
        sh.sh = 0;
      } else if (d1 < 70) {
        init();
        sc.p1 -= 3;
        sc.turn = 2;
        sh.sh = 0;
      }
    } else if (sc.turn == 2) {
      if (d1 < 70) {
        init();
        sc.p2 += 5;
        sc.turn = 1;
        sh.sh = 0;
      } else if (d2 < 70) {
        init();
        sc.p2 -= 3;
        sh.sh = 0;
        sc.turn = 1;
      }
    }
      if(sc.p1 >= in.end || sc.p2 >=in.end){
        S2D_Close(window);
        if(sc.p2>sc.p1)
            printf("player %s won!\n",in.n2);
        else
                 if(sc.p1>sc.p2)
            printf("player %s won!\n",in.n1);

        }




  }


    if((s4.x>size || s4.y>size || s4.y<0)&& sc.turn==1){
    init();
    sh.sh =0;
    sc.turn=2;
    }
    if((s4.x>size || s4.y>size || s4.y<0)&& sc.turn==2){
    init();
    sh.sh =0;
    sc.turn=1;
    }
//when the balls get outside the window by accident:
    if((s2.x<50 && s2.y>700) || (s1.x<50 && s1.y>700)){
        init();
    }
    if(s2.x>size+50|| s1.x>size+50 || s2.y>size+50 || s1.y>size+50){
        init();
    }

    if(s2.x<50|| s1.x<50 || s2.y<50 || s1.y<50 || s2.y<50){
    init();
        }
    if(s1.x<100 && s2.y>size-100){
    s1.x+=10;
    s1.y+=10;
    }

    if(s2.x<100 && s2.y>size-100){
    s2.x+=10;
    s2.y+=10;
    }


  }
////////////////////////////////////////////////////////////

int main() {
    printf("enter first players name:\n");
    scanf("%s",in.n1);
    printf("enter Second players name:\n");
    scanf("%s",&in.n2);
    printf("enter game speed:\n");
    scanf("%d",&in.s);
    printf("the END score:\n");
    scanf("%d",&in.end);
    printf("press any key to start...\n\n");
    getch();
    srand(time(NULL));
    s1.x = rand()%size-50;
    s1.y = rand()%size-50;
    s2.x = rand()%size-50;
    s2.y = rand()%size-50;
    s3.theta = 45;
    s3.x=50;
    s3.y=750;
    s3.r=50*sqrt(2);
    s4.x = s3.x;
    s4.y = s3.y;
    sh.sh =0;
    sh.t=1;
    sc.turn=rand()%2+1;
    sc.p1=0;
    sc.p2=0;
    S2D_Window *window = S2D_CreateWindow(
            "Shooting Game",
            size,size,
            update, render,
            0);
    window->on_key = on_key;

    window->viewport.mode = S2D_FIXED;
    window->background.r = 0.7;
    window->background.g = 0.75;
    window->background.b = 0.7;
    window->background.a = 1.0;

    S2D_Show(window);


    return 0;
}

// Rubik's Cube.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#define CLOCK 1
#define ANTICLOCK -1
#include <stdlib.h>
#include<glut.h>

typedef GLfloat point[3];
typedef GLfloat color[3];
static GLfloat theta[]={0.0,0.0,0.0};
static GLint axis=2;


point facetop[] = {{-3.0,3.0,3.0},{-1.0,3.0,3.0},{1.0,3.0,3.0},{3.0,3.0,3.0},			//(00)(01)(02)
					{-3.0,3.0,1.0},{-1.0,3.0,1.0},{1.0,3.0,1.0},{3.0,3.0,1.0},			//(10)(11)(12)
					{-3.0,3.0,-1.0},{-1.0,3.0,-1.0},{1.0,3.0,-1.0},{3.0,3.0,-1.0},		//(20)(21)(22)//front to back
					{-3.0,3.0,-3.0},{-1.0,3.0,-3.0},{1.0,3.0,-3.0},{3.0,3.0,-3.0}};

point facebottom[] = {{-3.0,-3.0,3.0},{-1.0,-3.0,3.0},{1.0,-3.0,3.0},{3.0,-3.0,3.0},	//(00)(01)(02)
					{-3.0,-3.0,1.0},{-1.0,-3.0,1.0},{1.0,-3.0,1.0},{3.0,-3.0,1.0},		//(10)(11)(12)
					{-3.0,-3.0,-1.0},{-1.0,-3.0,-1.0},{1.0,-3.0,-1.0},{3.0,-3.0,-1.0},	//(20)(21)(22)//front to back
					{-3.0,-3.0,-3.0},{-1.0,-3.0,-3.0},{1.0,-3.0,-3.0},{3.0,-3.0,-3.0}};

point faceright[] = {{3.0,3.0,3.0},{3.0,3.0,1.0},{3.0,3.0,-1.0},{3.0,3.0,-3.0},//front to back
					{3.0,1.0,3.0},{3.0,1.0,1.0},{3.0,1.0,-1.0},{3.0,1.0,-3.0},
					{3.0,-1.0,3.0},{3.0,-1.0,1.0},{3.0,-1.0,-1.0},{3.0,-1.0,-3.0},
					{3.0,-3.0,3.0},{3.0,-3.0,1.0},{3.0,-3.0,-1.0},{3.0,-3.0,-3.0}};

point faceleft[] = {{-3.0,3.0,-3.0},{-3.0,3.0,-1.0},{-3.0,3.0,1.0},{-3.0,3.0,3.0},//back to front
					{-3.0,1.0,-3.0},{-3.0,1.0,-1.0},{-3.0,1.0,1.0},{-3.0,1.0,3.0},
					{-3.0,-1.0,-3.0},{-3.0,-1.0,-1.0},{-3.0,-1.0,1.0},{-3.0,-1.0,3.0},
					{-3.0,-3.0,-3.0},{-3.0,-3.0,-1.0},{-3.0,-3.0,1.0},{-3.0,-3.0,3.0}};

point facefront[] = {{-3.0,3.0,3.0},{-1.0,3.0,3.0},{1.0,3.0,3.0},{3.0,3.0,3.0},
					{-3.0,1.0,3.0},{-1.0,1.0,3.0},{1.0,1.0,3.0},{3.0,1.0,3.0},
					{-3.0,-1.0,3.0},{-1.0,-1.0,3.0},{1.0,-1.0,3.0},{3.0,-1.0,3.0},
					{-3.0,-3.0,3.0},{-1.0,-3.0,3.0},{1.0,-3.0,3.0},{3.0,-3.0,3.0}};

point faceback[] = {{-3.0,3.0,-3.0},{-1.0,3.0,-3.0},{1.0,3.0,-3.0},{3.0,3.0,-3.0},//backward left to right??(User's initial view)
					{-3.0,1.0,-3.0},{-1.0,1.0,-3.0},{1.0,1.0,-3.0},{3.0,1.0,-3.0},
					{-3.0,-1.0,-3.0},{-1.0,-1.0,-3.0},{1.0,-1.0,-3.0},{3.0,-1.0,-3.0},
					{-3.0,-3.0,-3.0},{-1.0,-3.0,-3.0},{1.0,-3.0,-3.0},{3.0,-3.0,-3.0}};

color red={1.0,0.0,0.0};
color blue={0.0,0.0,1.0};
color green={0.0,1.0,0.0};
color orange={1.0,0.65,0.0};
color yellow={1.0,1.0,0.0};
color cyan={0.0,1.0,1.0};

GLfloat *ft[3][3]={{red,red,red},
					{red,red,red},
					{red,red,red}};

GLfloat *bk[3][3]={{blue,blue,blue},
					{blue,blue,blue},
					{blue,blue,blue}};

GLfloat *tp[3][3]={{green,green,green},
					{green,green,green},
					{green,green,green}};

GLfloat *bt[3][3]={{orange,orange,orange},
					{orange,orange,orange},
					{orange,orange,orange}};

GLfloat *lt[3][3]={{yellow,yellow,yellow},
					{yellow,yellow,yellow},
					{yellow,yellow,yellow}};

GLfloat *rt[3][3]={{cyan,cyan,cyan},
					{cyan,cyan,cyan},
					{cyan,cyan,cyan}};

int theta1=0,dir=0,rotcode=0,rot=0;
int rd=0,bl=0,gr=0,yl=0,or=0,cy=0;
int jl=0;
void colorface(point a,point b,point c,point d,GLfloat *clr)
{	
	glColor3fv(clr);
	glBegin(GL_POLYGON);
	glVertex3fv(a);
	glVertex3fv(b);
	glVertex3fv(c);
	glVertex3fv(d);
	glEnd();
}

void color_op()
{
	GLfloat *temp;

	if(rotcode==1){
		if(dir==ANTICLOCK){
			temp=ft[0][0];ft[0][0]=lt[0][0];lt[0][0]=bk[0][2];bk[0][2]=rt[0][0];rt[0][0]=temp;
			temp=ft[0][1];ft[0][1]=lt[0][1];lt[0][1]=bk[0][1];bk[0][1]=rt[0][1];rt[0][1]=temp;
			temp=ft[0][2];ft[0][2]=lt[0][2];lt[0][2]=bk[0][0];bk[0][0]=rt[0][2];rt[0][2]=temp;
			temp=tp[0][0];tp[0][0]=tp[2][0];tp[2][0]=tp[2][2];tp[2][2]=tp[0][2];tp[0][2]=temp;
			temp=tp[0][1];tp[0][1]=tp[1][0];tp[1][0]=tp[2][1];tp[2][1]=tp[1][2];tp[1][2]=temp;
		}
		else if(dir==CLOCK){
			temp=ft[0][0];ft[0][0]=rt[0][0];rt[0][0]=bk[0][2];bk[0][2]=lt[0][0];lt[0][0]=temp;
			temp=ft[0][1];ft[0][1]=rt[0][1];rt[0][1]=bk[0][1];bk[0][1]=lt[0][1];lt[0][1]=temp;
			temp=ft[0][2];ft[0][2]=rt[0][2];rt[0][2]=bk[0][0];bk[0][0]=lt[0][2];lt[0][2]=temp;
			temp=tp[0][0];tp[0][0]=tp[0][2];tp[0][2]=tp[2][2];tp[2][2]=tp[2][0];tp[2][0]=temp;
			temp=tp[0][1];tp[0][1]=tp[1][2];tp[1][2]=tp[2][1];tp[2][1]=tp[1][0];tp[1][0]=temp;
		}
	}
	if(rotcode==2){
		if(dir==ANTICLOCK){
			temp=ft[1][0];ft[1][0]=lt[1][0];lt[1][0]=bk[1][2];bk[1][2]=rt[1][0];rt[1][0]=temp;
			temp=ft[1][1];ft[1][1]=lt[1][1];lt[1][1]=bk[1][1];bk[1][1]=rt[1][1];rt[1][1]=temp;
			temp=ft[1][2];ft[1][2]=lt[1][2];lt[1][2]=bk[1][0];bk[1][0]=rt[1][2];rt[1][2]=temp;
		}
		else if(dir==CLOCK){
			temp=ft[1][0];ft[1][0]=rt[1][0];rt[1][0]=bk[1][0];bk[1][0]=lt[1][0];lt[1][0]=temp;
			temp=ft[1][1];ft[1][1]=rt[1][1];rt[1][1]=bk[1][1];bk[1][1]=lt[1][1];lt[1][1]=temp;
			temp=ft[1][2];ft[1][2]=rt[1][2];rt[1][2]=bk[1][2];bk[1][2]=lt[1][2];lt[1][2]=temp;
		}
	}
	if(rotcode==3){
		if(dir==ANTICLOCK){
			temp=ft[2][0];ft[2][0]=lt[2][0];lt[2][0]=bk[2][2];bk[2][2]=rt[2][0];rt[2][0]=temp;
			temp=ft[2][1];ft[2][1]=lt[2][1];lt[2][1]=bk[2][1];bk[2][1]=rt[2][1];rt[2][1]=temp;
			temp=ft[2][2];ft[2][2]=lt[2][2];lt[2][2]=bk[2][0];bk[2][0]=rt[2][2];rt[2][2]=temp;
			temp=bt[0][0];bt[0][0]=bt[2][0];bt[2][0]=bt[2][2];bt[2][2]=bt[0][2];bt[0][2]=temp;
			temp=bt[0][1];bt[0][1]=bt[1][0];bt[1][0]=bt[2][1];bt[2][1]=bt[1][2];bt[1][2]=temp;
		}
		else if(dir==CLOCK){
			temp=ft[2][0];ft[2][0]=rt[2][0];rt[2][0]=bk[2][2];bk[2][2]=lt[2][0];lt[2][0]=temp;
			temp=ft[2][1];ft[2][1]=rt[2][1];rt[2][1]=bk[2][1];bk[2][1]=lt[2][1];lt[2][1]=temp;
			temp=ft[2][2];ft[2][2]=rt[2][2];rt[2][2]=bk[2][0];bk[2][0]=lt[2][2];lt[2][2]=temp;
			temp=bt[0][0];bt[0][0]=bt[0][2];bt[0][2]=bt[2][2];bt[2][2]=bt[2][0];bt[2][0]=temp;
			temp=bt[0][1];bt[0][1]=bt[1][2];bt[1][2]=bt[2][1];bt[2][1]=bt[1][0];bt[1][0]=temp;
		}
	}
	if(rotcode==4){
		if(dir==ANTICLOCK){
			temp=ft[0][0];ft[0][0]=tp[2][0];tp[2][0]=bk[2][0];bk[2][0]=bt[0][0];bt[0][0]=temp;
			temp=ft[1][0];ft[1][0]=tp[1][0];tp[1][0]=bk[1][0];bk[1][0]=bt[1][0];bt[1][0]=temp;
			temp=ft[2][0];ft[2][0]=tp[0][0];tp[0][0]=bk[0][0];bk[0][0]=bt[2][0];bt[2][0]=temp;
			temp=lt[0][0];lt[0][0]=lt[0][2];lt[0][2]=lt[2][2];lt[2][2]=lt[2][0];lt[2][0]=temp;
			temp=lt[0][1];lt[0][1]=lt[1][2];lt[1][2]=lt[2][1];lt[2][1]=lt[1][0];lt[1][0]=temp;
		}
		else if(dir==CLOCK){
			temp=ft[0][0];ft[0][0]=bt[0][0];bt[0][0]=bk[2][0];bk[2][0]=tp[2][0];tp[2][0]=temp;
			temp=ft[1][0];ft[1][0]=bt[1][0];bt[1][0]=bk[1][0];bk[1][0]=tp[1][0];tp[1][0]=temp;
			temp=ft[2][0];ft[2][0]=bt[2][0];bt[2][0]=bk[0][0];bk[0][0]=tp[0][0];tp[0][0]=temp;
			temp=lt[0][0];lt[0][0]=lt[2][0];lt[2][0]=lt[2][2];lt[2][2]=lt[0][2];lt[0][2]=temp;
			temp=lt[0][1];lt[0][1]=lt[1][0];lt[1][0]=lt[2][1];lt[2][1]=lt[1][2];lt[1][2]=temp;
		}
	}
	if(rotcode==5){
		if(dir==ANTICLOCK){
			temp=ft[0][1];ft[0][1]=tp[2][1];tp[2][1]=bk[2][1];bk[2][1]=bt[0][1];bt[0][1]=temp;
			temp=ft[1][1];ft[1][1]=tp[1][1];tp[1][1]=bk[1][1];bk[1][1]=bt[1][1];bt[1][1]=temp;
			temp=ft[2][1];ft[2][1]=tp[0][1];tp[0][1]=bk[0][1];bk[0][1]=bt[2][1];bt[2][1]=temp;
		}
		else if(dir==CLOCK){
			temp=ft[0][1];ft[0][1]=bt[0][1];bt[0][1]=bk[2][1];bk[2][1]=tp[2][1];tp[2][1]=temp;
			temp=ft[1][1];ft[1][1]=bt[1][1];bt[1][1]=bk[1][1];bk[1][1]=tp[1][1];tp[1][1]=temp;
			temp=ft[2][1];ft[2][1]=bt[2][1];bt[2][1]=bk[0][1];bk[0][1]=tp[0][1];tp[0][1]=temp;
		}
	}
	if(rotcode==6){
		if(dir==ANTICLOCK){
			temp=ft[0][2];ft[0][2]=tp[2][2];tp[2][2]=bk[2][2];bk[2][2]=bt[0][2];bt[0][2]=temp;
			temp=ft[1][2];ft[1][2]=tp[1][2];tp[1][2]=bk[1][2];bk[1][2]=bt[1][2];bt[1][2]=temp;
			temp=ft[2][2];ft[2][2]=tp[0][2];tp[0][2]=bk[0][2];bk[0][2]=bt[2][2];bt[2][2]=temp;
			temp=rt[0][0];rt[0][0]=rt[0][2];rt[0][2]=rt[2][2];rt[2][2]=rt[2][0];rt[2][0]=temp;
			temp=rt[0][1];rt[0][1]=rt[1][2];rt[1][2]=rt[2][1];rt[2][1]=rt[1][0];rt[1][0]=temp;
		}
		else if(dir==CLOCK){
			temp=ft[0][2];ft[0][2]=bt[0][2];bt[0][2]=bk[2][2];bk[2][2]=tp[2][2];tp[2][2]=temp;
			temp=ft[1][2];ft[1][2]=bt[1][2];bt[1][2]=bk[1][2];bk[1][2]=tp[1][2];tp[1][2]=temp;
			temp=ft[2][2];ft[2][2]=bt[2][2];bt[2][2]=bk[0][2];bk[0][2]=tp[0][2];tp[0][2]=temp;
			temp=rt[0][0];rt[0][0]=rt[2][0];rt[2][0]=rt[2][2];rt[2][2]=rt[0][2];rt[0][2]=temp;
			temp=rt[0][1];rt[0][1]=rt[1][0];rt[1][0]=rt[2][1];rt[2][1]=rt[1][2];rt[1][2]=temp;
		}
	}
	if(rotcode==7){
		if(dir==ANTICLOCK){
			temp=ft[0][0];ft[0][0]=ft[0][2];ft[0][2]=ft[2][2];ft[2][2]=ft[2][0];ft[2][0]=temp;
			temp=ft[0][1];ft[0][1]=ft[1][2];ft[1][2]=ft[2][1];ft[2][1]=ft[1][0];ft[1][0]=temp;
			temp=tp[0][0];tp[0][0]=rt[0][0];rt[0][0]=bt[0][2];bt[0][2]=lt[2][2];lt[2][2]=temp;
			temp=tp[0][1];tp[0][1]=rt[1][0];rt[1][0]=bt[0][1];bt[0][1]=lt[1][2];lt[1][2]=temp;
			temp=tp[0][2];tp[0][2]=rt[2][0];rt[2][0]=bt[0][0];bt[0][0]=lt[0][2];lt[0][2]=temp;
		}
		else if(dir==CLOCK){
			temp=ft[0][0];ft[0][0]=ft[2][0];ft[2][0]=ft[2][2];ft[2][2]=ft[0][2];ft[0][2]=temp;
			temp=ft[0][1];ft[0][1]=ft[1][0];ft[1][0]=ft[2][1];ft[2][1]=ft[1][2];ft[1][2]=temp;
			temp=tp[0][0];tp[0][0]=lt[2][2];lt[2][2]=bt[0][2];bt[0][2]=rt[0][0];rt[0][0]=temp;
			temp=tp[0][1];tp[0][1]=lt[1][2];lt[1][2]=bt[0][1];bt[0][1]=rt[1][0];rt[1][0]=temp;
			temp=tp[0][2];tp[0][2]=lt[0][2];lt[0][2]=bt[0][0];bt[0][0]=rt[2][0];rt[2][0]=temp;
		}
	}
	if(rotcode==8){
		if(dir==ANTICLOCK){
			temp=tp[1][0];tp[1][0]=rt[0][1];rt[0][1]=bt[1][2];bt[1][2]=lt[2][2];lt[2][2]=temp;
			temp=tp[1][1];tp[1][1]=rt[1][1];rt[1][1]=bt[1][1];bt[1][1]=lt[1][2];lt[1][2]=temp;
			temp=tp[1][2];tp[1][2]=rt[2][1];rt[2][1]=bt[1][0];bt[0][0]=lt[0][2];lt[0][2]=temp;
		}
		else if(dir==CLOCK){
			temp=tp[1][0];tp[1][0]=lt[2][1];lt[2][1]=bt[1][2];bt[1][2]=rt[0][1];rt[0][1]=temp;
			temp=tp[1][1];tp[1][1]=lt[1][1];lt[1][1]=bt[1][1];bt[1][1]=rt[1][1];rt[1][1]=temp;
			temp=tp[1][2];tp[1][2]=lt[0][1];lt[0][1]=bt[1][0];bt[1][0]=rt[2][1];rt[2][1]=temp;
		}
	}
	if(rotcode==9){
		if(dir==ANTICLOCK){
			temp=bk[0][0];bk[0][0]=bk[0][2];bk[0][2]=bk[2][2];bk[2][2]=bk[2][0];bk[2][0]=temp;
			temp=bk[0][1];bk[0][1]=bk[1][2];bk[1][2]=bk[2][1];bk[2][1]=bk[1][0];bk[1][0]=temp;
			temp=tp[2][0];tp[2][0]=rt[0][2];rt[0][2]=bt[2][2];bt[2][2]=lt[2][0];lt[2][0]=temp;
			temp=tp[2][1];tp[2][1]=rt[1][2];rt[1][2]=bt[2][1];bt[2][1]=lt[1][0];lt[1][0]=temp;
			temp=tp[2][2];tp[2][2]=rt[2][2];rt[2][2]=bt[2][0];bt[2][0]=lt[0][0];lt[0][0]=temp;
		}
		else if(dir==CLOCK){
			temp=bk[0][0];bk[0][0]=bk[2][0];bk[2][0]=bk[2][2];bk[2][2]=bk[0][2];bk[0][2]=temp;
			temp=bk[0][1];bk[0][1]=bk[1][0];bk[1][0]=bk[2][1];bk[2][1]=bk[1][2];bk[1][2]=temp;
			temp=tp[2][0];tp[2][0]=lt[2][0];lt[2][0]=bt[2][2];bt[2][2]=rt[0][2];lt[0][2]=temp;
			temp=tp[2][1];tp[2][1]=lt[1][0];lt[1][0]=bt[2][1];bt[2][1]=rt[1][2];rt[1][2]=temp;
			temp=tp[2][2];tp[2][2]=lt[0][0];lt[0][0]=bt[2][0];bt[2][0]=rt[2][2];rt[2][2]=temp;
		}
	}

}

void face_jumble(int face){
	int i,j,l;
	if(face==1){
		for(i=0;i<3;i++){
			for(j=0;j<3;j++){
				a:l=rand()%6;
				switch(l){
				case 0:ft[i][j]=red;rd++;if(rd>9){goto a;}break;
				case 1:ft[i][j]=blue;bl++;if(bl>9){goto a;}break;
				case 2:ft[i][j]=green;gr++;if(gr>9){goto a;}break;
				case 3:ft[i][j]=yellow;yl++;if(yl>9){goto a;}break;
				case 4:ft[i][j]=orange;or++;if(or>9){goto a;}break;
				case 5:ft[i][j]=cyan;cy++;if(cy>9){goto a;}break;
				}
			}
		}
	}
	if(face==2){
		for(i=0;i<3;i++){
			for(j=0;j<3;j++){
				b:l=rand()%6;
				switch(l){
				case 0:bk[i][j]=red;rd++;if(rd>9){goto b;}break;
				case 1:bk[i][j]=blue;bl++;if(bl>9){goto b;}break;
				case 2:bk[i][j]=green;gr++;if(gr>9){goto b;}break;
				case 3:bk[i][j]=yellow;yl++;if(yl>9){goto b;}break;
				case 4:bk[i][j]=orange;or++;if(or>9){goto b;}break;
				case 5:bk[i][j]=cyan;cy++;if(cy>9){goto b;}break;
				}
			}
		}
	}
	if(face==3){
		for(i=0;i<3;i++){
			for(j=0;j<3;j++){
				c:l=rand()%6;
				switch(l){
				case 0:lt[i][j]=red;rd++;if(rd>9){goto c;}break;
				case 1:lt[i][j]=blue;bl++;if(bl>9){goto c;}break;
				case 2:lt[i][j]=green;gr++;if(gr>9){goto c;}break;
				case 3:lt[i][j]=yellow;yl++;if(yl>9){goto c;}break;
				case 4:lt[i][j]=orange;or++;if(or>9){goto c;}break;
				case 5:lt[i][j]=cyan;cy++;if(cy>9){goto c;}break;
				}
			}
		}
	}
	if(face==4){
		for(i=0;i<3;i++){
			for(j=0;j<3;j++){
				d:l=rand()%6;
				switch(l){
				case 0:rt[i][j]=red;rd++;if(rd>9){goto d;}break;
				case 1:rt[i][j]=blue;bl++;if(bl>9){goto d;}break;
				case 2:rt[i][j]=green;gr++;if(gr>9){goto d;}break;
				case 3:rt[i][j]=yellow;yl++;if(yl>9){goto d;}break;
				case 4:rt[i][j]=orange;or++;if(or>9){goto d;}break;
				case 5:rt[i][j]=cyan;cy++;if(cy>9){goto d;}break;
				}
			}
		}
	}
	if(face==5){
		for(i=0;i<3;i++){
			for(j=0;j<3;j++){
				e:l=rand()%6;
				switch(l){
				case 0:tp[i][j]=red;rd++;if(rd>9){goto e;}break;
				case 1:tp[i][j]=blue;bl++;if(bl>9){goto e;}break;
				case 2:tp[i][j]=green;gr++;if(gr>9){goto e;}break;
				case 3:tp[i][j]=yellow;yl++;if(yl>9){goto e;}break;
				case 4:tp[i][j]=orange;or++;if(or>9){goto e;}break;
				case 5:tp[i][j]=cyan;cy++;if(cy>9){goto e;}break;
				}
			}
		}
	}
	if(face==6){
		 for(i=0;i<3;i++){
			for(j=0;j<3;j++){
				f:l=rand()%6;
				switch(l){
				case 0:bt[i][j]=red;rd++;if(rd>9){goto f;}break;
				case 1:bt[i][j]=blue;bl++;if(bl>9){goto f;}break;
				case 2:bt[i][j]=green;gr++;if(gr>9){goto f;}break;
				case 3:bt[i][j]=yellow;yl++;if(yl>9){goto f;}break;
				case 4:bt[i][j]=orange;or++;if(or>9){goto f;}break;
				case 5:bt[i][j]=cyan;cy++;if(cy>9){goto f;}break;
				}
			}
		}
	}
}

void jumble(){
	int i;
	rd=0;bl=0;gr=0;yl=0;or=0;cy=0;
	for(i=1;i<=6;i++)
	{
		face_jumble(i);
	}
	printf("%d %d %d %d %d %d",rd,bl,gr,yl,or,cy);
	glutPostRedisplay();
}

void rot_hor()
{	
	glPushMatrix();
		glLineWidth(5.0);
		glColor3f(0.0,0.0,0.0);
		if(rotcode==0 || rotcode==1) glRotatef(theta1,0.0,1.0,0.0);
		glTranslatef(-2,2,-2);
		glutWireCube(2.0);
		glTranslatef(2,0,0);
		glutWireCube(2.0);
		glTranslatef(2,0,0);
		glutWireCube(2.0);
		glTranslatef(0,0,2);
		glutWireCube(2.0);
		glTranslatef(-2,0,0);
		glutWireCube(2.0);
		glTranslatef(-2,0,0);
		glutWireCube(2.0);
		glTranslatef(0,0,2);
		glutWireCube(2.0);
		glTranslatef(2,0,0);
		glutWireCube(2.0);
		glTranslatef(2,0,0);
		glutWireCube(2.0);
		glColor3fv(yellow);
		glTranslatef(-2,-2,-2);
		colorface(facefront[0],facefront[1],facefront[5],facefront[4],ft[0][0]);
		colorface(facefront[1],facefront[2],facefront[6],facefront[5],ft[0][1]);
		colorface(facefront[2],facefront[3],facefront[7],facefront[6],ft[0][2]);
		colorface(faceback[0],faceback[1],faceback[5],faceback[4],bk[0][0]);
		colorface(faceback[1],faceback[2],faceback[6],faceback[5],bk[0][1]);
		colorface(faceback[2],faceback[3],faceback[7],faceback[6],bk[0][2]);
		colorface(faceleft[0],faceleft[1],faceleft[5],faceleft[4],lt[0][0]);
		colorface(faceleft[1],faceleft[2],faceleft[6],faceleft[5],lt[0][1]);
		colorface(faceleft[2],faceleft[3],faceleft[7],faceleft[6],lt[0][2]);
		colorface(faceright[0],faceright[1],faceright[5],faceright[4],rt[0][0]);
		colorface(faceright[1],faceright[2],faceright[6],faceright[5],rt[0][1]);
		colorface(faceright[2],faceright[3],faceright[7],faceright[6],rt[0][2]);
		colorface(facetop[0],facetop[1],facetop[5],facetop[4],tp[0][0]);
		colorface(facetop[1],facetop[2],facetop[6],facetop[5],tp[0][1]);
		colorface(facetop[2],facetop[3],facetop[7],facetop[6],tp[0][2]);
		colorface(facetop[4],facetop[5],facetop[9],facetop[8],tp[1][0]);
		colorface(facetop[5],facetop[6],facetop[10],facetop[9],tp[1][1]);
		colorface(facetop[6],facetop[7],facetop[11],facetop[10],tp[1][2]);
		colorface(facetop[8],facetop[9],facetop[13],facetop[12],tp[2][0]);
		colorface(facetop[9],facetop[10],facetop[14],facetop[13],tp[2][1]);
		colorface(facetop[10],facetop[11],facetop[15],facetop[14],tp[2][2]);
	glPopMatrix();
	glPushMatrix();
		glColor3f(0.0,0.0,0.0);
		glLineWidth(5.0);
		if(rotcode==0 || rotcode==2) glRotatef(theta1,0.0,1.0,0.0);
		glTranslatef(2,0,2);
		glutWireCube(2.0);
		glTranslatef(-2,0,0);
		glutWireCube(2.0);
		glTranslatef(-2,0,0);
		glutWireCube(2.0);
		glTranslatef(0,0,-2);
		glutWireCube(2.0);
		glTranslatef(2,0,0);
		glutWireCube(2.0);
		glTranslatef(2,0,0);
		glutWireCube(2.0);
		glTranslatef(0,0,-2);
		glutWireCube(2.0);
		glTranslatef(-2,0,0);
		glutWireCube(2.0);
		glTranslatef(-2,0,0);
		glutWireCube(2.0);
		glTranslatef(2,0,2);
		colorface(facefront[4],facefront[5],facefront[9],facefront[8],ft[1][0]);
		colorface(facefront[5],facefront[6],facefront[10],facefront[9],ft[1][1]);
		colorface(facefront[6],facefront[7],facefront[11],facefront[10],ft[1][2]);
		colorface(faceback[4],faceback[5],faceback[9],faceback[8],bk[1][0]);
		colorface(faceback[5],faceback[6],faceback[10],faceback[9],bk[1][1]);
		colorface(faceback[6],faceback[7],faceback[11],faceback[10],bk[1][2]);
		colorface(faceleft[4],faceleft[5],faceleft[9],faceleft[8],lt[1][0]);
		colorface(faceleft[5],faceleft[6],faceleft[10],faceleft[9],lt[1][1]);
		colorface(faceleft[6],faceleft[7],faceleft[11],faceleft[10],lt[1][2]);
		colorface(faceright[4],faceright[5],faceright[9],faceright[8],rt[1][0]);
		colorface(faceright[5],faceright[6],faceright[10],faceright[9],rt[1][1]);
		colorface(faceright[6],faceright[7],faceright[11],faceright[10],rt[1][2]);
	glPopMatrix();
	glPushMatrix();
		glLineWidth(5.0);
		glColor3f(0.0,0.0,0.0);
		if(rotcode==0 || rotcode==3) glRotatef(theta1,0.0,1.0,0.0);
		glTranslatef(-2,-2,-2);
		glutWireCube(2.0);
		glTranslatef(2,0,0);
		glutWireCube(2.0);
		glTranslatef(2,0,0);
		glutWireCube(2.0);
		glTranslatef(0,0,2);
		glutWireCube(2.0);
		glTranslatef(-2,0,0);
		glutWireCube(2.0);
		glTranslatef(-2,0,0);
		glutWireCube(2.0);
		glTranslatef(0,0,2);
		glutWireCube(2.0);
		glTranslatef(2,0,0);
		glutWireCube(2.0);
		glTranslatef(2,0,0);
		glutWireCube(2.0);
		glTranslatef(-2,2,-2);
		colorface(facefront[8],facefront[9],facefront[13],facefront[12],ft[2][0]);
		colorface(facefront[9],facefront[10],facefront[14],facefront[13],ft[2][1]);
		colorface(facefront[10],facefront[11],facefront[15],facefront[14],ft[2][2]);
		colorface(faceback[8],faceback[9],faceback[13],faceback[12],bk[2][0]);
		colorface(faceback[9],faceback[10],faceback[14],faceback[13],bk[2][1]);
		colorface(faceback[10],faceback[11],faceback[15],faceback[14],bk[2][2]);
		colorface(faceleft[8],faceleft[9],faceleft[13],faceleft[12],lt[2][0]);
		colorface(faceleft[9],faceleft[10],faceleft[14],faceleft[13],lt[2][1]);
		colorface(faceleft[10],faceleft[11],faceleft[15],faceleft[14],lt[2][2]);
		colorface(faceright[8],faceright[9],faceright[13],faceright[12],rt[2][0]);
		colorface(faceright[9],faceright[10],faceright[14],faceright[13],rt[2][1]);
		colorface(faceright[10],faceright[11],faceright[15],faceright[14],rt[2][2]);
		colorface(facebottom[0],facebottom[1],facebottom[5],facebottom[4],bt[0][0]);
		colorface(facebottom[1],facebottom[2],facebottom[6],facebottom[5],bt[0][1]);
		colorface(facebottom[2],facebottom[3],facebottom[7],facebottom[6],bt[0][2]);
		colorface(facebottom[4],facebottom[5],facebottom[9],facebottom[8],bt[1][0]);
		colorface(facebottom[5],facebottom[6],facebottom[10],facebottom[9],bt[1][1]);
		colorface(facebottom[6],facebottom[7],facebottom[11],facebottom[10],bt[1][2]);
		colorface(facebottom[8],facebottom[9],facebottom[13],facebottom[12],bt[2][0]);
		colorface(facebottom[9],facebottom[10],facebottom[14],facebottom[13],bt[2][1]);
		colorface(facebottom[10],facebottom[11],facebottom[15],facebottom[14],bt[2][2]);
	glPopMatrix();
	glutPostRedisplay();
}

void rot_ver()
{	
	glPushMatrix();
		glLineWidth(5.0);
		glColor3f(0.0,0.0,0.0);
		if(rotcode==4) glRotatef(theta1,1.0,0.0,0.0);
		glTranslatef(-2,-2,-2);
		glutWireCube(2.0);
		glTranslatef(0,0,2);
		glutWireCube(2.0);
		glTranslatef(0,0,2);
		glutWireCube(2.0);
		glTranslatef(0,2,0);
		glutWireCube(2.0);
		glTranslatef(0,0,-2);
		glutWireCube(2.0);
		glTranslatef(0,0,-2);
		glutWireCube(2.0);
		glTranslatef(0,2,0);
		glutWireCube(2.0);
		glTranslatef(0,0,2);
		glutWireCube(2.0);
		glTranslatef(0,0,2);
		glutWireCube(2.0);
		glTranslatef(2,-2,-2);
		colorface(facefront[0],facefront[1],facefront[5],facefront[4],ft[0][0]);
		colorface(facefront[4],facefront[5],facefront[9],facefront[8],ft[1][0]);
		colorface(facefront[8],facefront[9],facefront[13],facefront[12],ft[2][0]);
		colorface(facetop[0],facetop[1],facetop[5],facetop[4],tp[0][0]);
		colorface(facetop[4],facetop[5],facetop[9],facetop[8],tp[1][0]);
		colorface(facetop[8],facetop[9],facetop[13],facetop[12],tp[2][0]);
		colorface(faceback[0],faceback[1],faceback[5],faceback[4],bk[0][0]);
		colorface(faceback[4],faceback[5],faceback[9],faceback[8],bk[1][0]);
		colorface(faceback[8],faceback[9],faceback[13],faceback[12],bk[2][0]);
		colorface(facebottom[0],facebottom[1],facebottom[5],facebottom[4],bt[0][0]);
		colorface(facebottom[4],facebottom[5],facebottom[9],facebottom[8],bt[1][0]);
		colorface(facebottom[8],facebottom[9],facebottom[13],facebottom[12],bt[2][0]);
		colorface(faceleft[0],faceleft[1],faceleft[5],faceleft[4],lt[0][0]);
		colorface(faceleft[1],faceleft[2],faceleft[6],faceleft[5],lt[0][1]);
		colorface(faceleft[2],faceleft[3],faceleft[7],faceleft[6],lt[0][2]);
		colorface(faceleft[4],faceleft[5],faceleft[9],faceleft[8],lt[1][0]);
		colorface(faceleft[5],faceleft[6],faceleft[10],faceleft[9],lt[1][1]);
		colorface(faceleft[6],faceleft[7],faceleft[11],faceleft[10],lt[1][2]);
		colorface(faceleft[8],faceleft[9],faceleft[13],faceleft[12],lt[2][0]);
		colorface(faceleft[9],faceleft[10],faceleft[14],faceleft[13],lt[2][1]);
		colorface(faceleft[10],faceleft[11],faceleft[15],faceleft[14],lt[2][2]);
	glPopMatrix();
	glPushMatrix();
		glLineWidth(5.0);
		glColor3f(0.0,0.0,0.0);
		if(rotcode==5) glRotatef(theta1,1.0,0.0,0.0);
		glTranslatef(0,-2,-2);
		glutWireCube(2.0);
		glTranslatef(0,0,2);
		glutWireCube(2.0);
		glTranslatef(0,0,2);
		glutWireCube(2.0);
		glTranslatef(0,2,0);
		glutWireCube(2.0);
		glTranslatef(0,0,-2);
		glutWireCube(2.0);
		glTranslatef(0,0,-2);
		glutWireCube(2.0);
		glTranslatef(0,2,0);
		glutWireCube(2.0);
		glTranslatef(0,0,2);
		glutWireCube(2.0);
		glTranslatef(0,0,2);
		glutWireCube(2.0);
		glTranslatef(0,-2,-2);
		colorface(facefront[1],facefront[2],facefront[6],facefront[5],ft[0][1]);
		colorface(facefront[5],facefront[6],facefront[10],facefront[9],ft[1][1]);
		colorface(facefront[9],facefront[10],facefront[14],facefront[13],ft[2][1]);
		colorface(facetop[1],facetop[2],facetop[6],facetop[5],tp[0][1]);
		colorface(facetop[5],facetop[6],facetop[10],facetop[9],tp[1][1]);
		colorface(facetop[9],facetop[10],facetop[14],facetop[13],tp[2][1]);
		colorface(faceback[1],faceback[2],faceback[6],faceback[5],bk[0][1]);
		colorface(faceback[5],faceback[6],faceback[10],faceback[9],bk[1][1]);
		colorface(faceback[9],faceback[10],faceback[14],faceback[13],bk[2][1]);
		colorface(facebottom[1],facebottom[2],facebottom[6],facebottom[5],bt[0][1]);
		colorface(facebottom[5],facebottom[6],facebottom[10],facebottom[9],bt[1][1]);
		colorface(facebottom[9],facebottom[10],facebottom[14],facebottom[13],bt[2][1]);
	glPopMatrix();
	glPushMatrix();
		glLineWidth(5.0);
		glColor3f(0.0,0.0,0.0);
		if(rotcode==6) glRotatef(theta1,1.0,0.0,0.0);
		glTranslatef(2,-2,-2);
		glutWireCube(2.0);
		glTranslatef(0,0,2);
		glutWireCube(2.0);
		glTranslatef(0,0,2);
		glutWireCube(2.0);
		glTranslatef(0,2,0);
		glutWireCube(2.0);
		glTranslatef(0,0,-2);
		glutWireCube(2.0);
		glTranslatef(0,0,-2);
		glutWireCube(2.0);
		glTranslatef(0,2,0);
		glutWireCube(2.0);
		glTranslatef(0,0,2);
		glutWireCube(2.0);
		glTranslatef(0,0,2);
		glutWireCube(2.0);
		glTranslatef(-2,-2,-2);
		colorface(facefront[2],facefront[3],facefront[7],facefront[6],ft[0][2]);
		colorface(facefront[6],facefront[7],facefront[11],facefront[10],ft[1][2]);
		colorface(facefront[10],facefront[11],facefront[15],facefront[14],ft[2][2]);
		colorface(facetop[2],facetop[3],facetop[7],facetop[6],tp[0][2]);
		colorface(facetop[6],facetop[7],facetop[11],facetop[10],tp[1][2]);
		colorface(facetop[10],facetop[11],facetop[15],facetop[14],tp[2][2]);
		colorface(faceback[2],faceback[3],faceback[7],faceback[6],bk[0][2]);
		colorface(faceback[6],faceback[7],faceback[11],faceback[10],bk[1][2]);
		colorface(faceback[10],faceback[11],faceback[15],faceback[14],bk[2][2]);
		colorface(facebottom[2],facebottom[3],facebottom[7],facebottom[6],bt[0][2]);
		colorface(facebottom[6],facebottom[7],facebottom[11],facebottom[10],bt[1][2]);
		colorface(facebottom[10],facebottom[11],facebottom[15],facebottom[14],bt[2][2]);
		colorface(faceright[0],faceright[1],faceright[5],faceright[4],rt[0][0]);
		colorface(faceright[1],faceright[2],faceright[6],faceright[5],rt[0][1]);
		colorface(faceright[2],faceright[3],faceright[7],faceright[6],rt[0][2]);
		colorface(faceright[4],faceright[5],faceright[9],faceright[8],rt[1][0]);
		colorface(faceright[5],faceright[6],faceright[10],faceright[9],rt[1][1]);
		colorface(faceright[6],faceright[7],faceright[11],faceright[10],rt[1][2]);
		colorface(faceright[8],faceright[9],faceright[13],faceright[12],rt[2][0]);
		colorface(faceright[9],faceright[10],faceright[14],faceright[13],rt[2][1]);
		colorface(faceright[10],faceright[11],faceright[15],faceright[14],rt[2][2]);
	glPopMatrix();
	glutPostRedisplay();
}

void rot_fac()
{
	glPushMatrix();
		glLineWidth(5.0);
		glColor3f(0.0,0.0,0.0);
		if(rotcode==7) glRotatef(theta1,0.0,0.0,1.0);
		glTranslatef(-2,-2,2);
		glutWireCube(2.0);
		glTranslatef(2,0,0);
		glutWireCube(2.0);
		glTranslatef(2,0,0);
		glutWireCube(2.0);
		glTranslatef(0,2,0);
		glutWireCube(2.0);
		glTranslatef(-2,0,0);
		glutWireCube(2.0);
		glTranslatef(-2,0,0);
		glutWireCube(2.0);
		glTranslatef(0,2,0);
		glutWireCube(2.0);
		glTranslatef(2,0,0);
		glutWireCube(2.0);
		glTranslatef(2,0,0);
		glutWireCube(2.0);
		glTranslatef(-2,-2,-2);
		colorface(facefront[0],facefront[1],facefront[5],facefront[4],ft[0][0]);
		colorface(facefront[1],facefront[2],facefront[6],facefront[5],ft[0][1]);
		colorface(facefront[2],facefront[3],facefront[7],facefront[6],ft[0][2]);
		colorface(facefront[4],facefront[5],facefront[9],facefront[8],ft[1][0]);
		colorface(facefront[5],facefront[6],facefront[10],facefront[9],ft[1][1]);
		colorface(facefront[6],facefront[7],facefront[11],facefront[10],ft[1][2]);
		colorface(facefront[8],facefront[9],facefront[13],facefront[12],ft[2][0]);
		colorface(facefront[9],facefront[10],facefront[14],facefront[13],ft[2][1]);
		colorface(facefront[10],facefront[11],facefront[15],facefront[14],ft[2][2]);
		colorface(facetop[0],facetop[1],facetop[5],facetop[4],tp[0][0]);
		colorface(facetop[1],facetop[2],facetop[6],facetop[5],tp[0][1]);
		colorface(facetop[2],facetop[3],facetop[7],facetop[6],tp[0][2]);
		colorface(facebottom[0],facebottom[1],facebottom[5],facebottom[4],bt[0][0]);
		colorface(facebottom[1],facebottom[2],facebottom[6],facebottom[5],bt[0][1]);
		colorface(facebottom[2],facebottom[3],facebottom[7],facebottom[6],bt[0][2]);
		colorface(faceleft[2],faceleft[3],faceleft[7],faceleft[6],lt[0][2]);
		colorface(faceleft[6],faceleft[7],faceleft[11],faceleft[10],lt[1][2]);
		colorface(faceleft[10],faceleft[11],faceleft[15],faceleft[14],lt[2][2]);
		colorface(faceright[2],faceright[3],faceright[7],faceright[6],rt[0][2]);
		colorface(faceright[6],faceright[7],faceright[11],faceright[10],rt[1][2]);
		colorface(faceright[10],faceright[11],faceright[15],faceright[14],rt[2][2]);		
	glPopMatrix();
	glPushMatrix();
		glLineWidth(5.0);
		glColor3f(0.0,0.0,0.0);
		if(rotcode==8) glRotatef(theta1,0.0,0.0,1.0);
		glTranslatef(-2,-2,0);
		glutWireCube(2.0);
		glTranslatef(2,0,0);
		glutWireCube(2.0);
		glTranslatef(2,0,0);
		glutWireCube(2.0);
		glTranslatef(0,2,0);
		glutWireCube(2.0);
		glTranslatef(-2,0,0);
		glutWireCube(2.0);
		glTranslatef(-2,0,0);
		glutWireCube(2.0);
		glTranslatef(0,2,0);
		glutWireCube(2.0);
		glTranslatef(2,0,0);
		glutWireCube(2.0);
		glTranslatef(2,0,0);
		glutWireCube(2.0);
		glTranslatef(-2,-2,0);
		colorface(facetop[4],facetop[5],facetop[9],facetop[8],tp[1][0]);
		colorface(facetop[5],facetop[6],facetop[10],facetop[9],tp[1][1]);
		colorface(facetop[6],facetop[7],facetop[11],facetop[10],tp[1][2]);
		colorface(facebottom[4],facebottom[5],facebottom[9],facebottom[8],bt[1][0]);
		colorface(facebottom[5],facebottom[6],facebottom[10],facebottom[9],bt[1][1]);
		colorface(facebottom[6],facebottom[7],facebottom[11],facebottom[10],bt[1][2]);
		colorface(faceleft[1],faceleft[2],faceleft[6],faceleft[5],lt[0][1]);
		colorface(faceleft[5],faceleft[6],faceleft[10],faceleft[9],lt[1][1]);
		colorface(faceleft[9],faceleft[10],faceleft[14],faceleft[13],lt[2][1]);
		colorface(faceright[1],faceright[2],faceright[6],faceright[5],rt[0][1]);
		colorface(faceright[5],faceright[6],faceright[10],faceright[9],rt[1][1]);
		colorface(faceright[9],faceright[10],faceright[14],faceright[13],rt[2][1]);
	glPopMatrix();
	glPushMatrix();
		glLineWidth(5.0);
		glColor3f(0.0,0.0,0.0);
		if(rotcode==9) glRotatef(theta1,0.0,0.0,1.0);
		glTranslatef(-2,-2,-2);
		glutWireCube(2.0);
		glTranslatef(2,0,0);
		glutWireCube(2.0);
		glTranslatef(2,0,0);
		glutWireCube(2.0);
		glTranslatef(0,2,0);
		glutWireCube(2.0);
		glTranslatef(-2,0,0);
		glutWireCube(2.0);
		glTranslatef(-2,0,0);
		glutWireCube(2.0);
		glTranslatef(0,2,0);
		glutWireCube(2.0);
		glTranslatef(2,0,0);
		glutWireCube(2.0);
		glTranslatef(2,0,0);
		glutWireCube(2.0);
		glTranslatef(-2,-2,2);
		colorface(faceback[0],faceback[1],faceback[5],faceback[4],bk[0][0]);
		colorface(faceback[1],faceback[2],faceback[6],faceback[5],bk[0][1]);
		colorface(faceback[2],faceback[3],faceback[7],faceback[6],bk[0][2]);
		colorface(faceback[4],faceback[5],faceback[9],faceback[8],bk[1][0]);
		colorface(faceback[5],faceback[6],faceback[10],faceback[9],bk[1][1]);
		colorface(faceback[6],faceback[7],faceback[11],faceback[10],bk[1][2]);
		colorface(faceback[8],faceback[9],faceback[13],faceback[12],bk[2][0]);
		colorface(faceback[9],faceback[10],faceback[14],faceback[13],bk[2][1]);
		colorface(faceback[10],faceback[11],faceback[15],faceback[14],bk[2][2]);
		colorface(facetop[8],facetop[9],facetop[13],facetop[12],tp[2][0]);
		colorface(facetop[9],facetop[10],facetop[14],facetop[13],tp[2][1]);
		colorface(facetop[10],facetop[11],facetop[15],facetop[14],tp[2][2]);
		colorface(facebottom[8],facebottom[9],facebottom[13],facebottom[12],bt[2][0]);
		colorface(facebottom[9],facebottom[10],facebottom[14],facebottom[13],bt[2][1]);
		colorface(facebottom[10],facebottom[11],facebottom[15],facebottom[14],bt[2][2]);
		colorface(faceleft[0],faceleft[1],faceleft[5],faceleft[4],lt[0][0]);
		colorface(faceleft[4],faceleft[5],faceleft[9],faceleft[8],lt[1][0]);
		colorface(faceleft[8],faceleft[9],faceleft[13],faceleft[12],lt[2][0]);
		colorface(faceright[0],faceright[1],faceright[5],faceright[4],rt[0][0]);
		colorface(faceright[4],faceright[5],faceright[9],faceright[8],rt[1][0]);
		colorface(faceright[8],faceright[9],faceright[13],faceright[12],rt[2][0]);
	glPopMatrix();
	glutPostRedisplay();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0,1.0,1.0,1.0);
	glLoadIdentity();
	glRotatef(theta[0],1.0,0.0,0.0);
	glRotatef(theta[1],0.0,1.0,0.0);
	//glRotatef(theta[2],0.0,0.0,1.0);
	if(jl==0){jumble();jl=1;}
	if(rot==0 || rot==1){
		rot_hor();	
	}
	if(rot==2){
		rot_ver();
	}
	if(rot==3){
		rot_fac();
	}
	if(theta1==90 || theta1==-90){
			color_op();theta1=0;
	}
	glFlush();
	glutSwapBuffers();
}

void rotate(int x,int y)
{
	theta[axis]+=1.0;
	if(theta[axis]>360)theta[axis]-=360.0;
	glutPostRedisplay();
}

void idle()
{
	if(dir==ANTICLOCK){
		theta1++;
		if(theta1>=90){
			glutIdleFunc(NULL);
		}
	}
	if(dir==CLOCK){
		theta1--;
		if(theta1<=-90){
			glutIdleFunc(NULL);
		}
	}
	glutPostRedisplay();
}

void mouse(int btn,int state,int x,int y)
{
	if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)axis=0;
	if(btn==GLUT_MIDDLE_BUTTON && state==GLUT_DOWN)axis=1;
	//if(btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)axis=2;
}

void myreshape(int w,int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w<=h)
		glOrtho(-6.0,6.0,-6.0*(GLfloat)h/(GLfloat)w,6.0*(GLfloat)h/(GLfloat)w,-6.0,6.0);
	else
		glOrtho(-6.0*(GLfloat)w/(GLfloat)h,6.0*(GLfloat)w/(GLfloat)h,-6.0,6.0,-6.0,6.0);
	glMatrixMode(GL_MODELVIEW);
}

void mainmenu(int id){
	jumble();
	glutPostRedisplay();
}
void rotv(int id){}
void roth(int id){}
void rotf(int id){}

void top(int id)
{
	switch(id)
	{
	case 1:dir=CLOCK;break;
	case 2:dir=ANTICLOCK;break;
	}
	rotcode=1;rot=1;theta1=0;
	glutIdleFunc(idle);
}
void midh(int id)
{
	switch(id)
	{
	case 1:dir=CLOCK;break;
	case 2:dir=ANTICLOCK;break;
	}
	rotcode=2;rot=1;theta1=0;
	glutIdleFunc(idle);
}
void bot(int id)
{
	switch(id)
	{
	case 1:dir=CLOCK;break;
	case 2:dir=ANTICLOCK;break;
	}
	rotcode=3;rot=1;theta1=0;
	glutIdleFunc(idle);
}
void left(int id)
{
	switch(id)
	{
	case 1:dir=CLOCK;break;
	case 2:dir=ANTICLOCK;break;
	}
	rotcode=4;rot=2;theta1=0;
	glutIdleFunc(idle);
}
void midv(int id)
{
	switch(id)
	{
	case 1:dir=CLOCK;break;
	case 2:dir=ANTICLOCK;break;
	}
	rotcode=5;rot=2;theta1=0;
	glutIdleFunc(idle);
}
void right(int id)
{
	switch(id)
	{
	case 1:dir=CLOCK;break;
	case 2:dir=ANTICLOCK;break;
	}
	rotcode=6;rot=2;theta1=0;
	glutIdleFunc(idle);
}
void front(int id)
{
	switch(id)
	{
	case 1:dir=CLOCK;break;
	case 2:dir=ANTICLOCK;break;
	}
	rotcode=7;rot=3;theta1=0;
	glutIdleFunc(idle);
}
void midf(int id)
{
	switch(id)
	{
	case 1:dir=CLOCK;break;
	case 2:dir=ANTICLOCK;break;
	}
	rotcode=8;rot=3;theta1=0;
	glutIdleFunc(idle);
}
void back(int id)
{
	switch(id)
	{
	case 1:dir=CLOCK;break;
	case 2:dir=ANTICLOCK;break;
	}
	rotcode=9;rot=3;theta1=0;
	glutIdleFunc(idle);
}

void main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize(768,768);
	glutCreateWindow("Rubik's Cube");
	glutDisplayFunc(display);
	glutReshapeFunc(myreshape);
	glutMouseFunc(mouse);
	glutMotionFunc(rotate);
	glutIdleFunc(idle);
	int htop=glutCreateMenu(top);
		glutAddMenuEntry("Rotate Clockwise",1);
		glutAddMenuEntry("Rotate Anticlockwise",2);
	int hmid=glutCreateMenu(midh);
		glutAddMenuEntry("Rotate Clockwise",1);
		glutAddMenuEntry("Rotate Anticlockwise",2);
	int hbot=glutCreateMenu(bot);
		glutAddMenuEntry("Rotate Clockwise",1);
		glutAddMenuEntry("Rotate Anticlockwise",2);
	int hrot=glutCreateMenu(roth);
		glutAddSubMenu("Top",htop);
		glutAddSubMenu("Middle",hmid);
		glutAddSubMenu("Bottom",hbot);

	int vleft=glutCreateMenu(left);
		glutAddMenuEntry("Rotate Clockwise",1);
		glutAddMenuEntry("Rotate Anticlockwise",2);
	int vmid=glutCreateMenu(midv);
		glutAddMenuEntry("Rotate Clockwise",1);
		glutAddMenuEntry("Rotate Anticlockwise",2);
	int vright=glutCreateMenu(right);
		glutAddMenuEntry("Rotate Clockwise",1);
		glutAddMenuEntry("Rotate Anticlockwise",2);
	int vrot=glutCreateMenu(rotv);
		glutAddSubMenu("Left",vleft);
		glutAddSubMenu("Middle",vmid);
		glutAddSubMenu("Right",vright);

	int ffront=glutCreateMenu(front);
		glutAddMenuEntry("Rotate Clockwise",1);
		glutAddMenuEntry("Rotate Anticlockwise",2);
	int fmid=glutCreateMenu(midf);
		glutAddMenuEntry("Rotate Clockwise",1);
		glutAddMenuEntry("Rotate Anticlockwise",2);
	int fback=glutCreateMenu(back);
		glutAddMenuEntry("Rotate Clockwise",1);
		glutAddMenuEntry("Rotate Anticlockwise",2);
	int frot=glutCreateMenu(rotf);
		glutAddSubMenu("Front",ffront);
		glutAddSubMenu("Middle",fmid);
		glutAddSubMenu("Back",fback);

	glutCreateMenu(mainmenu);
		glutAddSubMenu("Horizontal Rotation",hrot);
		glutAddSubMenu("Vertical Rotation",vrot);
		glutAddSubMenu("Face Rotation",frot);
		glutAddMenuEntry("Jumble",1);
		glutAttachMenu(GLUT_RIGHT_BUTTON);

	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
}
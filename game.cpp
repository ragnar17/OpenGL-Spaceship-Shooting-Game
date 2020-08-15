#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<bits/stdc++.h>
using namespace std;

float psz=10.0;
float psz7=7.0*(psz/10);
float psz10=psz;
int win_x=1000,win_y=1000;
float m_x=(float)(win_x/2),m_y=5*psz7;
float sz=20.0f;
float bb=10.0; //bot speed
clock_t current_time;
float bullet_speed=3.0f;
float enemy_speed=3.0f,enemy_bullets_speed=2.0f;
long long score=0;
bool keys[256];
int enemy_generation_speed=2000;
//***********COLORS********************//
struct enemy
{
	float x;
	float y;
	int type;
	int active;
};
struct bullet
{
	float x;
	float y;
	int type;
	int active;
};

vector<bullet> bullets;
vector<enemy> enemy_list;
vector<bullet> enemy_bullets;
void init()
{
    glClearColor(0.2352, 0.2352, 0.2352, 0.0);
    glColor3f(1.0f,0.0f,0.0f);
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (float)win_x, 0.0, (float)win_y);
    glMatrixMode(GL_MODELVIEW);
}
int cnt=0;
void draw_square(float x, float y, float height, float width,float c1,float c2,float c3)
{
	glColor3f(c1,c2,c3);
	glBegin(GL_POLYGON);
		glVertex3f(x, y, 0.0);
		glVertex3f(x, y+height, 0.0);
		glVertex3f(x+width, y+height, 0.0);
		glVertex3f(x+width, y, 0.0);
	glEnd();
}
void draw_left_square(float x, float y, float height, float width,float c1,float c2,float c3)
{
	glColor3f(c1,c2,c3);
	glBegin(GL_POLYGON);
		glVertex3f(x, y, 0.0);
		glVertex3f(x, y+height, 0.0);
		glVertex3f(x-width, y+height, 0.0);
		glVertex3f(x-width, y, 0.0);
	glEnd();
}
void draw_enemy_ship(float x,float y,int type)
{

	float o1=1.0,o2=0.6823,o3=0.0;
	float r1=1.0,r2=0.0,r3=0.0;
	float blx1=0.0,blx2=0.0,blx3=0.0;
	float b1=0.0,b2=0.5647,b3=0.9215;
	float w1=1.0,w2=1.0,w3=1.0;
	float y1=1.0,y2=0.8235,y3=0.0;
	float bl1=0.156,bl2=0.156,bl3=0.156;
	x=x-4*psz;
	y=y-3*psz;
	glColor3f(r1,r2,r3);
	glBegin(GL_POLYGON);
		glVertex3f(x, y, 0.0);
		glVertex3f(x, y+psz, 0.0);
		glVertex3f(x+psz, y+psz, 0.0);
	glEnd();

	draw_square(x,y+psz,5*psz,psz,blx1,blx2,blx3);
	draw_square(x+psz,y+4*psz,psz,psz,r1,r2,r3);
	draw_square(x+psz,y+5*psz,psz,psz,blx1,blx2,blx3);
	draw_square(x+3*psz,y+3*psz,psz,psz,r1,r2,r3);

	draw_square(x+psz,y+3*psz,psz,2*psz,blx1,blx2,blx3);
	draw_square(x+2*psz,y+4*psz,psz,2*psz,blx1,blx2,blx3);

	glColor3f(blx1,blx2,blx3);
	glBegin(GL_POLYGON);
		glVertex3f(x+psz, y+3*psz, 0.0);
		glVertex3f(x+4*psz, y, 0.0);
		glVertex3f(x+4*psz, y+3*psz, 0.0);
	glEnd();

	glColor3f(blx1,blx2,blx3);
	glBegin(GL_POLYGON);
		glVertex3f(x+2*psz, y+5*psz, 0.0);
		glVertex3f(x+2*psz, y+6*psz, 0.0);
		glVertex3f(x+3*psz, y+5*psz, 0.0);
	glEnd();

	glColor3f(r1,r2,r3);
	glBegin(GL_POLYGON);
		glVertex3f(x+2*psz, y+2*psz, 0.0);
		glVertex3f(x+3*psz, y+2*psz, 0.0);
		glVertex3f(x+3*psz, y+psz, 0.0);
	glEnd();
	draw_square(x+3*psz,y+psz,psz,psz,r1,r2,r3);


	///other half
	x+=8*psz;
	glColor3f(r1,r2,r3);
	glBegin(GL_POLYGON);
		glVertex3f(x, y, 0.0);
		glVertex3f(x, y+psz, 0.0);
		glVertex3f(x-psz, y+psz, 0.0);
	glEnd();

	draw_left_square(x,y+psz,5*psz,psz,blx1,blx2,blx3);
	draw_left_square(x-psz,y+4*psz,psz,psz,r1,r2,r3);
	draw_left_square(x-psz,y+5*psz,psz,psz,blx1,blx2,blx3);
	draw_left_square(x-3*psz,y+3*psz,psz,psz,r1,r2,r3);

	draw_left_square(x-psz,y+3*psz,psz,2*psz,blx1,blx2,blx3);
	draw_left_square(x-2*psz,y+4*psz,psz,2*psz,blx1,blx2,blx3);

	glColor3f(blx1,blx2,blx3);
	glBegin(GL_POLYGON);
		glVertex3f(x-psz, y+3*psz, 0.0);
		glVertex3f(x-4*psz, y, 0.0);
		glVertex3f(x-4*psz, y+3*psz, 0.0);
	glEnd();

	glColor3f(blx1,blx2,blx3);
	glBegin(GL_POLYGON);
		glVertex3f(x-2*psz, y+5*psz, 0.0);
		glVertex3f(x-2*psz, y+6*psz, 0.0);
		glVertex3f(x-3*psz, y+5*psz, 0.0);
	glEnd();

	glColor3f(r1,r2,r3);
	glBegin(GL_POLYGON);
		glVertex3f(x-2*psz, y+2*psz, 0.0);
		glVertex3f(x-3*psz, y+2*psz, 0.0);
		glVertex3f(x-3*psz, y+psz, 0.0);
	glEnd();
	draw_left_square(x-3*psz,y+psz,psz,psz,r1,r2,r3);
}

void single_bullet(float x,float y,int type)
{
	psz=psz7;
	float y1=1.0,y2=0.8235,y3=0.0;
	glColor3f(y1,y2,y3);
	glBegin(GL_POLYGON);
		glVertex3f(x, y, 0.0);
		glVertex3f(x, y+psz, 0.0);
		glVertex3f(x+psz, y+psz, 0.0);
		glVertex3f(x+psz, y, 0.0);
	glEnd();

	glColor3f(y1,y2,y3);
	glBegin(GL_POLYGON);
		glVertex3f(x, y+psz, 0.0);
		glVertex3f(x+psz/2, y+2*psz, 0.0);
		glVertex3f(x+psz, y+psz, 0.0);
	glEnd();
	psz=psz10;
}
void draw_enemy_bullet(float x,float y,int type)
{
	float y1=1.0,y2=0.8235,y3=0.0;
	float r1=1.0,r2=0.0,r3=0.0;
	glColor3f(r1,r2,r3);
	glBegin(GL_POLYGON);
		glVertex3f(x, y, 0.0);
		glVertex3f(x, y+psz, 0.0);
		glVertex3f(x+psz, y+psz, 0.0);
		glVertex3f(x+psz, y, 0.0);
	glEnd();

	glColor3f(r1,r2,r3);
	glBegin(GL_POLYGON);
		glVertex3f(x, y, 0.0);
		glVertex3f(x+psz/2, y-psz, 0.0);
		glVertex3f(x+psz, y, 0.0);
	glEnd();
	psz=psz10;
}
void draw_bullet(float x,float y,int type)
{
	float cx=x,cy=y;
		single_bullet(cx,cy,1);
}


void draw_main_ship(float x,float y)
{
	float o1=1.0,o2=0.6823,o3=0.0;
	float r1=1.0,r2=0.0,r3=0.0;
	float blx1=0.0,blx2=0.0,blx3=0.0;
	float b1=0.0,b2=0.5647,b3=0.9215;
	float w1=1.0,w2=1.0,w3=1.0;
	float y1=1.0,y2=0.8235,y3=0.0;
	float bl1=0.156,bl2=0.156,bl3=0.156;
	psz=psz7;
	x=x-5*psz,y=y-5*psz;
	draw_square(x,y,psz,psz,o1,o2,o3);
	draw_square(x,y+psz,2*psz,psz,y1,y2,y3);
	draw_square(x+psz,y+2*psz,3*psz,psz,w1,w2,w3);
	draw_square(x+2*psz,y+3*psz,4*psz,3*psz,b1,b2,b3);
	draw_square(x+3*psz,y+4*psz,2*psz,psz,w1,w2,w3);
	draw_square(x,y+4*psz,2*psz,psz,bl1,bl2,bl3);
	draw_square(x,y+6*psz,psz,psz,o1,o2,o3);
	draw_square(x+4*psz,y+psz,psz,psz,o1,o2,o3);
	draw_square(x+4*psz,y+2*psz,psz,psz,y1,y2,y3);
	draw_square(x+4*psz,y+7*psz,2*psz,psz,w1,w2,w3);
	draw_square(x+5*psz,y+2*psz,7*psz,psz,b1,b2,b3);
	draw_square(x+5*psz,y+psz,psz,psz,o1,o2,o3);
	draw_square(x+5*psz,y+9*psz,2*psz,psz,w1,w2,w3);
	x+=11*psz;
	draw_left_square(x,y,psz,psz,o1,o2,o3);
	draw_left_square(x,y+psz,2*psz,psz,y1,y2,y3);
	draw_left_square(x-psz,y+2*psz,3*psz,psz,w1,w2,w3);
	draw_left_square(x-2*psz,y+3*psz,4*psz,3*psz,b1,b2,b3);
	draw_left_square(x-3*psz,y+4*psz,2*psz,psz,w1,w2,w3);
	draw_left_square(x,y+4*psz,2*psz,psz,bl1,bl2,bl3);
	draw_left_square(x,y+6*psz,psz,psz,o1,o2,o3);
	draw_left_square(x-4*psz,y+psz,psz,psz,o1,o2,o3);
	draw_left_square(x-4*psz,y+2*psz,psz,psz,y1,y2,y3);
	draw_left_square(x-4*psz,y+7*psz,2*psz,psz,w1,w2,w3);
	psz=psz10;
	
}
void bullet_movement(int v)
{
	for(int i=0;i<bullets.size();i++)
		if(bullets[i].active)
			bullets[i].y+=bullet_speed;
	for(int i=0;i<enemy_bullets.size();i++)
		if(enemy_bullets[i].active)
			enemy_bullets[i].y-=enemy_bullets_speed;
	glutTimerFunc(10, bullet_movement, 1);
}
void bullet_generation(int v)
{
	cnt=(cnt+1)%2;
	int w=-1;
	bullet b;
	b.x=m_x-5*psz7; b.y=m_y+psz7; b.type=cnt;b.active=1;
	for(int i=0;i<bullets.size();i++)
	{
		if(bullets[i].active==0)
		{
			w=i;
			break;
		}
	}
	if(w!=-1)
		bullets[w]=b;
	else
		bullets.push_back(b);
	w=-1;
	b.x=m_x+6*psz7-psz7; b.y=m_y+psz7; b.type=cnt;b.active=1;
	for(int i=0;i<bullets.size();i++)
	{
		if(bullets[i].active==0)
		{
			w=i;
			break;
		}
	}
	if(w!=-1)
		bullets[w]=b;
	else
		bullets.push_back(b);
	glutTimerFunc(300,bullet_generation,1);
}
void enemy_bullet_generation(int v)
{
	bullet b;
	for(int i=0;i<enemy_list.size();i++)
	{
		b.x=enemy_list[i].x-5.0f; b.y=enemy_list[i].y-sz; b.type=cnt;b.active=1;
		int w=-1;
		for(int j=0;j<enemy_bullets.size();j++)
		{
			if(enemy_bullets[j].active==0)
			{
				w=j;
				break;
			}
		}
		if(w!=-1)
			enemy_bullets[w]=b;
		else
			enemy_bullets.push_back(b);
	}
	
	glutTimerFunc(1500,enemy_bullet_generation,1);
}
void enemy_generation(int v)
{
	int gg=rand()%win_x;
	int type=1;
	enemy e;
	e.x=(float)gg;
	e.y=win_y-sz;
	e.type=1;
	e.active=1;
	int w=-1;
	for(int i=0;i<enemy_list.size();i++)
	{
		if(enemy_list[i].active==0)
		{
			w=i;
			break;
		}
	}
	if(w!=-1)
		enemy_list[w]=e;
	else
		enemy_list.push_back(e);
	glutTimerFunc(enemy_generation_speed,enemy_generation,1);
}
void enemy_generation_speed_controller(int v)
{
	enemy_generation_speed-=100;
	enemy_generation_speed=max(enemy_generation_speed,400);
	glutTimerFunc(10000,enemy_generation_speed_controller,1);
}
void enemy_movement(int v)
{
	for(int i =0;i<enemy_list.size();i++)
		if(enemy_list[i].active)
			enemy_list[i].y-=enemy_speed;
	glutTimerFunc(50,enemy_movement,1);
}
void display_text(string c,int x,int y,int z)
{
	glPushMatrix();
	glTranslatef(x, y+8,z);
	glScalef(0.15f,0.15f,z);
	for(int i=0;i<c.length();i++)
    glutStrokeCharacter(GLUT_STROKE_ROMAN , c[i]);
	glPopMatrix();
}
string score_to_str()
{
	string a="SCORE : ";
	string b="";
	int n=score;
	if(n==0)
		b+"0";
	while(n!=0)
	{
		b+=char('0'+n%10);
		n/=10;
	}
	reverse(b.begin(),b.end());
	return a+b;
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	draw_main_ship(m_x,m_y);
	int game_over=0;
	display_text(score_to_str(),5,win_y-30,0);
	//cout<<enemy_generation_speed<<endl;
	for(int i=0;i<enemy_bullets.size();i++)
	{
		if(!enemy_bullets[i].active)
			continue;
		if(enemy_bullets[i].active)
			draw_enemy_bullet(enemy_bullets[i].x,enemy_bullets[i].y,enemy_bullets[i].type);
		float mn_x=max(m_x-5*psz7,enemy_bullets[i].x);
		float mx_x=min(m_x+6*psz7,enemy_bullets[i].x+psz);
		float mn_y=max(m_y-4*psz7,enemy_bullets[i].y-psz);
		float mx_y=min(m_y+6*psz7,enemy_bullets[i].y+psz);
		if(mn_x<=mx_x and mn_y<=mx_y)
		{
				game_over=1;
				break;
		}
	}
	if(game_over)
		exit(0);
	for(int i=0;i<enemy_list.size();i++)
	{
		if(enemy_list[i].active==0)
			continue;
		bool fnd=0;
		for(int j=0;j<bullets.size();j++)
		{
			if(bullets[j].active==0)
				continue;
			float mn_x=max(enemy_list[i].x-4*psz,bullets[j].x);
			float mx_x=min(enemy_list[i].x+4*psz,bullets[j].x+psz7);
			float mn_y=max(enemy_list[i].y-3*psz,bullets[j].y);
			float mx_y=min(enemy_list[i].y+3*psz,bullets[j].y+2*psz7);
			
			if(mn_x<=mx_x and mn_y<=mx_y)
			{
				bullets[j].active=0;
				fnd=1;
				score+=10;
				break;
			}

		}
		if(fnd)
		{
			enemy_list[i].active=0;
		}
		if(enemy_list[i].active)
		{
			if(enemy_list[i].y>0.0)
				draw_enemy_ship(enemy_list[i].x,enemy_list[i].y,enemy_list[i].type);
			else
				enemy_list[i].active=0;
		}
	}
	for(int i=0;i<bullets.size();i++)
	{
		if(bullets[i].active)
		{
			if(bullets[i].y<(float)win_y)
				draw_bullet(bullets[i].x,bullets[i].y+sz,bullets[i].type);
			else
				bullets[i].active=0;
		}
	}
    glutSwapBuffers();
}
void SpecialKeys(int key,int x,int y)
{
	if(key == GLUT_KEY_UP)
	{
		m_y+= bb;
		m_y=min(m_y,(float)win_y-5*psz7);
	}
	else if(key == GLUT_KEY_DOWN)
	{
		m_y-= bb;
		m_y=max(m_y,5*psz7);
	}
	else if(key == GLUT_KEY_RIGHT)
	{
		m_x += bb;
		m_x=min(m_x,(float)win_x-6*psz7);
	}
	else if(key == GLUT_KEY_LEFT)
	{
		m_x -= bb;
		m_x=max(m_x,5*psz7);
	}
	else
		exit(0);
	glutPostRedisplay();
}

void KeyboardActionup(unsigned char key, int x,int y)
{
	cout<<key<<endl;
	keys[key]=true;
	exit(0);
}
void KeyboardActionright(unsigned char key, int x,int y)
{
	keys[key]=true;
	exit(0);
}
int main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(win_x,win_y);
	glViewport(0, 0, win_x, win_y);
	glutCreateWindow("Project X");
	init();
 	glutKeyboardFunc(KeyboardActionup);
 	glutKeyboardFunc(KeyboardActionright);
	glutSpecialFunc(SpecialKeys);
	glutTimerFunc(1, bullet_movement, 1);
	glutTimerFunc(1, bullet_generation, 1);
	glutTimerFunc(1, enemy_generation, 1);
	glutTimerFunc(1, enemy_movement, 1);
	glutTimerFunc(1, enemy_bullet_generation, 1);
	glutTimerFunc(1, enemy_generation_speed_controller, 1);
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutMainLoop();
	return 0;
}

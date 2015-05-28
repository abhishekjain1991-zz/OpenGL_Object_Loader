// OpenGL Jet program.
// ECE8893, Georgia Tech, Fall 2012
// Abhishek Jain ajain333 902985939
// Final
#include <iostream>

#ifdef LINUX
//Linux Headers
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#ifdef OSX
// MAC Headers
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#endif

#ifdef WINDOWS
//Windows Headers
#include <Windows.h>
#include <gl/GL.h>
#include <gl/glut.h>
#endif

#include <fstream>
#include <vector>

using namespace std;

GLfloat updateRate = 72.5; // Change this later
GLfloat whiteSpecularLight[] = {1.0, 1.0, 1.0, 1.0};
GLfloat blackAmbientLight[] = {0.0, 0.0, 0.0, 1.0};
GLfloat whiteDiffuseLight[] = {1.0, 1.0, 1.0, 1.0};
GLfloat light0Position[] = {0.0, 50.0, 0.0, 1.0};
GLfloat light1Position[] = {50.0, 0.0, 0.0, 1.0};
GLfloat light2Position[] = {0.0, 0.0, 50.0, 1.0};
GLfloat light3Position[] = {25.0, 50.0, 0.0, 1.0};
GLfloat light4Position[] = {0.0, 50.0, 25.0, 1.0};
GLfloat light5Position[] = {25.0, 50.0, 25.0, 1.0};

float scale=1.2;
int lsource=0;
int rotate=0,rx=0,ry=0,rz=0,xct=0,yct=0,zct=0;
unsigned char kee=0;
int lcount=0;
int mesh=0;
class Vertex
{
public:
GLfloat x, y,z;
Vertex (GLfloat a, GLfloat b, GLfloat c) :x(a), y(b),z(c)
{}
};
class Material
{public:
int n;
//string Name;
GLfloat shiny,transparency ;
GLfloat sr,sg,sb, ar,ag,ab, dr,dg,db,er,eg,eb;
Material(int a, GLfloat b,GLfloat c,GLfloat d,GLfloat e,GLfloat f,GLfloat g,GLfloat h,GLfloat i,GLfloat j,GLfloat k,GLfloat l,GLfloat m, GLfloat z, GLfloat o)
{n=a;
shiny=b;
transparency=c;
ar=d; ag=e;ab=f;
dr=g; dg=h;db=i;
sr=j;sg=k;sb=l;
er=m;eg=z;eb=o;
}
};

class Face
{
public:
int facen[3];
int faces[3];
int mat;
Face(int facen1,int facen2, int facen3, int f1, int f2, int f3, int m)
{facen[0]=facen1;
facen[1]=facen2;
facen[2]=facen3;
faces[0]=f1;
faces[1]=f2;
faces[2]=f3;
mat = m;
}

};
vector<Vertex>VX;
vector<Face>FC;
vector<Vertex>VN;
vector<Material>materials;


void setMaterial(int materialId)
{
  GLfloat specular[4];
  GLfloat ambient[4];
  GLfloat diffuse[4];
  GLfloat emmisive[4];
  GLfloat shiny;
  
  // Ugly but works
  

  
  ambient[0] = materials[materialId].ar;
  ambient[1] = materials[materialId].ag;
  ambient[2] = materials[materialId].ab;
  ambient[3] = 1-materials[materialId].transparency;
  //cout<<ambient[0]<<" "<<ambient[1]<<" "<<ambient[2]<<" "<<ambient[3]<<endl;
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
  
  diffuse[0] = materials[materialId].dr;
  diffuse[1] = materials[materialId].dg;
  diffuse[2] = materials[materialId].db;
  diffuse[3] = 1-materials[materialId].transparency;
 //cout<<diffuse[0]<<" "<<diffuse[1]<<" "<<diffuse[2]<<" "<<diffuse[3]<<endl;
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);

  specular[0] = materials[materialId].sr;
  specular[1] = materials[materialId].sg;
  specular[2] = materials[materialId].sb;
  specular[3] = 1-materials[materialId].transparency;
 // cout<<specular[0]<<" "<<specular[1]<<" "<<specular[2]<<" "<<specular[3]<<endl;
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
  
  emmisive[0] = materials[materialId].er;
  emmisive[1] = materials[materialId].eg;
  emmisive[2] = materials[materialId].eb;
  emmisive[3] = 1-materials[materialId].transparency;
  
  glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emmisive);
  
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &materials[materialId].shiny);
}

int Read()
{
ifstream ifs1("jet.mtl");
  if (!ifs1) return 0;
  cout.precision(4);
  int count=0;
  while(ifs1)
    {int n,check=0;
float Ns,Ni,Ka[3],Kd[3],Ks[3],Ke[3];
      string header;
      ifs1 >> header;
      if (header == string("newmtl"))
        {count++;check=1;
          
          ifs1 >> n;
          cout << header << " " << n << endl;
        }
      else if (header == string("Ns"))
        {count++;check=1;
          
          ifs1 >> Ns;
          cout << header << " " << Ns << endl;
        }
      else if (header == string("Tr"))
        {count++;check=1;
          
          ifs1 >> Ni;
          cout << header << " " << Ni << endl;
        
        }
		else if (header == string("Ka"))
        {count++;check=1;
          
          ifs1 >> Ka[0]>>Ka[1]>>Ka[2];
          cout << header << " " << Ka[0]<<" "<<Ka[1]<<" "<<Ka[2]<< endl;
        
        }
		else if (header == string("Kd"))
        {count++;check=1;
          
          ifs1 >> Kd[0]>>Kd[1]>>Kd[2];
          cout << header << " " << Kd[0]<<" "<<Kd[1]<<" "<<Kd[2]<< endl;
        
        }
		else if (header == string("Ks"))
        {count++;check=1;
         
          ifs1>> Ks[0]>>Ks[1]>>Ks[2];
          cout << header << " " << Ks[0]<<" "<<Ks[1]<<" "<<Ks[2]<< endl;
        
        }
		else if (header == string("Ke"))
        {count++;check=1;
        
          ifs1 >> Ke[0]>>Ke[1]>>Ke[2];
          cout << header << " " << Ke[0]<<" "<<Ke[1]<<" "<<Ke[2]<< endl;
        
        }
if(count%7==0 && check==1)		
{materials.push_back(Material(n,Ns,Ni,Ka[0],Ka[1],Ka[2],Kd[0],Kd[1],Kd[2],Ks[0],Ks[1],Ks[2],Ke[0],Ke[1],Ke[2]));
/*cout<<"check"<<endl;
cout << "n" << " " << n << endl;
cout << "ka"<< " " << Ka[0]<<" "<<Ka[1]<<" "<<Ka[2]<< endl;
cout << "kd" << " " << Kd[0]<<" "<<Kd[1]<<" "<<Kd[2]<< endl;
cout << "ks" << " " << Ks[0]<<" "<<Ks[1]<<" "<<Ks[2]<< endl;
cout << "ke" << " " << Ke[0]<<" "<<Ke[1]<<" "<<Ke[2]<< endl;
  */      
}
    }
//return 0;
int mt=0;
ifstream ifs("jet.obj");
  if (!ifs) return 0;
  while(ifs)
    {
      string header;
      ifs >> header;
      if (header == string("mtllib"))
        {
          string mtllib;
          ifs >> mtllib;
          cout << header << " " << mtllib << endl;
        }
      else if (header == string("v"))
        {
          GLfloat v[3];
          ifs >> v[0] >> v[1] >> v[2];
          cout << header << " " << v[0] << " " << v[1] << " " << v[2] << endl;
VX.push_back(Vertex(v[0],v[1],v[2]));        
}
		
      else if (header == string("vn"))
        {
          GLfloat vn[3];
          ifs >> vn[0] >> vn[1] >> vn[2];
          cout << header << " " << vn[0] << " " << vn[1] << " " << vn[2] << endl;
VN.push_back(Vertex(vn[0],vn[1],vn[2]));        
}
		else if (header == string("usemtl"))
		{ifs>>mt;
		cout<<mt<<endl;
		}
		else if (header == string("f"))
		{
			int f[7];
char a;
			ifs >> f[0] >> a>>f[1] >>a>> f[2]>>f[3]>>a>>f[1]>>a>>f[5]>>f[4]>>a>>f[1]>>a>>f[6];
			cout << header << " " << f[0] << "/"<< f[1] << "/" << f[2] <<"  "<<f[3]<<"/"<<f[1]<<"/"<<f[5]<<" "<<f[4]<<"/"<<f[1]<<"/"<<f[6]<< "/"<<mt<<endl;
FC.push_back(Face(f[2],f[5],f[6],f[0],f[3],f[4],mt));

	}
}

		int num;
		num=glGenLists(1);
		glNewList(num,GL_COMPILE);
int last=-1;
		
		
		for(int i=0;i<FC.size();i++)
		{
		{
		setMaterial(FC[i].mat);
		}
		
		glBegin(GL_TRIANGLES);
		
		glNormal3f(VN[FC[i].facen[0]-1].x,VN[FC[i].facen[0]-1].y,VN[FC[i].facen[0]-1].z);
		glVertex3f(VX[FC[i].faces[0]-1].x,VX[FC[i].faces[0]-1].y,VX[FC[i].faces[0]-1].z);
		glNormal3f(VN[FC[i].facen[1]-1].x,VN[FC[i].facen[1]-1].y,VN[FC[i].facen[1]-1].z);
		glVertex3f(VX[FC[i].faces[1]-1].x,VX[FC[i].faces[1]-1].y,VX[FC[i].faces[1]-1].z);
		glNormal3f(VN[FC[i].facen[2]-1].x,VN[FC[i].facen[2]-1].y,VN[FC[i].facen[2]-1].z);	
		glVertex3f(VX[FC[i].faces[2]-1].x,VX[FC[i].faces[2]-1].y,VX[FC[i].faces[2]-1].z);
		
		glEnd();
		}

		glEndList();

		return num;
		
}



int jetp;
void init(void)
{


 glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	 glEnable(GL_LIGHTING);
	
        glEnable(GL_DEPTH_TEST);
	
        jetp=Read(); 
}


void display(void)
{static int pass;
  static GLfloat rotX = 0.0;
  static GLfloat rotY = 0.0;
  static GLfloat rotZ = 0.0;
cout << "Displaying pass " << ++pass << endl;
glClearColor(1.0,1.0,1.0,1.0);
glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
	glLightfv(GL_LIGHT0, GL_SPECULAR, whiteSpecularLight);
        glLightfv(GL_LIGHT0, GL_AMBIENT, blackAmbientLight);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteDiffuseLight);
        glLightfv(GL_LIGHT0, GL_POSITION, light0Position);

	glLightfv(GL_LIGHT1, GL_SPECULAR, whiteSpecularLight);
        glLightfv(GL_LIGHT1, GL_AMBIENT, blackAmbientLight);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, whiteDiffuseLight);
        glLightfv(GL_LIGHT1, GL_POSITION, light1Position);

	glLightfv(GL_LIGHT2, GL_SPECULAR, whiteSpecularLight);
        glLightfv(GL_LIGHT2, GL_AMBIENT, blackAmbientLight);
        glLightfv(GL_LIGHT2, GL_DIFFUSE, whiteDiffuseLight);
        glLightfv(GL_LIGHT2, GL_POSITION, light2Position);

	glLightfv(GL_LIGHT3, GL_SPECULAR, whiteSpecularLight);
        glLightfv(GL_LIGHT3, GL_AMBIENT, blackAmbientLight);
        glLightfv(GL_LIGHT3, GL_DIFFUSE, whiteDiffuseLight);
        glLightfv(GL_LIGHT3, GL_POSITION, light3Position);

	glLightfv(GL_LIGHT4, GL_SPECULAR, whiteSpecularLight);
        glLightfv(GL_LIGHT4, GL_AMBIENT, blackAmbientLight);
        glLightfv(GL_LIGHT4, GL_DIFFUSE, whiteDiffuseLight);
        glLightfv(GL_LIGHT4, GL_POSITION, light4Position);

	glLightfv(GL_LIGHT5, GL_SPECULAR, whiteSpecularLight);
        glLightfv(GL_LIGHT5, GL_AMBIENT, blackAmbientLight);
        glLightfv(GL_LIGHT5, GL_DIFFUSE, whiteDiffuseLight);
        glLightfv(GL_LIGHT5, GL_POSITION, light5Position);
	if(lsource==0)
{glDisable(GL_LIGHT0);glDisable(GL_LIGHT1);glDisable(GL_LIGHT2);glDisable(GL_LIGHT3);glDisable(GL_LIGHT4);glDisable(GL_LIGHT5);}
	if(lsource==1)
 	 {glEnable(GL_LIGHT0);glDisable(GL_LIGHT1);glDisable(GL_LIGHT2);glDisable(GL_LIGHT3);glDisable(GL_LIGHT4);glDisable(GL_LIGHT5);}
	if(lsource==2)
 	 {glEnable(GL_LIGHT0);glEnable(GL_LIGHT1);glDisable(GL_LIGHT2);glDisable(GL_LIGHT3);glDisable(GL_LIGHT4);glDisable(GL_LIGHT5);}
	if(lsource==3)
 	 {glEnable(GL_LIGHT0);glEnable(GL_LIGHT1);glEnable(GL_LIGHT2);glDisable(GL_LIGHT3);glDisable(GL_LIGHT4);glDisable(GL_LIGHT5);}
	if(lsource==4)
      {glEnable(GL_LIGHT0);glEnable(GL_LIGHT1);glEnable(GL_LIGHT2);glEnable(GL_LIGHT3);glDisable(GL_LIGHT4);glDisable(GL_LIGHT5);}
if(lsource==5)
      {glEnable(GL_LIGHT0);glEnable(GL_LIGHT1);glEnable(GL_LIGHT2);glEnable(GL_LIGHT3);glEnable(GL_LIGHT4);glDisable(GL_LIGHT5);}
if(lsource==6)
      {glEnable(GL_LIGHT0);glEnable(GL_LIGHT1);glEnable(GL_LIGHT2);glEnable(GL_LIGHT3);glEnable(GL_LIGHT4);glEnable(GL_LIGHT5);}
	gluLookAt(0, 15.0, -25.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glScalef(scale, scale, scale);
glRotatef(rotX, 1.0, 0.0, 0.0); glRotatef(rotY, 0.0, 1.0, 0.0);glRotatef(rotZ, 0.0, 0.0, 1.0);
/*if(rx==1 && rotate!=0)
 {rotX += 1.0;}
if(ry==1 && rotate!=0)
  {rotY += 1.0;}
if(rz==1 && rotate!=0)
  {rotZ += 1.0;}
 */ 
if(rx==1 )
 {rotX += 1.0;}
if(ry==1)
  {rotY += 1.0;}
if(rz==1)
  {rotZ += 1.0;}
  //rotY -= 1.0;
	glCallList(jetp);
	glutSwapBuffers();
}
void keyboard (unsigned char key, int x, int y) 
{//static int rx=0,ry=0,rz=0,xct=0,yct=0,zct=0;
if(key=='S' )
{scale+=(.01*scale);cout<<scale;}
else if (key=='s'  )
{scale=scale-(.01*scale);
if(scale<0.5)
{scale=0.5;}}
if(key=='x'||key=='y'||key=='z' || key=='X' || key== 'Y' || key == 'Z')
{
/*{if(kee==key && lcount==0) {rotate=0;lcount=1;}
else if(lcount==1 && key==kee){rotate=1;lcount=0;}
if(key!=kee ) {rotate=1;lcount=0;}*/
/*rx=0;ry=0;rz=0;
if(key=='x')
rx=1;
if(key=='y')
ry=1;
if(key=='z')
rz=1;

kee=key;*/
if(key=='x' || key=='X')
{	
	if(xct==0)	
	{rx=1;xct++;
	}
	else
	{rx=0;xct--;
	}
}
if(key=='y' || key == 'Y')
{	
	if(yct==0)	
	{ry=1;yct++;
	}
	else
	{ry=0;yct--;
	}
}
if(key=='z' || key == 'Z')
{	
	if(zct==0)	
	{rz=1;zct++;
	}
	else
	{rz=0;zct--;
	}
}
}

if(key=='L' && lsource<6)
{lsource++;}
if(key=='l' && lsource>0)
{lsource--;}
if(key=='q')
exit(0); 
}

void timer(int)
{
  // Adjust rotation angles as needed here
  // Then tell glut to redisplay
  glutPostRedisplay();
  // And reset tht timer
  glutTimerFunc(1000.0 / updateRate, timer, 0);
}

void reshape(int w, int h)
{
  
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    gluPerspective(60, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}
int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Jet Display");
    init();
    glutDisplayFunc(display);
    //glutIdleFunc(display);
    //mesh=0;
    glutKeyboardFunc (keyboard);
    glutReshapeFunc(reshape);
    
    // Compute the update rate here...
    glutTimerFunc(1000.0 / updateRate, timer, 0);
    glutMainLoop();
    return 0;
}



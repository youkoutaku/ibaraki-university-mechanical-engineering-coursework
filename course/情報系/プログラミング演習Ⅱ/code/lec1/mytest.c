#include <GL/freeglut.h>


void drawString2D( double x, double y, char *str )
{
  glRasterPos2d( x, y );  

  while( *str != '\0' ) {  
		
    glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, *str ); 
    str++;  
  }
}

void display(void) {  
 
    glClearColor( 0, 0, 0, 1 );  		
    glClear( GL_COLOR_BUFFER_BIT );	
		drawString2D(-0.7,  0.0, "Mechanical Systems Engineering" ); 
		drawString2D(-0.7, -0.1, "Programming Excercises II" );

    glFlush(); 					
 
}

int main( int argc, char *argv[] ) {  

    glutInit(&argc, argv);					
    glutInitDisplayMode(GLUT_RGBA);   
    glutInitWindowSize(500,500);     
    glutInitWindowPosition(100,100);  
    glutCreateWindow(argv[0]); 			

    glutDisplayFunc(display);       
    
    glutMainLoop(); 								

    return 0;
}
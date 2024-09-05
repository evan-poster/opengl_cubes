#include <GL/freeglut.h>
#include <iostream>
#include <string>

using namespace std;

// Colors
float black[3] = {0.0f, 0.0f, 0.0f};
float white[3] = {1.0f, 1.0f, 1.0f};
// Cube face colors
float colors[6][3] = {
	{1.0f, 0.0f, 0.0f}, // red
	{0.0f, 1.0f, 0.0f}, // green
	{0.0f, 0.0f, 1.0f},	// blue
	{1.0f, 1.0f, 0.0f},	// yellow
	{1.0f, 0.0f, 1.0f},	// magenta
	{0.0f, 1.0f, 1.0f}	// cyan
};
string color_names[] = {"Red", "Green", "Blue", "Yellow", "Magenta", "Cyan"};

int window_width = 1280;
int window_height = 720;
float clear_color[3] = {1.0f, 1.0f, 1.0f};

float initial_camera_position[3] = {0.0f, 0.0f, 5.0f};
float camera_position[3] = {0.0f, 0.0f, 5.0f};
float camera_speed = 0.5f;

int array_width = 1;
int array_height = 1;
int array_depth = 1;

float cube_size = 1.0f;
int face_color = 0;
bool show_faces = true;

void print_array_info() {
	cout    << "Array width: "		<< array_width
			<< ", Array height: "	<< array_height
			<< ", Array depth: "	<< array_depth << endl;
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	// Apply camera translation
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camera_position[0], camera_position[1], camera_position[2], camera_position[0], camera_position[1], camera_position[2] - 5.0f, 0.0, 1.0, 0.0);

	// Draw cube array
	for (int i = 0; i < array_height; i++) {
		for (int j = 0; j < array_width; j++) {
			for (int k = 0; k < array_depth; k++) {
				glPushMatrix();
				glTranslatef(j * cube_size * 1.5, i * cube_size * 1.5, -k * cube_size * 1.5 - 5.0f);

				// Draw cube with solid faces
				if (show_faces) {
					glColor3f(colors[face_color][0], colors[face_color][1], colors[face_color][2]);
					glutSolidCube(1.0f);
				}

				// Draw cube with edges on top of the solid faces
				glColor3f(black[0], black[1], black[2]);
				glTranslatef(0.0f, 0.0f, 0.01f);
				glutWireCube(1.0f);

				glPopMatrix();
			}
		}
	}

	glutSwapBuffers();
}

void reshape(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)width / (GLfloat)height, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
		case 'q':
		case 'Q':
			exit(0);
			break;

		// Toggle face visibility
		case 'e':
			show_faces = !show_faces;
			// cout if the faces are visible or not
			if (show_faces) {
				cout << "Toggle Faces: Visible." << endl;
			} else {
				cout << "Toggle Faces: Hidden." << endl;
			}
			break;

		// Toggle face color; loop from last to first color
		case 'c':
			face_color++;
			if (face_color > 5) {
				face_color = 0;
			}
			cout << "Toggle Face Color: " << color_names[face_color] << endl;
			break;

		// Camera Controls
		case ' ':
			camera_position[0] = initial_camera_position[0];
			camera_position[1] = initial_camera_position[1];
			camera_position[2] = initial_camera_position[2];
			cout << "Camera position reset." << endl;
			break;
		case 'w':
			camera_position[2] += camera_speed;
			break;
		case 'a':
			camera_position[0] -= camera_speed;
			break;
		case 's':
			camera_position[2] -= camera_speed;
			break;
		case 'd':
			camera_position[0] += camera_speed;
			break;
		case 'r':
			camera_position[1] += camera_speed;
			break;
		case 'f':
			camera_position[1] -= camera_speed;
			break;

		// Cube Controls
		case 'x':
			array_width++;
			glutPostRedisplay();
			print_array_info();
			break;
		case 'X':
			array_width--;
			glutPostRedisplay();
			print_array_info();
			break;
		case 'y':
			array_height++;
			glutPostRedisplay();
			print_array_info();
			break;
		case 'Y':
			array_height--;
			glutPostRedisplay();
			print_array_info();
			break;
		case 'z':
			array_depth++;
			glutPostRedisplay();
			print_array_info();
			break;
		case 'Z':
			array_depth--;
			glutPostRedisplay();
			print_array_info();
			break;
		// Add more cases for different keyboard keys
		default:
			break;
	}
	// Prevent zero cubes from displaying
	if (array_width < 1) {
		array_width = 1;
	}
	if (array_height < 1) {
		array_height = 1;
	}
	if (array_depth < 1) {
		array_depth = 1;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(window_width, window_height);
	glutCreateWindow("Cube Array");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);

	glEnable(GL_DEPTH_TEST);
	glClearColor(clear_color[0], clear_color[1], clear_color[2], 1.0f);

	glutMainLoop();

	return 0;
}

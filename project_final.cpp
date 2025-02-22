#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>

#define PNG_SETJMP_NOT_SUPPORTED
#include <png.h>

using namespace std;

#define WIDTH 256
#define HEIGHT 256
#define COLOR_DEPTH 8

struct Pixel {
	png_byte r, g, b, a;
};

int main(int argc, char *argv[]) {
	srand(time(NULL));

	/* open PNG file for writing */
	FILE *f = fopen("out.png", "wb");
	if (!f) {
		fprintf(stderr, "could not open out.png\n");
		return 1;
	}

	/* initialize png data structures */
	png_structp png_ptr;
	png_infop info_ptr;

	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png_ptr) {
		fprintf(stderr, "could not initialize png struct\n");
		return 1;
	}

	info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr) {
		png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
		fclose(f);
		return 1;
	}

	/* begin writing PNG File */
	png_init_io(png_ptr, f);
	png_set_IHDR(png_ptr, info_ptr, WIDTH, HEIGHT, COLOR_DEPTH,
	             PNG_COLOR_TYPE_RGB_ALPHA, PNG_INTERLACE_NONE,
	             PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
	png_write_info(png_ptr, info_ptr);

	/* allocate image data */
	struct Pixel *row_pointers[HEIGHT];
	for (int row = 0; row < HEIGHT; row++) {
		row_pointers[row] = (Pixel *)calloc(WIDTH*2, sizeof(struct Pixel));
	}

	/* draw shape based on input */

	char x;
	int y,z;
	int r, g, b;
	
	cout << "r for rectangle, t for triangle, and c for circle: " ;
	cin >> x;

	if (x == 't'){
		cout << "width(1~256): ";
		cin >> y;
		if (y < 0 || y > 256){
			cout << "error: out of value"<< endl;
			return 0;
		}
		cout << "height(1~256): ";
		cin >> z;
		if (z < 0 || z > 256){
			cout << "error: out of value"<< endl;
			return 0;
		}
		cout << "rgb data(0~255): ";
		cin >> r >> g >> b;
		if (r < 0 || r > 255){
			cout << "error: out of value"<< endl;
			return 0;
		}
		if (g < 0 || g > 255){
			cout << "error: out of value"<< endl;
			return 0;
		}
		if (b < 0 || b > 255){
			cout << "error: out of value"<< endl;
			return 0;
		}


		for (int col = 0; col < WIDTH; col++) {
				for (int row = 0; row < HEIGHT; row++) {

					if (row >= (2*z/y)*(col-128)+128-(z/2) && row >= -(2*z/y)*(col-128)+128-(z/2) && row <= 128 + (z/2)){
					
					row_pointers[row][col].r = r; // red
					row_pointers[row][col].g = g; // green
					row_pointers[row][col].b = b; // blue
					row_pointers[row][col].a = 255; // opacity
						
					}
				}


	}
	} else if (x == 'r'){
		cout << "width(1~256): ";
		cin >> y;
		if (y < 0 || y > 256){
			cout << "error: out of value"<< endl;
			return 0;
		}
		cout << "height(1~256): ";
		cin >> z;
		if (z < 0 || z > 256){
			cout << "error: out of value"<< endl;
			return 0;
		}
		cout << "rgb data(0~255): ";
		cin >> r >> g >> b;
		if (r < 0 || r > 255){
			cout << "error: out of value"<< endl;
			return 0;
		}
		if (g < 0 || g > 255){
			cout << "error: out of value"<< endl;
			return 0;
		}
		if (b < 0 || b > 255){
			cout << "error: out of value"<< endl;
			return 0;
		}

		for (int col = 0; col < WIDTH; col++) {
				for (int row = 0; row < HEIGHT; row++) {

					if (col <= 128+(y/2) && 128-(y/2) <= col && row <= 128 + (z/2) && 128 - (z/2) <= row){
					
					row_pointers[row][col].r = r; // red
					row_pointers[row][col].g = g; // green
					row_pointers[row][col].b = b; // blue
					row_pointers[row][col].a = 255; // opacity
						
					}
				}


	}
	} else if (x == 'c'){
		cout << "radius of the circle(0~128): ";
		cin >> y;
		if (y < 0 || y > 128){
			cout << "error: out of value"<< endl;
			return 0;
		}
		cout << "rgb data(0~255): ";
		cin >> r >> g >> b;
		if (r < 0 || r > 255){
			cout << "error: out of value"<< endl;
			return 0;
		}
		if (g < 0 || g > 255){
			cout << "error: out of value"<< endl;
			return 0;
		}
		if (b < 0 || b > 255){
			cout << "error: out of value"<< endl;
			return 0;
		}

		for (int col = 0; col < WIDTH; col++) {
				for (int row = 0; row < HEIGHT; row++) {

					if (pow(col-128,2)+pow(row-128,2) <= pow(y,2)){
					
					row_pointers[row][col].r = r; // red
					row_pointers[row][col].g = g; // green
					row_pointers[row][col].b = b; // blue
					row_pointers[row][col].a = 255; // opacity
					
					}
					
				}

	}
	} else {
		cout << "wrong input. try again" << endl;
	}


	

	



	
	

	/* write image data to disk */
	png_write_image(png_ptr, (png_byte **)row_pointers);

	/* finish writing PNG file */
	png_write_end(png_ptr, NULL);

	/* clean up PNG-related data structures */
	png_destroy_write_struct(&png_ptr, &info_ptr);

	/* close the file */
	fclose(f);
	f = NULL;

	return 0;
}

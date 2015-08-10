/*
	XShoot: Simple command line XServer screen capture tool. 
	
    Copyright (C) 2015  Alberto Sola Comino

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
	
	
	Caracteristics:
	=======================
	
		- Save image as PPM.
		- Supports multi-monitor. ( Capture both screens )

	Dependencies:
	=======================
	
		libx11-dev

	Usage:
	========================
	
		./xshoot
		
		Saves the image as img_capture.ppm where the app
		is called.

*/

#include <iostream>
#include <fstream>

#include <cstdlib> // exit()

#include <X11/Xlib.h>
#include <X11/Xutil.h> // XGetPixel


typedef unsigned long PIXEL_COLOR;

////////////////////////////
//
//		Main Program
//
////////////////////////////

int main(){

	// Open 'display'.
	Display * display = XOpenDisplay(0);

	// Check for errors
	if( !display ){

		std::cout << "No se pudo abrir 'display'." << std::endl;
		exit(1);

	}

	// Screen
	const int screen = XDefaultScreen(display);

	// Size
	const int width = DisplayWidth(display, screen);
  	const int height = DisplayHeight(display, screen);

   	const Window window = RootWindow(display, screen);

	// Window attributes
	XWindowAttributes window_attr;

	//  Check for errors
	if (!XGetWindowAttributes(display, window, &window_attr)) {
		
		std::cout << "No se pudieron obtener los atributos de la ventana." << std::endl;
		
		XCloseDisplay(display);
		exit(1);
	}

   // Colour mask
	PIXEL_COLOR red_mask = window_attr.visual -> red_mask;
	PIXEL_COLOR green_mask = window_attr.visual -> green_mask;
	PIXEL_COLOR blue_mask = window_attr.visual -> blue_mask;

	// Image capture.
	XImage * screen_capture;

	screen_capture = XGetImage( display, window, 0, 0,
						  				 width, height, AllPlanes, ZPixmap );
	
	//  Check for errors
	if( !screen_capture ){

		std::cout << "No se pudo obtener la imagen." << std::endl;

		XCloseDisplay(display);
		exit(1);
	}

	// Output file
	std::ofstream img_capture;
	img_capture.open("img_capture.ppm");

	if( img_capture.fail() ){

		std::cout << "No se pudo abrir el fichero de salida." << std::endl;

		XCloseDisplay(display);
		XDestroyImage( screen_capture );
		img_capture.close();
		exit(1);
	}

	//////////////////
	//
	//		PPM
	//
	//////////////////

	// HEADER
	img_capture << "P6" << std::endl;
	img_capture << width << " " << height << std::endl;
	img_capture << "255" << std::endl;

	// Pixel
	PIXEL_COLOR pixel;

	// rows
	for( int y = 0; y < height; y++ ){
		
		// columns
		for( int x = 0; x < width; x++ ){

			// Get every pixel (x, y)
			pixel = XGetPixel( screen_capture, x, y );
			
			/*			
				Conversion: DEC -> RGB

				Apply mask to every colour.

				Shift the bits.

				Convert every color to unsigned char and
				write it to the file.
			*/
			img_capture << ( unsigned char ) ( (pixel & red_mask) >> 16 );
			img_capture << ( unsigned char ) ( (pixel & green_mask) >> 8 );
			img_capture << ( unsigned char ) ( (pixel & blue_mask) );

		}

	}

	// Close file
	img_capture.close();

	// Free memory
	XDestroyImage( screen_capture );
   XCloseDisplay( display );

}

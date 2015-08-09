/*
	Screnshot

	Simple programa para capturar la pantalla.

	- Guarda la imagen en formato ".ppm".
	- Soporta múltiples monitores.

	Compilación:

	Uso:

	Alberto Sola - 2015

*/

#include <iostream>
#include <fstream>

#include <cstdlib> // exit()

#include <X11/Xlib.h>
#include <X11/Xutil.h> // XGetPixel

#include "Vector/Vector.hpp"


typedef unsigned long PIXEL_COLOR;

////////////////////////////
//
//		Programa Principal
//
////////////////////////////

int main(){

	// Nos conectamos al 'display'.
	Display * display = XOpenDisplay(0);

	// Comprobamos si se ha realizado con éxito.
	if( !display ){

		std::cout << "No se pudo abrir 'display'." << std::endl;
		exit(1);

	}

	// Pantalla.
	const int screen = XDefaultScreen(display);

	// Dimensiones.
	const int width = DisplayWidth(display, screen);
   const int height = DisplayHeight(display, screen);

   const Window window = RootWindow(display, screen);

	// Atributos de la ventana.
	XWindowAttributes window_attr;

	// Comprobamos quue se haya realizado con éxito.
	if (!XGetWindowAttributes(display, window, &window_attr)) {
		
		std::cout << "No se pudieron obtener los atributos de la ventana." << std::endl;
		
		XCloseDisplay(display);
		exit(1);
	}

   // Máscaras
	PIXEL_COLOR red_mask = window_attr.visual -> red_mask;
	PIXEL_COLOR green_mask = window_attr.visual -> green_mask;
	PIXEL_COLOR blue_mask = window_attr.visual -> blue_mask;

	// Image capture.
	XImage * screen_capture;

	screen_capture = XGetImage( display, window, 0, 0,
						  				 width, height, AllPlanes, ZPixmap );
	
	// Comprobamos quue se haya realizado con éxito.
	if( !screen_capture ){

		std::cout << "No se pudo obtener la imagen." << std::endl;

		XCloseDisplay(display);
		exit(1);
	}

	// Archivo de salida
	std::ofstream img_capture;
	img_capture.open("img_capture.ppm");

	if( img_capture.fail() ){

		std::cout << "No se pudo abrir el fichero de salida." << std::endl;

		XCloseDisplay(display);
		XDestroyImage( screen_capture );
		img_capture.close();
		exit(1);
	}

	// HEADER
	img_capture << "P6" << std::endl;
	img_capture << width << " " << height << std::endl;
	img_capture << "255" << std::endl;

	// Pixel
	PIXEL_COLOR pixel;

	// Recorremos las filas
	for( int y = 0; y < height; y++ ){
		
		// Recorremos cada columna
		for( int x = 0; x < width; x++ ){

			// Obtenemos cada píxel
			pixel = XGetPixel( screen_capture, x, y );
			
			/*
				Conversión DEC -> RGB

				Utilizamos las máscaras para quedarnos con el byte
				que nos interesa.

				Filtramos con 'shift operator'.

				Convertimos en un caracter para que al escribirlo
				en el fichero aparezca como un caracter.
			*/
			img_capture << ( unsigned char ) ( (pixel & red_mask) >> 16 );
			img_capture << ( unsigned char ) ( (pixel & green_mask) >> 8 );
			img_capture << ( unsigned char ) ( (pixel & blue_mask) );

		}

	}

	// Cerramos el fichero.
	img_capture.close();

	// Liberamos la memoria.
	XDestroyImage( screen_capture );
   XCloseDisplay( display );

}
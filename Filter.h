#ifndef FILTER_H
#define FILTER_H

#include <cmath>
#include <iostream>
#include "FL/gl.h"

template<typename dataType>
class Filter
{
public:
	Filter(dataType* mat, int wid, int hei) {
		width = wid;
		height = hei;
		matrix = new dataType [wid*hei];
		for(int i=0;i<wid*hei;i++){
				matrix[i] = mat[i];
		}
	}
	~Filter() {
		if (matrix != NULL) {
			delete[] matrix;
		}
	}
	double conv2(const GLubyte* source, int sourceWid, int sourceHei, int x, int y) {
		double result = 0;
		int newX = x - width/2;
		int newY = y - height/2;
		for (int i=0;i<width;i++){
			for(int j=0;j<height;j++){
				int corX=newX+i;
				if (corX<0)
					corX = abs(corX);
				else if (corX>= sourceWid)
					corX = 2 * sourceWid  - corX - 1;
				int corY=newY+j;
				if (corY<0)
					corY = abs(corY);
				else if (corY>= sourceHei)
					corY = 2 * sourceHei - corY - 1;
				result += (double)(matrix[i*height+j] )*
					(double)(source[corX+sourceWid * corY]);//not sured
				
			}
		}
		//printf("%f ", result);
		if (result > 255)
			result = 255;
		if (result < 0)
			result = 0;
		return result;
	}
	void printFilter() {
		for (int i = 0; i<width; i++) {
			for (int j = 0; j<height; j++) {
				printf("%f ", matrix[j*width + i]);

			}
			printf("\n");
		}
		printf("done\n");
	}
private:
	int width;
	int height;
	dataType* matrix; // the source type is one dimen
};

#endif

#include "image.h"
#include "pngwriter.h"
using namespace std;
using namespace Eigen;

Image::Image(string filename) {
	pngwriter writer(1,1,0,"");
	writer.readfromfile(filename.c_str());
	
	w = writer.getwidth();
	h = writer.getheight();
	
	image.resize(h);
	
	for (int i = 0; i < h; i++) {
		image[i].resize(w);
		for (int j = 0; j < w; j++)
		for (int k = 0; k < 3; k++) 
			image[i][j][k] = writer.read(j,i,k+1)/65535.;
	}
}

Image::Image(int width, int height) : w(width), h(height) {
	image.resize(h);
	for (int i = 0; i < h; i++)
		image[i].resize(w);
}

void Image::write(string filename) {
	pngwriter writer(w,h,0,filename.c_str());
	
	for (int i = 0; i < h; i++)
	for (int j = 0; j < w; j++)
		writer.plot(j,i,image[i][j][0],image[i][j][1],image[i][j][2]);
		
	writer.close();
}

ImageCol Image::getCol(int j) {
	return ImageCol(j,*this);
}

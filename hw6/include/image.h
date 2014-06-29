#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include <string>
#include <Eigen/Dense>

typedef std::vector<Eigen::Vector3d> ImageRow;
class ImageCol;

class Image {
public:
	Image(std::string filename);
	Image(int width, int height);
	
	void write(std::string filename);
	ImageRow &getRow(int i) { return image[i]; }
	ImageRow &operator[](int i) { return image[i]; }
	
	ImageCol getCol(int j);
	int width() { return w; }
	int height() { return h; }
private:
	std::vector<std::vector<Eigen::Vector3d> > image;
	int w, h;
};

class ImageCol {
public:
	ImageCol(int c, Image &image) : j(c), im(image) {}
	Eigen::Vector3d &operator[](int i) { return im[i][j]; }
	int size() { return im.height(); }
private:
	int j;
	Image &im;
};

#endif

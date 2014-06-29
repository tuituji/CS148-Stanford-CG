#include <iostream>
#include "Image.h"
#include "Scene.h"
#include "Sphere.h"
using namespace std;
using namespace Raytracer148;
using namespace Eigen;

int main() {
    Image im(400,400);
    
    Scene scene;
    
    Vector3d center;
    center[0] = 0;
    center[1] = 0;
    center[2] = 4;
    scene.addShape(new Sphere(center,2));
    
    center[0] = -.5;
    center[1] = 1;
    center[2] = 2.5;
    scene.addShape(new Sphere(center,.5));
    
    center[0] = .5;
    center[1] = 1.25;
    center[2] = 2.75;
    scene.addShape(new Sphere(center,.5));
    
    scene.render(im);
       
    im.writePNG("test.png");

    return 0;
}

#ifndef PLOT_H
#define PLOT_H

#include "graph.h"
#include "node.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <list>

class plot_nodes{
public: 
cv::Size PlotSize;
int unitSize;
const Graph * graph;
cv::Mat *canvas;
plot_nodes(const Graph *gs,int unitSize_ );
~plot_nodes();
double scale=1;

void draw_nodes();
void draw_path(std::list<Node*> path);
void puttext(std::string,cv::Point2i,int face=cv::FONT_HERSHEY_DUPLEX,double scale=1,double thickness=1.5,cv::Scalar color=cv::Scalar(0));

};




#endif
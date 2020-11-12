#include "graph.h"
#include "node.h"
#include "plot_nodes.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core.hpp>
#include <sstream>
#include <iomanip>


plot_nodes::plot_nodes(const Graph *g,int unitSize_):graph(g),unitSize(unitSize_)
{
    //dsfd
    auto width=std::max_element(g->nodes.begin(),g->nodes.end(),[](const auto &n1, const auto &n2){return n1.coordinates.x<n2.coordinates.x;})->coordinates.x;
    auto height=std::max_element(g->nodes.begin(),g->nodes.end(),[](const auto &n1, const auto &n2){return n1.coordinates.y<n2.coordinates.y;})->coordinates.y;    
    PlotSize=cv::Size(width*unitSize+unitSize,height*unitSize+unitSize);
    canvas=new cv::Mat(PlotSize,CV_8UC3,cv::Scalar(255,255,255));
}
plot_nodes::~plot_nodes(){
    delete canvas;
}

void plot_nodes::draw_nodes(){
    std::stringstream ss;
    ss<<std::setprecision(2);
    for(auto &node: graph->nodes){
        auto center=cv::Point(node.coordinates.x*unitSize,node.coordinates.y*unitSize);
        for(auto nghb:node.edges)
        {
            auto nghb_center=cv::Point(nghb.first->coordinates.x*unitSize,nghb.first->coordinates.y*unitSize);
            cv::line(*canvas,center,nghb_center,cv::Scalar(100,100,100),1);
            auto TEXT = std::to_string(static_cast<int>(nghb.second));
            auto text_pos=center+(nghb_center-center)/3*scale;//-cv::Point2i(text_size.width/2,-text_size.height/2);
            puttext(TEXT,text_pos);
            //cv::circle(*canvas,text_pos,10,cv::Scalar(255,255,255),-1);    
        }  
    }
     int radius=40*scale;
    for(auto &node: graph->nodes){
        
       
        auto center=cv::Point(node.coordinates.x*unitSize,node.coordinates.y*unitSize);
        cv::circle(*canvas,center,radius,cv::Scalar(200,200,200),-1);
        cv::circle(*canvas,center,radius,cv::Scalar(0,150,0),3);

       
        auto text_pos=center+cv::Point2i(0,-radius*0.7);
        puttext(node.name,text_pos,2,0.8*scale,1.5*scale,cv::Scalar(0,150,0));
        ss<<"h:"<<node.distance;
        text_pos=center+cv::Point2i(0,-radius*0.3);
        puttext(ss.str(),text_pos,2,0.5*scale,1*scale,cv::Scalar(0,0,200));
        ss.str(std::string());
        ss.clear();

        ss<<"g:"<<node.g;
        text_pos=center+cv::Point2i(0,-radius*0);
        puttext(ss.str(),text_pos,2,0.5*scale,1*scale,cv::Scalar(0,0,0));
        ss.str(std::string());
        ss.clear();

    }
    auto center=cv::Point(graph->startNode->coordinates.x*unitSize,graph->startNode->coordinates.y*unitSize);
    cv::circle(*canvas,center,radius,cv::Scalar(255,0,0),4*scale);

    center=cv::Point(graph->endNode->coordinates.x*unitSize,graph->endNode->coordinates.y*unitSize);
    cv::circle(*canvas,center,radius,cv::Scalar(0,0,255),4*scale);

    cv::imshow("okno",*canvas);
   
    cv::waitKey(0);
}

void plot_nodes::draw_path(std::list<Node*> path){

    auto prevNode=path.front();

    for (std::list<Node*>::const_iterator it = ++path.begin(); it != path.end(); ++it){
        auto center1=cv::Point(prevNode->coordinates.x*unitSize,prevNode->coordinates.y*unitSize);
        auto center2=cv::Point((*it)->coordinates.x*unitSize,(*it)->coordinates.y*unitSize);
        prevNode=(*it);
        
        cv::line(*canvas,center1,center2,cv::Scalar(255,0,255),5);
    
    }
}

void plot_nodes::puttext(std::string text,cv::Point2i center,int face,double scale,double thickness,cv::Scalar color){
    int baseline;
  
    auto text_size=cv::getTextSize(text, face, scale, thickness,&baseline);
    auto text_pos=center-cv::Point2i(text_size.width/2,-text_size.height/2);
    cv::putText(*canvas,text,text_pos,face,scale,color,thickness,cv::LINE_AA);
    
}


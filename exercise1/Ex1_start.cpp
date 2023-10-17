// TU Dresden, Inf, CV1 Ex1, Holger Heidrich
// Aufg 1, non-linear grey value transformation, solarization
// --
// This program plays with colors simulating solarization.	
// Clicking two times into the "GreyCurve"-image gives two points.
// Make these points be the extremals of a polynomial of degree three in the range 0..255 x 0..255.\n"
// The "GreyCurve"-image itself has size (512,512). Point (0,0) is upper left corner. \n"
// Use the polynomial y(x) to map values x of the input image to values y of an output image by creating and using a lookup table.\n"
// Saturate to 0 and 255 if the mapped grey / color values exceed these values. \n"
//-----------------------------------------------------------------------------
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/videoio/videoio.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <functional>
#include <queue>

#define MaxPoints 2
int nb_points=0;
double LUT[512];

cv::Mat MapCurveimage512;
cv::Mat image, mapped_result_img;
cv::Point    SrcPtInt[MaxPoints];

void help()
{
	std::cout <<
	"\nTU Dresden, Inf, CV1 Ex1, Holger Heidrich\n"
	"This program plays with colors simulating solarization.\n"
	"Clicking two times into the \"GreyCurve\"-image gives two points.\n"
	"Make these points be the extremals of a polynomial of degree three in the range 0..255 x 0..255.\n"
	"The \"GreyCurve\"-image itself has size (512,512). Point (0,0) is upper left corner. \n"
	"Use the polynomial y(x) to map values x of the input image to values y of an output image.\n"
	"Saturate to 0 and 255 if the mapped grey / color values exceed these values. \n"
	"Call:\n"
	"./image Image [image-name Default: fruits.jpg]\n" << std::endl;
}

void on_mouse( int event, int x, int y, int flags, void* param )
{
    switch( event )
    {
        case cv::EVENT_LBUTTONDOWN:
        {
            // ad new point to polygon
            if (nb_points < MaxPoints) 
            {  
               SrcPtInt[nb_points].x=x;
               SrcPtInt[nb_points].y=y;
               if (nb_points)
               {   // second point in SrcPtInt
				   
                  MapCurveimage512 = 0;

                  // read the two extrema points
                  int x1 = SrcPtInt[0].x;	
				      int x2 = SrcPtInt[1].x;	
                  int y1 = 511 - SrcPtInt[0].y; // "511 -" cause we want "0" in lower left corner
                  int y2 = 511 - SrcPtInt[1].y;

                  // determine polynomial coefficients of y(x):=a*(x-x0)ｳ-b*x+c 
                  // (want to cheat? see end of file)
                  double        dx = x1 - x2;	double		  dy = y1 - y2;
                    float x0 = (float)(x1 + x2) / 2;
                    float a = (float)(-2.0*dy / pow(dx, 3.0));
                    float b = (float)(-3.0 / 2.0*dy / dx);
                    float c = (float)((y1 + y2) / 2.0 + b*x0);

                  
                  // create the LUT for that polynom and 
                  // draw the polynom in the MapCurveimage (pixelwise)
				      // your code for the polynomial and color transform (instead of the following line)
                    for (int i = 0; i < 512; i++) {
                        LUT[i] = a * pow(i - x0, 3) - b * i + c;
                        if (LUT[i] > 511) {
                            LUT[i] = 511;
                        }
                        else if (LUT[i] < 0) {
                            LUT[i] = 0;
                        }
                        circle(MapCurveimage512, cv::Point(i, 511 - LUT[i]), 1, cv::Scalar(255, 255, 255), 1);
                    }

                  // use the lookup table (LUT) to map the input image to the result image
                  // use the same LUT for each color channel (or fantasize) 

                    // your code for the color transform (instead of the following line)
                        for (int i = 0; i < image.rows; i++) {
                            for (int j = 0; j < image.cols; j++) {
                                mapped_result_img.at<cv::Vec3b>(i, j)[0] = LUT[image.at<cv::Vec3b>(i, j)[0]];
                                mapped_result_img.at<cv::Vec3b>(i, j)[1] = LUT[image.at<cv::Vec3b>(i, j)[1]];
                                mapped_result_img.at<cv::Vec3b>(i, j)[2] = LUT[image.at<cv::Vec3b>(i, j)[2]];
                            }
                        }



				      // show non-linear mapping curve
                  imshow("GreyCurve", MapCurveimage512);
				   
				      // show the result
				      imshow( "result image", mapped_result_img );

				      // mapped_result_img = image.clone();
                      nb_points = 0;
               } else nb_points++;
			   }
        }
        break;
    }
}  // void on_mouse( int event, int x, int y, int flags, void* param )


int main( int argc, char** argv )
{
	help();
    
	char* filename = argc == 3 ? argv[1] : (char*)"C:/Users/mcall/OneDrive/Dokumente/CoputerVision/exercise1/img/fruits.jpg";
    image = cv::imread(filename, 1);
	mapped_result_img = image.clone();

    cv::namedWindow( "GreyCurve");
    cv::namedWindow( "Fruits!");
	imshow( "Fruits!", mapped_result_img );
	
   MapCurveimage512.create(512, 512, CV_8U);
   MapCurveimage512 = 0;
   imshow("GreyCurve", MapCurveimage512);

   cv::setMouseCallback( "GreyCurve", on_mouse, 0 );
   cv::waitKey();
    
    return 0;
    // all the memory will automatically be released by Vector<>, Mat and Ptr<> destructors.
}




































































































/*
// determine polynomial coefficients of y(x):=a*(x-x0)ｳ-b*x+c;
int x1 = SrcPtInt[0].x;	int y1 = 511 - SrcPtInt[0].y;
int x2 = SrcPtInt[1].x;	int y2 = 511 - SrcPtInt[1].y;
double        dx = x1 - x2;	double		  dy = y1 - y2;
float x0 = (float)(x1 + x2) / 2;
float a = (float)(-2.0*dy / pow(dx, 3.0));
float b = (float)(-3.0 / 2.0*dy / dx);
float c = (float)((y1 + y2) / 2.0 + b*x0);
*/
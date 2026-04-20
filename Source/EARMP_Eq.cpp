//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: EARMP_Eq.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 15-May-2023 10:32:25
//

// Include Files
#pragma once

#include <JuceHeader.h>

#include "EARMP_Eq.h"
#include <cmath>

// Function Definitions
//
// Arguments    : void
// Return Type  : void
//
EARMP_Eq::EARMP_Eq() = default;

//
// Arguments    : void
// Return Type  : void
//
EARMP_Eq::~EARMP_Eq() = default;

//
// Arguments    : double x
//                const double a[3]
//                const double b[2]
//                double xbuf[2]
//                double ybuf[2]
// Return Type  : double
//
double EARMP_Eq::filterProcess(double x, const double a[3], const double b[2],
                               double xbuf[2], double ybuf[2])
{
  double y;
#if myBugMessage
    DBG("修改前的參數：");
    DBG("xbuf[0]:"<<xbuf[0]);
    DBG("xbuf[1]:"<<xbuf[1]);
    DBG("ybuf[0]:"<<ybuf[0]);
    DBG("ybuf[1]:"<<ybuf[1]);
#endif
  y = (((a[0] * x + xbuf[0] * a[1]) + xbuf[1] * a[2]) - b[0] * ybuf[0]) -
      b[1] * ybuf[1];
  xbuf[1] = xbuf[0];
  xbuf[0] = x;
  ybuf[1] = ybuf[0];
  ybuf[0] = y;
#if myBugMessage
      DBG("修改後的參數：");
      DBG("xbuf[0]:"<<xbuf[0]);
      DBG("xbuf[1]:"<<xbuf[1]);
      DBG("ybuf[0]:"<<ybuf[0]);
      DBG("ybuf[1]:"<<ybuf[1]);
#endif
  return y;
}

//
// Arguments    : double fc
//                double fs
//                double a[3]
//                double b[2]
// Return Type  : void
//
void EARMP_Eq::highpass_setup(double fc, double fs, double a[3], double b[2])
{
  double theta;
  theta = 6.2831 * fc / fs;
  theta = (std::cos(theta)+0.00001) / (std::sin(theta) + 1.0);
  a[0] = theta / 2.0 + 0.5;
  //  a0
  a[1] = -a[0];
  a[2] = 0.0;
  b[0] = -theta;
  b[1] = 0.0;
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            xbuf[i][j]=0;
            ybuf[i][j]=0;
        }
    }
}

//
// Arguments    : double fc
//                double fs
//                double a[3]
//                double b[2]
// Return Type  : void
//
void EARMP_Eq::lowpass_setup(double fc, double fs, double a[3], double b[2])
{
  double theta;
  theta = 6.2831853071795862 * fc / fs;
  theta = (std::cos(theta)+0.00001) / (std::sin(theta) + 1.0);

  a[0] = 0.5 - theta / 2.0;
  //  a0
  a[1] = a[0];
  a[2] = 0.0;
  b[0] = -theta;
  b[1] = 0.0;
    
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            xbuf[i][j]=0;
            ybuf[i][j]=0;
        }
    }
}

//
// File trailer for EARMP_Eq.cpp
//
// [EOF]
//

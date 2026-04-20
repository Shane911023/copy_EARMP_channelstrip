//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: EARMP_Eq.h
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 15-May-2023 10:32:25
//

#ifndef EARMP_EQ_H
#define EARMP_EQ_H

// Include Files
//#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
class EARMP_Eq {
public:
  EARMP_Eq();
  ~EARMP_Eq();
  double filterProcess(double x, const double a[3], const double b[2],
                       double xbuf[2], double ybuf[2]);
  void highpass_setup(double fc, double fs, double a[3], double b[2]);
  void lowpass_setup(double fc, double fs, double a[3], double b[2]);
    
    double a[3], b[2];
    double xbuf[2][2], ybuf[2][2];  // Step2: define the variable for Eq function
};

#endif
//
// File trailer for EARMP_Eq.h
//
// [EOF]
//

/*
 *  GBVTD.cpp
 *  vortrac
 *
 *  Created by Michael Bell on 5/6/06.
 *  Copyright 2006 University Corporation for Atmospheric Research.
 *  All rights reserved.
 *
 */

#include "GBVTD.h"
#include <math.h>
#include "IO/Message.h"
#include "Math/Matrix.h"

GBVTD::GBVTD(QString& initClosure, int& wavenumbers, float*& gaps, float hvvpwind)
  : VTD(initClosure, wavenumbers, gaps, hvvpwind)
{
}

GBVTD::~GBVTD()
{
}

bool GBVTD::analyzeRing(float& xCenter, float& yCenter, float& radius, float& height, int& numData, 
                        float*& ringData, float*& ringAzimuths, Coefficient*& vtdCoeffs, float& vtdStdDev)
{
  // Analyze a ring of data
  
  // Make a Psi array
  ringPsi = new float[numData];
  vel = new float[numData];
  psi = new float[numData];

  // Get thetaT
  thetaT = atan2(yCenter,xCenter);
  thetaT = fixAngle(thetaT);
  centerDistance = sqrt(xCenter*xCenter + yCenter*yCenter);

  for (int i = 0; i <= numData - 1; i++) {
    // Convert to Psi
    float angle = ringAzimuths[i] * DEG2RAD - thetaT;
    angle = fixAngle(angle);
    float xx = xCenter + radius * cos(angle + thetaT);
    float yy = yCenter + radius * sin(angle + thetaT);
    float psiCorrection = atan2(yy, xx) - thetaT;
    ringPsi[i] = angle - psiCorrection;
    ringPsi[i] = fixAngle(ringPsi[i]);
  }

  // Threshold bad values
  int goodCount = 0;

  for (int i = 0; i <= numData - 1; i++) {
    if (ringData[i] != -999.) {
      // Good point
      vel[goodCount] = ringData[i];
      psi[goodCount] = ringPsi[i];
      goodCount++;
    }
  }
  numData = goodCount;

  // Get the maximum number of coefficients for the given data distribution and geometry
  int numCoeffs = getNumCoefficients(numData);

  if (numCoeffs == 0) {
    // Too much missing data, set everything to 0 and return
    for (int i = 0; i <= (_maxWaveNum * 2 + 2); i++) {

      FourierCoeffs[i] = 0.;
    }
    vtdStdDev = -999;
    setWindCoefficients(radius, height, numCoeffs, FourierCoeffs, vtdCoeffs);
    delete[] ringPsi;
    delete[] vel;
    delete[] psi;
    return false;
  }

  // Least squares
  float** xLLS = new float*[numCoeffs];
  for (int i = 0; i <= numCoeffs - 1; i++) {
    xLLS[i] = new float[numData];
  }
  float* yLLS = new float[numData];
  for (int i = 0; i <= numData - 1; i++) {
    xLLS[0][i] = 1.;
    for (int j = 1; j <= (numCoeffs / 2); j++) {
      xLLS[2 * j - 1][i] = sin(float(j) * psi[i]);
      xLLS[ 2 * j][i] = cos(float(j) * psi[i]);
    }
    yLLS[i] = vel[i];
  }

  float* stdError = new float[numCoeffs];
  if( ! Matrix::lls(numCoeffs, numData, xLLS, yLLS, vtdStdDev, FourierCoeffs, stdError)) {
    //Message::toScreen("GBVTD Returned Nothing from LLS");
    for (int i = 0; i <= numCoeffs - 1; i++)
      delete[] xLLS[i];
    delete[] yLLS;
    delete[] stdError;
    delete[] ringPsi;
    delete[] vel;
    delete[] psi;
    return false;
  }

  // Convert Fourier coefficients into wind coefficients
  setWindCoefficients(radius, height, numCoeffs, FourierCoeffs, vtdCoeffs);
  for (int i = 0; i <= numCoeffs - 1; i++)
    delete[] xLLS[i];
  delete[] xLLS;
  delete[] yLLS;
  delete[] stdError;
  delete[] ringPsi;
  delete[] vel;
  delete[] psi;
  
  return true;
}

void GBVTD::setWindCoefficients(float& radius, float& level, int& numCoeffs,
				float*& FourierCoeffs, Coefficient*& vtdCoeffs)
{
  // Allocate and initialize the A & B coefficient arrays
  
  float* A;
  float* B;
  int maxIndex = numCoeffs / 2 + 1;
    
  if (maxIndex > 5) {
    A = new float[numCoeffs / 2 + 1];
    B = new float[numCoeffs / 2 + 1];
  } else {
    A = new float[5];
    B = new float[5];
  }
  for (int i=0; i <= 4; i++) {
    A[i] = 0;
    B[i] = 0;
  }

  float sinAlphamax = radius/centerDistance;
  float cosAlphamax = sqrt(centerDistance * centerDistance - radius * radius) / centerDistance;
    
  A[0] = FourierCoeffs[0];
  B[0] = 0.;
    
  for (int i=1; i <= (numCoeffs/2); i++) {
    A[i] = FourierCoeffs[2 * i];
    B[i] = FourierCoeffs[2 * i - 1];
  }

  // Use the specified closure method to set VT, VR, and VM
  if (closure.contains(QString("original"), Qt::CaseInsensitive)) {

    vtdCoeffs[0].setLevel(level);
    vtdCoeffs[0].setRadius(radius);
    vtdCoeffs[0].setParameter("VTC0");
    float value;
    if(closure.contains(QString("hvvp"), Qt::CaseInsensitive) and
       (B[1] != 0)) {
      value = - B[1] - B[3] - _hvvpMean * sinAlphamax;
    }
    else {
      value = - B[1] - B[3];
    }
    vtdCoeffs[0].setValue(value);

    vtdCoeffs[1].setLevel(level);
    vtdCoeffs[1].setRadius(radius);
    vtdCoeffs[1].setParameter("VRC0");
    value = A[1] +A[3];
    vtdCoeffs[1].setValue(value);

    vtdCoeffs[2].setLevel(level);
    vtdCoeffs[2].setRadius(radius);
    vtdCoeffs[2].setParameter("VMC0");
    value = A[0] + A[2]+ A[4];
    vtdCoeffs[2].setValue(value);

    vtdCoeffs[3].setLevel(level);
    vtdCoeffs[3].setRadius(radius);
    vtdCoeffs[3].setParameter("VTS1");

    if ((sinAlphamax < 0.8) and (numCoeffs >= 5)) {
      value = A[2] - A[0] + A[4] + (A[0] + A[2] + A[4]) * cosAlphamax;
      if (value < vtdCoeffs[0].getValue()) {
	vtdCoeffs[3].setValue(value);
      } else {
	vtdCoeffs[3].setValue(0);
      }
    } else {
      vtdCoeffs[3].setValue(0);
    }

    vtdCoeffs[4].setLevel(level);
    vtdCoeffs[4].setRadius(radius);
    vtdCoeffs[4].setParameter("VTC1");
	
    if ((sinAlphamax < 0.8) and (numCoeffs >= 5)) {
      value = -2. * (B[2] + B[4]);
      if (value < vtdCoeffs[0].getValue()) {
	vtdCoeffs[4].setValue(value);
      } else {
	vtdCoeffs[4].setValue(0);
      }
    } else {
      vtdCoeffs[4].setValue(0);
    }

    for (int i=5; i <= numCoeffs - 1; i += 2) {
      vtdCoeffs[i].setLevel(level);
      vtdCoeffs[i].setRadius(radius);
      QString param = "VTC" + QString().setNum(int(i / 2));
      vtdCoeffs[i].setParameter(param);
      value = -2. * B[i / 2 + 1];
      vtdCoeffs[i].setValue(value);

      vtdCoeffs[i+1].setLevel(level);
      vtdCoeffs[i+1].setRadius(radius);
      param = "VTS" + QString().setNum(int(i / 2));
      vtdCoeffs[i + 1].setParameter(param);
      value = 2 * A[i / 2 + 1];
      vtdCoeffs[i + 1].setValue(value);
    }
  } 

  delete[] A;
  delete[] B;
}

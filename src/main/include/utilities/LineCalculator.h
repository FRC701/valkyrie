#pragma once

// A transfer function for a line

class LineCalculator
{
public:
  LineCalculator() {}

  LineCalculator(double slope, double yIntercept)
  : mSlope {slope}
  , mYIntercept { yIntercept}
  { }

  LineCalculator(double x1, double y1, double x2, double y2)
  : LineCalculator(slopeFromPoints(x1,y1,x2,y2), yInterceptFromPoints(x1,y1,x2,y2))
  { }
  
  double operator()(double x)
  {
    return (mSlope * x) + mYIntercept;
  }

  double slope() const { return mSlope; }
  double yIntercept() const { return mYIntercept; }

  LineCalculator invert() const
  {
    return LineCalculator(1.0 / slope(), -1.0 * yIntercept() / slope());
  }

  static double slopeFromPoints(double x1, double y1, double x2, double y2)
  {
    return (y2 - y1) / (x2 - x1);
  }

  static double yInterceptFromPoints(double x1, double y1, double x2, double y2)
  {
    double slope = slopeFromPoints(x1, y1, x2, y2);
    return y2 - (slope * x2);
  }

private:
  double mSlope {0.};
  double mYIntercept {0.};
};


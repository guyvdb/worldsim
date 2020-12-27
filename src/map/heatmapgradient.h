#ifndef HEATMAPGRADIENT_H
#define HEATMAPGRADIENT_H

#include <vector>
#include <QColor>

namespace map {


  class HeatMapGradient {
    public:
      HeatMapGradient();
      void AddColorPoint(float red, float green, float blue, float value);
      void ClearGradient();
      void CreateDefaultHeatGradient();
      void GetColorAtValue(const float value, float &red, float &green, float &blue);
      QColor GetColor(const float value);
    private:
      struct ColorPoint  // Internal class used to store colors at different points in the gradient.
      {
        float r,g,b;      // Red, green and blue values of our color.
        float value;        // Position of our color along the gradient (between 0 and 1).
        ColorPoint(float red, float green, float blue, float value)
          : r(red), g(green), b(blue), value(value) {}
      };
      std::vector<ColorPoint> m_colors;      // An array of color points in ascending value.

  };


}
#endif // HEATMAPGRADIENT_H



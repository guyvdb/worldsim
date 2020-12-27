#include "heatmapgradient.h"

#include <algorithm>
#include <iostream>

namespace map {
  HeatMapGradient::HeatMapGradient() {
    this->CreateDefaultHeatGradient();
  }

  void HeatMapGradient::AddColorPoint(float red, float green, float blue, float value) {
    // do we need to insert somewhere
    for(std::size_t i=0; i< this->m_colors.size(); i++)  {
      if(value < this->m_colors[i].value) {
        this->m_colors.insert(this->m_colors.begin()+i, ColorPoint(red,green,blue, value));
        return;
      }
    }

    // no insert - push back
    this->m_colors.push_back(ColorPoint(red,green,blue, value));
  }

  void HeatMapGradient::ClearGradient() {
    this->m_colors.clear();
  }

  void HeatMapGradient::CreateDefaultHeatGradient() {
    this->m_colors.clear();
    this->m_colors.push_back(ColorPoint(0, 0, 1,   0.0f));      // Blue.
    this->m_colors.push_back(ColorPoint(0, 1, 1,   0.5f));     // Cyan.
    this->m_colors.push_back(ColorPoint(0, 1, 0,   1.0f));      // Green.
    this->m_colors.push_back(ColorPoint(1, 1, 0,   1.5f));     // Yellow.
    this->m_colors.push_back(ColorPoint(1, 0, 0,   2.0f));      // Red.
  }

  void HeatMapGradient::GetColorAtValue(const float value, float &red, float &green, float &blue) {
    if(this->m_colors.size() == 0) {
      return;
    }

    for(std::size_t i=0;i<this->m_colors.size(); i++) {
      ColorPoint& current = this->m_colors[i];
      if(value < current.value) {
        ColorPoint& prev = this->m_colors[std::max<std::size_t>(0,i-1)];
        float valueDiff = (prev.value - current.value);
        float fractBetween = (valueDiff==0) ? 0 : (value - current.value) / valueDiff;
        red = (prev.r - current.r) * fractBetween + current.r;
        green = (prev.r - current.r) * fractBetween + current.r;
        blue = (prev.r - current.r) * fractBetween + current.r;
        std::cout << "set color= [r" << red << ", g" << green << ", b" << blue << "] value=" << value
                  << ", diff=" << valueDiff << ", fract=" << fractBetween << std::endl;
        return;
      }
    }

    ColorPoint& back = this->m_colors.back();
    red = back.r;
    green = back.g;
    blue = back.b;
    std::cout << "set color= [r" << red << ", g" << green << ", b" << blue << "] value=" << value << std::endl;
    return;
  }

  QColor HeatMapGradient::GetColor(const float value) {
    float r, g, b;
    this->GetColorAtValue(value,r,g,b);
    return QColor((int)r,(int)g,(int)b);
  }

}


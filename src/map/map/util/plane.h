#ifndef PLANE_H
#define PLANE_H

namespace map {
  namespace utils {

  }
}


/*
 move a point from one plane (lat/lon) to another (screen x/y) - this is not a projection.
 the original point needs to be already projected.

#input
IMG = ...
XLEFT,YTOP,XRIGHT,YBOTTOM = ...
CONSTRAIN = True

#constrain dimensions to avoid distortion
if CONSTRAIN:
    xwidth = max(XLEFT,XRIGHT) - min(XLEFT,XRIGHT)
    yheight = max(YTOP,YBOTTOM) - min(YTOP,YBOTTOM)
    if xwidth > yheight:
        YBOTTOM = YTOP+xwidth
    elif yheight > xwidth:
        XRIGHT = XLEFT+yheight

#prepare scale values
imgwidth = float(IMG.width)
imgheight = float(IMG.height)
scalex = imgwidth / (XRIGHT - XLEFT)
scaley = 0 - imgheight / (YTOP - YBOTTOM)

With that, the coordinate conversion of inx and iny is calculated as:

newx = scalex * (inx - XLEFT)
newy = imgheight + scaley * (iny - YBOTTOM)

*/


#endif // PLANE_H

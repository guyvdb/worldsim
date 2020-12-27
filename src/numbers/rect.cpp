#include "rect.h"


namespace num {



  Rect::Rect(Vector topleft, Vector bottomright) {
    this->Top = topleft.X;
    this->Left = topleft.Y;
    this->Width = bottomright.X - topleft.X;
    this->Height = bottomright.Y - topleft.Y;
  }


  Bounds Rect::XBounds() {
    return Bounds(this->Left,  this->Left + this->Width);
  }

  Bounds Rect::YBounds() {
    return Bounds(this->Top, this->Top + this->Height);
  }
}

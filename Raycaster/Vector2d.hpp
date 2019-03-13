#ifndef V2D_h
#define V2D_h

class Vector2d {
    
private:
    double x;
    double y;
    
public:
    Vector2d(double x_, double y_);
    
    double getX() const;
    double getY() const;
    
    void operator += (const Vector2d b);
    void operator -= (const Vector2d b);
    void operator *= (const double b);
    void operator /= (const double b);
    
    void rotateThis(const double b);
    Vector2d rotate(const double b);
    
    Vector2d operator + (const Vector2d b);
    Vector2d operator - (const Vector2d b);
    Vector2d operator * (const double b);
    Vector2d operator / (const double b);
    
    double mag();
    Vector2d copy();
    Vector2d norm();
};

#endif

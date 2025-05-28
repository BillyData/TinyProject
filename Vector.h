#ifndef VECTOR_H
#define VECTOR_H

class Vector {
    private:
        int mSize;
        double* mData;
        Vector();
    public:
        Vector(int Size);
        int getSize() const;
        double* getData() const;
        Vector operator+(const Vector& a) const;
        Vector operator-(const Vector& a) const; 
        double operator*(const Vector& a) const;
        Vector operator+(double a) const;
        Vector operator+(int a) const;
        Vector operator-(double a) const;
        Vector operator-(int a) const;
        Vector operator*(double a) const;
        Vector operator*(int a) const;
        int operator[](int a) const;
        double& operator()(int a);
        Vector& operator=(const Vector& a);
        ~Vector();
};

#endif

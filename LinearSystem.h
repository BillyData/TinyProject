// LinearSystem.h
#ifndef LINEARSYSTEM_H
#define LINEARSYSTEM_H

#include "Matrix.h"
#include "Vector.h"

class LinearSystem {
   protected:
    int mSize;
    Matrix* mpA;
    Vector* mpb;

   private:
    LinearSystem();
    LinearSystem(const LinearSystem&);

   public:
    LinearSystem(Matrix* A, Vector* b);
    virtual ~LinearSystem() {}

    virtual Vector Solve();
};

class PosSymLinSystem : public LinearSystem {
   public:
    PosSymLinSystem(Matrix* A, Vector* b);
    Vector Solve() override;
};

class LeastSquaresSystem {
   private:
    Matrix* mpA;
    Vector* mpb;

   public:
    LeastSquaresSystem(Matrix* A, Vector* b);
    Vector Solve();
};

#endif  // LINEARSYSTEM_H

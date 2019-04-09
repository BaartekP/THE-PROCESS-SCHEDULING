#include "generator.h"
#include <cmath>


UniformGenerator::UniformGenerator(int kernel): kernel_(kernel)
{
   M = 2147483647.0;
   A = 16807;
   Q = 127773;
   R = 2836;
}

UniformGenerator::~UniformGenerator()
{

}

double UniformGenerator::Rand()
{
   int h = kernel_/Q;
   kernel_ = A*(kernel_-Q*h)-R*h;
   if (kernel_ < 0)
      kernel_ = kernel_ + static_cast<int>(M);
   return kernel_/M;
}

double UniformGenerator::Rand(int start, int end)
{
   return Rand()*(end-start) + start;
}

ExpGenerator::ExpGenerator(double lambda, UniformGenerator *ug): lambda_(lambda), uniform_(ug)
{

}

ExpGenerator::~ExpGenerator()
{
   if (uniform_ != nullptr)
      delete uniform_;
}

double ExpGenerator::Rand()
{
   double k = uniform_->Rand();
   double s = -(1.0 / lambda_)*log(k);
   return s;
}
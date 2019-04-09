#ifndef AS_RANDOM_GENERATOR_GENERATOR_H_
#define AS_RANDOM_GENERATOR_GENERATOR_H_

#include <string>

class UniformGenerator
{
   public:
      UniformGenerator(int kernel);
      virtual ~UniformGenerator();

      // Draws number between <0,1>
      double Rand();
      // Draws number between <start, end>
      double Rand(int start, int end);

      int get_kernel() {return kernel_;};
   private:
      int kernel_;
      double M;
      int A;
      int Q;
      int R;
};

class ExpGenerator
{
    public:
      ExpGenerator(double lambda, UniformGenerator *ug);
      virtual ~ExpGenerator();
      double Rand();
   private:
      double lambda_;
      UniformGenerator *uniform_;
};

#endif /* AS_RANDOM_GENERATOR_GENERATOR_H_ */
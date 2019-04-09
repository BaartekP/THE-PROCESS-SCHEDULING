#ifndef AS_RANDOM_GENERATOR_GENERATORS_H_
#define AS_RANDOM_GENERATOR_GENERATORS_H_

class UniformGenerator;
class ExpGenerator;
class Kernels;

struct RNG
{
	  RNG();
      virtual ~RNG();

      void Initialize(Kernels *kernels, int set_idx, double lambda);

      UniformGenerator *tpw;
      UniformGenerator *tpd;
      UniformGenerator *tpo;
      UniformGenerator *tpio;
	  UniformGenerator *tdq;
      ExpGenerator *tpg;
};

#endif /* AS_RANDOM_GENERATOR_GENERATORS_H_ */
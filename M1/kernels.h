#ifndef AS_RANDOM_GENERATOR_KERNELS_H_
#define AS_RANDOM_GENERATOR_KERNELS_H_

#include <map>
#include <vector>

class Kernels
{
   public:
      enum GTypes
      {
         TPG = 0, // New process arrives event
         TPW,     // Processor occupation time
         TPIO,    // IO device demand event
         TPO,     // IO device occupation time
         TPD,   // IO device choice
		 DQ,	// device queue
         COUNT
      };
      
      Kernels();

      virtual ~Kernels();

      int GetKernel(GTypes gtype, int set) const;

      void GenerateKernels(std::string filePath);

      void ReadKernels(const std::string input_file_path);

   private:

      const int kNrofSets;
      const int kSetLength;
      
      bool kernels_loaded_;

      std::map<GTypes, std::vector<int> > kernelSet_;
};

#endif /*AS_RANDOM_GENERATOR_KERNELS_H_*/

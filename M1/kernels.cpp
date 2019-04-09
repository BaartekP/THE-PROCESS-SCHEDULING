#include "kernels.h"
#include <cassert>
#include <fstream>
#include "generator.h"
#include <boost/algorithm/string.hpp>

using namespace std;

int Kernels::GetKernel(GTypes gtype, int set) const
{
   assert(kernels_loaded_ && "Kernels::GetKernel(): Kernels not loaded from the file!");
   assert(gtype != COUNT && "Kernels::GetKernel(): Wrong generator type!");
   auto setSize = kernelSet_.at(gtype);
   assert(set >= 0 && set < setSize.size() && "Kernels::GetKernel(): set index out of range!");
   return kernelSet_.at(gtype)[set];
}

void Kernels::GenerateKernels(std::string filePath)
{
   printf("Kernels generation...\n");
   int k = 10;
   ofstream fout(filePath);
   UniformGenerator *uniform = new UniformGenerator(k);

   if (fout.is_open())
   {
      for (int genTypeIdx = 0; genTypeIdx < COUNT; genTypeIdx++)
      {
         printf("\n  Generator Type %d/%d\n  Set: ", genTypeIdx+1, COUNT);
         for (int i = 0; i < kNrofSets; i++)
         {
            printf("%d/%d, ", i+1, kNrofSets);
            for (int j = 0; j < kSetLength; j++)
            {
               uniform->Rand();
            }
            fout << uniform->get_kernel() << " ";
         }
         fout << endl;
      }
      fout.close();
   }
}
//				liczba symulacji // odstep pomiedzy seedami
Kernels::Kernels(): kNrofSets(10), kSetLength(100000)
{
   kernelSet_.insert(pair<GTypes, vector<int>>(TPG,vector<int>()));
   kernelSet_.insert(pair<GTypes, vector<int>>(TPW,vector<int>()));
   kernelSet_.insert(pair<GTypes, vector<int>>(TPIO,vector<int>()));
   kernelSet_.insert(pair<GTypes, vector<int>>(TPO,vector<int>()));
   kernelSet_.insert(pair<GTypes, vector<int>>(TPD,vector<int>()));
   kernelSet_.insert(pair<GTypes, vector<int>>(DQ, vector<int>()));

   kernels_loaded_ = false;
}

Kernels::~Kernels()
{

}

void Kernels::ReadKernels(const std::string input_file_path)
{
   printf("   Reading kernels from %s file....", input_file_path.c_str());
   ifstream fin(input_file_path);

   if (fin.is_open())
   {
      string line; int line_idx = 0;
      std::vector<std::string> splitted;

      while (getline(fin, line) && line_idx < COUNT)
      {         
         vector<int> kernels;

         boost::trim(line);

         boost::split(splitted, line , boost::is_any_of(" "));

         for (auto val : splitted)
            kernels.push_back(atoi(val.c_str()));
      
         kernelSet_[static_cast<GTypes>(line_idx)] = kernels;
         line_idx++;
      }
      printf("OK!\n");
      kernels_loaded_ = true;
      fin.close();
   }
   else
   {
      printf("FILE ERROR!\n");
   }
}
#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include "SensorCluster.hpp"

using std::string;
using std::ifstream;
using std::cout;
using std::endl;

unsigned int hashfct1(unsigned int nic) {

    nic=nic/100000;
    unsigned int t;
    t = nic % 5;
    return t;
}
unsigned int hashfct2(unsigned int nic) {
   nic=nic/10000;
   unsigned int t;
   t = nic % 5;
   return t;
}

unsigned int hashfct3(unsigned int nic) {
   nic=nic/1000;
   unsigned int t;
   t = nic % 5;
   return t;
}

unsigned int hashfct4(unsigned int nic) {

   nic=nic/100;
   unsigned int t;
   t = nic % 5;
   return t;
}


unsigned int hashfct5(unsigned int nic) {
  nic=nic/10;
    unsigned int t;
    t = nic % 5;
    return t;
}

unsigned int hashfct6(unsigned int nic) {
    nic=nic/1;
    unsigned int t;
    t = nic % 5;
    return t;
}

Item::Item(string itemName, unsigned int nic):itemName_(itemName), nic_(nic)
{};

void SensorCluster::readTextfile(string filename) {
  ifstream myfile(filename);

  if (myfile.is_open()) {
    cout << "Successfully opened file " << filename << endl;
    string itemName;
    unsigned int nic;
    while (myfile >> itemName >> nic) {
			if (itemName.size() > 0)
      	addItem(itemName, nic);
    }
    myfile.close();
  }
  else
    throw std::invalid_argument("Could not open file " + filename);
}

void SensorCluster::addItem(string itemName, unsigned int nic) {


  Item sensnet =Item(itemName,nic);

  hT1.insert({nic, sensnet});
  hT2.insert({nic, sensnet});
  hT3.insert({nic, sensnet});
  hT4.insert({nic, sensnet});
  hT5.insert({nic, sensnet});
  hT6.insert({nic, sensnet});


}

bool SensorCluster::removeItem(unsigned int nic) {
   if (hT1.find(nic) != hT1.end())
    {
      hT1.erase(nic); hT2.erase(nic); hT3.erase(nic); hT4.erase(nic); hT5.erase(nic); hT6.erase(nic);

      return true;
    }

   else

     return false;

}

  unsigned int SensorCluster::bestHashing() {
  unsigned int min = hT1.bucket_size(0);
  unsigned int max = hT1.bucket_size(0);

  int i = 0;
  while(i<10)
  {
    unsigned int bucket = hT1.bucket_size(i);
    if (bucket > max)
    {
      max = bucket;

    }
     else if (bucket < max)
     {
      min = bucket;
    }
  }
  unsigned int top1 = max - min;

  min = hT2.bucket_size(0);
  max = hT2.bucket_size(0);
  
  while(i<10)
  {
    unsigned int bucket = hT2.bucket_size(i);
    if (bucket > max)
    {
      max = bucket;

    }
     else if (bucket < max)
     {
      min = bucket;
    }
  }
  unsigned int top2 = max - min;

  min = hT3.bucket_size(0);
  max = hT3.bucket_size(0);
  
  while(i<10)
  {
    unsigned int bucket = hT3.bucket_size(i);
    if (bucket > max)
    {
      max = bucket;

    }
     else if (bucket < max)
     {
      min = bucket;
    }
  }
  unsigned int top3 = max - min;

  min = hT4.bucket_size(0);
  max = hT4.bucket_size(0);
  
  while(i<10)
  {
    unsigned int bucket = hT4.bucket_size(i);
    if (bucket > max)
    {
      max = bucket;

    }
     else if (bucket < max)
     {
      min = bucket;
    }
  }
  unsigned int top4 = max - min;

  min = hT5.bucket_size(0);
  max = hT5.bucket_size(0);
  
  while(i<10)
  {
    unsigned int bucket = hT5.bucket_size(i);
    if (bucket > max)
    {
      max = bucket;

    }
     else if (bucket < max)
     {
      min = bucket;
    }
  }
  unsigned int top5 = max - min;

  min = hT6.bucket_size(0);
  max = hT6.bucket_size(0);
  
  while(i<10)
  {
    unsigned int bucket = hT6.bucket_size(i);
    if (bucket > max)
    {
      max = bucket;

    }
     else if (bucket < max)
     {
      min = bucket;
    }
  }
  unsigned int top6 = max - min;
  unsigned int array[6] = {top1,top2,top3,top4,top5,top6};
  unsigned int minimum_value = array[0];
  for (i = 0; i <= 5; i++)
  {
    if (array[i] <= minimum_value)
    {
      if (i != 5)
      {
        minimum_value = array[i];
      } else
      {
        minimum_value = array[i];
        cout << minimum_value << endl;
      }
    }
  }

  for (int i = 1; i <= 6; i++){
    if (minimum_value == top1){
      return 1;
    } else if (minimum_value == top2){
      return 2;
    } else if (minimum_value == top3){
      return 3;
    } else if (minimum_value == top4){
      return 4;
    } else if (minimum_value == top5){
      return 5;
    } else if (minimum_value == top6){
      return 6;
    }
  }

  return 0;
}



size_t SensorCluster::size() {
    if ((hT1.size() != hT2.size()) || (hT1.size() != hT3.size()) || (hT1.size() != hT4.size()) || (hT1.size() != hT5.size())|| (hT1.size() != hT6.size()) )
  	throw std::length_error("Hash table sizes are not the same");

	return hT1.size();
}

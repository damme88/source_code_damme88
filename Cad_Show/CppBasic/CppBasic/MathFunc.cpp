
#include "MathFunc.h"

namespace BaseMath {
  std::vector<unsigned int> DecimalToBinary(unsigned int decimal) {
    std::vector<unsigned int> ret_list;
    unsigned int result = decimal;
    while (result != 0) {
      int binary = result % 2;
      ret_list.push_back(binary);
      result = result/2;
    }
    std::vector<unsigned int> binary_list;
    for (int i = ret_list.size()-1; i >= 0; i --) {
      int ret = ret_list[i];
      binary_list.push_back(ret);
    }
    return binary_list;
  }
	// Primer Number are numbers Which can div 1 and itself
	// Return : False. this number is not primer number
	//          True. this number is primer number
	bool CheckPrimerNumber(unsigned int pnum) {
    for (int i = 2; i < pnum/2; i++) {
			if (pnum % i == 0)
				return false;
		}
		return true;
	}
}
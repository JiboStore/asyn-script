﻿/*!
* \file Recursion.cpp
* \date 7-7-2016 20:00:00
*
*
* \author cs (04nycs@gmail.com)
*/


#include <iostream>
#include "../../../lib-asyn-script/source/Function.h"
#include "../../../lib-asyn-script/source/AsynScript.h"

asys_reg_funs;

asys::FunctionCode* sum(ASYS_P(int, n))
{
	BEGIN_FUN(n){
		ASYS_VAR(int, n_minus_one);
		_CC{
			if (n <= 0)
			{
				asys_return(0);
			}

			n_minus_one = n - 1;
		}CC_;

		ASYS_VAR(int, sub_result);
		CALL(sum(), n_minus_one) >>= {sub_result};

		_CC{
			asys_return(n + sub_result);
		}CC_;
	}END_FUN;
}

asys::FunctionCode* print()
{
	BEGIN_FUN(){
		ASYS_VAR(int, n);
		ASSIGN(n, 0);

		WHILE_CC(true){
			ASYS_VAR(int, result);
			CALL(sum(), n) >>= {result};

			_CC{
				std::cout << "s(" << n << ") = " << result << std::endl;
				n = n + 1;
			}CC_;
		}END_WHILE;
	}END_FUN;
}

int main()
{
	asys::Machine machine;
	machine.installCode(print());
	while (machine.run() == asys::CodeFlow::redo_);

	char c{};
	std::cin >> c;

	return 0;
}
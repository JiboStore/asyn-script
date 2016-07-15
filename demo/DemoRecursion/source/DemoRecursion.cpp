﻿/*!
* \file Recursion.cpp
* \date 7-7-2016 20:00:00
*
*
* \author cs (04nycs@gmail.com)
*/


#include <iostream>
#include "../../../lib-asyn-script/source/Function.h"

asys::FunctionMap m_asynFunctions;

asys::FunctionCode* sum(ASYS_PARAM(n))
{
	auto& f = m_asynFunctions[__FUNCTION__];
	if (f) return f;

	f = new asys::FunctionCode;
	{
		f->INPUT({n})_;
		
		ASYS_VAR(n_minus_one);
		f->EXPRESS([=](asys::Executable* executable){
			asys_value(n);
			asys_value(n_minus_one);
			if (n.toInt() <= 0)
			{
				executable->setOutputValues({ 0 });
				return asys::CodeFlow::return_;
			}

			n_minus_one = n.toInt() - 1;
			return asys::CodeFlow::next_;
		})_;

		ASYS_VAR(sub_result);
		f->CALL({ sub_result }, { n_minus_one }, sum())_;

		f->EXPRESS([=](asys::Executable* executable){
			asys_value(sub_result);
			asys_value(n);
			executable->setOutputValues({ n.toInt() + sub_result.toInt() });
			return asys::CodeFlow::return_;
		})_;
	}

	return f;
}

asys::FunctionCode* print()
{
	auto& f = m_asynFunctions[__FUNCTION__];
	if (f) return f;

	f = new asys::FunctionCode;
	{
		ASYS_VAR(n);
		f->ASSIGN(n, asys_const(0))_;

		f->WHILE(asys::True)_
		{
			ASYS_VAR(result);
			f->CALL({ result }, { n }, sum())_;

			f->EXPRESS([=](asys::Executable* executable){
				asys_value(result);
				asys_value(n);
				std::cout << "s(" << n.toInt() << ") = " << result.toInt() << std::endl;

				n = n.toInt() + 1;
				return asys::CodeFlow::next_;
			})_;
		}f->END_WHILE()_;
		
	}

	return f;
}

int main()
{
	auto executable = print()->compile();
	while (executable->run() == asys::CodeFlow::yield_);
	executable->release();

	char c{};
	std::cin >> c;

	return 0;
}
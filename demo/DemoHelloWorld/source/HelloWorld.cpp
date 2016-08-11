﻿/*!
* \file HelloWorld.cpp
* \date 03-31-2016 19:32:27
*
*
* \author cs 04nycs@gmail.com
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

		ASYS_VAR(sum);
		f->ASSIGN(sum, asys_const(0))_;

		ASYS_VAR(i);
		f->ASSIGN(i, asys_const(0))_;

		f->WHILE_NOT_EQUAL(i, n)_
		{
			f->OPERATE(sum, sum, i, asys::Operator::plus)_;
			f->OPERATE(i, i, asys_const(1), asys::Operator::plus)_;
		}f->END_WHILE()_;

		f->RETURN({ sum })_;
	}

	return f;
}

asys::FunctionCode* sum2(ASYS_PARAM(n))
{
	auto& f = m_asynFunctions[__FUNCTION__];
	if (f) return f;

	f = new asys::FunctionCode;
	{
		f->INPUT({ n })_;

		f->DO([n](asys::Executable* executable){
			asys_value(n);
			int v_sum = 0;
			for (int i = 0; i != n.toInt(); ++i)
			{
				v_sum += i;
			}
			asys_return(v_sum);
		})_;
	}

	return f;
}

asys::FunctionCode* print_sum(ASYS_PARAM(n))
{
	auto& f = m_asynFunctions[__FUNCTION__];
	if (f) return f;

	f = new asys::FunctionCode;
	{
		f->INPUT({n})_;

		ASYS_VAR(index);
		f->ASSIGN(index, asys_const(0))_;

		f->WHILE_NOT_EQUAL(index, n)_
		{
			ASYS_VAR(v_sum);
			f->CALL({v_sum}, { index }, sum())_;

			f->DO([v_sum](asys::Executable* executable){
				asys_value(v_sum);
				std::cout << "sum = " << v_sum.toString() << std::endl;
			})_;

			ASYS_VAR(v_sum2);
			f->CALL({ v_sum2 }, { index }, sum2())_;

			f->DO([v_sum2](asys::Executable* executable){
				asys_value(v_sum2);
				std::cout << "sum2 = " << v_sum2.toString() << std::endl;
			})_;

			f->OPERATE(index, index, asys_const(1), asys::Operator::plus)_;
		}f->END_WHILE()_;
	}

	return f;
}

int main()
{
	auto executable = print_sum()->compile();
	executable->setInputValue(0, 100);

	while (executable->run() == asys::CodeFlow::redo_);
	executable->release();

	char c{};
	std::cin >> c;

	return 0;
}
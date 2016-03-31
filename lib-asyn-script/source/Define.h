﻿
/*!
 * \file Define.h
 * \date 02-11-2016 18:31:20
 * 
 * 
 * \author cs 04nycs@gmail.com
 */

#pragma once

#include <string>
#include <sstream>

namespace patch
{
	template < typename T > std::string to_string(const T& n)
	{
		std::ostringstream stm;
		stm << n;
		return stm.str();
	}
}

namespace asys
{
	enum class RetCode
	{
		code_continue,
		code_done,
	};

	enum class Operator
	{
		plus,
		minus,
		multiply,
		divide,
		equal,
		not_equal,
		greater_than,
		greater_than_equal,
		less_than,
		less_than_equal,
		and_,
		or_,
		not_,
	};

	extern const std::string OUTPUT_VARIABLE_PREFIX;
	extern const std::string INPUT_VARIABLE_PREFIX;

	inline bool isValidVariableName(const std::string& var) { return var.size() > 0 && var[0] == '$'; }
	inline bool isSystemReservedVariableName(const std::string& var) { return var.size() > 1 && var[0] == '$' && var[1] == '$'; }

	inline std::string getOutputVariableName(int index) { return OUTPUT_VARIABLE_PREFIX + patch::to_string(index); }
	inline std::string getInputVariableName(int index) { return INPUT_VARIABLE_PREFIX + patch::to_string(index); }
}

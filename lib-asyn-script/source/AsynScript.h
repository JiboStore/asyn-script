﻿/*!
 * \file AsynScript.h
 * \date 11-16-2016 9:15:54
 * 
 * 
 * \author cs (04nycs@gmail.com)
 */

#pragma once

#include "Function.h"
#include "Define.h"

// append this macro to the instruction calls to set a break point for ease of debug in C++
#ifdef _DEBUG
#define _ ([](asys::Executable* asys_this, const asys::BreakPoint& breakPoint) \
								{ \
			asys_this->setValue("$$__FILE__", breakPoint.fileName()); \
			asys_this->setValue("$$__FUNCTION__", breakPoint.functionName()); \
			asys_this->setValue("$$__LINE__", breakPoint.lineNumber());},\
			__FILE__, __FUNCTION__, __LINE__);
#else
#define _ ;
#endif

#define asys_this asys_this

#define BEGIN_FUN(...) auto& __this_function = m_asynFunctions[__FUNCTION__]; \
					if (__this_function) return __this_function; \
					__this_function = new asys::FunctionCode; \
					__this_function->Input({__VA_ARGS__})_; \

#define END_FUN return __this_function;

#define __C __this_function->Do([=](asys::Executable* asys_this){
#define C__ })_;

#define CALL(...)  __this_function->Call(__VA_ARGS__)_;

#define IF(var) __this_function->If(var)_;
#define IF_EX(...) __this_function->If_ex(__VA_ARGS__)_;
#define IF_NOT(condition) __this_function->If_not(condition)_;
#define IF_EQUAL(var1, var2) __this_function->If_equal(var1, var2)_;
#define IF_NOT_EQUAL(var1, var2) __this_function->If_not_equal(var1, var2)_;

#define ELSE __this_function->Else()_;
#define END_IF __this_function->End_if()_;

#define WHILE(var) __this_function->While(var)_;
#define WHILE_EX(express) __this_function->While_ex(express)_;
#define WHILE_NOT(var) __this_function->While_not(var)_;
#define WHILE_EQUAL(var1, var2)  __this_function->While_equal(var)_;
#define WHILE_NOT_EQUAL(var1, var2) __this_function->While_not_equal(var1, var2)_;

#define END_WHILE __this_function->End_while()_;
#define CONTINUE __this_function->Continue()_;
#define BREAK __this_function->Break()_;

#define RETURN(...) __this_function->Return({__VA_ARGS__})_;

#define ASSIGN(var1, var2) __this_function->Assign(var1, var2)_;
#define OPERATE(...) __this_function->Operate(__VA_ARGS__)_;

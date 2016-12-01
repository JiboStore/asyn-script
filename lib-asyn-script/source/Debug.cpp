﻿
/*!
 * \file Debug.cpp
 * \date 12-1-2016 15:24:50
 * 
 * 
 * \author cs (04nycs@gmail.com)
 */

#include "Debug.h"
#include "Function.h"

asys::DebugInfo::~DebugInfo()
{
	for (auto& pair : m_variables)
	{
		delete pair.second;
	}
	m_variables.clear();
}

void asys::DebugInfo::initialize(FunctionExecutable* executable)
{
	m_pExecutable = executable;

	m_pExecutable->m_stack.m_structure.forEachVariable([=](AsysVariable* var){
		m_pExecutable->m_stack.construct(*var);
		auto metaVar = m_pExecutable->m_stack.getMetaVariable(*var);
		auto viewer = metaVar->createVariableViewer();
		if (!m_variables[viewer->getName()])
		{
			m_variables[viewer->getName()] = viewer;
		}
		m_pExecutable->m_stack.destruct(*var);
	});
}

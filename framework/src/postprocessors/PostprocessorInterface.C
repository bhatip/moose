/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#include "PostprocessorInterface.h"
#include "FEProblem.h"
#include "Postprocessor.h"
#include "MooseTypes.h"

PostprocessorInterface::PostprocessorInterface(InputParameters & params) :
    _pi_feproblem(*params.get<FEProblem *>("_fe_problem")),
    _pi_tid(params.have_parameter<THREAD_ID>("_tid") ? params.get<THREAD_ID>("_tid") : 0),
    _ppi_params(params)
{
}

PostprocessorValue &
PostprocessorInterface::getPostprocessorValue(const std::string & name)
{
  // Return the default if the Postprocessor does not exist and a default does, otherwise
  // continue as usual
  if (!hasPostprocessor(name) && _ppi_params.hasDefaultPostprocessorValue(name))
    return _ppi_params.defaultPostprocessorValue(name);
  else
    return _pi_feproblem.getPostprocessorValue(_ppi_params.get<PostprocessorName>(name), _pi_tid);
}

const PostprocessorValue &
PostprocessorInterface::getPostprocessorValueByName(const PostprocessorName & name)
{
  return _pi_feproblem.getPostprocessorValue(name, _pi_tid);
}

PostprocessorValue &
PostprocessorInterface::getPostprocessorValueOld(const std::string & name)
{
  // // Return the default if the Postprocessor does not exist and a default does, otherwise
  // // continue as usual
  if (!hasPostprocessor(name) && _ppi_params.hasDefaultPostprocessorValue(name))
    return _ppi_params.defaultPostprocessorValue(name);
  else
    return _pi_feproblem.getPostprocessorValueOld(_ppi_params.get<PostprocessorName>(name), _pi_tid);
}

const PostprocessorValue &
PostprocessorInterface::getPostprocessorValueOldByName(const PostprocessorName & name)
{
  return _pi_feproblem.getPostprocessorValueOld(name, _pi_tid);
}

bool
PostprocessorInterface::hasPostprocessor(const std::string & name)
{
  return _pi_feproblem.hasPostprocessor(_ppi_params.get<PostprocessorName>(name), _pi_tid);
}


bool
PostprocessorInterface::hasPostprocessorByName(const PostprocessorName & name)
{
  return _pi_feproblem.hasPostprocessor(name, _pi_tid);
}

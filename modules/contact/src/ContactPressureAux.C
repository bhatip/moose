#include "ContactPressureAux.h"

#include "NodalArea.h"
#include "PenetrationLocator.h"

#include "libmesh/string_to_enum.h"

template<>
InputParameters validParams<ContactPressureAux>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addRequiredCoupledVar("nodal_area", "The nodal area");
  params.addRequiredParam<BoundaryName>("paired_boundary", "The boundary to be penetrated");
  params.set<MultiMooseEnum>("execute_on") = "nonlinear";
  return params;
}

ContactPressureAux::ContactPressureAux(const std::string & name, InputParameters params) :
    AuxKernel(name, params),
    _nodal_area(coupledValue("nodal_area")),
    _penetration_locator(getPenetrationLocator(getParam<BoundaryName>("paired_boundary"), getParam<std::vector<BoundaryName> >("boundary")[0], Utility::string_to_enum<Order>(getParam<MooseEnum>("order"))))
{
}

ContactPressureAux::~ContactPressureAux()
{
}

Real
ContactPressureAux::computeValue()
{
  Real value(0);
  const Real area = _nodal_area[_qp];
  const PenetrationInfo * pinfo(NULL);

  const std::map<dof_id_type, PenetrationInfo*>::const_iterator it = _penetration_locator._penetration_info.find( _current_node->id() );
  if (it != _penetration_locator._penetration_info.end())
  {
    pinfo = it->second;
  }

  if (pinfo && area != 0)
  {
    value = -(pinfo->_contact_force * pinfo->_normal) / area;
  }
  return value;
}

[Mesh]
  type = FileMesh
  file = square.e
  # This test uses SolutionUserObject which doesn't work with ParallelMesh.
  distribution = serial
[]

[Variables]
  [./u]
    order = FIRST
    family = LAGRANGE
  [../]
[]

[AuxVariables]
  [./u_aux]
    order = FIRST
    family = LAGRANGE
  [../]
[]

[Kernels]
  [./diff]
    type = Diffusion
    variable = u
  [../]
[]

[AuxKernels]
  [./initial_cond_aux]
    type = SolutionAux
    solution = xda_soln
    execute_on = initial
    variable = u_aux
  [../]
[]

[UserObjects]
  [./xda_soln]
    type = SolutionUserObject
    mesh = build_out_0001_mesh.xda
    es = build_out_0001.xda
    system_variables = u
  [../]
[]

[BCs]
  [./left]
    type = DirichletBC
    variable = u
    boundary = 1
    value = 0
  [../]
  [./right]
    type = DirichletBC
    variable = u
    boundary = 2
    value = 1
  [../]
[]

[Executioner]
  type = Steady

  # Preconditioned JFNK (default)
  solve_type = 'PJFNK'

  nl_rel_tol = 1e-10
[]

[Outputs]
  exodus = true
  output_on = 'initial timestep_end'
  [./console]
    type = Console
    perf_log = true
    output_on = 'timestep_end failed nonlinear'
  [../]
  [./xda]
    type = XDA
  [../]
[]

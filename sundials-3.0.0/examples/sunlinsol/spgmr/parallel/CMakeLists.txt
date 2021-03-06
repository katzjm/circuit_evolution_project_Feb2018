# ---------------------------------------------------------------
# Programmer(s): Daniel Reynolds @ SMU
# -----------------------------------------------------------------
# LLNS/SMU Copyright Start
# Copyright (c) 2017, Southern Methodist University and 
# Lawrence Livermore National Security
#
# This work was performed under the auspices of the U.S. Department 
# of Energy by Southern Methodist University and Lawrence Livermore 
# National Laboratory under Contract DE-AC52-07NA27344.
# Produced at Southern Methodist University and the Lawrence 
# Livermore National Laboratory.
#
# All rights reserved.
# For details, see the LICENSE file.
# LLNS/SMU Copyright End
# ---------------------------------------------------------------
# CMakeLists.txt file for sunlinsol examples

# Add variable sunlinsol_spgmr_examples with the names of the sunlinsol examples

SET(sunlinsol_spgmr_examples
  test_sunlinsol_spgmr_parallel
)

SET(sunlinsol_spgmr_dependencies
  test_sunlinsol
  sundials_nvector
  sundials_linearsolver
)

# Add source directory to include directories
INCLUDE_DIRECTORIES(. ../..)

# Specify libraries to link against (through the target that was used to 
# generate them) based on the value of the variable LINK_LIBRARY_TYPE

IF(LINK_LIBRARY_TYPE MATCHES "static")
  SET(NVEC_LIB sundials_nvecparallel_static)
  SET(SUNLINSOL_LIB sundials_sunlinsolspgmr_static)
ELSE(LINK_LIBRARY_TYPE MATCHES "static")
  SET(NVEC_LIB sundials_nvecparallel_shared)
  SET(SUNLINSOL_LIB sundials_sunlinsolspgmr_shared)
ENDIF(LINK_LIBRARY_TYPE MATCHES "static")

# Set-up linker flags and link libraries

SET(SUNDIALS_LIBS ${NVEC_LIB} ${SUNLINSOL_LIB} ${EXTRA_LINK_LIBS})

IF(MPI_MPICC)
  # use MPI_MPICC as the compiler
  SET(CMAKE_C_COMPILER ${MPI_MPICC})
ELSE(MPI_MPICC)
  # add MPI_INCLUDE_PATH to include directories
  INCLUDE_DIRECTORIES(${MPI_INCLUDE_PATH})
ENDIF(MPI_MPICC)

# Add the build and install targets for each sunlinsol example

FOREACH(example ${sunlinsol_spgmr_examples})

  IF(WIN32)
    ADD_DEFINITIONS(-DBUILD_SUNDIALS_LIBRARY)
  ENDIF(WIN32)

  ADD_EXECUTABLE(${example} ${example}.c ../../test_sunlinsol.c ../../../../src/sundials/sundials_linearsolver.c ../../../../src/sundials/sundials_nvector.c)
  SET_TARGET_PROPERTIES(${example} PROPERTIES FOLDER "Examples")

  SUNDIALS_ADD_TEST( ${example}_100_1_1_50_3_0 ${example} MPI_NPROCS 4 TEST_ARGS 100 1 1 50 1e-3 0)
  SUNDIALS_ADD_TEST( ${example}_100_1_2_50_3_0 ${example} MPI_NPROCS 4 TEST_ARGS 100 1 2 50 1e-3 0)
  SUNDIALS_ADD_TEST( ${example}_100_2_1_50_3_0 ${example} MPI_NPROCS 4 TEST_ARGS 100 2 1 50 1e-3 0)
  SUNDIALS_ADD_TEST( ${example}_100_2_2_50_3_0 ${example} MPI_NPROCS 4 TEST_ARGS 100 2 2 50 1e-3 0)

  TARGET_LINK_LIBRARIES(${example} ${SUNDIALS_LIBS})
  IF(NOT MPI_MPICC)
    TARGET_LINK_LIBRARIES(${example} ${MPI_LIBRARIES})
  ENDIF()

  IF(EXAMPLES_INSTALL)
    INSTALL(FILES ${example}.c ../../test_sunlinsol.h ../../test_sunlinsol.c ../../../../src/sundials/sundials_linearsolver.c ../../../../src/sundials/sundials_nvector.c DESTINATION ${EXAMPLES_INSTALL_PATH}/sunlinsol/spgmr/parallel)
  ENDIF(EXAMPLES_INSTALL)
ENDFOREACH(example ${sunlinsol_spgmr_examples})

IF(EXAMPLES_INSTALL)

  # Install the README file
  INSTALL(FILES DESTINATION ${EXAMPLES_INSTALL_PATH}/sunlinsol/spgmr/parallel)

  # Prepare substitution variables for Makefile and/or CMakeLists templates
  SET(SOLVER_LIB "sundials_sunlinsolspgmr")
  LIST2STRING(sunlinsol_spgmr_examples EXAMPLES)
  LIST2STRING(sunlinsol_spgmr_dependencies EXAMPLES_DEPENDENCIES)

  # Regardless of the platform we're on, we will generate and install 
  # CMakeLists.txt file for building the examples. This file  can then 
  # be used as a template for the user's own programs.

  # generate CMakelists.txt in the binary directory
  CONFIGURE_FILE(
      ${PROJECT_SOURCE_DIR}/examples/templates/cmakelists_parallel_C_ex.in
      ${PROJECT_BINARY_DIR}/examples/sunlinsol/spgmr/parallel/CMakeLists.txt
      @ONLY
      )

  # install CMakelists.txt
  INSTALL(
    FILES ${PROJECT_BINARY_DIR}/examples/sunlinsol/spgmr/parallel/CMakeLists.txt
    DESTINATION ${EXAMPLES_INSTALL_PATH}/sunlinsol/spgmr/parallel
    )

  # On UNIX-type platforms, we also  generate and install a makefile for 
  # building the examples. This makefile can then be used as a template 
  # for the user's own programs.

  IF(UNIX)
    # generate Makefile and place it in the binary dir
    CONFIGURE_FILE(
      ${PROJECT_SOURCE_DIR}/examples/templates/makefile_parallel_C_ex.in
      ${PROJECT_BINARY_DIR}/examples/sunlinsol/spgmr/parallel/Makefile_ex
      @ONLY
      )
    # install the configured Makefile_ex as Makefile
    INSTALL(
      FILES ${PROJECT_BINARY_DIR}/examples/sunlinsol/spgmr/parallel/Makefile_ex 
      DESTINATION ${EXAMPLES_INSTALL_PATH}/sunlinsol/spgmr/parallel
      RENAME Makefile
      )
  ENDIF(UNIX)

ENDIF(EXAMPLES_INSTALL)

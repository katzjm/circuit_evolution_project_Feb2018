# ---------------------------------------------------------------
# Programmer: Radu Serban @ LLNL
# ---------------------------------------------------------------
# LLNS Copyright Start
# Copyright (c) 2014, Lawrence Livermore National Security
# This work was performed under the auspices of the U.S. Department 
# of Energy by Lawrence Livermore National Laboratory in part under 
# Contract W-7405-Eng-48 and in part under Contract DE-AC52-07NA27344.
# Produced at the Lawrence Livermore National Laboratory.
# All rights reserved.
# For details, see the LICENSE file.
# LLNS Copyright End
# ---------------------------------------------------------------
# CMakeLists.txt file for the FKINSOL serial examples
# ---------------------------------------------------------------

# Examples using SUNDIALS linear solvers
SET(FKINSOL_examples
  fkinDiagon_kry
  )

# Specify libraries to link against (through the target that was used to 
# generate them) based on the value of the variable LINK_LIBRARY_TYPE
IF(LINK_LIBRARY_TYPE MATCHES "static")
  SET(KINSOL_LIB sundials_kinsol_static)
  SET(NVECS_LIB sundials_nvecserial_static)
  SET(FNVECS_LIB sundials_fnvecserial_static)
ELSE()
  SET(KINSOL_LIB sundials_kinsol_shared)
  SET(NVECS_LIB sundials_nvecserial_shared)
  SET(FNVECS_LIB sundials_fnvecserial_shared)
ENDIF()

# Only static FCMIX libraries are available
SET(FKINSOL_LIB sundials_fkinsol_static)

# Set-up linker flags and link libraries
SET(SUNDIALS_LIBS ${FKINSOL_LIB} ${KINSOL_LIB} ${FNVECS_LIB} ${NVECS_LIB} ${EXTRA_LINK_LIBS})

# Add the build and install targets for each example
FOREACH(example ${FKINSOL_examples})

  # example source files
  ADD_EXECUTABLE(${example} ${example}.f)

  SET_TARGET_PROPERTIES(${example} PROPERTIES FOLDER "Examples")

  # add to regression tests
  SUNDIALS_ADD_TEST(${example} ${example})

  # libraries to link against
  TARGET_LINK_LIBRARIES(${example} ${SUNDIALS_LIBS})

   # install example source and out files
  IF(EXAMPLES_INSTALL)
    INSTALL(FILES ${example}.f ${example}.out
      DESTINATION ${EXAMPLES_INSTALL_PATH}/kinsol/fcmix_serial)
  ENDIF()

ENDFOREACH(example ${FKINSOL_examples})

# create Makfile and CMakeLists.txt for examples
IF(EXAMPLES_INSTALL)

  # Install the README file
  INSTALL(FILES README DESTINATION ${EXAMPLES_INSTALL_PATH}/kinsol/fcmix_serial)

  # Prepare substitution variables for Makefile and/or CMakeLists templates
  SET(SOLVER "KINSOL")
  SET(SOLVER_LIB "sundials_kinsol")
  SET(SOLVER_FLIB "sundials_fkinsol")

  LIST2STRING(FKINSOL_examples EXAMPLES)

  # Regardless of the platform we're on, we will generate and install 
  # CMakeLists.txt file for building the examples. This file  can then 
  # be used as a template for the user's own programs.

  # generate CMakelists.txt in the binary directory
  CONFIGURE_FILE(
      ${PROJECT_SOURCE_DIR}/examples/templates/cmakelists_serial_F77_ex.in
      ${PROJECT_BINARY_DIR}/examples/kinsol/fcmix_serial/CMakeLists.txt
      @ONLY
      )

  # install CMakelists.txt
  INSTALL(
    FILES ${PROJECT_BINARY_DIR}/examples/kinsol/fcmix_serial/CMakeLists.txt
    DESTINATION ${EXAMPLES_INSTALL_PATH}/kinsol/fcmix_serial 
    )

  # On UNIX-type platforms, we also  generate and install a makefile for 
  # building the examples. This makefile can then be used as a template 
  # for the user's own programs.

  IF(UNIX)
    # generate Makefile and place it in the binary dir
    CONFIGURE_FILE(
      ${PROJECT_SOURCE_DIR}/examples/templates/makefile_serial_F77_ex.in
      ${PROJECT_BINARY_DIR}/examples/kinsol/fcmix_serial/Makefile_ex
      @ONLY
      )
    # install the configured Makefile_ex as Makefile
    INSTALL(
      FILES ${PROJECT_BINARY_DIR}/examples/kinsol/fcmix_serial/Makefile_ex 
      DESTINATION ${EXAMPLES_INSTALL_PATH}/kinsol/fcmix_serial 
      RENAME Makefile
      )
  ENDIF(UNIX)

ENDIF(EXAMPLES_INSTALL)

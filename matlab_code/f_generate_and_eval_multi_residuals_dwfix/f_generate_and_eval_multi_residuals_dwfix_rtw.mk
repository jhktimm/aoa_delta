###########################################################################
## Makefile generated for MATLAB file/project 'f_generate_and_eval_multi_residuals_dwfix'. 
## 
## Makefile     : f_generate_and_eval_multi_residuals_dwfix_rtw.mk
## Generated on : Thu Jun 11 08:15:01 2020
## MATLAB Coder version: 3.3 (R2017a)
## 
## Build Info:
## 
## Final product: $(RELATIVE_PATH_TO_ANCHOR)/f_generate_and_eval_multi_residuals_dwfix.a
## Product type : static-library
## 
###########################################################################

###########################################################################
## MACROS
###########################################################################

# Macro Descriptions:
# PRODUCT_NAME            Name of the system to build
# MAKEFILE                Name of this makefile
# COMPUTER                Computer type. See the MATLAB "computer" command.

PRODUCT_NAME              = f_generate_and_eval_multi_residuals_dwfix
MAKEFILE                  = f_generate_and_eval_multi_residuals_dwfix_rtw.mk
COMPUTER                  = GLNXA64
MATLAB_ROOT               = /usr/local/software/matlab2017a
MATLAB_BIN                = /usr/local/software/matlab2017a/bin
MATLAB_ARCH_BIN           = /usr/local/software/matlab2017a/bin/glnxa64
MASTER_ANCHOR_DIR         = 
START_DIR                 = /home/nawaz/Documents/MATLAB/Cavity_Fault_Detection/CavityFaultDetection/Skripts_for_codegen
ARCH                      = glnxa64
RELATIVE_PATH_TO_ANCHOR   = .
C_STANDARD_OPTS           = -ansi -pedantic -Wno-long-long -fwrapv
CPP_STANDARD_OPTS         = -std=c++98 -pedantic -Wno-long-long -fwrapv

###########################################################################
## TOOLCHAIN SPECIFICATIONS
###########################################################################

# Toolchain Name:          GNU gcc/g++ v4.4.x | gmake (64-bit Linux)
# Supported Version(s):    4.4.x
# ToolchainInfo Version:   R2017a
# Specification Revision:  1.0
# 
#-------------------------------------------
# Macros assumed to be defined elsewhere
#-------------------------------------------

# C_STANDARD_OPTS
# CPP_STANDARD_OPTS

#-----------
# MACROS
#-----------

WARN_FLAGS         = -Wall -W -Wwrite-strings -Winline -Wstrict-prototypes -Wnested-externs -Wpointer-arith -Wcast-align
WARN_FLAGS_MAX     = $(WARN_FLAGS) -Wcast-qual -Wshadow
CPP_WARN_FLAGS     = -Wall -W -Wwrite-strings -Winline -Wpointer-arith -Wcast-align
CPP_WARN_FLAGS_MAX = $(CPP_WARN_FLAGS) -Wcast-qual -Wshadow

TOOLCHAIN_SRCS = 
TOOLCHAIN_INCS = 
TOOLCHAIN_LIBS = 

#------------------------
# BUILD TOOL COMMANDS
#------------------------

# C Compiler: GNU C Compiler
CC = gcc

# Linker: GNU Linker
LD = gcc

# C++ Compiler: GNU C++ Compiler
CPP = g++

# C++ Linker: GNU C++ Linker
CPP_LD = g++

# Archiver: GNU Archiver
AR = ar

# MEX Tool: MEX Tool
MEX_PATH = $(MATLAB_BIN)
MEX = "$(MEX_PATH)/mex"

# Download: Download
DOWNLOAD =

# Execute: Execute
EXECUTE = $(PRODUCT)

# Builder: GMAKE Utility
MAKE_PATH = %MATLAB%/bin/glnxa64
MAKE = "$(MAKE_PATH)/gmake"


#-------------------------
# Directives/Utilities
#-------------------------

CDEBUG              = -g
C_OUTPUT_FLAG       = -o
LDDEBUG             = -g
OUTPUT_FLAG         = -o
CPPDEBUG            = -g
CPP_OUTPUT_FLAG     = -o
CPPLDDEBUG          = -g
OUTPUT_FLAG         = -o
ARDEBUG             =
STATICLIB_OUTPUT_FLAG =
MEX_DEBUG           = -g
RM                  = @rm -f
ECHO                = @echo
MV                  = @mv
RUN                 =

#----------------------------------------
# "Faster Builds" Build Configuration
#----------------------------------------

ARFLAGS              = ruvs
CFLAGS               = -c $(C_STANDARD_OPTS) -fPIC \
                       -O0
CPPFLAGS             = -c $(CPP_STANDARD_OPTS) -fPIC \
                       -O0
CPP_LDFLAGS          = -Wl,-rpath,"$(MATLAB_ARCH_BIN)",-L"$(MATLAB_ARCH_BIN)"
CPP_SHAREDLIB_LDFLAGS  = -shared -Wl,-rpath,"$(MATLAB_ARCH_BIN)",-L"$(MATLAB_ARCH_BIN)" -Wl,--no-undefined
DOWNLOAD_FLAGS       =
EXECUTE_FLAGS        =
LDFLAGS              = -Wl,-rpath,"$(MATLAB_ARCH_BIN)",-L"$(MATLAB_ARCH_BIN)"
MEX_CPPFLAGS         = -MATLAB_ARCH=$(ARCH) $(INCLUDES) \
                         \
                       COPTIMFLAGS="$(C_STANDARD_OPTS)  \
                       -O0 \
                        $(DEFINES)" \
                         \
                       -silent
MEX_CPPLDFLAGS       = LDFLAGS=='$$LDFLAGS'
MEX_CFLAGS           = -MATLAB_ARCH=$(ARCH) $(INCLUDES) \
                         \
                       COPTIMFLAGS="$(C_STANDARD_OPTS)  \
                       -O0 \
                        $(DEFINES)" \
                         \
                       -silent
MEX_LDFLAGS          = LDFLAGS=='$$LDFLAGS'
MAKE_FLAGS           = -f $(MAKEFILE)
SHAREDLIB_LDFLAGS    = -shared -Wl,-rpath,"$(MATLAB_ARCH_BIN)",-L"$(MATLAB_ARCH_BIN)" -Wl,--no-undefined

#--------------------
# File extensions
#--------------------

H_EXT               = .h
OBJ_EXT             = .o
C_EXT               = .c
EXE_EXT             =
SHAREDLIB_EXT       = .so
HPP_EXT             = .hpp
OBJ_EXT             = .o
CPP_EXT             = .cpp
EXE_EXT             =
SHAREDLIB_EXT       = .so
STATICLIB_EXT       = .a
MEX_EXT             = .mexa64
MAKE_EXT            = .mk


###########################################################################
## OUTPUT INFO
###########################################################################

PRODUCT = $(RELATIVE_PATH_TO_ANCHOR)/f_generate_and_eval_multi_residuals_dwfix.a
PRODUCT_TYPE = "static-library"
BUILD_TYPE = "Static Library"

###########################################################################
## INCLUDE PATHS
###########################################################################

INCLUDES_BUILDINFO = -I$(START_DIR)/codegen/lib/f_generate_and_eval_multi_residuals_dwfix -I$(START_DIR) -I$(MATLAB_ROOT)/extern/include -I$(MATLAB_ROOT)/simulink/include -I$(MATLAB_ROOT)/rtw/c/src -I$(MATLAB_ROOT)/rtw/c/src/ext_mode/common -I$(MATLAB_ROOT)/rtw/c/ert

INCLUDES = $(INCLUDES_BUILDINFO)

###########################################################################
## DEFINES
###########################################################################

DEFINES_STANDARD = -DMODEL=f_generate_and_eval_multi_residuals_dwfix -DHAVESTDIO -DUSE_RTMODEL -DUNIX

DEFINES = $(DEFINES_STANDARD)

###########################################################################
## SOURCE FILES
###########################################################################

SRCS = $(START_DIR)/codegen/lib/f_generate_and_eval_multi_residuals_dwfix/f_generate_and_eval_multi_residuals_dwfix_rtwutil.c $(START_DIR)/codegen/lib/f_generate_and_eval_multi_residuals_dwfix/f_generate_and_eval_multi_residuals_dwfix_initialize.c $(START_DIR)/codegen/lib/f_generate_and_eval_multi_residuals_dwfix/f_generate_and_eval_multi_residuals_dwfix_terminate.c $(START_DIR)/codegen/lib/f_generate_and_eval_multi_residuals_dwfix/f_generate_and_eval_multi_residuals_dwfix.c $(START_DIR)/codegen/lib/f_generate_and_eval_multi_residuals_dwfix/abs.c $(START_DIR)/codegen/lib/f_generate_and_eval_multi_residuals_dwfix/eps.c $(START_DIR)/codegen/lib/f_generate_and_eval_multi_residuals_dwfix/power.c $(START_DIR)/codegen/lib/f_generate_and_eval_multi_residuals_dwfix/rdivide.c $(START_DIR)/codegen/lib/f_generate_and_eval_multi_residuals_dwfix/sum.c $(START_DIR)/codegen/lib/f_generate_and_eval_multi_residuals_dwfix/mean.c $(START_DIR)/codegen/lib/f_generate_and_eval_multi_residuals_dwfix/f_generate_online_UKF_residual_full.c $(START_DIR)/codegen/lib/f_generate_and_eval_multi_residuals_dwfix/exp.c $(START_DIR)/codegen/lib/f_generate_and_eval_multi_residuals_dwfix/f_calibrateData.c $(START_DIR)/codegen/lib/f_generate_and_eval_multi_residuals_dwfix/f_compute_ukf_residual_not_pers.c $(START_DIR)/codegen/lib/f_generate_and_eval_multi_residuals_dwfix/f_cavitySystem.c $(START_DIR)/codegen/lib/f_generate_and_eval_multi_residuals_dwfix/unscentedKalmanFilter.c $(START_DIR)/codegen/lib/f_generate_and_eval_multi_residuals_dwfix/UnscentedKalmanFilter1.c $(START_DIR)/codegen/lib/f_generate_and_eval_multi_residuals_dwfix/isSymmetricPositiveSemiDefinite.c $(START_DIR)/codegen/lib/f_generate_and_eval_multi_residuals_dwfix/sqrt.c $(START_DIR)/codegen/lib/f_generate_and_eval_multi_residuals_dwfix/eig.c $(START_DIR)/codegen/lib/f_generate_and_eval_multi_residuals_dwfix/xgehrd.c $(START_DIR)/codegen/lib/f_generate_and_eval_multi_residuals_dwfix/xzlarfg.c $(START_DIR)/codegen/lib/f_generate_and_eval_multi_residuals_dwfix/xnrm2.c $(START_DIR)/codegen/lib/f_generate_and_eval_multi_residuals_dwfix/xscal.c $(START_DIR)/codegen/lib/f_generate_and_eval_multi_residuals_dwfix/xhseqr.c $(START_DIR)/codegen/lib/f_generate_and_eval_multi_residuals_dwfix/xdhseqr.c $(START_DIR)/codegen/lib/f_generate_and_eval_multi_residuals_dwfix/xdlanv2.c $(START_DIR)/codegen/lib/f_generate_and_eval_multi_residuals_dwfix/xrot.c $(START_DIR)/codegen/lib/f_generate_and_eval_multi_residuals_dwfix/xzgeev.c $(START_DIR)/codegen/lib/f_generate_and_eval_multi_residuals_dwfix/xzlartg.c $(START_DIR)/codegen/lib/f_generate_and_eval_multi_residuals_dwfix/xzhgeqz.c $(START_DIR)/codegen/lib/f_generate_and_eval_multi_residuals_dwfix/calcSigmaPoints.c $(START_DIR)/codegen/lib/f_generate_and_eval_multi_residuals_dwfix/xdotc.c $(START_DIR)/codegen/lib/f_generate_and_eval_multi_residuals_dwfix/mldivide.c $(START_DIR)/codegen/lib/f_generate_and_eval_multi_residuals_dwfix/inv.c $(START_DIR)/codegen/lib/f_generate_and_eval_multi_residuals_dwfix/xswap.c $(START_DIR)/codegen/lib/f_generate_and_eval_multi_residuals_dwfix/f_GLT.c $(START_DIR)/codegen/lib/f_generate_and_eval_multi_residuals_dwfix/cov.c $(START_DIR)/codegen/lib/f_generate_and_eval_multi_residuals_dwfix/f_generate_online_UKF_residual_full_dwfix.c $(START_DIR)/codegen/lib/f_generate_and_eval_multi_residuals_dwfix/f_compute_ukf_residual_fixdw.c $(START_DIR)/codegen/lib/f_generate_and_eval_multi_residuals_dwfix/f_generate_online_parityRes1_full.c $(START_DIR)/codegen/lib/f_generate_and_eval_multi_residuals_dwfix/f_compute_parity_Res1_full.c $(START_DIR)/codegen/lib/f_generate_and_eval_multi_residuals_dwfix/f_generate_online_parityRes2_full.c $(START_DIR)/codegen/lib/f_generate_and_eval_multi_residuals_dwfix/f_compute_parity_Res2_full.c $(START_DIR)/codegen/lib/f_generate_and_eval_multi_residuals_dwfix/svd.c $(START_DIR)/codegen/lib/f_generate_and_eval_multi_residuals_dwfix/xaxpy.c $(START_DIR)/codegen/lib/f_generate_and_eval_multi_residuals_dwfix/xrotg.c $(START_DIR)/codegen/lib/f_generate_and_eval_multi_residuals_dwfix/conv.c $(START_DIR)/codegen/lib/f_generate_and_eval_multi_residuals_dwfix/median.c $(START_DIR)/codegen/lib/f_generate_and_eval_multi_residuals_dwfix/sort3.c $(START_DIR)/codegen/lib/f_generate_and_eval_multi_residuals_dwfix/quickselect.c $(START_DIR)/codegen/lib/f_generate_and_eval_multi_residuals_dwfix/sort1.c $(START_DIR)/codegen/lib/f_generate_and_eval_multi_residuals_dwfix/sortIdx.c $(START_DIR)/codegen/lib/f_generate_and_eval_multi_residuals_dwfix/var.c $(START_DIR)/codegen/lib/f_generate_and_eval_multi_residuals_dwfix/f_computeQL.c $(START_DIR)/codegen/lib/f_generate_and_eval_multi_residuals_dwfix/f_compute_detuning.c $(START_DIR)/codegen/lib/f_generate_and_eval_multi_residuals_dwfix/filter.c $(START_DIR)/codegen/lib/f_generate_and_eval_multi_residuals_dwfix/f_generate_and_eval_multi_residuals_dwfix_emxutil.c $(START_DIR)/codegen/lib/f_generate_and_eval_multi_residuals_dwfix/f_generate_and_eval_multi_residuals_dwfix_emxAPI.c $(START_DIR)/codegen/lib/f_generate_and_eval_multi_residuals_dwfix/rt_nonfinite.c $(START_DIR)/codegen/lib/f_generate_and_eval_multi_residuals_dwfix/rtGetNaN.c $(START_DIR)/codegen/lib/f_generate_and_eval_multi_residuals_dwfix/rtGetInf.c

ALL_SRCS = $(SRCS)

###########################################################################
## OBJECTS
###########################################################################

OBJS = f_generate_and_eval_multi_residuals_dwfix_rtwutil.o f_generate_and_eval_multi_residuals_dwfix_initialize.o f_generate_and_eval_multi_residuals_dwfix_terminate.o f_generate_and_eval_multi_residuals_dwfix.o abs.o eps.o power.o rdivide.o sum.o mean.o f_generate_online_UKF_residual_full.o exp.o f_calibrateData.o f_compute_ukf_residual_not_pers.o f_cavitySystem.o unscentedKalmanFilter.o UnscentedKalmanFilter1.o isSymmetricPositiveSemiDefinite.o sqrt.o eig.o xgehrd.o xzlarfg.o xnrm2.o xscal.o xhseqr.o xdhseqr.o xdlanv2.o xrot.o xzgeev.o xzlartg.o xzhgeqz.o calcSigmaPoints.o xdotc.o mldivide.o inv.o xswap.o f_GLT.o cov.o f_generate_online_UKF_residual_full_dwfix.o f_compute_ukf_residual_fixdw.o f_generate_online_parityRes1_full.o f_compute_parity_Res1_full.o f_generate_online_parityRes2_full.o f_compute_parity_Res2_full.o svd.o xaxpy.o xrotg.o conv.o median.o sort3.o quickselect.o sort1.o sortIdx.o var.o f_computeQL.o f_compute_detuning.o filter.o f_generate_and_eval_multi_residuals_dwfix_emxutil.o f_generate_and_eval_multi_residuals_dwfix_emxAPI.o rt_nonfinite.o rtGetNaN.o rtGetInf.o

ALL_OBJS = $(OBJS)

###########################################################################
## PREBUILT OBJECT FILES
###########################################################################

PREBUILT_OBJS = 

###########################################################################
## LIBRARIES
###########################################################################

LIBS = 

###########################################################################
## SYSTEM LIBRARIES
###########################################################################

SYSTEM_LIBS =  -lm

###########################################################################
## ADDITIONAL TOOLCHAIN FLAGS
###########################################################################

#---------------
# C Compiler
#---------------

CFLAGS_BASIC = $(DEFINES) $(INCLUDES)

CFLAGS += $(CFLAGS_BASIC)

#-----------------
# C++ Compiler
#-----------------

CPPFLAGS_BASIC = $(DEFINES) $(INCLUDES)

CPPFLAGS += $(CPPFLAGS_BASIC)

###########################################################################
## INLINED COMMANDS
###########################################################################

###########################################################################
## PHONY TARGETS
###########################################################################

.PHONY : all build clean info prebuild download execute


all : build
	@echo "### Successfully generated all binary outputs."


build : prebuild $(PRODUCT)


prebuild : 


download : build


execute : download


###########################################################################
## FINAL TARGET
###########################################################################

#---------------------------------
# Create a static library         
#---------------------------------

$(PRODUCT) : $(OBJS) $(PREBUILT_OBJS)
	@echo "### Creating static library "$(PRODUCT)" ..."
	$(AR) $(ARFLAGS)  $(PRODUCT) $(OBJS)
	@echo "### Created: $(PRODUCT)"


###########################################################################
## INTERMEDIATE TARGETS
###########################################################################

#---------------------
# SOURCE-TO-OBJECT
#---------------------

%.o : %.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.o : %.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(RELATIVE_PATH_TO_ANCHOR)/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.o : $(RELATIVE_PATH_TO_ANCHOR)/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(MATLAB_ROOT)/rtw/c/src/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.o : $(MATLAB_ROOT)/rtw/c/src/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/codegen/lib/f_generate_and_eval_multi_residuals_dwfix/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/codegen/lib/f_generate_and_eval_multi_residuals_dwfix/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


###########################################################################
## DEPENDENCIES
###########################################################################

$(ALL_OBJS) : $(MAKEFILE) rtw_proj.tmw


###########################################################################
## MISCELLANEOUS TARGETS
###########################################################################

info : 
	@echo "### PRODUCT = $(PRODUCT)"
	@echo "### PRODUCT_TYPE = $(PRODUCT_TYPE)"
	@echo "### BUILD_TYPE = $(BUILD_TYPE)"
	@echo "### INCLUDES = $(INCLUDES)"
	@echo "### DEFINES = $(DEFINES)"
	@echo "### ALL_SRCS = $(ALL_SRCS)"
	@echo "### ALL_OBJS = $(ALL_OBJS)"
	@echo "### LIBS = $(LIBS)"
	@echo "### MODELREF_LIBS = $(MODELREF_LIBS)"
	@echo "### SYSTEM_LIBS = $(SYSTEM_LIBS)"
	@echo "### TOOLCHAIN_LIBS = $(TOOLCHAIN_LIBS)"
	@echo "### CFLAGS = $(CFLAGS)"
	@echo "### LDFLAGS = $(LDFLAGS)"
	@echo "### SHAREDLIB_LDFLAGS = $(SHAREDLIB_LDFLAGS)"
	@echo "### CPPFLAGS = $(CPPFLAGS)"
	@echo "### CPP_LDFLAGS = $(CPP_LDFLAGS)"
	@echo "### CPP_SHAREDLIB_LDFLAGS = $(CPP_SHAREDLIB_LDFLAGS)"
	@echo "### ARFLAGS = $(ARFLAGS)"
	@echo "### MEX_CFLAGS = $(MEX_CFLAGS)"
	@echo "### MEX_CPPFLAGS = $(MEX_CPPFLAGS)"
	@echo "### MEX_LDFLAGS = $(MEX_LDFLAGS)"
	@echo "### MEX_CPPLDFLAGS = $(MEX_CPPLDFLAGS)"
	@echo "### DOWNLOAD_FLAGS = $(DOWNLOAD_FLAGS)"
	@echo "### EXECUTE_FLAGS = $(EXECUTE_FLAGS)"
	@echo "### MAKE_FLAGS = $(MAKE_FLAGS)"


clean : 
	$(ECHO) "### Deleting all derived files..."
	$(RM) $(PRODUCT)
	$(RM) $(ALL_OBJS)
	$(ECHO) "### Deleted all derived files."



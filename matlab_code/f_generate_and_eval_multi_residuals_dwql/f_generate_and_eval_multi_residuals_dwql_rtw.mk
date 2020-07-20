###########################################################################
## Makefile generated for MATLAB file/project 'f_generate_and_eval_multi_residuals_dwql'. 
## 
## Makefile     : f_generate_and_eval_multi_residuals_dwql_rtw.mk
## Generated on : Fri Jul 17 09:45:01 2020
## MATLAB Coder version: 5.0 (R2020a)
## 
## Build Info:
## 
## Final product: ./f_generate_and_eval_multi_residuals_dwql.a
## Product type : static-library
## 
###########################################################################

###########################################################################
## MACROS
###########################################################################

# Macro Descriptions:
# PRODUCT_NAME            Name of the system to build
# MAKEFILE                Name of this makefile
# MODELLIB                Static library target

PRODUCT_NAME              = f_generate_and_eval_multi_residuals_dwql
MAKEFILE                  = f_generate_and_eval_multi_residuals_dwql_rtw.mk
MATLAB_ROOT               = /usr/local/software/matlab2020a
MATLAB_BIN                = /usr/local/software/matlab2020a/bin
MATLAB_ARCH_BIN           = $(MATLAB_BIN)/glnxa64
MASTER_ANCHOR_DIR         = 
START_DIR                 = /home/nawaz/Documents/MATLAB/Cavity_Fault_Detection/CavityFaultDetection/Skripts_for_codegen/codegen/lib/f_generate_and_eval_multi_residuals_dwql
TGT_FCN_LIB               = ISO_C
SOLVER_OBJ                = 
CLASSIC_INTERFACE         = 0
MODEL_HAS_DYNAMICALLY_LOADED_SFCNS = 
RELATIVE_PATH_TO_ANCHOR   = .
C_STANDARD_OPTS           = -fwrapv -std=c99 -pedantic
CPP_STANDARD_OPTS         = -fwrapv -std=c++98 -pedantic -Wno-long-long
MODELLIB                  = f_generate_and_eval_multi_residuals_dwql.a

###########################################################################
## TOOLCHAIN SPECIFICATIONS
###########################################################################

# Toolchain Name:          GNU gcc/g++ | gmake (64-bit Linux)
# Supported Version(s):    
# ToolchainInfo Version:   2020a
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
LD = g++

# C++ Compiler: GNU C++ Compiler
CPP = g++

# C++ Linker: GNU C++ Linker
CPP_LD = g++

# Archiver: GNU Archiver
AR = ar

# MEX Tool: MEX Tool
MEX_PATH = $(MATLAB_ARCH_BIN)
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

#--------------------------------------
# "Faster Runs" Build Configuration
#--------------------------------------

ARFLAGS              = ruvs
CFLAGS               = -c $(C_STANDARD_OPTS) -fPIC \
                       -O3 -fno-loop-optimize -fno-aggressive-loop-optimizations
CPPFLAGS             = -c $(CPP_STANDARD_OPTS) -fPIC \
                       -O3 -fno-loop-optimize -fno-aggressive-loop-optimizations
CPP_LDFLAGS          = -Wl,-rpath,"$(MATLAB_ARCH_BIN)",-L"$(MATLAB_ARCH_BIN)"
CPP_SHAREDLIB_LDFLAGS  = -shared -Wl,-rpath,"$(MATLAB_ARCH_BIN)",-L"$(MATLAB_ARCH_BIN)" -Wl,--no-undefined
DOWNLOAD_FLAGS       =
EXECUTE_FLAGS        =
LDFLAGS              = -Wl,-rpath,"$(MATLAB_ARCH_BIN)",-L"$(MATLAB_ARCH_BIN)"
MEX_CPPFLAGS         =
MEX_CPPLDFLAGS       =
MEX_CFLAGS           =
MEX_LDFLAGS          =
MAKE_FLAGS           = -f $(MAKEFILE)
SHAREDLIB_LDFLAGS    = -shared -Wl,-rpath,"$(MATLAB_ARCH_BIN)",-L"$(MATLAB_ARCH_BIN)" -Wl,--no-undefined



###########################################################################
## OUTPUT INFO
###########################################################################

PRODUCT = ./f_generate_and_eval_multi_residuals_dwql.a
PRODUCT_TYPE = "static-library"
BUILD_TYPE = "Static Library"

###########################################################################
## INCLUDE PATHS
###########################################################################

INCLUDES_BUILDINFO = -I$(START_DIR) -I/home/nawaz/Documents/MATLAB/Cavity_Fault_Detection/CavityFaultDetection/Skripts_for_codegen -I$(MATLAB_ROOT)/extern/include

INCLUDES = $(INCLUDES_BUILDINFO)

###########################################################################
## DEFINES
###########################################################################

DEFINES_CUSTOM = 
DEFINES_STANDARD = -DMODEL=f_generate_and_eval_multi_residuals_dwql

DEFINES = $(DEFINES_CUSTOM) $(DEFINES_STANDARD)

###########################################################################
## SOURCE FILES
###########################################################################

SRCS = $(START_DIR)/rt_nonfinite.c $(START_DIR)/rtGetNaN.c $(START_DIR)/rtGetInf.c $(START_DIR)/f_generate_and_eval_multi_residuals_dwql_rtwutil.c $(START_DIR)/f_generate_and_eval_multi_residuals_dwql_data.c $(START_DIR)/f_generate_and_eval_multi_residuals_dwql_initialize.c $(START_DIR)/f_generate_and_eval_multi_residuals_dwql_terminate.c $(START_DIR)/f_generate_and_eval_multi_residuals_dwql.c $(START_DIR)/colon.c $(START_DIR)/find.c $(START_DIR)/mean.c $(START_DIR)/f_generate_online_UKF_residual_full.c $(START_DIR)/exp.c $(START_DIR)/f_calibrateData.c $(START_DIR)/f_compute_ukf_residual_not_pers.c $(START_DIR)/f_cavitySystem.c $(START_DIR)/UnscentedKalmanFilter.c $(START_DIR)/isSymmetricPositiveSemiDefinite.c $(START_DIR)/minOrMax.c $(START_DIR)/xnrm2.c $(START_DIR)/xrot.c $(START_DIR)/calcSigmaPoints.c $(START_DIR)/xdotc.c $(START_DIR)/inv.c $(START_DIR)/xswap.c $(START_DIR)/f_GLT.c $(START_DIR)/cov.c $(START_DIR)/f_generate_online_UKF_residual_full_dwfix.c $(START_DIR)/f_compute_ukf_residual_fixdw.c $(START_DIR)/f_generate_online_parityRes1_full.c $(START_DIR)/f_generate_online_parityRes2_full.c $(START_DIR)/f_compute_parity_Res2_full.c $(START_DIR)/svd.c $(START_DIR)/xaxpy.c $(START_DIR)/xrotg.c $(START_DIR)/median.c $(START_DIR)/quickselect.c $(START_DIR)/mode.c $(START_DIR)/sort.c $(START_DIR)/sortIdx.c $(START_DIR)/var.c $(START_DIR)/f_computeQL.c $(START_DIR)/f_comp_dw_ql_Rybaniec.c $(START_DIR)/filter.c $(START_DIR)/diff.c $(START_DIR)/smoothdata.c $(START_DIR)/repmat.c $(START_DIR)/f_generate_and_eval_multi_residuals_dwql_emxutil.c $(START_DIR)/f_generate_and_eval_multi_residuals_dwql_emxAPI.c

ALL_SRCS = $(SRCS)

###########################################################################
## OBJECTS
###########################################################################

OBJS = rt_nonfinite.o rtGetNaN.o rtGetInf.o f_generate_and_eval_multi_residuals_dwql_rtwutil.o f_generate_and_eval_multi_residuals_dwql_data.o f_generate_and_eval_multi_residuals_dwql_initialize.o f_generate_and_eval_multi_residuals_dwql_terminate.o f_generate_and_eval_multi_residuals_dwql.o colon.o find.o mean.o f_generate_online_UKF_residual_full.o exp.o f_calibrateData.o f_compute_ukf_residual_not_pers.o f_cavitySystem.o UnscentedKalmanFilter.o isSymmetricPositiveSemiDefinite.o minOrMax.o xnrm2.o xrot.o calcSigmaPoints.o xdotc.o inv.o xswap.o f_GLT.o cov.o f_generate_online_UKF_residual_full_dwfix.o f_compute_ukf_residual_fixdw.o f_generate_online_parityRes1_full.o f_generate_online_parityRes2_full.o f_compute_parity_Res2_full.o svd.o xaxpy.o xrotg.o median.o quickselect.o mode.o sort.o sortIdx.o var.o f_computeQL.o f_comp_dw_ql_Rybaniec.o filter.o diff.o smoothdata.o repmat.o f_generate_and_eval_multi_residuals_dwql_emxutil.o f_generate_and_eval_multi_residuals_dwql_emxAPI.o

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


download : $(PRODUCT)


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


%.o : $(START_DIR)/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : /home/nawaz/Documents/MATLAB/Cavity_Fault_Detection/CavityFaultDetection/Skripts_for_codegen/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.o : /home/nawaz/Documents/MATLAB/Cavity_Fault_Detection/CavityFaultDetection/Skripts_for_codegen/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


rt_nonfinite.o : $(START_DIR)/rt_nonfinite.c
	$(CC) $(CFLAGS) -o "$@" "$<"


rtGetNaN.o : $(START_DIR)/rtGetNaN.c
	$(CC) $(CFLAGS) -o "$@" "$<"


rtGetInf.o : $(START_DIR)/rtGetInf.c
	$(CC) $(CFLAGS) -o "$@" "$<"


f_generate_and_eval_multi_residuals_dwql_rtwutil.o : $(START_DIR)/f_generate_and_eval_multi_residuals_dwql_rtwutil.c
	$(CC) $(CFLAGS) -o "$@" "$<"


f_generate_and_eval_multi_residuals_dwql_data.o : $(START_DIR)/f_generate_and_eval_multi_residuals_dwql_data.c
	$(CC) $(CFLAGS) -o "$@" "$<"


f_generate_and_eval_multi_residuals_dwql_initialize.o : $(START_DIR)/f_generate_and_eval_multi_residuals_dwql_initialize.c
	$(CC) $(CFLAGS) -o "$@" "$<"


f_generate_and_eval_multi_residuals_dwql_terminate.o : $(START_DIR)/f_generate_and_eval_multi_residuals_dwql_terminate.c
	$(CC) $(CFLAGS) -o "$@" "$<"


f_generate_and_eval_multi_residuals_dwql.o : $(START_DIR)/f_generate_and_eval_multi_residuals_dwql.c
	$(CC) $(CFLAGS) -o "$@" "$<"


colon.o : $(START_DIR)/colon.c
	$(CC) $(CFLAGS) -o "$@" "$<"


find.o : $(START_DIR)/find.c
	$(CC) $(CFLAGS) -o "$@" "$<"


mean.o : $(START_DIR)/mean.c
	$(CC) $(CFLAGS) -o "$@" "$<"


f_generate_online_UKF_residual_full.o : $(START_DIR)/f_generate_online_UKF_residual_full.c
	$(CC) $(CFLAGS) -o "$@" "$<"


exp.o : $(START_DIR)/exp.c
	$(CC) $(CFLAGS) -o "$@" "$<"


f_calibrateData.o : $(START_DIR)/f_calibrateData.c
	$(CC) $(CFLAGS) -o "$@" "$<"


f_compute_ukf_residual_not_pers.o : $(START_DIR)/f_compute_ukf_residual_not_pers.c
	$(CC) $(CFLAGS) -o "$@" "$<"


f_cavitySystem.o : $(START_DIR)/f_cavitySystem.c
	$(CC) $(CFLAGS) -o "$@" "$<"


UnscentedKalmanFilter.o : $(START_DIR)/UnscentedKalmanFilter.c
	$(CC) $(CFLAGS) -o "$@" "$<"


isSymmetricPositiveSemiDefinite.o : $(START_DIR)/isSymmetricPositiveSemiDefinite.c
	$(CC) $(CFLAGS) -o "$@" "$<"


minOrMax.o : $(START_DIR)/minOrMax.c
	$(CC) $(CFLAGS) -o "$@" "$<"


xnrm2.o : $(START_DIR)/xnrm2.c
	$(CC) $(CFLAGS) -o "$@" "$<"


xrot.o : $(START_DIR)/xrot.c
	$(CC) $(CFLAGS) -o "$@" "$<"


calcSigmaPoints.o : $(START_DIR)/calcSigmaPoints.c
	$(CC) $(CFLAGS) -o "$@" "$<"


xdotc.o : $(START_DIR)/xdotc.c
	$(CC) $(CFLAGS) -o "$@" "$<"


inv.o : $(START_DIR)/inv.c
	$(CC) $(CFLAGS) -o "$@" "$<"


xswap.o : $(START_DIR)/xswap.c
	$(CC) $(CFLAGS) -o "$@" "$<"


f_GLT.o : $(START_DIR)/f_GLT.c
	$(CC) $(CFLAGS) -o "$@" "$<"


cov.o : $(START_DIR)/cov.c
	$(CC) $(CFLAGS) -o "$@" "$<"


f_generate_online_UKF_residual_full_dwfix.o : $(START_DIR)/f_generate_online_UKF_residual_full_dwfix.c
	$(CC) $(CFLAGS) -o "$@" "$<"


f_compute_ukf_residual_fixdw.o : $(START_DIR)/f_compute_ukf_residual_fixdw.c
	$(CC) $(CFLAGS) -o "$@" "$<"


f_generate_online_parityRes1_full.o : $(START_DIR)/f_generate_online_parityRes1_full.c
	$(CC) $(CFLAGS) -o "$@" "$<"


f_generate_online_parityRes2_full.o : $(START_DIR)/f_generate_online_parityRes2_full.c
	$(CC) $(CFLAGS) -o "$@" "$<"


f_compute_parity_Res2_full.o : $(START_DIR)/f_compute_parity_Res2_full.c
	$(CC) $(CFLAGS) -o "$@" "$<"


svd.o : $(START_DIR)/svd.c
	$(CC) $(CFLAGS) -o "$@" "$<"


xaxpy.o : $(START_DIR)/xaxpy.c
	$(CC) $(CFLAGS) -o "$@" "$<"


xrotg.o : $(START_DIR)/xrotg.c
	$(CC) $(CFLAGS) -o "$@" "$<"


median.o : $(START_DIR)/median.c
	$(CC) $(CFLAGS) -o "$@" "$<"


quickselect.o : $(START_DIR)/quickselect.c
	$(CC) $(CFLAGS) -o "$@" "$<"


mode.o : $(START_DIR)/mode.c
	$(CC) $(CFLAGS) -o "$@" "$<"


sort.o : $(START_DIR)/sort.c
	$(CC) $(CFLAGS) -o "$@" "$<"


sortIdx.o : $(START_DIR)/sortIdx.c
	$(CC) $(CFLAGS) -o "$@" "$<"


var.o : $(START_DIR)/var.c
	$(CC) $(CFLAGS) -o "$@" "$<"


f_computeQL.o : $(START_DIR)/f_computeQL.c
	$(CC) $(CFLAGS) -o "$@" "$<"


f_comp_dw_ql_Rybaniec.o : $(START_DIR)/f_comp_dw_ql_Rybaniec.c
	$(CC) $(CFLAGS) -o "$@" "$<"


filter.o : $(START_DIR)/filter.c
	$(CC) $(CFLAGS) -o "$@" "$<"


diff.o : $(START_DIR)/diff.c
	$(CC) $(CFLAGS) -o "$@" "$<"


smoothdata.o : $(START_DIR)/smoothdata.c
	$(CC) $(CFLAGS) -o "$@" "$<"


repmat.o : $(START_DIR)/repmat.c
	$(CC) $(CFLAGS) -o "$@" "$<"


f_generate_and_eval_multi_residuals_dwql_emxutil.o : $(START_DIR)/f_generate_and_eval_multi_residuals_dwql_emxutil.c
	$(CC) $(CFLAGS) -o "$@" "$<"


f_generate_and_eval_multi_residuals_dwql_emxAPI.o : $(START_DIR)/f_generate_and_eval_multi_residuals_dwql_emxAPI.c
	$(CC) $(CFLAGS) -o "$@" "$<"


###########################################################################
## DEPENDENCIES
###########################################################################

$(ALL_OBJS) : rtw_proj.tmw $(MAKEFILE)


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



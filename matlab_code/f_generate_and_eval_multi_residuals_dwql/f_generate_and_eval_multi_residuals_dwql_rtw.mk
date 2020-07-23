###########################################################################
## Makefile generated for MATLAB file/project 'f_generate_and_eval_multi_residuals_dwql'. 
## 
## Makefile     : f_generate_and_eval_multi_residuals_dwql_rtw.mk
## Generated on : Mon Jul 20 17:32:23 2020
## MATLAB Coder version: 5.0 (R2020a)
## 
## Build Info:
## 
## Final product: ./f_generate_and_eval_multi_residuals_dwql.lib
## Product type : static-library
## 
###########################################################################

###########################################################################
## MACROS
###########################################################################

# Macro Descriptions:
# PRODUCT_NAME            Name of the system to build
# MAKEFILE                Name of this makefile
# CMD_FILE                Command file
# MODELLIB                Static library target

PRODUCT_NAME              = f_generate_and_eval_multi_residuals_dwql
MAKEFILE                  = f_generate_and_eval_multi_residuals_dwql_rtw.mk
MATLAB_ROOT               = C:/PROGRA~1/MATLAB/R2020a
MATLAB_BIN                = C:/PROGRA~1/MATLAB/R2020a/bin
MATLAB_ARCH_BIN           = $(MATLAB_BIN)/win64
MASTER_ANCHOR_DIR         = 
START_DIR                 = C:/Users/anawaz/Documents/MATLAB/Cavity_Fault_Detection_windows/CavityFaultDetection/Skripts_for_codegen/codegen/lib/f_generate_and_eval_multi_residuals_dwql
TGT_FCN_LIB               = None
SOLVER_OBJ                = 
CLASSIC_INTERFACE         = 0
MODEL_HAS_DYNAMICALLY_LOADED_SFCNS = 
RELATIVE_PATH_TO_ANCHOR   = .
CMD_FILE                  = f_generate_and_eval_multi_residuals_dwql_rtw.rsp
C_STANDARD_OPTS           = 
CPP_STANDARD_OPTS         = 
MODELLIB                  = f_generate_and_eval_multi_residuals_dwql.lib

###########################################################################
## TOOLCHAIN SPECIFICATIONS
###########################################################################

# Toolchain Name:          LCC-win64 v2.4.1 | gmake (64-bit Windows)
# Supported Version(s):    2.4.1
# ToolchainInfo Version:   2020a
# Specification Revision:  1.0
# 

#-----------
# MACROS
#-----------

SHELL              = cmd
LCC_ROOT           = $(MATLAB_ROOT)/sys/lcc64/lcc64
LCC_BUILDLIB       = $(LCC_ROOT)/bin/buildlib
LCC_LIB            = $(LCC_ROOT)/lib64
MW_EXTERNLIB_DIR   = $(MATLAB_ROOT)/extern/lib/win64/microsoft
MW_LIB_DIR         = $(MATLAB_ROOT)/lib/win64
TOOLCHAIN_INCLUDES = -I$(LCC_ROOT)/include64

TOOLCHAIN_SRCS = 
TOOLCHAIN_INCS = 
TOOLCHAIN_LIBS = 

#------------------------
# BUILD TOOL COMMANDS
#------------------------

# C Compiler: Lcc-win64 C Compiler
CC_PATH = $(LCC_ROOT)/bin
CC = "$(CC_PATH)/lcc64"

# Linker: Lcc-win64 Linker
LD_PATH = $(LCC_ROOT)/bin
LD = "$(LD_PATH)/lcclnk64"

# Archiver: Lcc-win64 Archiver
AR_PATH = $(LCC_ROOT)/bin
AR = "$(AR_PATH)/lcclib64"

# MEX Tool: MEX Tool
MEX_PATH = $(MATLAB_ARCH_BIN)
MEX = "$(MEX_PATH)/mex"

# Download: Download
DOWNLOAD =

# Execute: Execute
EXECUTE = $(PRODUCT)

# Builder: GMAKE Utility
MAKE_PATH = %MATLAB%\bin\win64
MAKE = "$(MAKE_PATH)/gmake"


#-------------------------
# Directives/Utilities
#-------------------------

CDEBUG              = -g
C_OUTPUT_FLAG       = -Fo
LDDEBUG             =
OUTPUT_FLAG         = -o
ARDEBUG             =
STATICLIB_OUTPUT_FLAG = /out:
MEX_DEBUG           = -g
RM                  = @del /F
ECHO                = @echo
MV                  = @move
RUN                 =

#--------------------------------------
# "Faster Runs" Build Configuration
#--------------------------------------

ARFLAGS              =
CFLAGS               = -c -w -noregistrylookup -nodeclspec -I$(LCC_ROOT)/include64
DOWNLOAD_FLAGS       =
EXECUTE_FLAGS        =
LDFLAGS              = -s -L$(LCC_LIB) $(LDFLAGS_ADDITIONAL)
MEX_CPPFLAGS         =
MEX_CPPLDFLAGS       =
MEX_CFLAGS           =
MEX_LDFLAGS          =
MAKE_FLAGS           = -f $(MAKEFILE)
SHAREDLIB_LDFLAGS    = -dll -entry LibMain -s -L$(LCC_LIB) $(LDFLAGS_ADDITIONAL) $(DEF_FILE)



###########################################################################
## OUTPUT INFO
###########################################################################

PRODUCT = ./f_generate_and_eval_multi_residuals_dwql.lib
PRODUCT_TYPE = "static-library"
BUILD_TYPE = "Static Library"

###########################################################################
## INCLUDE PATHS
###########################################################################

INCLUDES_BUILDINFO = -I$(START_DIR) -IC:/Users/anawaz/DOCUME~1/MATLAB/CAVITY~2/CAVITY~1/SKRIPT~1 -I$(MATLAB_ROOT)/extern/include

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

OBJS = rt_nonfinite.obj rtGetNaN.obj rtGetInf.obj f_generate_and_eval_multi_residuals_dwql_rtwutil.obj f_generate_and_eval_multi_residuals_dwql_data.obj f_generate_and_eval_multi_residuals_dwql_initialize.obj f_generate_and_eval_multi_residuals_dwql_terminate.obj f_generate_and_eval_multi_residuals_dwql.obj colon.obj find.obj mean.obj f_generate_online_UKF_residual_full.obj exp.obj f_calibrateData.obj f_compute_ukf_residual_not_pers.obj f_cavitySystem.obj UnscentedKalmanFilter.obj isSymmetricPositiveSemiDefinite.obj minOrMax.obj xnrm2.obj xrot.obj calcSigmaPoints.obj xdotc.obj inv.obj xswap.obj f_GLT.obj cov.obj f_generate_online_UKF_residual_full_dwfix.obj f_compute_ukf_residual_fixdw.obj f_generate_online_parityRes1_full.obj f_generate_online_parityRes2_full.obj f_compute_parity_Res2_full.obj svd.obj xaxpy.obj xrotg.obj median.obj quickselect.obj mode.obj sort.obj sortIdx.obj var.obj f_computeQL.obj f_comp_dw_ql_Rybaniec.obj filter.obj diff.obj smoothdata.obj repmat.obj f_generate_and_eval_multi_residuals_dwql_emxutil.obj f_generate_and_eval_multi_residuals_dwql_emxAPI.obj

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

SYSTEM_LIBS = 

###########################################################################
## ADDITIONAL TOOLCHAIN FLAGS
###########################################################################

#---------------
# C Compiler
#---------------

CFLAGS_BASIC = $(DEFINES) $(INCLUDES)

CFLAGS += $(CFLAGS_BASIC)

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
	$(AR) $(ARFLAGS) /out:$(PRODUCT) @$(CMD_FILE)
	@echo "### Created: $(PRODUCT)"


###########################################################################
## INTERMEDIATE TARGETS
###########################################################################

#---------------------
# SOURCE-TO-OBJECT
#---------------------

%.obj : %.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


%.obj : $(RELATIVE_PATH_TO_ANCHOR)/%.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


%.obj : $(START_DIR)/%.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


%.obj : C:/Users/anawaz/Documents/MATLAB/Cavity_Fault_Detection_windows/CavityFaultDetection/Skripts_for_codegen/%.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


rt_nonfinite.obj : $(START_DIR)/rt_nonfinite.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


rtGetNaN.obj : $(START_DIR)/rtGetNaN.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


rtGetInf.obj : $(START_DIR)/rtGetInf.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


f_generate_and_eval_multi_residuals_dwql_rtwutil.obj : $(START_DIR)/f_generate_and_eval_multi_residuals_dwql_rtwutil.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


f_generate_and_eval_multi_residuals_dwql_data.obj : $(START_DIR)/f_generate_and_eval_multi_residuals_dwql_data.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


f_generate_and_eval_multi_residuals_dwql_initialize.obj : $(START_DIR)/f_generate_and_eval_multi_residuals_dwql_initialize.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


f_generate_and_eval_multi_residuals_dwql_terminate.obj : $(START_DIR)/f_generate_and_eval_multi_residuals_dwql_terminate.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


f_generate_and_eval_multi_residuals_dwql.obj : $(START_DIR)/f_generate_and_eval_multi_residuals_dwql.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


colon.obj : $(START_DIR)/colon.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


find.obj : $(START_DIR)/find.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


mean.obj : $(START_DIR)/mean.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


f_generate_online_UKF_residual_full.obj : $(START_DIR)/f_generate_online_UKF_residual_full.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


exp.obj : $(START_DIR)/exp.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


f_calibrateData.obj : $(START_DIR)/f_calibrateData.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


f_compute_ukf_residual_not_pers.obj : $(START_DIR)/f_compute_ukf_residual_not_pers.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


f_cavitySystem.obj : $(START_DIR)/f_cavitySystem.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


UnscentedKalmanFilter.obj : $(START_DIR)/UnscentedKalmanFilter.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


isSymmetricPositiveSemiDefinite.obj : $(START_DIR)/isSymmetricPositiveSemiDefinite.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


minOrMax.obj : $(START_DIR)/minOrMax.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


xnrm2.obj : $(START_DIR)/xnrm2.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


xrot.obj : $(START_DIR)/xrot.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


calcSigmaPoints.obj : $(START_DIR)/calcSigmaPoints.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


xdotc.obj : $(START_DIR)/xdotc.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


inv.obj : $(START_DIR)/inv.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


xswap.obj : $(START_DIR)/xswap.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


f_GLT.obj : $(START_DIR)/f_GLT.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


cov.obj : $(START_DIR)/cov.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


f_generate_online_UKF_residual_full_dwfix.obj : $(START_DIR)/f_generate_online_UKF_residual_full_dwfix.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


f_compute_ukf_residual_fixdw.obj : $(START_DIR)/f_compute_ukf_residual_fixdw.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


f_generate_online_parityRes1_full.obj : $(START_DIR)/f_generate_online_parityRes1_full.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


f_generate_online_parityRes2_full.obj : $(START_DIR)/f_generate_online_parityRes2_full.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


f_compute_parity_Res2_full.obj : $(START_DIR)/f_compute_parity_Res2_full.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


svd.obj : $(START_DIR)/svd.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


xaxpy.obj : $(START_DIR)/xaxpy.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


xrotg.obj : $(START_DIR)/xrotg.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


median.obj : $(START_DIR)/median.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


quickselect.obj : $(START_DIR)/quickselect.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


mode.obj : $(START_DIR)/mode.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


sort.obj : $(START_DIR)/sort.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


sortIdx.obj : $(START_DIR)/sortIdx.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


var.obj : $(START_DIR)/var.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


f_computeQL.obj : $(START_DIR)/f_computeQL.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


f_comp_dw_ql_Rybaniec.obj : $(START_DIR)/f_comp_dw_ql_Rybaniec.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


filter.obj : $(START_DIR)/filter.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


diff.obj : $(START_DIR)/diff.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


smoothdata.obj : $(START_DIR)/smoothdata.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


repmat.obj : $(START_DIR)/repmat.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


f_generate_and_eval_multi_residuals_dwql_emxutil.obj : $(START_DIR)/f_generate_and_eval_multi_residuals_dwql_emxutil.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


f_generate_and_eval_multi_residuals_dwql_emxAPI.obj : $(START_DIR)/f_generate_and_eval_multi_residuals_dwql_emxAPI.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


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
	$(RM) $(subst /,\,$(PRODUCT))
	$(RM) $(subst /,\,$(ALL_OBJS))
	$(ECHO) "### Deleted all derived files."



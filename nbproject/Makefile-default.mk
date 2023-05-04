#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/bldc_01.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/bldc_01.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=main.c adc.c bridge.c IntADCp7.c current_controller.c buck_converter.c pins_config.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/main.o ${OBJECTDIR}/adc.o ${OBJECTDIR}/bridge.o ${OBJECTDIR}/IntADCp7.o ${OBJECTDIR}/current_controller.o ${OBJECTDIR}/buck_converter.o ${OBJECTDIR}/pins_config.o
POSSIBLE_DEPFILES=${OBJECTDIR}/main.o.d ${OBJECTDIR}/adc.o.d ${OBJECTDIR}/bridge.o.d ${OBJECTDIR}/IntADCp7.o.d ${OBJECTDIR}/current_controller.o.d ${OBJECTDIR}/buck_converter.o.d ${OBJECTDIR}/pins_config.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/main.o ${OBJECTDIR}/adc.o ${OBJECTDIR}/bridge.o ${OBJECTDIR}/IntADCp7.o ${OBJECTDIR}/current_controller.o ${OBJECTDIR}/buck_converter.o ${OBJECTDIR}/pins_config.o

# Source Files
SOURCEFILES=main.c adc.c bridge.c IntADCp7.c current_controller.c buck_converter.c pins_config.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/bldc_01.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MK1024MCF064
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/baee18b5a5e6f0481d7aae6c2462ed7772b5dc0c .generated_files/flags/default/c0d105b5fb21a2d6a1a1391cf0024b1662afb238
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/adc.o: adc.c  .generated_files/flags/default/70b009b26ff9f086f3eca5dd3f87b748f20f6f5b .generated_files/flags/default/c0d105b5fb21a2d6a1a1391cf0024b1662afb238
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/adc.o.d 
	@${RM} ${OBJECTDIR}/adc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/adc.o.d" -o ${OBJECTDIR}/adc.o adc.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/bridge.o: bridge.c  .generated_files/flags/default/be45ae89b92bde49869081297669884dd68b7eb2 .generated_files/flags/default/c0d105b5fb21a2d6a1a1391cf0024b1662afb238
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/bridge.o.d 
	@${RM} ${OBJECTDIR}/bridge.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/bridge.o.d" -o ${OBJECTDIR}/bridge.o bridge.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/IntADCp7.o: IntADCp7.c  .generated_files/flags/default/817e3cf4c33bf0a9b69531ae1801a4deb4ff2325 .generated_files/flags/default/c0d105b5fb21a2d6a1a1391cf0024b1662afb238
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/IntADCp7.o.d 
	@${RM} ${OBJECTDIR}/IntADCp7.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/IntADCp7.o.d" -o ${OBJECTDIR}/IntADCp7.o IntADCp7.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/current_controller.o: current_controller.c  .generated_files/flags/default/f4d9905f75251bf1d2af384be59db2db105cc239 .generated_files/flags/default/c0d105b5fb21a2d6a1a1391cf0024b1662afb238
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/current_controller.o.d 
	@${RM} ${OBJECTDIR}/current_controller.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/current_controller.o.d" -o ${OBJECTDIR}/current_controller.o current_controller.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/buck_converter.o: buck_converter.c  .generated_files/flags/default/ea56927b24c6cbdfccae39d251315028409710e4 .generated_files/flags/default/c0d105b5fb21a2d6a1a1391cf0024b1662afb238
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/buck_converter.o.d 
	@${RM} ${OBJECTDIR}/buck_converter.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/buck_converter.o.d" -o ${OBJECTDIR}/buck_converter.o buck_converter.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/pins_config.o: pins_config.c  .generated_files/flags/default/36a03c0116b7ea92eba8e6922cf594db53579daa .generated_files/flags/default/c0d105b5fb21a2d6a1a1391cf0024b1662afb238
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/pins_config.o.d 
	@${RM} ${OBJECTDIR}/pins_config.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/pins_config.o.d" -o ${OBJECTDIR}/pins_config.o pins_config.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/25f5b2062fbc7405c960a37b8e9551e4bccdfb84 .generated_files/flags/default/c0d105b5fb21a2d6a1a1391cf0024b1662afb238
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/adc.o: adc.c  .generated_files/flags/default/d82e8446015fd2a119aa93e2a7151029bbbec819 .generated_files/flags/default/c0d105b5fb21a2d6a1a1391cf0024b1662afb238
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/adc.o.d 
	@${RM} ${OBJECTDIR}/adc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/adc.o.d" -o ${OBJECTDIR}/adc.o adc.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/bridge.o: bridge.c  .generated_files/flags/default/6cf18aa531e65fe69084ad0cae9c21d76c4681d1 .generated_files/flags/default/c0d105b5fb21a2d6a1a1391cf0024b1662afb238
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/bridge.o.d 
	@${RM} ${OBJECTDIR}/bridge.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/bridge.o.d" -o ${OBJECTDIR}/bridge.o bridge.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/IntADCp7.o: IntADCp7.c  .generated_files/flags/default/2d19e0e11c360fd2b95766402d05b3b4f591f9d5 .generated_files/flags/default/c0d105b5fb21a2d6a1a1391cf0024b1662afb238
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/IntADCp7.o.d 
	@${RM} ${OBJECTDIR}/IntADCp7.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/IntADCp7.o.d" -o ${OBJECTDIR}/IntADCp7.o IntADCp7.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/current_controller.o: current_controller.c  .generated_files/flags/default/8d7765cdd6c1819bc3be39ae36834b74374ec3ef .generated_files/flags/default/c0d105b5fb21a2d6a1a1391cf0024b1662afb238
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/current_controller.o.d 
	@${RM} ${OBJECTDIR}/current_controller.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/current_controller.o.d" -o ${OBJECTDIR}/current_controller.o current_controller.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/buck_converter.o: buck_converter.c  .generated_files/flags/default/13fb8024d2a0c7b9e1708a1844191c0962d86fec .generated_files/flags/default/c0d105b5fb21a2d6a1a1391cf0024b1662afb238
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/buck_converter.o.d 
	@${RM} ${OBJECTDIR}/buck_converter.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/buck_converter.o.d" -o ${OBJECTDIR}/buck_converter.o buck_converter.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/pins_config.o: pins_config.c  .generated_files/flags/default/ed16ee479b24296a02767003ab309b456aebaf9a .generated_files/flags/default/c0d105b5fb21a2d6a1a1391cf0024b1662afb238
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/pins_config.o.d 
	@${RM} ${OBJECTDIR}/pins_config.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/pins_config.o.d" -o ${OBJECTDIR}/pins_config.o pins_config.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/bldc_01.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g   -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/bldc_01.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)   -mreserve=data@0x0:0x36F   -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=_min_heap_size=2048,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	
else
${DISTDIR}/bldc_01.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/bldc_01.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=2048,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	${MP_CC_DIR}\\xc32-bin2hex ${DISTDIR}/bldc_01.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif

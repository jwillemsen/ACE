# -*- makefile -*-
#----------------------------------------------------------------------------
#       GNU ACE Workspace
#
# $Id: GNUACEWorkspaceCreator.pm 94635 2011-10-06 12:59:23Z johnnyw $
#
# This file was generated by MPC.  Any changes made directly to
# this file will be lost the next time it is generated.
#
# MPC Command:
# /home/build/DOC_ROOT/stage-644/ACE_wrappers/bin/mwc.pl -type gnuace -exclude "TAO/TAO_*.mwc,TAO/CIAO/CIAO_*.mwc" -workers 10 -recurse -hierarchy -relative ACE_ROOT=/home/build/DOC_ROOT/stage-644/ACE_wrappers -relative TAO_ROOT=/home/build/DOC_ROOT/stage-644/ACE_wrappers/TAO -relative CIAO_ROOT=/home/build/DOC_ROOT/stage-644/ACE_wrappers/TAO/CIAO -relative DANCE_ROOT=/home/build/DOC_ROOT/stage-644/ACE_wrappers/TAO/DAnCE
#
#----------------------------------------------------------------------------

MAKEFILE = GNUmakefile

ifeq ($(findstring k,$(MAKEFLAGS)),k)
  KEEP_GOING = -
endif

include $(ACE_ROOT)/include/makeinclude/macros.GNU

all: Struct_Multi_Filter_Idl Struct_Multi_Filter_Ntf_Struct_Cons Struct_Multi_Filter_Ntf_Struct_Supp

REMAINING_TARGETS := $(filter-out all,$(TARGETS_NESTED:.nested=)) $(CUSTOM_TARGETS)

$(REMAINING_TARGETS):
	$(KEEP_GOING)@$(MAKE) -f GNUmakefile.Struct_Multi_Filter_Idl $(@)
	$(KEEP_GOING)@$(MAKE) -f GNUmakefile.Struct_Multi_Filter_Ntf_Struct_Cons $(@)
	$(KEEP_GOING)@$(MAKE) -f GNUmakefile.Struct_Multi_Filter_Ntf_Struct_Supp $(@)

.PHONY: Struct_Multi_Filter_Idl
Struct_Multi_Filter_Idl:
	$(KEEP_GOING)@$(MAKE) -f GNUmakefile.Struct_Multi_Filter_Idl all

.PHONY: Struct_Multi_Filter_Ntf_Struct_Cons
Struct_Multi_Filter_Ntf_Struct_Cons: Struct_Multi_Filter_Idl
	$(KEEP_GOING)@$(MAKE) -f GNUmakefile.Struct_Multi_Filter_Ntf_Struct_Cons all

.PHONY: Struct_Multi_Filter_Ntf_Struct_Supp
Struct_Multi_Filter_Ntf_Struct_Supp: Struct_Multi_Filter_Idl Struct_Multi_Filter_Ntf_Struct_Cons
	$(KEEP_GOING)@$(MAKE) -f GNUmakefile.Struct_Multi_Filter_Ntf_Struct_Supp all

project_name_list:
	@echo Struct_Multi_Filter_Idl
	@echo Struct_Multi_Filter_Ntf_Struct_Cons
	@echo Struct_Multi_Filter_Ntf_Struct_Supp

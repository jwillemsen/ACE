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

all: CosEvent_Basic_Disconnect CosEvent_Basic_MT_Disconnect CosEvent_Basic_Pull_Push_Event CosEvent_Basic_Push_Event CosEvent_Basic_Random CosEvent_Basic_Shutdown

REMAINING_TARGETS := $(filter-out all,$(TARGETS_NESTED:.nested=)) $(CUSTOM_TARGETS)

$(REMAINING_TARGETS):
	$(KEEP_GOING)@$(MAKE) -f GNUmakefile.CosEvent_Basic_Disconnect $(@)
	$(KEEP_GOING)@$(MAKE) -f GNUmakefile.CosEvent_Basic_MT_Disconnect $(@)
	$(KEEP_GOING)@$(MAKE) -f GNUmakefile.CosEvent_Basic_Pull_Push_Event $(@)
	$(KEEP_GOING)@$(MAKE) -f GNUmakefile.CosEvent_Basic_Push_Event $(@)
	$(KEEP_GOING)@$(MAKE) -f GNUmakefile.CosEvent_Basic_Random $(@)
	$(KEEP_GOING)@$(MAKE) -f GNUmakefile.CosEvent_Basic_Shutdown $(@)

.PHONY: CosEvent_Basic_Disconnect
CosEvent_Basic_Disconnect:
	$(KEEP_GOING)@$(MAKE) -f GNUmakefile.CosEvent_Basic_Disconnect all

.PHONY: CosEvent_Basic_MT_Disconnect
CosEvent_Basic_MT_Disconnect:
	$(KEEP_GOING)@$(MAKE) -f GNUmakefile.CosEvent_Basic_MT_Disconnect all

.PHONY: CosEvent_Basic_Pull_Push_Event
CosEvent_Basic_Pull_Push_Event:
	$(KEEP_GOING)@$(MAKE) -f GNUmakefile.CosEvent_Basic_Pull_Push_Event all

.PHONY: CosEvent_Basic_Push_Event
CosEvent_Basic_Push_Event:
	$(KEEP_GOING)@$(MAKE) -f GNUmakefile.CosEvent_Basic_Push_Event all

.PHONY: CosEvent_Basic_Random
CosEvent_Basic_Random:
	$(KEEP_GOING)@$(MAKE) -f GNUmakefile.CosEvent_Basic_Random all

.PHONY: CosEvent_Basic_Shutdown
CosEvent_Basic_Shutdown:
	$(KEEP_GOING)@$(MAKE) -f GNUmakefile.CosEvent_Basic_Shutdown all

project_name_list:
	@echo CosEvent_Basic_Disconnect
	@echo CosEvent_Basic_MT_Disconnect
	@echo CosEvent_Basic_Pull_Push_Event
	@echo CosEvent_Basic_Push_Event
	@echo CosEvent_Basic_Random
	@echo CosEvent_Basic_Shutdown

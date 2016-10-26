# $Revision: 1.4 $$Date: 2003/09/22 14:06:09 $$Author: wsnyder $ -*- Makefile -*-
#*****************************************************************************
#
# DESCRIPTION: Verilator Example: Makefile for inside object directory
#
# This executed in the object directory, and called by ../Makefile
#
# Copyright 2004 by Wilson Snyder. This program is free software; you can
# redistribute it and/or modify it under the terms of either the GNU
# General Public License or the Perl Artistic License.
#
#*****************************************************************************

default:
	@echo "Please run 'make v3', 'make nc', 'make vcs', or 'make icarus'"
	false

PWD := $(shell pwd)

COMMON_FLAGS = -f ../input.vc
NC_FLAGS  = +ncsimargs+-status +nowarn+LIBNOU -q ../bench/bench.v
VCS_FLAGS = +twostate \
		+define+vcs+1 ../bench/bench.v
V3_FLAGS  = --cc ../bench/k68_soc_test.v --exe $(PWD)/../bench/bench.cpp  -prefix m68 -Wno-WIDTH \
	-O3 -x-assign 0
ICARUS_FLAGS = -o simi -y ../bench -y ../rtl -y \
	-I../bench -I../rtl \
	../bench/bench.v
VBS_FLAGS = -o simi -y ../bench -y ../rtl -y \
	-I../bench -I../rtl \
	../bench/bench.v

######################################################################

M32 = -m64
CPPFLAGS += $(M32)
LDFLAGS += $(M32)
# +~5% with -O3
OPT_FAST = $(M32) -O3

#OPT_FAST += -ggdb -fverbose-asm -S
#OPT_FAST += -pg
OPT_SLOW = $(OPT_FAST)
#LDFLAGS += -pg
export OPT_FAST
export OPT_SLOW
export LDFLAGS

v3:  v3_v v3_compile v3_sim
v3_v: 
	$(VERILATOR_ROOT)/bin/verilator $(V3_FLAGS) $(COMMON_FLAGS)
v3_compile:
	( cd obj_dir ; make -f m68.mk )
v3_sim:
	time obj_dir/m68  10000000

m68.gprof:  v3
	gprof obj_dir/m68 > $@

v3_waves:
	$(VERILATOR_ROOT)/bin/verilator --trace $(V3_FLAGS) $(COMMON_FLAGS)
	( cd obj_dir ; make -f m68.mk )
	time obj_dir/m68 -l sim.log

######################################################################

novcs:
	@echo "No VCS simulator installed."
	@echo "Not running VCS regression test."

vcs:
	vcs $(VCS_FLAGS) $(COMMON_FLAGS)
	time ./simv -l sim.log

vcs_waves:
	vcs +cli -I $(VCS_FLAGS) $(COMMON_FLAGS)
	time ./simv -l sim.log

######################################################################

nonc:
	@echo "No NC-Verilog simulator installed."
	@echo "Not running NC-Verilog regression test."

nc:
	time ncverilog $(NC_FLAGS) $(COMMON_FLAGS)

nc_waves:
	time ncverilog +access+rc $(NC_FLAGS) $(COMMON_FLAGS)

######################################################################

noicarus:
	@echo "No Icarus-Verilog simulator installed."
	@echo "Not running Icarus-Verilog regression test."

icarus:
	time iverilog $(ICARUS_FLAGS)
	time vvp simi

######################################################################

novbs:
	@echo "No Vbs simulator installed."
	@echo "Not running Vbs regression test."

vbs: 
	@echo "Need .vpp files made by v3"
	time vbs obj_dir/*.vpp

######################################################################

maintainer-copy::
clean mostlyclean distclean maintainer-clean::
	-rm -rf obj_dir *.log *.dmp *.vpd simv* vcs.key csrc INCA_libs simi


#!/bin/sh 
# install test procedures

args=$#

if test $args = "0"; then
  OS="lnx32"
  if which cvc >& /dev/null; then
    CVC="cvc -q"
  elif test -f /tmp/cvc; then
    CVC="/tmp/cvc -q"
  else
   echo "ERROR - there is no cvc on PATH or in /tmp"
   exit 1
  fi
else 
 if test $1 != "cvc64"; then 
   echo "ERROR - only option is 'cvc64' to run 64-bit otherwise leave empty for 32-bit CVC"
   exit 2
  else
  OS="lnx64"
  if which cvc64 >& /dev/null; then
    CVC="cvc64 -q"
  elif test -f /tmp/cvc64; then
    CVC="/tmp/cvc64 -q"
  else
   echo "ERROR - there is no cvc on PATH or in /tmp"
   exit 1
  fi
  fi
fi


make -f makefile.$OS vhello1.so
$CVC -q +loadvpi=./vhello1:vpi_compat_bootstrap vhello1.v >/dev/null
if test ! -f cvcsim
then
 echo "ERROR - compiling test1" 
 echo "Run 'checkcvc' from bin to check configuration"
 exit;
fi
./cvcsim >&/dev/null
rm cvcsim
./rmlic.pl
diff verilog.log vhello1.plg
rm vhello1.so vhello1.o

make -f makefile.$OS vhello2.so
$CVC -q +loadvpi=./vhello2:vpi_compat_bootstrap vhello2.v >/dev/null
if test ! -f cvcsim
then
 echo "ERROR - compiling test2" 
 echo "Run 'checkcvc' from bin to check configuration"
 exit;
fi
./cvcsim >&/dev/null
rm cvcsim
./rmlic.pl
diff verilog.log vhello2.plg
rm vhello2.so vhello2.o


#this one is end of compile time startup so nothing to diff
#make -f makefile.$OS vhelbad.so
#$CVC -q +loadvpi=./vhelbad:vpi_compat_bootstrap vhelbad.v >/dev/null
#if test ! -f cvcsim
#then
# echo "ERROR - compiling test3" 
# echo "Run 'checkcvc' from bin to check configuration"
# exit;
#fi
#./cvcsim >&/dev/null
#./rmlic.pl
#diff verilog.log vhelbad.plg
#rm vhelbad.so vhelbad.o

make -f makefile.$OS findcaus.so
$CVC -q +loadvpi=./findcaus:vpi_compat_bootstrap task10.v >/dev/null
if test ! -f cvcsim
then
 echo "ERROR - compiling test4" 
 echo "Run 'checkcvc' from bin to check configuration"
 exit;
fi
./cvcsim >&/dev/null
rm cvcsim
./rmlic.pl
diff verilog.log findcaus.plg
rm findcaus.so findcaus.o

make -f makefile.$OS vprtchg.so
$CVC +acc+2 -q +loadvpi=./vprtchg:vpi_compat_bootstrap  task10.v >/dev/null
if test ! -f cvcsim
then
 echo "ERROR - compiling test5" 
 echo "Run 'checkcvc' from bin to check configuration"
 exit;
fi
./cvcsim >&/dev/null
rm cvcsim
./rmlic.pl
diff verilog.log vprtchg.plg
rm vprtchg.so vprtchg.o 

make -f makefile.$OS vprtchg2.so
$CVC +acc+2 -q +loadvpi=./vprtchg2:vpi_compat_bootstrap task10.v >/dev/null
if test ! -f cvcsim
then
 echo "ERROR - compiling test6" 
 echo "Run 'checkcvc' from bin to check configuration"
 exit;
fi
./cvcsim >&/dev/null
rm cvcsim
./rmlic.pl
diff verilog.log vprtchg2.plg
rm vprtchg2.so vprtchg2.o

make -f makefile.$OS vprtchg3.so
$CVC +acc+2 -q +loadvpi=./vprtchg3:vpi_compat_bootstrap task10.v >/dev/null
if test ! -f cvcsim
then
 echo "ERROR - compiling test7" 
 echo "Run 'checkcvc' from bin to check configuration"
 exit;
fi
./cvcsim >&/dev/null
rm cvcsim
./rmlic.pl
diff verilog.log vprtchg3.plg
rm vprtchg3.so vprtchg3.o

make -f makefile.$OS vprtdels.so
$CVC -q +loadvpi=./vprtdels:vpi_compat_bootstrap fdspec01.v >/dev/null
if test ! -f cvcsim
then
 echo "ERROR - compiling test8" 
 echo "Run 'checkcvc' from bin to check configuration"
 exit;
fi
./cvcsim >&/dev/null
rm cvcsim
./rmlic.pl
diff verilog.log vprtdels.plg
rm vprtdels.so vprtdels.o

make -f makefile.$OS vprtdel2.so
$CVC -q +loadvpi=./vprtdel2:vpi_compat_bootstrap timtst03.v >/dev/null
if test ! -f cvcsim
then
 echo "ERROR - compiling test9" 
 echo "Run 'checkcvc' from bin to check configuration"
 exit;
fi
./cvcsim >&/dev/null
rm cvcsim
./rmlic.pl
diff verilog.log vprtdel2.plg
rm vprtdel2.so vprtdel2.o

make -f makefile.$OS vsetdels.so
$CVC -q +loadvpi=./vsetdels:vpi_compat_bootstrap fdspec01.v >/dev/null
if test ! -f cvcsim
then
 echo "ERROR - compiling test10" 
 echo "Run 'checkcvc' from bin to check configuration"
 exit;
fi
./cvcsim >&/dev/null
rm cvcsim
./rmlic.pl
diff verilog.log vsetdels.plg
rm vsetdels.so vsetdels.o

make -f makefile.$OS vsetval2.so
$CVC -q +loadvpi=./vsetval2:vpi_compat_bootstrap vsetval2.v >/dev/null
if test ! -f cvcsim
then
 echo "ERROR - compiling test11" 
 echo "Run 'checkcvc' from bin to check configuration"
 exit;
fi
./cvcsim >&/dev/null
rm cvcsim
./rmlic.pl
diff verilog.log vsetval2.plg
rm vsetval2.so vsetval2.o

#make -f makefile.$OS vtimcbs.so
#$CVC +acc+1 -q +loadvpi=./vtimcbs:vpi_compat_bootstrap task10.v >/dev/null
#./rmlic.pl
#diff verilog.log vtimcbs.plg
#rm vtimcbs.so vtimcbs.o 

make -f makefile.$OS vfopen1.so
$CVC +acc+1 -q +loadvpi=./vfopen1:vpi_compat_bootstrap vfopen1.v >/dev/null
if test ! -f cvcsim
then
 echo "ERROR - compiling test12" 
 echo "Run 'checkcvc' from bin to check configuration"
 exit;
fi
./cvcsim >&/dev/null
rm cvcsim
./rmlic.pl
diff verilog.log vfopen1.plg
diff vpifout.fil vpifout.xfl
rm vfopen1.so vfopen1.o

make -f makefile.$OS vfopen2.so
$CVC -q +loadvpi=./vfopen2:vpi_compat_bootstrap vfopen2.v >/dev/null
if test ! -f cvcsim
then
 echo "ERROR - compiling test13" 
 echo "Run 'checkcvc' from bin to check configuration"
 exit;
fi
./cvcsim >&/dev/null
rm cvcsim
./rmlic.pl
diff verilog.log vfopen2.plg
diff vpitout.fil vpitout.xfl
rm vfopen2.so vfopen2.o

make -f makefile.$OS vconta1.so
$CVC -q +loadvpi=./vconta1:vpi_compat_bootstrap cacatmd1.v >/dev/null
if test ! -f cvcsim
then
 echo "ERROR - compiling test14" 
 echo "Run 'checkcvc' from bin to check configuration"
 exit;
fi
./cvcsim >&/dev/null
rm cvcsim
./rmlic.pl
diff verilog.log vconta1.plg
rm vconta1.so vconta1.o

make -f makefile.$OS vchkprt1.so
$CVC -q +loadvpi=./vchkprt1:vpi_compat_bootstrap prtbg09.v >/dev/null
if test ! -f cvcsim
then
 echo "ERROR - compiling test15" 
 echo "Run 'checkcvc' from bin to check configuration"
 exit;
fi
./cvcsim >&/dev/null
rm cvcsim
# cannot compare verilog.log because has vpi_get_vlog_info
diff fff9 fff9.exp
rm vchkprt1.so vchkprt1.o

# SJM 09-15-12  - added variant of vchkprt1 that calls vpi_check_error 
make -f makefile.$OS vchkprt2.so
$CVC -q +loadvpi=./vchkprt2:vpi_compat_bootstrap prtbg09.v >/dev/null
if test ! -f cvcsim
then
 echo "ERROR - compiling test15a" 
 echo "Run 'checkcvc' from bin to check configuration"
 exit;
fi
./cvcsim >&/dev/null
rm cvcsim
# cannot compare verilog.log because has vpi_get_vlog_info
diff fff9 fff9.exp
rm vchkprt2.so vchkprt2.o

make -f makefile.$OS vdrvld1.so
$CVC -q +loadvpi=./vdrvld1:vpi_compat_bootstrap fdspec01.v >/dev/null
if test ! -f cvcsim
then
 echo "ERROR - compiling test16" 
 echo "Run 'checkcvc' from bin to check configuration"
 exit;
fi
./cvcsim >&/dev/null
rm cvcsim
./rmlic.pl
diff verilog.log vdrvld1.plg
rm vdrvld1.so vdrvld1.o

make -f makefile.$OS vdrvld2.so
$CVC -q +loadvpi=./vdrvld2:vpi_compat_bootstrap cacatmd1.v >/dev/null
if test ! -f cvcsim
then
 echo "ERROR - compiling test17" 
 echo "Run 'checkcvc' from bin to check configuration"
 exit;
fi
./cvcsim >&/dev/null
rm cvcsim
./rmlic.pl
diff verilog.log vdrvld2.plg
rm vdrvld2.so vdrvld2.o

#make -f makefile.$OS dfpsetd.so
#$CVC +acc+1 -q +loadvpi=./dfpsetd:vpi_compat_bootstrap dfpsetd.v >/dev/null
#./rmlic.pl
#diff verilog.log dfpsetd.plg
#rm dfpsetd.so dfpsetd.o

echo ">>>> PLI 2.0 Install test Finished - no diff differences should be printed."
echo " "

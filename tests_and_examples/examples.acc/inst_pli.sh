#!/bin/sh 
# install test procedures

# pass name for your OS as argument to shell script
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

make -f makefile.$OS acc_probe.so
$CVC +acc+2 -q +loadpli1=./acc_probe:pli1_compat_bootstrap probe.v >/dev/null
if test ! -f cvcsim
then
 echo "ERROR - compiling test1" 
 echo "Run 'checkcvc' from bin to check configuration"
 exit;
fi
./cvcsim >&/dev/null
rm cvcsim
./rmlic.pl
diff verilog.log acc_probe.plg
rm acc_probe.so acc_probe.o 

make -f makefile.$OS acc_nxtchld.so
$CVC -q +loadpli1=./acc_nxtchld:pli1_compat_bootstrap nc_fdsp.v >/dev/null
if test ! -f cvcsim
then
 echo "ERROR - compiling test2" 
 echo "Run 'checkcvc' from bin to check configuration"
 exit;
fi
./cvcsim >&/dev/null
rm cvcsim
./rmlic.pl
diff verilog.log acc_nxtchld.plg
rm acc_nxtchld.so acc_nxtchld.o

make -f makefile.$OS accxl_drvld.so
$CVC -q +loadpli1=./accxl_drvld:pli1_compat_bootstrap accxldrvtst.v >/dev/null
if test ! -f cvcsim
then
 echo "ERROR - compiling test3" 
 echo "Run 'checkcvc' from bin to check configuration"
 exit;
fi
./cvcsim >&/dev/null
rm cvcsim
./rmlic.pl
diff verilog.log accxldrvtst.plg
rm accxl_drvld.so accxl_drvld.o 

make -f makefile.$OS acc_prtchg.so
$CVC +acc+2 -q +loadpli1=./acc_prtchg:pli1_compat_bootstrap pchg_fdsp.v >/dev/null
if test ! -f cvcsim
then
 echo "ERROR - compiling test4" 
 echo "Run 'checkcvc' from bin to check configuration"
 exit;
fi
./cvcsim >&/dev/null
rm cvcsim
./rmlic.pl
diff verilog.log pchg_fdsp.plg
rm acc_prtchg.so acc_prtchg.o 

echo ">>>> acc_ test Finished - no diff differences should be printed."
echo " "

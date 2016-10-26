#!/bin/sh 
# install test procedures


args=$#

if test $args = "0"; then
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


#test xif.v
$CVC +xprop xif.v >/dev/null
if test ! -f cvcsim
then
 echo "ERROR - compiling xif.v -" 
 echo "Run 'checkcvc' from bin to check configuration"
 exit;
fi
./cvcsim >/dev/null
rm cvcsim
./rmlic.pl
diff verilog.log xif.plg

#test xcase.v
$CVC +xprop xcase.v >/dev/null
if test ! -f cvcsim
then
 echo "ERROR - compiling xcase.v -" 
 echo "Run 'checkcvc' from bin to check configuration"
 exit;
fi
./cvcsim >/dev/null
rm cvcsim
./rmlic.pl
diff verilog.log xcase.plg

#test xnested.v
$CVC +xprop xnested.v >/dev/null
if test ! -f cvcsim
then
 echo "ERROR - compiling xnested.v -" 
 echo "Run 'checkcvc' from bin to check configuration"
 exit;
fi
./cvcsim >/dev/null
rm cvcsim
./rmlic.pl
diff verilog.log xnested.plg

#test xtrace.v
$CVC +xtrace +xprop xtrace.v >/dev/null
if test ! -f cvcsim
then
 echo "ERROR - compiling xtrace.v -" 
 echo "Run 'checkcvc' from bin to check configuration"
 exit;
fi
./cvcsim >/dev/null
rm cvcsim
./rmlic.pl
diff verilog.log xtrace.plg

#test xprop2.v
$CVC +xprop2 xprop2.v >/dev/null
if test ! -f cvcsim
then
 echo "ERROR - compiling xprop2.v -" 
 echo "Run 'checkcvc' from bin to check configuration"
 exit;
fi
./cvcsim >/dev/null
rm cvcsim
./rmlic.pl
diff verilog.log xprop2.plg

#test xprop_eval.v
$CVC +xprop_eval xprop_eval.v >/dev/null
if test ! -f cvcsim
then
 echo "ERROR - compiling xprop_eval.v -" 
 echo "Run 'checkcvc' from bin to check configuration"
 exit;
fi
./cvcsim >/dev/null
rm cvcsim
./rmlic.pl
diff verilog.log xprop_eval.plg

#test xexcluded.v
$CVC +xprop +xprop_excluded xexcluded.v >/dev/null
if test ! -f cvcsim
then
 echo "ERROR - compiling xexcluded.v -" 
 echo "Run 'checkcvc' from bin to check configuration"
 exit;
fi
./cvcsim >/dev/null
rm cvcsim
./rmlic.pl
diff verilog.log xexcluded.plg

#test xconfig.v
$CVC -optconfigfile x.optconfig xconfig.v >/dev/null
if test ! -f cvcsim
then
 echo "ERROR - compiling x.optconfig xconfig.v -" 
 echo "Run 'checkcvc' from bin to check configuration"
 exit;
fi
./cvcsim >/dev/null
rm cvcsim
./rmlic.pl
diff verilog.log xconfig.plg

#test xedges.v
$CVC +xprop xedges.v >/dev/null
if test ! -f cvcsim
then
 echo "ERROR - compiling xedges" 
 echo "Run 'checkcvc' from bin to check configuration"
 exit;
fi
./cvcsim >/dev/null
rm cvcsim
./rmlic.pl
diff verilog.log xedges.plg

echo ">>>> Install test completed (this should be only message printed)."
echo " "

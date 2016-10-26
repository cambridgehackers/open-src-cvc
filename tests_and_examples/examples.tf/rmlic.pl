#!/usr/bin/perl
use strict;
my $file;
my $i;
my $line;
 
 $file = 'verilog.log';
 if (@ARGV == 1)
 {
     $file = $ARGV[0];
 }

 open(FILE, $file) or die "Can't open $file\n";
 open(TMP, '>tmp') or die "Can't open tmp file\n";
 for($i = 0; $i < 3; $i++)
 {
      $line = <FILE>;
 }
 while(<FILE>)
 {
      print TMP $_;
 }
 close TMP;
 close FILE;
 rename 'tmp', $file;

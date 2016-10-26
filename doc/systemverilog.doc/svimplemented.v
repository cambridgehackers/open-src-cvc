`define SIZE 10
module testbench;
 //2-state types
 int i, d1, d2;
 //new array size doesn't need [9:0]
 int a[`SIZE];
 int a2d[4][4];
 
 initial begin : loopblock
  //for loop with local increment defined 'int j'
  //and j++
  for (int j = 0; j < `SIZE; j++) a[j] = j;

  //do/while loop
  i = 0;
  do $display("a[%0d] = %0d", i, a[i]);
  while (++i < `SIZE);

  //for loop with break/continue and += 
  for (int j = 0; j < `SIZE; j+=2)
   begin
    if (j == 2) continue;
    a[j] += 2*a[j];
    if (j == 6) break; 
   end

  //foreach
  $display("\nforeach");
  foreach (a[k]) $display("a[%0d] = %0d", k, a[k]);


  //loop with multiple init/incs
  for (d1 = 0, d2 = 0; d1 < 4; d1++, d2++)
    a2d[d1][d2] = d1*d2;

  //2-dimension foreach
  $display("\nforeach 2d");
  foreach (a2d[i, j]) $display("a2d[%0d][%0d] = %0d", i, j, a2d[i][j]);

 // : block name
 end : loopblock
 
 bit b1 = 0, b2;
 //support for SV always_comb/always_latch/always_ff 
 always_comb 
   b2 = b1;

 initial $display("always_comb b2 = %b", b2);



 //'1/'0/'x/'z
 integer e;
 initial begin : unsized_expand_number
   //expand '1 to 'hffffffff
   e = '1;
   //'1 expand to 'hffffffff
   if (e == '1) $display("true '1");
   //'1 same as
   if (e == 'hffffffff) $display("true 'hffffffff");
 end : unsized_expand_number


 //SV strings
 string s;
 string astr[`SIZE];
 byte b;

 initial begin : stringblock
  //new SV strings are auto-sized
  s = "string";
  $display("s=%s", s);
  s = "looooooooooooooooooooooooooooooooooooooooooooooooooooooooongstring";
  $display("s=%s", s);
  foreach (astr[i]) 
   begin
    get_string("string test", s);
    astr[i] = s;
   end

  foreach (astr[i]) $display("astr[%0d] = %s", i, astr[i]);

  //string compares
  if (astr[0] != astr[1]) $display("string != ");

  //get and set string chars 
  s = "abcdefgh";
  b = s[3];
  $display("byte = %c", b);
  s[1] = b;
  $display("s = %s", s);


 end : stringblock
 
 //string task - no longer needs begin/end for multiple statements
 task get_string(input string s, output string os);
  string io_str;
  //new string tasks $psprintf and string concat {}
  io_str = $psprintf("at %0t : ", $time);
  io_str = {io_str, s}; 
  os = io_str;
 //endtask : taskname
 endtask : get_string

 int f, fo;
 initial begin : newfunctions
  $display("\nSV FUNCTIONS");
  fvoid(12);
  freturn(12);
  freturn(12);
  f = f1(12);
  $display("f=%0d", f);
  f = f1(10);
  $display("f=%0d", f);
  fout(f, fo);
  $display("fo=%0d", f);
 end : newfunctions
 
 //void functions
 function void fvoid(input int i);
  begin
    $display("void function=%0d", i);
  end
 endfunction

 //functions with c-style returns
 function void freturn(input int i);
  begin
   if (i == 12) return;
   $display("void function=%0d", i);
  end
 endfunction
 
 //functions with c-style returns with expression value
 function int f1(input int i);
  begin
   if (i == 12) return 1;
   $display("function=%0d", i);
   return(i*2);
  end
 endfunction

 //functions can now have outputs
 function void fout(input int i, output int o);
   o = i;
  endfunction

 reg [31:0] r;
 int count;

 initial begin : systemfunctions 
   //`__FILE__, `__LINE__ - used for debugging/messages
   $display("\nSYSTEM FUNCTIONS : \nfile %0s : line %0d", `__FILE__, `__LINE__);
   //$info/$fatal/$error/$warning - severity functions   
   r = 32'b10101010101010000000;
   //$onehot/$onehot0/$isunknown/$countones
   if ($onehot(r)) $info("onehot0");
   if ($onehot0(r)) $info("onehot0");
   if ($isunknown(r)) $info("unknown");
   count = $countones(r);
   $info("count=%0d", count);
   $fatal(1, "exiting ");

 end : systemfunctions
 

// endmodule : modulename
endmodule : testbench

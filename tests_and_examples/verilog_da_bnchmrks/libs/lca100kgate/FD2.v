module FD2 (d, cp, cd, q, qn); 

  input d, cp, cd;
  output q, qn;

  nand #1   nand_2 (n2, d_, cp_),
            nand_3 (n3, n1, n4),   
            nand_7 (q, n5, qn);
 
// SJM  nand #0   nand_1 (n1, d, cp_, cd),
  nand   nand_1 (n1, d, cp_, cd),
            nand_4 (n4, n2, n3, cd),
            nand_5 (n5, n3, cp),
            nand_6 (n6, n4, cp),
            nand_8 (qn, n6, cd, q);  

// SJM not  #0   inv_1 (cp_, cp),
  not   inv_1 (cp_, cp),
            inv_2 (d_, d);

endmodule  

module FA1A(CI, A, B, S, CO);
    output 
        S,
        CO;
    input 
        CI,
        A,
        B;
or
 #1     (CO, w1, w2, w3);
and
        (w1, A, B);
    and
        (w2, CI, dd_net_11);
    and
        (w3, CI, dd_net_13);
xor
 #1     (S, CI, dd_net_11, dd_net_13);
buf
        (dd_net_11, A);
buf
        (dd_net_13, B);


endmodule

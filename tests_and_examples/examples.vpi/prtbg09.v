

module test;
 wire [31:0] net_31;
 wire [31:0] net_44;
 wire [127:96] Data_In;

        Mux #(4,32,2) Mux554(.Select(net_31[3:2]), .Output(net_44[31:0]),
                .In0(Data_In[127:96]), .In1(Data_In[95:64]), .In2(Data_In[63:32]),
                .In3(Data_In[31:0]), .In4(), .In5(), .In6(), .In7(), .In8(), .In9(),
                .In10(), .In11(), .In12(), .In13(), .In14(), .In15() );
endmodule

module Mux (Select, Output, In0, In1, In2, In3, In4,
                            In5, In6, In7, In8, In9,
                            In10,In11,In12,In13,In14,
                            In15);


        parameter       ninputs=2,
                        width=4,
                        select_width=1;

        input   [width-1:0]     In0;
        input   [width-1:0]     In1;
        input   [width-1:0]     In2;
        input   [width-1:0]     In3;
        input   [width-1:0]     In4;
        input   [width-1:0]     In5;
        input   [width-1:0]     In6;
        input   [width-1:0]     In7;
        input   [width-1:0]     In8;
        input   [width-1:0]     In9;
        input   [width-1:0]     In10;
        input   [width-1:0]     In11;
        input   [width-1:0]     In12;
        input   [width-1:0]     In13;
        input   [width-1:0]     In14;
        input   [width-1:0]     In15;

        input   [select_width-1:0]      Select;

        output  [width-1:0]     Output;
        reg     [width-1:0]     Output;

        integer selection;
        integer temp;

        always begin
          deassign Output;
          selection = Select;
          if (select_width == ninputs) begin
            // Non-decoded select inputs
            temp = 0;
            if ((selection & 'hff00) != 0) begin
              temp = temp + 8;
              selection = selection >> 8;
            end
            if ((selection & 'hf0) != 0) begin
              temp = temp + 4;
              selection = selection >> 4;
            end
            if ((selection & 'hc) != 0) begin
              temp = temp + 2;
              selection = selection >> 2;
            end
            if ((selection & 'h2) != 0) begin
              temp = temp + 1;
            end
            selection = temp;
          end
          // Decoded select inputs
          case (selection & 15)
            4'b0000 : assign Output = In0;
            4'b0001 : assign Output = In1;
            4'b0010 : assign Output = In2;
            4'b0011 : assign Output = In3;
            4'b0100 : assign Output = In4;
            4'b0100 : assign Output = In5;
            4'b0110 : assign Output = In6;
            4'b0111 : assign Output = In7;
            4'b1000 : assign Output = In8;
            4'b1001 : assign Output = In9;
            4'b1010 : assign Output = In10;
            4'b1011 : assign Output = In11;
            4'b1100 : assign Output = In12;
            4'b1101 : assign Output = In13;
            4'b1110 : assign Output = In14;
            4'b1111 : assign Output = In15;
            default : assign Output = In0 & In1;
          endcase
          @(Select);
        end // always

endmodule               // mux

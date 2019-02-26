`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/26/2019 10:41:14 PM
// Design Name: 
// Module Name: q2barellb
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module q3barellb(a,s,out);
input [7:0]a;
input [2:0]s;
output[7:0]out;
reg [7:0]out;
always@(*)
begin
case(s[0])
1'b0 : out=a;  //shift =0
1'b1 : out={a[0],a[7:1]}; //shift=1  
endcase

case(s[1])
1'b1 : out={out[1:0],out[7:2]};  //shift=2
endcase

case(s[2])
1'b1 : out={out[3:0],out[7:4]};  //shift=4
endcase
end
endmodule
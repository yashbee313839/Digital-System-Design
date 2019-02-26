`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/26/2019 09:27:31 PM
// Design Name: 
// Module Name: q2alu
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


module q2alu(a,b,s,out);
input [7:0]a; //first 8 bit input
input [7:0]b; //second 8 bit input
input [2:0]s; //selecting inputs
output [8:0]out; //9 bit output
reg [8:0]out;
always @(*)
begin
case (s)
3'b000 : out=a+b;  //a+b
3'b001 : out=a-b;  //a-b
3'b010 : out=a+(2*b);//a+2b
3'b011 : out=a-(2*b);//a-2b
3'b100 : out=(a[3:0])*(b[3:0]); //last 4 bits of a* last 4 bits of b
3'b101: out = (a<b)?a:b;    //min(a,b)
3'b110 : out=(a<0)?(-1*a):a;  //abs(a)
default : out=b; //b
endcase
end
endmodule

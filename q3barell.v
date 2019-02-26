`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/26/2019 10:11:20 PM
// Design Name: 
// Module Name: q3barell
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


module q3barella(a,s,out);
input [7:0]a;
input [2:0]s;
output[7:0]out;
reg [7:0]out;
always@(*)
begin
case(s)
3'b000 : out=a;  //shift =0
3'b001 : out={a[0],a[7:1]};  //shift=1
3'b010 : out={a[1:0],a[7:2]};  //shift=2
3'b011 : out={a[2:0],a[7:3]};  //shift=3
3'b100 : out={a[3:0],a[7:4]};  //shift=4
3'b101 : out={a[4:0],a[7:5]};  //shift=5
3'b110 : out={a[5:0],a[7:6]};  //shift=5
3'b111 : out={a[6:0],a[7]};  //shift=6

endcase
end
endmodule

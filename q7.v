`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/27/2019 12:00:41 AM
// Design Name: 
// Module Name: q7
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


module q7(rs,oc,md,io,clk,a);
input rs;   //reset
input oc;   //output control
input clk;  //clock
input [2:0]md;  //select
output [7:0]io; //outputs
input [7:0]a;   //loading input
reg [7:0]io;
reg [7:0]q1;
reg [7:0]q2;
always@(posedge clk )
begin
if(rs==1'b1)   begin
               io=8'b00000000; //reset all to 0
               q1=8'b00000000;
               q2=8'b00000000;
               end

if(oc==1'b1 && md!=3'b111)
begin
case(md)
3'b001: io=io<<1; //left shift
3'b010: io=io>>1;   //right shift
3'b011: begin
        q2=q2+1;    //count in binary
        q1=q2>>1;   //convert to gray code
        io=q2^q1;
        end
3'b100: begin
         q2=q2-1;   //count in binary
         q1=q2>>1;  //convert to gray code
         io=q2^q1;
        end

3'b101: io=~io; //complement the bits
3'b110: io={io[3:0],io[7:4]};   //swap first and last 4 bits

endcase
end
if(oc ==1'b0 && md==3'b111)
io=a;
end
endmodule

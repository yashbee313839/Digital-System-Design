`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/26/2019 11:39:16 PM
// Design Name: 
// Module Name: q4mul
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


module q4mul(a,b,inp,done,sum);
input [7:0]a;
input [7:0]b;
input inp;
output [15:0] sum;
reg [15:0]sum;

output done;
reg done;
reg [7:0]ii;
always@(*)
if(inp==1'b1)
begin
ii=8'b00000000;
sum={ii,ii};
while(ii<b && ii<9'b100000000)
begin
ii = ii + 1;
sum=sum+a;
end
done=1;
end
endmodule

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
input [7:0]a;       //operand 1
input [7:0]b;       //operand 2
input inp;          //control
output [15:0] sum;  //product
reg [15:0]sum;

output done;        //done
reg done;
reg [7:0]ii;
always@(*)
if(inp==1'b1)
begin               
ii=8'b00000000;         //counter variable
sum={ii,ii};            //reset to zero
while(ii<b && ii<9'b100000000)  //while loop with maximum limit of iterations
begin
ii = ii + 1;    //increment count
sum=sum+a;      //add repeatedly
end
done=1;         //multiplication done
end
endmodule

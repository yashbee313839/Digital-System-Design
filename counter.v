`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/26/2019 10:59:54 PM
// Design Name: 
// Module Name: counter
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


module counter(q,s,en,rst,clk);
output [3:0]q;  //count
input clk;      //trigger
input en;       //active high enable
input rst;      //active low reset
input s;        //select line
reg [3:0]q;     
always @(posedge clk or negedge rst) //positive edge of clk
begin
if(rst==1'b0)
q=4'b0000;//reset to 0000

else if(en==1'b1)
q=q;                    //hold the output

else if(en==1'b0)
begin
if(s==1) q<=q+3;    //up count
if(s==1'b0) q<=q-5; //down count
end

end
endmodule

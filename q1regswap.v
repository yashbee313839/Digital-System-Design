`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/25/2019 07:16:59 PM
// Design Name: 
// Module Name: q1regswap
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


module q1regswap(clk,x,y);
    input clk;  //to trigger 
    output x;   //variable 1
    output y;   //variable 2
    reg y;      //register 2
    reg x;      //register 1
    
    always @(posedge clk)   
    begin       //procedural statements
      #2;
      x<=y;     //non-blocking assignment 
      y<=x;
    end
    endmodule
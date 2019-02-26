`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: Requiem Tech   
// Engineer: Yashwanth G
// 
// Create Date: 01/31/2019 10:42:02 AM
// Design Name: 
// Module Name: bcd_adder_2
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


module bcd_adder_2(output [8:0]z,input [7:0]x,y);
    wire w1,w2;
    bcd_adder b1(x[3:0],y[3:0],0,z[3:0],w1);
    bcd_adder b2(x[7:4],y[7:4],w1,z[7:4],z[8]);
endmodule

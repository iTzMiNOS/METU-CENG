`timescale 1ns / 1ps

module bh(input B, input H, input clk, output reg Q);

    initial begin
        Q = 1;
    end

    always @(posedge clk) begin
        case ({B, H})
            2'b00: Q <= ~Q;   // Complement
            2'b01: Q <= 1'b1; // Set to 1
            2'b10: Q <= 1'b0; // Set to 0
            2'b11: Q <= Q;    // No change
        endcase
    end
    
endmodule

module ic1337(// Inputs
              input A0,
              input A1,
              input A2,
              input clk,
              // Outputs
              output Q0,
              output Q1,
              output Z);

	wire p1,p2,p3,p4,p5;
	assign p1 = A0 ^ ~A1;
	assign p2 = p1 | A2;
	assign p3 = ~(A1 | ~A0);
	assign p4 = p3 & A2;
	assign p5 = A0 & ~A2;
	
	
	bh bh1(p2, p5, clk, Q0);
	bh bh2(p5, p4, clk, Q1);
	
	assign Z = ~(Q0 ^ Q1);
	

endmodule

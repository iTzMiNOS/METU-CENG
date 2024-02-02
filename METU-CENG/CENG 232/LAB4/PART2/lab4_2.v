`timescale 1ns / 1ps

module SelectionOfAvatar(
	input [1:0] mode,
	input [5:0] userID,
	input [1:0] candidate, 
	input CLK,
	output reg [1:0] ballotBoxId,
	output reg [5:0] numberOfRegisteredVoters,
	output reg [5:0] numberOfVotesWinner, 
	output reg [1:0] WinnerId,
	output reg AlreadyRegistered,
	output reg AlreadyVoted,
	output reg NotRegistered,
	output reg VotingHasNotStarted,
	output reg RegistrationHasEnded
);

reg [5:0] registeredUsers [0:63]; 
reg [1:0] votedUsers [0:63]; 
reg [5:0] candidateVotes [0:3]; 


reg [12:0] phaseCount; 
initial begin
    for (integer i = 0; i <= 63; i = i + 1) begin 
    registeredUsers[i] = 0; 
    votedUsers[i] = 0;
    end
    for (integer i = 0; i <= 3; i = i + 1) begin
    candidateVotes[i] = 2'b00;
    end
	phaseCount = 0;
	numberOfRegisteredVoters = 0;
	numberOfVotesWinner = 6'b0;
	WinnerId = 2'b00;
	AlreadyRegistered = 0;
	AlreadyVoted = 0;
	NotRegistered = 0;
	VotingHasNotStarted = 0;
	RegistrationHasEnded = 0;
end

always @(posedge CLK) begin
    AlreadyRegistered = 0;
    AlreadyVoted = 0;
    NotRegistered = 0;
    VotingHasNotStarted = 0;
    RegistrationHasEnded = 0;
    ballotBoxId = 2'b00;
    if (phaseCount < 100) begin
        case (mode)
            2'b00: begin 
                if (registeredUsers[userID[5:0]] != 0) begin
                    ballotBoxId = {userID[5:4]};
                    AlreadyRegistered = 1;
                end else begin
                   
                    ballotBoxId = {userID[5:4]};
                    
                    registeredUsers[userID[5:0]] = 1;
                    numberOfRegisteredVoters = numberOfRegisteredVoters + 1;
                    end
                end
            2'b01: begin
                VotingHasNotStarted = 1;
                ballotBoxId = {userID[5:4]}; 
            end
        endcase
        phaseCount = phaseCount + 1;
    end else if (phaseCount < 200) begin
        case (mode)
            2'b00: begin 
                RegistrationHasEnded = 1;
                ballotBoxId = {userID[5:4]}; 
                end
            2'b01: begin
                 if (registeredUsers[userID[5:0]]  != 0) begin
                    
                        if (votedUsers[userID[5:0]] != 0) begin
                            AlreadyVoted = 1;
                            ballotBoxId = {userID[5:4]}; 
                        end else begin
                            votedUsers[userID[5:0]] = 1;
                            if(candidate == 2'b00) begin
                            candidateVotes[0] = candidateVotes[0] + 1;
                            end else if(candidate == 2'b01) begin
                            candidateVotes[1] = candidateVotes[1] + 1;
                            end else if(candidate == 2'b10) begin
                            candidateVotes[2] = candidateVotes[2] + 1;
                            end else if(candidate == 2'b11) begin
                            candidateVotes[3] = candidateVotes[3] + 1;
                            end
                            
                            ballotBoxId = {userID[5:4]};
                        end
                    end else begin
                        NotRegistered = 1;
                        ballotBoxId = {userID[5:4]};
                    end
                end
        endcase
        phaseCount = phaseCount + 1;
    end else begin
            phaseCount = 205;
            for (integer i = 0; i < 4; i = i + 1) begin
                if (candidateVotes[i] > numberOfVotesWinner) begin
                    numberOfVotesWinner = candidateVotes[i];
                    WinnerId = i;
                end
            end
        end
    end
endmodule
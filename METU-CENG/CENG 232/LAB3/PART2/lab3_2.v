module lab3_2(
    input [5:0] money,
    input CLK,
    input vm, //0:VM0, 1:VM1
    input [2:0] productID, //000:sandwich, 001:chocolate, 11x: dont care  
    input sugar, //0: No sugar, 1: With Sugar
    output reg [5:0] moneyLeft,
    output reg [4:0] itemLeft,
    output reg productUnavailable,//1:show warning, 0:do not show warning
    output reg insufficientFund , //1:full, 0:not full  
    output reg notExactFund , //1:full, 0:not full
    output reg invalidProduct, //1: empty, 0:not empty
    output reg sugarUnsuitable, //1: empty, 0:not empty
    output reg productReady	//1:door is open, 0:closed
);

    // Internal State of the Module
    // (you can change this but you probably need this)
    reg [4:0] numOfSandwiches;
    reg [4:0] numOfChocolate;
    reg [4:0] numOfWaterVM1;
    reg [4:0] numOfWaterVM2;
    reg [4:0] numOfCoffee;
    reg [4:0] numOfTea;

    initial begin
        // Initialize the internal state
        numOfSandwiches = 10;
        numOfChocolate = 10;
        numOfWaterVM1 = 5;
        numOfWaterVM2 = 10;
        numOfCoffee = 10;
        numOfTea = 10;
    end

    always @(posedge CLK) begin
        // Update the output signals
        moneyLeft = money;
        itemLeft = {numOfSandwiches, numOfChocolate, numOfWaterVM1, numOfWaterVM2, numOfCoffee, numOfTea};

        // Check if the product is available
        if (vm == 0) begin
            invalidProduct = 0;
            productUnavailable = 0;
            notExactFund = 0;
            productReady = 0;
            sugarUnsuitable = 0;
            insufficientFund = 0;
            if (productID == 3 || productID == 4) begin
                invalidProduct = 1;
            end else begin
                case(productID)
                    0: begin // Sandwich
                        if (numOfSandwiches > 0) begin
                            if (moneyLeft == 20) begin
                                moneyLeft = 0;
                                numOfSandwiches = numOfSandwiches - 1;
                                itemLeft = numOfSandwiches;
                                productReady = 1;
                            end else begin
                                notExactFund = 1;
                            end
                        end else begin
                            productUnavailable = 1;
                        end
                    end
                    1: begin // Chocolate
                        if (numOfChocolate > 0) begin
                            if (moneyLeft == 10) begin
                                moneyLeft = 0;
                                numOfChocolate = numOfChocolate - 1;
                                itemLeft = numOfChocolate;
                                productReady = 1;
                            end else begin
                                notExactFund = 1;
                            end
                        end else begin
                            productUnavailable = 1;
                        end
                    end
                    2: begin // WaterVM1
                        if (numOfWaterVM1 > 0) begin
                            if (moneyLeft == 5) begin
                                moneyLeft = 0;
                                numOfWaterVM1 = numOfWaterVM1 - 1;
                                itemLeft = numOfWaterVM1;
                                productReady = 1;
                            end else begin
                                notExactFund = 1;
                            end
                        end else begin
                            productUnavailable = 1;
                        end
                    end
                    default: invalidProduct = 1;
                endcase
            end
        end else if (vm == 1) begin
            invalidProduct = 0;
            productUnavailable = 0;
            notExactFund = 0;
            productReady = 0;
            sugarUnsuitable = 0;
            insufficientFund = 0;

            if (productID == 0 || productID == 1) begin
                invalidProduct = 1;
            end else begin
                case(productID)
                    2: begin // WaterVM2
                        if (numOfWaterVM2 > 0) begin
                            if (moneyLeft >= 5) begin
                                if (sugar == 1) begin
                                    productReady = 0;
                                    sugarUnsuitable = 1;
                                end else begin
                                    moneyLeft = moneyLeft - 5;
                                    numOfWaterVM2 = numOfWaterVM2 - 1;
                                    itemLeft = numOfWaterVM2;
                                    productReady = 1;
                                end
                            end else begin
                                insufficientFund = 1;
                                if (sugar == 1) begin
                                    productReady = 0;
                                    sugarUnsuitable = 1;
                                end
                            end
                        end else begin
                            productUnavailable = 1;
                        end
                    end
                    3: begin // Coffee
                        if (numOfCoffee > 0) begin
                            if (moneyLeft >= 12) begin
                                moneyLeft = moneyLeft - 12;
                                numOfCoffee = numOfCoffee - 1;
                                itemLeft = numOfCoffee;
                                productReady = 1;
                            end else begin
                                insufficientFund = 1;
                            end
                        end else begin
                            productUnavailable = 1;
                        end
                    end
                    4: begin // Tea
                        if (numOfTea > 0) begin
                            if (moneyLeft >= 8) begin
                                moneyLeft = moneyLeft - 8;
                                numOfTea = numOfTea - 1;
                                itemLeft = numOfTea;
                                productReady = 1;
                            end else begin
                                insufficientFund = 1;
                            end
                        end else begin
                            productUnavailable = 1;
                        end
                    end
                    default: invalidProduct = 1;
                endcase
            end
        end 
    end
endmodule
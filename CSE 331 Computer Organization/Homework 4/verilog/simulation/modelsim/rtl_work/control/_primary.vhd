library verilog;
use verilog.vl_types.all;
entity control is
    port(
        OPCode          : in     vl_logic_vector(5 downto 0);
        functionField   : in     vl_logic_vector(5 downto 0);
        RegDst          : out    vl_logic;
        Branch          : out    vl_logic;
        BranchNotEqual  : out    vl_logic;
        Jump            : out    vl_logic;
        JumpRegister    : out    vl_logic;
        MemRead         : out    vl_logic;
        MemtoReg        : out    vl_logic;
        MemWrite        : out    vl_logic;
        ALUSrc          : out    vl_logic;
        RegWrite        : out    vl_logic;
        Mult            : out    vl_logic;
        ALUOP           : out    vl_logic_vector(2 downto 0)
    );
end control;

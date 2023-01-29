library verilog;
use verilog.vl_types.all;
entity datapath is
    port(
        RegDst          : in     vl_logic;
        Branch          : in     vl_logic;
        MemRead         : in     vl_logic;
        MemtoReg        : in     vl_logic;
        MemWrite        : in     vl_logic;
        ALUSrc          : in     vl_logic;
        RegWrite        : in     vl_logic;
        clock           : in     vl_logic;
        Mult            : in     vl_logic;
        ALUControl      : in     vl_logic_vector(2 downto 0);
        Instruction     : in     vl_logic_vector(31 downto 0);
        zero            : out    vl_logic;
        datapath_result : out    vl_logic_vector(15 downto 0)
    );
end datapath;

library verilog;
use verilog.vl_types.all;
entity regfile16x16 is
    port(
        RA              : in     vl_logic_vector(3 downto 0);
        RB              : in     vl_logic_vector(3 downto 0);
        RW              : in     vl_logic_vector(3 downto 0);
        busW            : in     vl_logic_vector(15 downto 0);
        Multiplication  : in     vl_logic_vector(31 downto 0);
        writeEnable     : in     vl_logic;
        Mult            : in     vl_logic;
        clock           : in     vl_logic;
        busA            : out    vl_logic_vector(15 downto 0);
        busB            : out    vl_logic_vector(15 downto 0)
    );
end regfile16x16;

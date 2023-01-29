library verilog;
use verilog.vl_types.all;
entity alu32 is
    port(
        a               : in     vl_logic_vector(31 downto 0);
        b               : in     vl_logic_vector(31 downto 0);
        ALUop           : in     vl_logic_vector(2 downto 0);
        clock           : in     vl_logic;
        result          : out    vl_logic_vector(31 downto 0)
    );
end alu32;

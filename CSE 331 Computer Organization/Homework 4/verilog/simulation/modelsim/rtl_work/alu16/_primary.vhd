library verilog;
use verilog.vl_types.all;
entity alu16 is
    port(
        A               : in     vl_logic_vector(15 downto 0);
        B               : in     vl_logic_vector(15 downto 0);
        ALUOP           : in     vl_logic_vector(2 downto 0);
        Result          : out    vl_logic_vector(15 downto 0);
        Multiplication  : out    vl_logic_vector(31 downto 0);
        zero            : out    vl_logic
    );
end alu16;

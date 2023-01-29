library verilog;
use verilog.vl_types.all;
entity instruction_mem is
    port(
        PC              : in     vl_logic_vector(9 downto 0);
        Instruction     : out    vl_logic_vector(31 downto 0)
    );
end instruction_mem;

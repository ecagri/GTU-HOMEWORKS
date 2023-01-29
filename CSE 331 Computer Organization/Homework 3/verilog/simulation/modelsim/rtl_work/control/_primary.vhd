library verilog;
use verilog.vl_types.all;
entity control is
    port(
        cypher          : in     vl_logic_vector(15 downto 0);
        data            : in     vl_logic_vector(3 downto 0);
        reset           : in     vl_logic;
        read            : in     vl_logic;
        rs_col          : out    vl_logic;
        rs_sum          : out    vl_logic;
        add_sum         : out    vl_logic
    );
end control;

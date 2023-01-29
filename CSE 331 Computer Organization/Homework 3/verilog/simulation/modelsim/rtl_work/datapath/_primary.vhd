library verilog;
use verilog.vl_types.all;
entity datapath is
    port(
        data            : in     vl_logic_vector(3 downto 0);
        add_sum         : in     vl_logic;
        rs_sum          : in     vl_logic;
        rs_col          : in     vl_logic;
        clock           : in     vl_logic;
        collected       : out    vl_logic;
        sum             : out    vl_logic_vector(7 downto 0)
    );
end datapath;

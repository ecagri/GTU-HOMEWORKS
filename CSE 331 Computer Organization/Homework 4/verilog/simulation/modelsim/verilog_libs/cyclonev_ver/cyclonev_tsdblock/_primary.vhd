library verilog;
use verilog.vl_types.all;
entity cyclonev_tsdblock is
    generic(
        clock_divider_enable: string  := "on";
        clock_divider_value: integer := 40;
        sim_tsdcalo     : integer := 0;
        lpm_type        : string  := "cyclonev_tsdblock"
    );
    port(
        clk             : in     vl_logic;
        ce              : in     vl_logic;
        clr             : in     vl_logic;
        tsdcalo         : out    vl_logic_vector(7 downto 0);
        tsdcaldone      : out    vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of clock_divider_enable : constant is 1;
    attribute mti_svvh_generic_type of clock_divider_value : constant is 1;
    attribute mti_svvh_generic_type of sim_tsdcalo : constant is 1;
    attribute mti_svvh_generic_type of lpm_type : constant is 1;
end cyclonev_tsdblock;

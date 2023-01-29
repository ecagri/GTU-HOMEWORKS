library verilog;
use verilog.vl_types.all;
entity arriav_hssi_refclk_divider is
    generic(
        lpm_type        : string  := "arriav_hssi_refclk_divider";
        divide_by       : integer := 1;
        enabled         : string  := "true";
        refclk_coupling_termination: string  := "normal_100_ohm_termination"
    );
    port(
        refclkin        : in     vl_logic_vector(0 downto 0);
        refclkout       : out    vl_logic_vector(0 downto 0);
        nonuserfrompmaux: in     vl_logic_vector(0 downto 0)
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of lpm_type : constant is 1;
    attribute mti_svvh_generic_type of divide_by : constant is 1;
    attribute mti_svvh_generic_type of enabled : constant is 1;
    attribute mti_svvh_generic_type of refclk_coupling_termination : constant is 1;
end arriav_hssi_refclk_divider;

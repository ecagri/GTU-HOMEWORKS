library verilog;
use verilog.vl_types.all;
entity cyclonev_pll_lvds_output is
    generic(
        pll_loaden_coarse_dly: string  := "0 ps";
        pll_loaden_enable_disable: string  := "false";
        pll_loaden_fine_dly: string  := "0 ps";
        pll_lvdsclk_coarse_dly: string  := "0 ps";
        pll_lvdsclk_enable_disable: string  := "false";
        pll_lvdsclk_fine_dly: string  := "0 ps"
    );
    port(
        ccout           : in     vl_logic_vector(1 downto 0);
        loaden          : out    vl_logic_vector(0 downto 0);
        lvdsclk         : out    vl_logic_vector(0 downto 0)
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of pll_loaden_coarse_dly : constant is 1;
    attribute mti_svvh_generic_type of pll_loaden_enable_disable : constant is 1;
    attribute mti_svvh_generic_type of pll_loaden_fine_dly : constant is 1;
    attribute mti_svvh_generic_type of pll_lvdsclk_coarse_dly : constant is 1;
    attribute mti_svvh_generic_type of pll_lvdsclk_enable_disable : constant is 1;
    attribute mti_svvh_generic_type of pll_lvdsclk_fine_dly : constant is 1;
end cyclonev_pll_lvds_output;

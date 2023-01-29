library verilog;
use verilog.vl_types.all;
entity cyclonev_pll_extclk_output is
    generic(
        pll_extclk_cnt_src: string  := "vss";
        pll_extclk_enable: string  := "true";
        pll_extclk_invert: string  := "false"
    );
    port(
        cclk            : in     vl_logic_vector(17 downto 0);
        clken           : in     vl_logic_vector(0 downto 0);
        mcnt0           : in     vl_logic_vector(0 downto 0);
        mcnt1           : in     vl_logic_vector(0 downto 0);
        extclk          : out    vl_logic_vector(0 downto 0)
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of pll_extclk_cnt_src : constant is 1;
    attribute mti_svvh_generic_type of pll_extclk_enable : constant is 1;
    attribute mti_svvh_generic_type of pll_extclk_invert : constant is 1;
end cyclonev_pll_extclk_output;

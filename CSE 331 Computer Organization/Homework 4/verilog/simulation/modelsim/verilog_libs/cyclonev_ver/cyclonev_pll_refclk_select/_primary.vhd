library verilog;
use verilog.vl_types.all;
entity cyclonev_pll_refclk_select is
    generic(
        pll_auto_clk_sw_en: string  := "false";
        pll_clk_loss_edge: string  := "both_edges";
        pll_clk_loss_sw_en: string  := "false";
        pll_clk_sw_dly  : integer := 0;
        pll_clkin_0_src : string  := "ref_clk0";
        pll_clkin_1_src : string  := "ref_clk1";
        pll_manu_clk_sw_en: string  := "false";
        pll_sw_refclk_src: string  := "clk_0"
    );
    port(
        adjpllin        : in     vl_logic_vector(0 downto 0);
        cclk            : in     vl_logic_vector(0 downto 0);
        clkin           : in     vl_logic_vector(3 downto 0);
        coreclkin       : in     vl_logic_vector(0 downto 0);
        extswitch       : in     vl_logic_vector(0 downto 0);
        iqtxrxclkin     : in     vl_logic_vector(0 downto 0);
        plliqclkin      : in     vl_logic_vector(0 downto 0);
        pllen           : in     vl_logic_vector(0 downto 0);
        refiqclk        : in     vl_logic_vector(1 downto 0);
        rxiqclkin       : in     vl_logic_vector(0 downto 0);
        clk0bad         : out    vl_logic_vector(0 downto 0);
        clk1bad         : out    vl_logic_vector(0 downto 0);
        clkout          : out    vl_logic_vector(0 downto 0);
        extswitchbuf    : out    vl_logic_vector(0 downto 0);
        pllclksel       : out    vl_logic_vector(0 downto 0)
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of pll_auto_clk_sw_en : constant is 1;
    attribute mti_svvh_generic_type of pll_clk_loss_edge : constant is 1;
    attribute mti_svvh_generic_type of pll_clk_loss_sw_en : constant is 1;
    attribute mti_svvh_generic_type of pll_clk_sw_dly : constant is 1;
    attribute mti_svvh_generic_type of pll_clkin_0_src : constant is 1;
    attribute mti_svvh_generic_type of pll_clkin_1_src : constant is 1;
    attribute mti_svvh_generic_type of pll_manu_clk_sw_en : constant is 1;
    attribute mti_svvh_generic_type of pll_sw_refclk_src : constant is 1;
end cyclonev_pll_refclk_select;

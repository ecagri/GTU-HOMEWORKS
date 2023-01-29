library verilog;
use verilog.vl_types.all;
entity cyclonev_pll_output_counter is
    generic(
        output_clock_frequency: string  := "";
        phase_shift     : string  := "";
        duty_cycle      : integer := 50;
        c_cnt_coarse_dly: string  := "0 ps";
        c_cnt_fine_dly  : string  := "0 ps";
        c_cnt_in_src    : string  := "test_clk0";
        c_cnt_ph_mux_prst: integer := 0;
        c_cnt_prst      : integer := 1;
        cnt_fpll_src    : string  := "fpll_0";
        dprio0_cnt_bypass_en: string  := "false";
        dprio0_cnt_hi_div: integer := 1;
        dprio0_cnt_lo_div: integer := 1;
        dprio0_cnt_odd_div_even_duty_en: string  := "false";
        fractional_pll_index: integer := 1;
        output_counter_index: integer := 0
    );
    port(
        cascadein       : in     vl_logic_vector(0 downto 0);
        nen0            : in     vl_logic_vector(0 downto 0);
        shift0          : in     vl_logic_vector(0 downto 0);
        shiftdone0i     : in     vl_logic_vector(0 downto 0);
        shiften         : in     vl_logic_vector(0 downto 0);
        tclk0           : in     vl_logic_vector(0 downto 0);
        up0             : in     vl_logic_vector(0 downto 0);
        vco0ph          : in     vl_logic_vector(7 downto 0);
        cascadeout      : out    vl_logic_vector(0 downto 0);
        divclk          : out    vl_logic_vector(0 downto 0);
        shiftdone0o     : out    vl_logic_vector(0 downto 0)
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of output_clock_frequency : constant is 1;
    attribute mti_svvh_generic_type of phase_shift : constant is 1;
    attribute mti_svvh_generic_type of duty_cycle : constant is 1;
    attribute mti_svvh_generic_type of c_cnt_coarse_dly : constant is 1;
    attribute mti_svvh_generic_type of c_cnt_fine_dly : constant is 1;
    attribute mti_svvh_generic_type of c_cnt_in_src : constant is 1;
    attribute mti_svvh_generic_type of c_cnt_ph_mux_prst : constant is 1;
    attribute mti_svvh_generic_type of c_cnt_prst : constant is 1;
    attribute mti_svvh_generic_type of cnt_fpll_src : constant is 1;
    attribute mti_svvh_generic_type of dprio0_cnt_bypass_en : constant is 1;
    attribute mti_svvh_generic_type of dprio0_cnt_hi_div : constant is 1;
    attribute mti_svvh_generic_type of dprio0_cnt_lo_div : constant is 1;
    attribute mti_svvh_generic_type of dprio0_cnt_odd_div_even_duty_en : constant is 1;
    attribute mti_svvh_generic_type of fractional_pll_index : constant is 1;
    attribute mti_svvh_generic_type of output_counter_index : constant is 1;
end cyclonev_pll_output_counter;

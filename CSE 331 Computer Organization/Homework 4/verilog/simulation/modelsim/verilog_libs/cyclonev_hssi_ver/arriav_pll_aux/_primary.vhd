library verilog;
use verilog.vl_types.all;
entity arriav_pll_aux is
    generic(
        lpm_type        : string  := "arriav_pll_aux";
        pl_aux_atb_atben0_precomp: vl_logic := Hi1;
        pl_aux_atb_atben1_precomp: vl_logic := Hi1;
        pl_aux_atb_comp_minus: vl_logic := Hi0;
        pl_aux_atb_comp_plus: vl_logic := Hi0;
        pl_aux_comp_pwr_dn: vl_logic := Hi1
    );
    port(
        atb0out         : in     vl_logic;
        atb1out         : in     vl_logic;
        atbcompout      : out    vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of lpm_type : constant is 1;
    attribute mti_svvh_generic_type of pl_aux_atb_atben0_precomp : constant is 1;
    attribute mti_svvh_generic_type of pl_aux_atb_atben1_precomp : constant is 1;
    attribute mti_svvh_generic_type of pl_aux_atb_comp_minus : constant is 1;
    attribute mti_svvh_generic_type of pl_aux_atb_comp_plus : constant is 1;
    attribute mti_svvh_generic_type of pl_aux_comp_pwr_dn : constant is 1;
end arriav_pll_aux;

library verilog;
use verilog.vl_types.all;
entity cyclonev_pll_dpa_output is
    generic(
        output_clock_frequency: string  := "";
        pll_vcoph_div   : integer := 1
    );
    port(
        pd              : in     vl_logic_vector(0 downto 0);
        phin            : in     vl_logic_vector(7 downto 0);
        phout           : out    vl_logic_vector(7 downto 0)
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of output_clock_frequency : constant is 1;
    attribute mti_svvh_generic_type of pll_vcoph_div : constant is 1;
end cyclonev_pll_dpa_output;

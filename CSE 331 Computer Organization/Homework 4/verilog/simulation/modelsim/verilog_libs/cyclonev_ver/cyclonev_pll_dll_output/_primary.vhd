library verilog;
use verilog.vl_types.all;
entity cyclonev_pll_dll_output is
    generic(
        pll_dll_src     : string  := "vss"
    );
    port(
        cclk            : in     vl_logic_vector(17 downto 0);
        clkin           : in     vl_logic_vector(3 downto 0);
        clkout          : out    vl_logic_vector(0 downto 0)
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of pll_dll_src : constant is 1;
end cyclonev_pll_dll_output;

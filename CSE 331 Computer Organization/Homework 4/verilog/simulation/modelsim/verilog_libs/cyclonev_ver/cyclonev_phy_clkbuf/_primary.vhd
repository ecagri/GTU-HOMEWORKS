library verilog;
use verilog.vl_types.all;
entity cyclonev_phy_clkbuf is
    port(
        inclk           : in     vl_logic_vector(3 downto 0);
        outclk          : out    vl_logic_vector(3 downto 0)
    );
end cyclonev_phy_clkbuf;

library verilog;
use verilog.vl_types.all;
entity cyclonev_oscillator is
    port(
        oscena          : in     vl_logic;
        clkout          : out    vl_logic;
        clkout1         : out    vl_logic
    );
end cyclonev_oscillator;

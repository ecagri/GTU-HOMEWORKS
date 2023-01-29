library verilog;
use verilog.vl_types.all;
entity cyclonev_routing_wire is
    port(
        datain          : in     vl_logic;
        dataout         : out    vl_logic
    );
end cyclonev_routing_wire;

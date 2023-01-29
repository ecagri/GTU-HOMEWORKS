library verilog;
use verilog.vl_types.all;
entity cyclonev_controller is
    generic(
        lpm_type        : string  := "cyclonev_controller"
    );
    port(
        nceout          : out    vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of lpm_type : constant is 1;
end cyclonev_controller;

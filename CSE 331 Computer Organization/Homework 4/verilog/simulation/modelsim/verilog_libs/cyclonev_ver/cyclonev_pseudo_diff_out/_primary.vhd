library verilog;
use verilog.vl_types.all;
entity cyclonev_pseudo_diff_out is
    generic(
        lpm_type        : string  := "cyclonev_pseudo_diff_out"
    );
    port(
        i               : in     vl_logic;
        o               : out    vl_logic;
        obar            : out    vl_logic;
        dtcin           : in     vl_logic;
        dtc             : out    vl_logic;
        dtcbar          : out    vl_logic;
        oein            : in     vl_logic;
        oeout           : out    vl_logic;
        oebout          : out    vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of lpm_type : constant is 1;
end cyclonev_pseudo_diff_out;

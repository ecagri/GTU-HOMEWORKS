library verilog;
use verilog.vl_types.all;
entity cyclonev_termination_logic is
    generic(
        lpm_type        : string  := "cyclonev_termination_logic";
        a_iob_oct_test  : string  := "a_iob_oct_test_off"
    );
    port(
        s2pload         : in     vl_logic;
        serdata         : in     vl_logic;
        scanenable      : in     vl_logic;
        scanclk         : in     vl_logic;
        enser           : in     vl_logic;
        seriesterminationcontrol: out    vl_logic_vector(15 downto 0);
        parallelterminationcontrol: out    vl_logic_vector(15 downto 0)
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of lpm_type : constant is 1;
    attribute mti_svvh_generic_type of a_iob_oct_test : constant is 1;
end cyclonev_termination_logic;
